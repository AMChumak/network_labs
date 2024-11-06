#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#define SOCKET_NAME "socket"
#define BUFFER_SIZE 128

#define MAX_CLIENT_SUPPORTED 32

struct pollfd monitored_pollfd_set[MAX_CLIENT_SUPPORTED];

int monitored_fd_set[MAX_CLIENT_SUPPORTED];

static void intitiaze_monitor_fd_set() {

  int i = 0;
  for (; i < MAX_CLIENT_SUPPORTED; i++)
    monitored_fd_set[i] = -1;
}

static void initialize_monitor_pollfd_set() {
  for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
    monitored_pollfd_set[i].fd = -1;
    monitored_pollfd_set[i].events = POLLIN;
    monitored_pollfd_set[i].revents = 0;
  }
}

static void add_to_monitored_fd_set(int skt_fd) {

  int i = 0;
  for (; i < MAX_CLIENT_SUPPORTED; i++) {

    if (monitored_fd_set[i] != -1)
      continue;
    monitored_fd_set[i] = skt_fd;
    break;
  }
}

static void add_to_monitored_pollfd_set(int new_fd) {
  for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
    if (monitored_pollfd_set[i].fd == -1) {
      monitored_pollfd_set[i].fd = new_fd;
      break;
    }
  }
}

static void remove_from_monitored_fd_set(int skt_fd) {
  int i = 0;
  for (; i < MAX_CLIENT_SUPPORTED; i++) {

    if (monitored_fd_set[i] != skt_fd)
      continue;

    monitored_fd_set[i] = -1;
    break;
  }
}

static void remove_from_monitored_pollfd_set(int del_fd) {
  for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
    if (monitored_pollfd_set[i].fd == del_fd) {
      monitored_pollfd_set[i].fd = -1;
      break;
    }
  }
}

static void refresh_fd_set(fd_set *fd_set_ptr) {

  FD_ZERO(fd_set_ptr);
  int i = 0;
  for (; i < MAX_CLIENT_SUPPORTED; i++) {
    if (monitored_fd_set[i] != -1) {
      FD_SET(monitored_fd_set[i], fd_set_ptr);
    }
  }
}

static int get_max_fd() {

  int i = 0;
  int max = -1;

  for (; i < MAX_CLIENT_SUPPORTED; i++) {
    if (monitored_fd_set[i] > max)
      max = monitored_fd_set[i];
  }

  return max;
}

void set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char *argv[]) {
  struct sockaddr_in server_addr;

  int ret;
  int connection_socket;
  int data_socket;
  int result;
  int data;
  char buffer[BUFFER_SIZE];
  int comm_socket_fd, i;
  // intitiaze_monitor_fd_set();
  initialize_monitor_pollfd_set();
  // add_to_monitored_fd_set(0);
  add_to_monitored_pollfd_set(0);

  unlink(SOCKET_NAME);
  connection_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

  if (connection_socket == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // printf("Master socket created\n");

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(9876);

  ret = bind(connection_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

  if (ret == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // printf("bind() call succeed\n");

  ret = listen(connection_socket, 32);
  if (ret == -1) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // add_to_monitored_fd_set(connection_socket);
  add_to_monitored_pollfd_set(connection_socket);

  while (1) {
    // printf("Hello! %d %d %d\n", monitored_pollfd_set[0].fd,
    //        monitored_pollfd_set[1].fd, connection_socket);
    //  select(get_max_fd() + 1, &readfds, NULL, NULL, NULL);

    int ret = poll(monitored_pollfd_set, MAX_CLIENT_SUPPORTED, -1);

    if (monitored_pollfd_set[1].revents & POLLIN) { // check connection socket
      monitored_pollfd_set[1].revents = 0;
      // printf("New connection recieved recvd, accept the connection\n");

      data_socket = accept(connection_socket, NULL, NULL);
      set_nonblocking(data_socket);
      if (data_socket == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
      }

      // printf("Connection accepted from client\n");

      // add_to_monitored_fd_set(data_socket);
      add_to_monitored_pollfd_set(data_socket);
    } else if (monitored_pollfd_set[0].revents & POLLIN) { // check stdin
      monitored_pollfd_set[0].revents = 0;
      memset(buffer, 0, BUFFER_SIZE);
      ret = read(0, buffer, BUFFER_SIZE);
      printf("Input read from console : %s\n", buffer);
    } else {
      i = 0, comm_socket_fd = -1;
      for (; i < MAX_CLIENT_SUPPORTED; i++) {

        if (monitored_pollfd_set[i].revents & POLLIN) {
          monitored_pollfd_set[i].revents = 0;
          comm_socket_fd = monitored_pollfd_set[i].fd;

          memset(buffer, 0, BUFFER_SIZE);

          // printf("Waiting for data from the client\n");
          ret = read(comm_socket_fd, buffer, BUFFER_SIZE);

          if (ret == -1) {
            perror("read");
            exit(EXIT_FAILURE);
          } else if (ret == 0) {
            // remove_from_monitored_fd_set(monitored_fd_set[i]);
            remove_from_monitored_pollfd_set(monitored_pollfd_set[i].fd);
          }
          // printf("%d\n", ret);

          // print recieved message
          printf("%s\n", buffer);
        }
      }
    }
  }

  close(connection_socket);
  remove_from_monitored_fd_set(connection_socket);
  printf("connection closed..\n");

  unlink(SOCKET_NAME);
  exit(EXIT_SUCCESS);
}