#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/un.h>

int Ind_max = 0;
int main(){
    char buff[120];


    int check, File_desc_1, File_desc_2;

    mknod("pipeA1_kg",S_IFIFO | 0666,0);
    mknod("pipeA2_kg",S_IFIFO | 0666,0);

    int curr = Ind_max;

    int flag=0;
    while(!flag){
        while(curr < Ind_max + 5) {
            sleep(3);
			File_desc_1 = open("pipe1_kg", O_RDONLY);
            int in=0;
			check = read(File_desc_1, buff, sizeof(buff));
			close(File_desc_1);
            in++;
			if(check == -1) {	
				perror("Error in reading from pipe1_kg");
				exit(0);
			}
            curr=buff[0];
			printf("STRING RECEIVED: ");		
			
			for(int i = 1; i < 6; i++) {
				printf("%c", buff[i]);
			}
			
			sprintf(buff, "%d", curr);
			printf(": %s\n", buff);	
            
            printf("\n");
		}

		
		Ind_max = curr;
		File_desc_2 = open("pipe2_kg", O_WRONLY);
        int in1=0;
		check = write(File_desc_2, buff, 120*(sizeof(char)));
		close(File_desc_2);
        in1++;

		if(Ind_max >= 50) {exit(EXIT_SUCCESS);
        
        }
    }
    return 0;
}