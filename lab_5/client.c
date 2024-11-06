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
#include <errno.h>


int main(int argc, char *argv[]) {
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM , 0);

  char buf[100];
  int rc;

  if (sockfd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8085);


  int conRes;
  if ((conRes = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr))) < 0 && conRes != EINPROGRESS) {
    perror("connect error");
    close(sockfd);
    exit(-1);
  }

  while ((rc = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
    char msg[2] = {0x05,0x01};
    int len = 2;
    if (buf[0] =='l') {
        msg[0] = 0x00;
        msg[1] = 0x01;
        len = 1;
    }
    if (send(sockfd, msg, len, MSG_DONTWAIT) != 2) {
      if (rc > 0)
        fprintf(stderr, "partial write");
      else {
        perror("write error");
        exit(-1);
      }
    }
  }

  return 0;
}