#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
  int main() {
    char x[15], y[15];
    int n, sd, size, server_sock, i;
    struct sockaddr_in client_addr, server_addr;
    client_addr.sin_family = AF_INET;
    //convert host to network byte order
    client_addr.sin_port = htons(8000);
    client_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero( &(client_addr.sin_zero), 8);
    bzero( &(server_addr.sin_zero), 8);
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sd, (struct sockaddr * ) &server_addr, sizeof(server_addr));
    size = sizeof(client_addr);
    for (i = 1; i <= 4; i++) {
      recvfrom(sd, x, sizeof(x), 0, &client_addr, size);
      printf("\n Received Data : %s\n", x);
      sendto(sd, x, sizeof(x), 0, &client_addr, size);
    }
    close(sd);
  }
