#include < stdio.h >
#include < sys / types.h >
#include < netinet / in .h >
#include < string.h >
#include < sys / socket.h >
  main() {
    int x, a, bd, sd, newsd, port, clilen, i;
    char lost[20], sendmsg[20], recvmsg[20];
    struct sockaddr_in servaddr, cliaddr;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
      printf("Can't Create \n");
    else
      printf("Socket is Created\n");
    printf("Enter the port no\n");
    scanf("%d", & port);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    a = sizeof(servaddr);
    bd = bind(sd, (struct sockaddr * ) & servaddr, a);
    if (bd < 0)
      printf(" Can't Bind\n");
    else
      printf("\n Binded\n");
    listen(sd, 5);
    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr * ) & cliaddr, & clilen);
    if (newsd < 0)
      printf("Can't Accept\n");
    else
      printf("Accepted\n");
    send(newsd, lost, 20, 0);
    recv(newsd, recvmsg, 20, 0);
    printf("\n Frame is successfully received");
  }
