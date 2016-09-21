#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define PORT 5009
int main(int age, char * argv[]) {
    int sockfd = 0, a, connfd = 0, len;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1000];
    time_t seconds;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
      printf("error creating socket");
    bzero( & servaddr, sizeof(servaddr));
    bzero(buffer, sizeof(buffer));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr * ) & servaddr, sizeof(servaddr));
    if ((listen(sockfd, 10)) < 0)
      printf("error in the listen func");
    while (1) {
      len = sizeof(cliaddr);
      if ((connfd = accept(sockfd, (struct sockaddr * ) & cliaddr, & len)) < 0)
        printf("error in the accept");
      seconds = time(NULL);
      sprintf(buffer, "%s", ctime( & seconds));
      write(connfd, buffer, sizeof(buffer));
      close(connfd);
    }
  }
