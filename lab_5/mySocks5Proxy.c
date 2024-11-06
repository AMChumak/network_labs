#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <ares.h>
#include <errno.h>


#define BUFFER_SIZE 1024
#define SOCKS_PORT 8085
#define MAX_CONNECTIONS 1024

typedef struct {
    int client_fd;
    int server_fd;
    ares_channel channel;
    char *buffer;
    int size;
    int state;  // 0: initial, -1: DNS lookup, 2: connected -5: error 1: ready to connection
} connection_t;


connection_t connections[MAX_CONNECTIONS];
struct pollfd pfds[MAX_CONNECTIONS + 1];
int countUsedFds = 1;

//SET SOCKET TO NONBLOCKING
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

//WORKING WITH POLLFD BUFFER

static void initialize_monitor_pollfd_set() {
  for (int i = 0; i < MAX_CONNECTIONS; i++) {
    pfds[i].fd = -1;
    pfds[i].events = POLLIN;
    pfds[i].revents = 0;
  }
}


static int add_to_pfds(int new_fd, short int flags) {
  int i = 0;
  for (i = 0; i < MAX_CONNECTIONS; i++) {
    if (pfds[i].fd == -1) {
      pfds[i].fd = new_fd;
      pfds[i].events = flags;
      countUsedFds++;
      break;
    }
  }
  return i;
}


static void remove_from_pfds(int del_fd) {
  for (int i = 0; i < MAX_CONNECTIONS; i++) {
    if (pfds[i].fd == del_fd) {
      pfds[i].fd = -1;
      countUsedFds--;
      break;
    }
  }
}


// CALLBACK FUNCTION FOR SOCKET

void sock_state_cb(void *data, ares_socket_t socket_fd, int readable, int writable)
{
  size_t idx;

  /* Find match */
  for (idx=0; idx<MAX_CONNECTIONS; idx++) {
    if (pfds[idx].fd == socket_fd) {
      break;
    }
  }

  /* Not found */
  if (idx > MAX_CONNECTIONS) {
    /* Do nothing */
    if (!readable && !writable) {
      return;
    }
    //find first free fd
    for(idx = 0; pfds[idx].fd != -1; idx++);
        
    // in implementation with dynamic fds buffer we should realloc it here!
  } else {
    /* Remove */
    if (!readable && !writable) {
      remove_from_pfds(idx);
      return;
    }
  }

  /* Update Poll Events (including on Add) */
  connections[idx].state = -1;
  pfds[idx].fd = socket_fd;
  pfds[idx].events = 0;
  if (readable) {
    pfds[idx].events |= POLLIN;
  }
  if (writable) {
    pfds[idx].events |= POLLOUT;
  }
}

// CALLBACK FOR DNS FINISHED CASE



//GREETING STAGE

void greeting(int idx, int bytes_read, char *buffer) {
    if (connections[idx].buffer == NULL) {
        connections[idx].buffer = (char *)calloc(1024, sizeof(char));
        connections[idx].size = 0;
    }

    for (int j = 0; j < bytes_read; ++j) {
        connections[idx].buffer[connections[idx].size + j] = buffer[j];
    }
    connections[idx].size += bytes_read;
    printf("buffer now is \'%hx\'\n",*((short int *)connections[idx].buffer));
    if (connections[idx].size > 2 && connections[idx].size >= 2 + connections[idx].buffer[1]) {
        connections[idx].state = 1;
        connections[idx].size = 0;
        char msg[2] = {0x05, 0xFF};
        for (int i = 0; i < connections[idx].buffer[1]; i++) {
            if (connections[idx].buffer[2+i] == 0) {
                msg[1] = 0x00;
                break;
            }
        }
        send(pfds[idx].fd, msg, 2, 0);
        printf("sended: \'%hx\'\n",*((short int *)msg));
        if (msg[1] == 0x00) {
            connections[idx].state = 1;
        }
    }
}

//CONNECTION STAGE

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

void collectingMeta(int idx, int bytes_read, char *buffer, struct ares_options *options) {
    for (int j = 0; j < bytes_read; ++j) {
        connections[idx].buffer[connections[idx].size + j] = buffer[j];
    }
    connections[idx].size += bytes_read;

    int secLen = -1;
    if (connections[idx].size > 4) {
        //SET EXPECTED LENGTH  It depends on mode (ipv4 or dns)
        if (connections[idx].buffer[3] == 0x01) {
            secLen = 10;
        } else if (connections[idx].buffer[3] == 0x03) {
            secLen = 6 + 1 + connections[idx].buffer[4];
        } else {
            fprintf(stderr, "not implemented ipv6");
            //todo send message        
        }
        if (connections[idx].size == secLen) {
            printf("Ye2!\n");
            if (connections[idx].buffer[3] == 0x01) {
                //create socket to destination
                int proxy_socket;
                struct sockaddr_in dest_addr;
                proxy_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

                memset(&dest_addr, 0, sizeof(dest_addr));
                dest_addr.sin_family = AF_INET;
                dest_addr.sin_addr.s_addr = *(uint32_t *)(connections[idx].buffer + secLen - 6);
                dest_addr.sin_port = ntohs(*(short *)(connections[idx].buffer + secLen - 2));

                if (connect(proxy_socket, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
                    if (errno != EINPROGRESS) {
                        perror("connect");
                        char * ans = msg(0, 1, *(uint32_t *)(connections[idx].buffer + secLen - 6),0,NULL,*(short *)(connections[idx].buffer + secLen - 2));
                        send(pfds[idx].fd, ans, strlen(ans), 0);
                        free(ans);
                        close(proxy_socket);
                    }
                }

                //Add new socket in poll and link server and client
                int newIdx = add_to_pfds(proxy_socket, POLLIN|POLLOUT);
                connections[idx].server_fd = newIdx;
                pfds[idx].events |= POLLOUT;
                connections[newIdx].client_fd = idx;
                connections[idx].state = 2;
                connections[newIdx].state = 2;

                char * ans = msg(4, 1, *(uint32_t *)(connections[idx].buffer + secLen - 6),0,NULL,*(short *)(connections[idx].buffer + secLen - 2));
                send(pfds[idx].fd, ans, strlen(ans), 0);
                free(ans);

            } else if (connections[idx].buffer[3] == 0x03) {
                printf("dns now doesn't work\n");
                //Prepare dns request
            }
            
            
        }
    }

}

//TRANSFER STAGE

void transfer(int idx, int bytes_read, char *buffer, int mode) { //mode = 1 - POLLIN //mode = 2 - POLLOUT
    if (mode == 1) {
        for (int j = 0; j < bytes_read; ++j) {
            connections[idx].buffer[connections[idx].size + j] = buffer[j];
        }
        connections[idx].size += bytes_read;
    } else {
        int fd = 0;
        if (connections[idx].server_fd) {
            fd = connections[idx].server_fd;
        } else if (connections[idx].client_fd) {
            fd = connections[idx].client_fd;
        }
        if (fd) {
            send(pfds[fd].fd, connections[fd].buffer,connections[fd].size, 0);
            connections[fd].size = 0;
        }
    }
}



int main() {
    struct ares_options options;
    int optmask = 0;
    struct ares_addrinfo_hints hints;
    /* Initialize library */
    ares_library_init(ARES_LIB_INIT_ALL);

    /* Enable sock state callbacks, we should not use ares_fds() or ares_getsock()
    * in modern implementations. */
    memset(&options, 0, sizeof(options));
    optmask |= ARES_OPT_SOCK_STATE_CB;
    options.sock_state_cb = sock_state_cb;
    options.sock_state_cb_data = NULL;

    //INITIALIZE SERVER
    char buffer[BUFFER_SIZE];
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
    connections[0].state = 0;
    for (int i = 1; i <= MAX_CONNECTIONS; i++) {
        pfds[i].fd = -1;
        pfds[i].events = 0;
        connections[i].state = 0;
    }

    //PROCESS CONNECTIONS

    while (1) {
        int ready = poll(pfds, MAX_CONNECTIONS + 1, -1);
        if (ready < 0) {
            perror("poll");
            break;
        }

        if (pfds[0].revents & POLLIN) {
            //NEW CONNECTION 
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
            printf("adds new connection\n");
            int idx = add_to_pfds(client_fd, POLLIN);
            connections[idx].client_fd = 0;
            connections[idx].server_fd = 0;
            connections[idx].state = 0;
        } else {
            int i = 1, comm_socket_fd = -1;

            for (; i < MAX_CONNECTIONS; i++) {
                //PROCESS INCOMING CONNECTIONS
                if (pfds[i].revents & POLLIN) {
                    int bytes_read = recv(pfds[i].fd, buffer, BUFFER_SIZE, 0);

                    if (bytes_read < 0) {
                        if (errno != EWOULDBLOCK && errno != EAGAIN) {
                            perror("recv");
                            close(pfds[i].fd);
                            if(connections[i].client_fd) {
                                close(pfds[connections[i].client_fd].fd);
                                remove_from_pfds(connections[i].client_fd);    
                            }
                            if (connections[i].server_fd) {
                                close(pfds[connections[i].server_fd].fd);
                                remove_from_pfds(connections[i].server_fd);
                            }
                            remove_from_pfds(i);
                        }
                    } else if (bytes_read == 0) {
                        printf("Client disconnected: %d\n", pfds[i].fd);
                        close(pfds[i].fd);
                        remove_from_pfds(i);
                    } else {
                        if (connections[i].state == 0) {
                            printf("go to greeting\n");
                            // Greeting
                            greeting(i, bytes_read, buffer);
                        } else if (connections[i].state == 1) {
                            printf("go to collecting meta\n");
                            // Collecting meta
                            collectingMeta(i, bytes_read, buffer, &options);
                        } else if (connections[i].state == 2) {
                            printf("go to transfer\n");
                            // Transfer
                            transfer(i, bytes_read, buffer, 1);
                        }
                    }
                }


                if (pfds[i].fd != -1 && pfds[i].revents & POLLOUT) {
                    printf("Hi\n");
                    if (connections[i].state == 2) {
                        transfer(i, 0, NULL, 2);
                    }
                }
            }
        }

    }

}