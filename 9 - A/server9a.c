#include < stdio.h > #include < sys / types.h > #include < netinet / in .h > #include < string.h >
  main() {
    int sd, sd2, nsd, clilen, sport, len, i;
    char sendmsg[20], recvmsg[20];
    char ipid[20][20] = {
      "172.15.64.66",
      "172.15.44.55",
      "172.15.33.44",
      "172.15.22.33"
    };
    char hostid[20][20] = {
      "www.yahoo.com",
      "www.google.com",
      "www.hotmail.com"
    };
    struct sockaddr_in servaddr, cliaddr;
    printf("DNS Server Side\n");
    printf("Enter the Port\n");
    scanf("%d", & sport);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
      printf("Can't Create \n");
    else
      printf("Socket is Created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);
    sd2 = bind(sd, (struct sockaddr * ) & servaddr, sizeof(servaddr));
    if (sd2 < 0)
      printf("Can't Bind\n");
    else
      printf("\n Binded\n");
    listen(sd, 5);
    clilen = sizeof(cliaddr);
    nsd = accept(sd, (struct sockaddr * ) & cliaddr, & clilen);
    if (nsd < 0)
      printf("Can't Accept\n");
    else
      printf("Accepted\n");
    recv(nsd, recvmsg, 20, 0);
    for (i = 0; i < 4; i++) {
      if (strcmp(recvmsg, hostid[i]) == 0) {
        send(nsd, ipid[i], 20, 20);
        break;
      }
    }
  }