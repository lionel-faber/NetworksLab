#include < stdio.h > #include < sys / types.h > #include < netinet / in .h >
  main() {
    int csd, cport, len;
    char sendmsg[20], recvmsg[20];
    struct sockaddr_in servaddr;
    printf("DNS Client Side\n");
    printf("Enter the Client port\n");
    scanf("%d", & cport);
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0)
      printf("Can't Create\n");
    else
      printf("Socket is Created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);
    if (connect(csd, (struct sockaddr * ) & servaddr, sizeof(servaddr)) < 0)
      printf("Can't Connect\n");
    else
      printf("Connected\n");
    printf("Enter the host address\n");
    scanf("%s", sendmsg);
    send(csd, sendmsg, 20, 0);
    recv(csd, recvmsg, 20, 20);
    printf("The Coresponding IP Address is\n");
    printf("%s", recvmsg);
  }