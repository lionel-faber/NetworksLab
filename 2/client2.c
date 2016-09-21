#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 5009
int main(int argc, char * argv[]) {
    int sockfd;
    struct sockaddr_in serv;
    char buff[30];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset( & serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(argv[1]);
    if (connect(sockfd, (struct sockaddr * ) & serv, sizeof(serv)) < 0)
      printf("error in the connect");
    strcpy(buff, "");
    read(sockfd, buff, sizeof(buff));
    fputs(buff, stdout);
    close(sockfd);
  }
