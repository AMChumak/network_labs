#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <ares.h>


#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024


void dns_callback(void *arg, int status, int timeouts, struct ares_addrinfo *addrinfo) {
    if (status != ARES_SUCCESS) {
        fprintf(stderr, "DNS lookup failed: %s\n", ares_strerror(status));
        return;
    }

    struct ares_addrinfo_node *node;
    for (node = addrinfo->nodes; node; node = node->ai_next) {
        if (node->ai_family == AF_INET) {
            struct sockaddr_in *sin = (struct sockaddr_in *)node->ai_addr;
            printf("IPv4 address: %s\n", inet_ntoa(sin->sin_addr));
        } else if (node->ai_family == AF_INET6) {
            char ip6[INET6_ADDRSTRLEN];
            struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)node->ai_addr;
            inet_ntop(AF_INET6, &(sin6->sin6_addr), ip6, INET6_ADDRSTRLEN);
            printf("IPv6 address: %s\n", ip6);
        }
    }

    ares_freeaddrinfo(addrinfo);
}

void set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


char *msg(char code, char type, int ipv4Addr, char dnsLen, const char *name, short portBE) {
    char *msg = NULL;
    if (type == 1) {
        msg = malloc(sizeof(char) * 10);
        msg[0] = 5;
        msg[1] = code;
        msg[2] = 0;
        msg[3] = 1;
        *((int *)(msg + 4)) = ipv4Addr;
        *((short *)(msg + 8)) = portBE;
        return msg;
    } else {
        msg = malloc(sizeof(char) * (6 + 1 + dnsLen));
        msg[0] = 5;
        msg[1] = code;
        msg[2] = 0;
        msg[3] = 3;
        msg[4] = dnsLen;
        for(int i = 0; i < dnsLen; ++i) {
            msg[5 + i] = name[i];
        }
        *((short *)(msg + 4 + 1 + dnsLen)) = portBE;
        return msg;
    }
    return msg;
}



int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    struct pollfd fds[MAX_CLIENTS + 1];
    int states[MAX_CLIENTS + 1] = {0};
    int bufflens[MAX_CLIENTS + 1] = {0};
    int edges[MAX_CLIENTS + 1] = {0};
    char fdBuffers[MAX_CLIENTS + 1][BUFFER_SIZE];
    int nfds = 1;
    int proxFdsCnt = 0;
    char buffer[BUFFER_SIZE];

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set server socket to non-blocking
    set_nonblocking(server_socket);

    // Bind server socket
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8085);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Initialize pollfd array
    fds[0].fd = server_socket;
    fds[0].events = POLLIN;


    ares_channel channel;
    if (ares_init(&channel) != ARES_SUCCESS) {
        fprintf(stderr, "Failed to initialize C-Ares\n");
        return 1;
    }
    while (1) {

        // Use poll to handle asynchronous I/O
        int potNfds = ares_fds(channel, NULL, NULL);

        int ret = poll(fds, nfds, -1);
        if (ret < 0) {
            perror("poll");
            break;
        }

        // Check server socket for new connections
        if (fds[0].revents & POLLIN) {
            client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
            if (client_socket < 0) {
                perror("accept");
            } else {
                set_nonblocking(client_socket);
                fds[nfds].fd = client_socket;
                fds[nfds].events = POLLIN;
                nfds++;
                printf("New client connected: %d\n", client_socket);
            }
        }

        // Check client sockets for data
        for (int i = 1; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                int bytes_read = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
                if (bytes_read < 0) {
                    if (errno != EWOULDBLOCK && errno != EAGAIN) {
                        perror("recv");
                        close(fds[i].fd);
                        fds[i] = fds[nfds - 1];
                        for (int k = 0; k < BUFFER_SIZE; ++k) {
                            fdBuffers[i][k] = fdBuffers[nfds-1][k];
                        }
                        edges[i] = edges[nfds-1];
                        bufflens[i] = bufflens[nfds-1];                        
                        nfds--;
                    }
                } else if (bytes_read == 0) {
                    printf("Client disconnected: %d\n", fds[i].fd);
                    close(fds[i].fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                } else {
                    printf("Received from client %d: %.*s\n", fds[i].fd, bytes_read, buffer);
                    
                    for (int j = 0; j < bytes_read; ++j) {
                        fdBuffers[i][bufflens[i] + j] = buffer[j];
                    }
                    bufflens[i] += bytes_read;

                    printf("%d %d\n",bufflens[i], fdBuffers[i][1]);
                    if (states[i] == 0) {
                        printf("for %d state 0\n",i);
                        if (bufflens[i] > 2 && bufflens[i] == 2 + fdBuffers[i][1]) {
                            states[i] = 1;
                            bufflens[i] = 0;
                            char msg[2] = {0x05, 0x00};
                            send(fds[i].fd, msg, 2, 0);
                        }
                    } else if (states[i] == 1) {
                        printf("for %d state 1\n",i);
                        int secLen = -1;
                        if (bufflens[i] > 4) {
                            if (fdBuffers[i][3] == 0x01) {
                                secLen = 10;
                            } else if (fdBuffers[i][3] == 0x03) {
                                secLen = 6 + 1 + fdBuffers[i][4];
                            } else {
                                fprintf(stderr, "not implemented ipv6");        
                            }
                            if (bufflens[i] == secLen) {
                                printf("Ye2!\n");
                                if (fdBuffers[i][3] == 0x01) {
                                    //create socket to destination
                                    int proxy_socket;
                                    struct sockaddr_in dest_addr;
                                    proxy_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

                                    memset(&dest_addr, 0, sizeof(dest_addr));
                                    dest_addr.sin_family = AF_INET;
                                    dest_addr.sin_addr.s_addr = *(uint32_t *)(fdBuffers[i] + secLen - 6);
                                    dest_addr.sin_port = *(short *)(fdBuffers[i] + secLen - 2);

                                    if (connect(proxy_socket, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
                                        if (errno != EINPROGRESS) {
                                            perror("connect");
                                            char * ans = msg(4, 1, *(uint32_t *)(fdBuffers[i] + secLen - 6),0,NULL,*(short *)(fdBuffers[i] + secLen - 2));
                                            send(fds[i].fd, ans, strlen(ans), 0);
                                            free(ans);
                                            close(proxy_socket);
                                        }
                                    }
                                    fds[MAX_CLIENTS/2 + proxFdsCnt].fd = proxy_socket;
                                    fds[MAX_CLIENTS/2 + proxFdsCnt].events = POLLIN | POLLOUT;
                                    edges[i] = MAX_CLIENTS/2 + proxFdsCnt;
                                    edges[MAX_CLIENTS/2 + proxFdsCnt] = i;
                                    proxFdsCnt++;
                                    states[MAX_CLIENTS/2 + proxFdsCnt] = 10; 


                                } else if (fdBuffers[i][3] == 0x03) {

                                    struct ares_addrinfo_hints hints = {
                                        .ai_family = AF_INET,  // AF_INET or AF_INET6 for specific family
                                        .ai_socktype = SOCK_STREAM,
                                        .ai_flags = ARES_AI_CANONNAME,
                                    };
                                    char *hostN = calloc(fdBuffers[i][4] + 1,sizeof(char));
                                    for (int l = 0; l < fdBuffers[i][4];l++) {
                                        hostN[l] = fdBuffers[i][5+l];
                                    }
                                    ares_getaddrinfo(channel, hostN, NULL, &hints, dns_callback, msg);
                                }
                                
                                
                            }
                        }
                         

                    } else if (states[i] == 2) {

                    } else if (states[i] == 10) {

                    } else {
                        fprintf(stderr, "not implemented file descriptor state");
                    }
                }
            }
        }
    }

    // Close all sockets
    for (int i = 0; i < nfds; i++) {
        close(fds[i].fd);
    }

    return 0;
}