#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;
    key = ftok("Prog1.c", 65);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }
    shmid = shmget(key, 4096, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }


    int Ind_last = 1;
    int curr = Ind_last;
    for (int u = 0; u < 10; u++)
    {
        s = shm;
        int f = 0;
        while (curr < Ind_last + 5)
        {   printf("Received string:");
            for(int k=0;k<5;k++){
            printf("%c", *s);
            s++;}
            printf("\n");
            curr++;
            f = 1;
        }
        if (f == 0)
        {
            printf("Error: didnt enter loop , chk line 56\n");
            exit(0);
        }
        Ind_last = curr;
        *shm = '*';
        while (*shm == '*') 
        {
        }

    }

    return 0;
}
