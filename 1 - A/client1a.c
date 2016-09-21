#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
void  main() {
    int i, sd, n, port, a, b;
    char sendmsg[100], recvmsg[100];
    struct sockaddr_in servaddr;
    printf("Enter the port\n");
    scanf("%d", & port);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
      printf("Can't Create\n");
    else
      printf("Socket is Created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if (connect(sd, (struct sockaddr * ) & servaddr, sizeof(servaddr)) < 0)
      printf("Can't Connect\n");
    else
      printf("Connected\n");
    printf("Enter the no of frames\n");
    scanf("%d", & n);
    for (i = 1; i <= n; i++) {
      printf("\nFrame %d\n", i);
      printf("Is the acknowledgement received?\t1.Yes 2.No");
      scanf("%d", & a);
      switch (a) {
      case 1:
        printf("The frame is transmitted correctly");
        break;
      case 2:
        printf("Enter the frame to be retransmitted\n");
        scanf("%d", & b);
        recv(sd, recvmsg, 20, 0);
        printf("\n Lost frame is retransmitted ");
        strcpy(sendmsg, recvmsg);
        send(sd, sendmsg, 20, 0);
        i++;
        //goto z;
        break;
      }
    }
  }
