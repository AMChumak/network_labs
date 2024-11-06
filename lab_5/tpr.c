#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <ares.h>
#include <errno.h>


#define BUFFER_SIZE 1024
#define SOCKS_PORT 1080
#define MAX_CONNECTIONS 1024

typedef struct {
    int client_fd;
    int server_fd;
    ares_channel channel;
    int state;  // 0: initial, 1: DNS lookup, 2: connected
} connection_t;

connection_t connections[MAX_CONNECTIONS];
struct pollfd pfds[MAX_CONNECTIONS + 1];

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return -1;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
        return -1;
    }
    return 0;
}

void dns_callback(void *arg, int status, int timeouts, struct ares_addrinfo *addrinfo) {
    connection_t *conn = (connection_t *)arg;
    if (status != ARES_SUCCESS) {
        fprintf(stderr, "DNS lookup failed: %s\n", ares_strerror(status));
        close(conn->client_fd);
        close(conn->server_fd);
        conn->state = 0;
        return;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);  // Default to port 80 for HTTP

    struct ares_addrinfo_node *node;
    for (node = addrinfo->nodes; node; node = node->ai_next) {
        if (node->ai_family == AF_INET) {
            struct sockaddr_in *sin = (struct sockaddr_in *)node->ai_addr;
            server_addr.sin_addr = sin->sin_addr;
            break;
        }
    }

    ares_freeaddrinfo(addrinfo);

    if (connect(conn->server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 && errno != EINPROGRESS) {
        perror("connect");
        close(conn->client_fd);
        close(conn->server_fd);
        conn->state = 0;
        return;
    }

    // Send SOCKS5 reply
    char reply[8] = {0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    send(conn->client_fd, reply, sizeof(reply), 0);

    conn->state = 2;  // Connected
}

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t len = recv(client_fd, buffer, sizeof(buffer), 0);
    if (len <= 0) {
        close(client_fd);
        return;
    }

    // SOCKS5 handshake
    if (buffer[0] != 0x05) {
        close(client_fd);
        return;
    }

    // Send authentication method reply
    char reply[2] = {0x05, 0x00};
    send(client_fd, reply, sizeof(reply), 0);

    // Receive SOCKS5 request
    len = recv(client_fd, buffer, sizeof(buffer), 0);
    if (len <= 0) {
        close(client_fd);
        return;
    }

    // Check if it's a CONNECT request
    if (buffer[1] != 0x01) {
        close(client_fd);
        return;
    }

    // Extract hostname and port
    char hostname[256];
    int port;
    if (buffer[3] == 0x03) {  // Domain name
        int hostname_len = buffer[4];
        memcpy(hostname, buffer + 5, hostname_len);
        hostname[hostname_len] = '\0';
        port = ntohs(*(uint16_t *)(buffer + 5 + hostname_len));
    } else {
        close(client_fd);
        return;
    }

    // Create a new socket for the destination server
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        close(client_fd);
        return;
    }

    if (set_nonblocking(server_fd) < 0) {
        close(client_fd);
        close(server_fd);
        return;
    }

    // Initialize C-Ares
    ares_channel channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        fprintf(stderr, "Failed to initialize C-Ares\n");
        close(client_fd);
        close(server_fd);
        return;
    }

    // Perform DNS lookup
    connection_t *conn = NULL;
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (connections[i].state == 0) {
            conn = &connections[i];
            break;
        }
    }

    if (!conn) {
        fprintf(stderr, "No free connection slots\n");
        close(client_fd);
        close(server_fd);
        return;
    }

    conn->client_fd = client_fd;
    conn->server_fd = server_fd;
    conn->channel = channel;
    conn->state = 1;  // DNS lookup

    struct ares_addrinfo_hints hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = ARES_AI_CANONNAME,
    };

    ares_getaddrinfo(channel, hostname, NULL, &hints, dns_callback, conn);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    if (set_nonblocking(server_fd) < 0) {
        close(server_fd);
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SOCKS_PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("SOCKS5 proxy server listening on port %d\n", SOCKS_PORT);

    // Initialize pollfd array
    pfds[0].fd = server_fd;
    pfds[0].events = POLLIN;
    for (int i = 1; i <= MAX_CONNECTIONS; i++) {
        pfds[i].fd = -1;
        pfds[i].events = 0;
    }

    // Initialize connections array
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        connections[i].state = 0;
    }

    while (1) {
        int ready = poll(pfds, MAX_CONNECTIONS + 1, -1);
        if (ready < 0) {
            perror("poll");
            break;
        }

        if (pfds[0].revents & POLLIN) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
            if (client_fd < 0) {
                perror("accept");
                continue;
            }

            if (set_nonblocking(client_fd) < 0) {
                close(client_fd);
                continue;
            }

            handle_client(client_fd);
        }

        for (int i = 1; i <= MAX_CONNECTIONS; i++) {
            if (pfds[i].fd != -1 && pfds[i].revents & POLLIN) {
                connection_t *conn = &connections[i - 1];
                if (conn->state == 2) {
                    char buffer[BUFFER_SIZE];
                    ssize_t len = recv(conn->client_fd, buffer, sizeof(buffer), 0);
                    if (len <= 0) {
                        close(conn->client_fd);
                        close(conn->server_fd);
                        ares_destroy(conn->channel);
                        conn->state = 0;
                        pfds[i].fd = -1;
                        pfds[i].events = 0;
                        continue;
                    }
                    send(conn->server_fd, buffer, len, 0);
                }
            }

            if (pfds[i].fd != -1 && pfds[i].revents & POLLOUT) {
                connection_t *conn = &connections[i - 1];
                if (conn->state == 2) {
                    char buffer[BUFFER_SIZE];
                    ssize_t len = recv(conn->server_fd, buffer, sizeof(buffer), 0);
                    if (len <= 0) {
                        close(conn->client_fd);
                        close(conn->server_fd);
                        ares_destroy(conn->channel);
                        conn->state = 0;
                        pfds[i].fd = -1;
                        pfds[i].events = 0;
                        continue;
                    }
                    send(conn->client_fd, buffer, len, 0);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}