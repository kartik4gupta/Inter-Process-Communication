#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <math.h>
#include <sys/time.h>


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
int Ind_Last = 1;
int main(){
    srand(time(0));
    char buff[120];
    int check, File_desc_1, File_desc_2;
    char arr[51][6]={{}};
    
    for(int j=0; j<=50;j++){
        arr[j][0]=j;
    }

    for(int j=0; j<=50;j++){
        char random_str[5];
        int len=5;
        for (int i = 1; i <=len; i++) {
            if(i%2==0){
                arr[j][i] = 'A' + rand() % 26;
            }
            else{
                arr[j][i] = 'a' + rand() % 26;
            }
        }
    }
    mknod("pipeA1_kg",S_IFIFO | 0666,0);
    mknod("pipeA2_kg",S_IFIFO | 0666,0);
   
    //prints arr
    printf("Following are the strings to be sent: \n");
    for(int j=1; j<=50;j++){
        for(int i=1; i<=5;i++){
            printf("%c", arr[j][i]);
        }
        if(j!=50) printf(" , ");
    }
    printf("\n\n");

    int flag=0;

    clock_gettime(CLOCK_REALTIME, &st);
    while(!flag){
        if(File_desc_1 == -1) {
			perror("Couldn't access pipeA1_kg");
		}

		printf("Currently sending Strings Indexed from %d - %d\n", Ind_Last, Ind_Last + 4);
        int j=Ind_Last;
        int Flag_in=0;
        while(j<Ind_Last+5){
            File_desc_1 = open("pipe1_kg", O_WRONLY);
            check=write(File_desc_1, arr[j], sizeof(arr[j])+1);
            close(File_desc_1);
            sleep(2);	
            j++;
        }        

        File_desc_2 = open("pipe2_kg", O_RDONLY);
		check = read(File_desc_2, buff, 120*(sizeof(char)));
		close(File_desc_2);

        if(check == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}

        int Ind_final = atoi(buff);
 		printf("MAX ID ACKNOWLEDGED = %s\n\n", buff);

        Ind_Last = Ind_final+1;
		if(Ind_Last >= 50) {
            clock_gettime(CLOCK_REALTIME, &fn);
            sub_time(st, fn, &gap);
            printf("Time taken: %ld.%09ld\n", gap.tv_sec, gap.tv_nsec);
            exit(EXIT_SUCCESS);}

    }
    
    return 0;
}






