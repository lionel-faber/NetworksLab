#include < stdio.h > #include < sys / types.h > #include < sys / socket.h > #include < netinet / in .h > #include < string.h > #include < stdlib.h >
  int main(int argc, char * * argv) {
    int len, sfd, connfd, i = 0, r, b;
    char c, buff[1024], d[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    FILE * fs;
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(atoi(argv[1]));
    b = bind(sfd, (struct sockaddr * ) & servaddr, sizeof(servaddr));
    clilen = sizeof(cliaddr);
    r = recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr * ) & cliaddr, & clilen);
    fs = fopen("f1.txt", "r");
    printf("\ndata is reading from 'source.txt'...");
    while ((c = getc(fs)) != EOF) {
      d[i++] = c;
    }
    d[i] = '\0';
    sendto(sfd, d, sizeof(d), 0, (struct sockaddr * ) & cliaddr, sizeof(cliaddr));
    printf("\ndata sent to client is %s", d);
    return 0;
  }