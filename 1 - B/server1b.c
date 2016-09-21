#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
# define MAX 100
# define PORT 7386
int main(int argc, char * * argv) {
  int sfd, cfd, slen, clen, i, ch, len;
  FILE * fp;
  char buff[MAX], filename[MAX];
  struct sockaddr_in servaddr, cliaddr;
  if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket not created\n");
    exit(0);
  }
  slen = sizeof(servaddr);
  memset( & servaddr, slen, 0);
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_family = AF_INET;
  if (bind(sfd, (struct sockaddr * ) & servaddr, slen) < 0) {
    printf("Bind failed\n");
    close(sfd);
    exit(1);
  }
  printf("SERVER SOCKET BINDED\n");
  listen(sfd, 5);
  printf("SERVER SOCKET listened\n");
  len = sizeof(cliaddr);
  if ((cfd = accept(sfd, (struct sockaddr * ) & cliaddr, & len)) < 0) {
    printf("Accept failed\n");
    close(sfd);
    exit(1);
  }
  printf("SERVER Socket accepted connection with a Client\n");
  bzero(filename, MAX);
  if (recv(cfd, filename, sizeof(filename), 0) < 0) {
    printf("Did not receive the filename");
    close(sfd);
    close(cfd);
    exit(1);
  }
  for (i = 0; i < MAX; i++)
    if (filename[i] == '\n' || filename[i] == '\r') {
      filename[i] = '\0';
      break;
    }
  printf("File requested: %s\n", filename);
  if ((fp = fopen(filename, "r")) == NULL) {
    printf("File could not be opened\n");
    close(sfd);
    close(cfd);
    exit(1);
  }
  if ((ch = fgetc(fp)) == EOF) {
    close(sfd);
    close(cfd);
    fclose(fp);
    exit(1);
    exit(1);
  }
  bzero(buff, sizeof(buff));
  buff[0] = ch;
  buff[1] = '\0';
  send(cfd, buff, 2, 0);
  printf("Sending:%s", buff);
  while (!feof(fp)) {
    bzero(buff, sizeof(buff));
    do {
      recv(cfd, buff, MAX, 0);
    } while (strcmp(buff, "ACK") != 0);
    printf("Received ACK...\n");
    if ((ch = fgetc(fp)) == EOF)
      break;
    bzero(buff, sizeof(buff));
    buff[0] = ch;
    buff[1] = '\0';
    send(cfd, buff, 2, 0);
    printf("Sending:%s", buff);
  }
  send(cfd, "OVER", 5, 0);
  printf("Sending: OVER");
  close(sfd);
  close(cfd);
  close(fp);
  return 0;
}
