#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#define PORT 7676
int main(int argc, char * argv[]) {
  char buffer[20];
  int sockfd, connfd, a, len;
  struct sockaddr_in servaddr, cliaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    printf("ERROR CREATING SOCKET!");
  bzero( & servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(sockfd, (struct sockaddr * ) & servaddr, sizeof(servaddr));
  if ((a = listen(sockfd, 5)) < 0)
    printf("ERROR IN LISTEN FUNCTION!");
  while (1) {
    len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr * ) & cliaddr, & len);
    strcpy(buffer, "");
    read(connfd, buffer, 10);
    printf("Message Received and Echoed : %s", buffer);
    write(connfd, buffer, sizeof(buffer));
  }
  close(sockfd);
return 0;
}
