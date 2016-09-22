#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
# define MAX 100
# define PORT 7386
int main(int argc, char *argv[]) {
  int ct, sockfd;
  int sfd, slen, clen, bufsize;
  char buff[MAX];
  FILE *fp;
  struct sockaddr_in serv, cliaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 1) {
    perror("Socket error");
    exit(0);
  }
  printf("CLIENT SOCKED CREATED");
  bzero( &serv, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  serv.sin_addr.s_addr = inet_addr(argv[1]);
  if (connect(sockfd, (struct sockaddr * ) &serv, sizeof(serv)) < 0) {
    printf("ERROR IN CONNECT");
    exit(1);
  }
  printf("CLIENT SOCKET CONNECTED");
  printf("\nEnter filename");
  scanf("%s", buff);
  send(sockfd, buff, sizeof(buff), 0);
  do {
    bzero(buff, sizeof(buff));
    recv(sockfd, buff, MAX, 0);
    if (strncmp(buff, "OVER", 3) == 0)
      break;
    printf("\nReceived:%s, sending ACK...\n", buff);
    send(sockfd, "ACK", 4, 0);
  }
  while (1);
  close(sockfd);
  printf("\nReceived and signal(OVER) terminating\n");
  return 0;
}
