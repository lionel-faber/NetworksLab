#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
  int main() {
    char x[15], y[15];
    int n, sd, size, server_sock, i;
    long sec, msec, p[50];

    struct timeval tp;
    struct timezone tzp;
    struct sockaddr_in client_addr, server_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8000);
    client_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    //convert host to network byte order
    server_addr.sin_port = htons(8080);
    //any internet interface on the system
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero( &(client_addr.sin_zero), 8);
    bzero( &(server_addr.sin_zero), 8);
    //socket creation
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    //binding
    bind(sd, (struct sockaddr * ) &client_addr, sizeof(client_addr));
    size = sizeof(server_addr);
    printf("\nEnter the data to be sent :\n");
    scanf("%s", x);
    for (i = 0; i <= 4; i++) {
      gettimeofday( &tp, &tzp);
      sec = tp.tv_sec;
      msec = tp.tv_usec;
      sendto(sd, x, sizeof(x), 0, &server_addr, size);
      recvfrom(sd, y, sizeof(y), 0, &server_addr, size);
      gettimeofday( &tp, &tzp);
      sec = tp.tv_sec - sec;
      msec = tp.tv_usec - msec;
      msec = msec + (sec * 1000000);
      if ((strcmp(x, y)) == 0) {

        printf("\n64 bytes from 10.6.2.6  ICMP_Seq-no=%d time=%ld ms \n", i, msec);
      }
    }
    close(sd);
  }
