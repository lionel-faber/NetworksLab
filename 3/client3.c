#include<stdio.h>
#include<sys/types.h> 
#include<sys/shm.h>
#include<string.h>
main() 
  {
    int shmid, a, i;
    char * ptr, * shmptr;
    shmid = shmget(3000, 10, IPC_CREAT | 0666);
    shmptr = shmat(shmid, NULL, 0);
    ptr = shmptr;
    for (i = 0; i < 3; i++) 
    {
      puts("enter the mac");
      scanf("%s", ptr);
      a = strlen(ptr);
      printf("\nstring length:%d\n", a);
      ptr[a] = ' ';
      puts("enter ip");
      ptr = ptr + a + 1;
      scanf("%s", ptr);
      ptr[a] = '\n';
      ptr = ptr + a + 1;
    }
    ptr[strlen(ptr)] = '\0';
    printf("\n ARP table at serverside is=\n%s", shmptr);
    shmdt(shmptr);
  }