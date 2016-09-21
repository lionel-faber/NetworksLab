#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main() {
    FILE * fp;
    int csd, n, ser, s, cli, cport, newsd;
    char name[100], rcvmsg[100], rcvg[100], fname[100];
    struct sockaddr_in servaddr;
    printf("Enter the port");
    scanf("%d", & cport);
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0) {
      printf("Error...");
      exit(0);
    } else
      printf("Socket is Created...\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);
    if (connect(csd, (struct sockaddr * ) & servaddr, sizeof(servaddr)) < 0) printf("Error in Connection...\n");
    else
      printf("Connected...\n");
    printf("Enter the existing file name: ");
    scanf("%s", name);
    printf("\nEnter the new filename: ");
    scanf("%s", fname);
    fp = fopen(fname, "w");
    send(csd, name, sizeof(name), 0);
    while (1) {
      s = recv(csd, rcvg, 100, 0);
      rcvg[s] = '\0';
      if (strcmp(rcvg, "error") == 0)
        printf("File is not Available...\n");
      if (strcmp(rcvg, "completed") == 0) {
        printf("file is transferred...\n");
        fclose(fp);
        close(csd);
        break;
      } else
        fputs(rcvg, stdout);
      fprintf(fp, "%s", rcvg);
    }
  }
