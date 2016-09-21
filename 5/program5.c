#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
  /*htttp port 80*/
# define HTTP_PORT 80
# define RANDOM_ORG "www.google.com"
int main(int argc, char * * argv) {
  struct sockaddr_in server;
  struct hostent * host_info;
  unsigned long addr;
  int sock;
  char buffer[8192];
  int count;
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("failed to create socket");
    exit(1);
  }
  memset(&server, 0, sizeof(server));
  host_info = gethostbyname(RANDOM_ORG);
  if (NULL == host_info) {
    fprintf(stderr, "unknown server:%s\n", RANDOM_ORG);
    exit(1);
  }
  memcpy((char * ) &server.sin_addr, host_info -> h_addr, host_info -> h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(HTTP_PORT);
  if (connect(sock, (struct sockaddr * ) &server, sizeof(server)) < 0) {
    perror("Can't connect to server");
    exit(1);
  }
  sprintf(buffer, "GET http://125.17.181.198/index.html%s\n\n", RANDOM_ORG);
  send(sock, buffer, strlen(buffer), 0);
  do {
    count = recv(sock, buffer, sizeof(buffer), 0);
    write(1, buffer, count);
  }
  while (count > 0);
  close(sock);
  return count;
}
