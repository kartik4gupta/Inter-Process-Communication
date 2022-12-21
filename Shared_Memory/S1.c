#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void sub_time(struct timespec st, struct timespec fn, struct timespec *gap)
{

    time_t secs;
    long nsecs;
    secs = fn.tv_sec - st.tv_sec;
    nsecs = fn.tv_nsec - st.tv_nsec;
    if (nsecs < 0){
        nsecs = nsecs + 1000000000;
        secs=secs-1;
    }
    gap->tv_sec=secs;
    gap->tv_nsec=nsecs;
}

struct timespec st, fn, gap;




int main()
{
    srand(time(0));
    char arr[51][6] = {{}};

    for (int j = 0; j <= 50; j++)
    {
        arr[j][0] = j;
    }

    for (int j = 0; j <= 50; j++)
    {
        char random_str[5];
        int len = 5;
        for (int i = 1; i <= len; i++)
        {
            if (i % 2 == 0)
            {
                arr[j][i] = 'A' + rand() % 26;
            }
            else
            {
                arr[j][i] = 'a' + rand() % 26;
            }
        }
    }

    printf("Following are the strings to be sent: \n");
    for (int j = 1; j <= 50; j++)
    {
        for (int i = 1; i <= 5; i++)
        {
            printf("%c", arr[j][i]);
        }
        if (j != 50)
            printf(" , ");
    }
    printf("\n\n");

    int shmid, shmid2;

    key_t key, key2;
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
    clock_gettime(CLOCK_REALTIME, &st);
    int Ind_last = 1;
    int curr = Ind_last;
    for (int u = 1; u <= 10; u++)
    {
        s = shm;
        int f = 0;
        printf("Currently sending strings indexed from %d - %d\n", Ind_last, Ind_last + 4);
        while (curr < Ind_last + 5)
        {
            for (int i = 1; i <= 5; i++)
            {
                *s = arr[curr][i];
                s++;
            }
            curr++;
            f = 1;
        }
        // curr value 6 after first iter.
        if (f == 0)
        {
            printf("Error, on line 84...did not enter while loop\n");
            exit(0);
        }
        Ind_last = curr;
        char st[10];
        sprintf(st, "%d", curr - 1);

  
        while (*shm != '*') 
        {
        }
        printf("Highest index received : %d\n", Ind_last - 1);
    }
    clock_gettime(CLOCK_REALTIME, &fn);
    sub_time(st, fn, &gap);
    printf("Time taken: %ld.%09ld\n", gap.tv_sec, gap.tv_nsec);

    return 0;
}
