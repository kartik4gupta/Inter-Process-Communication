#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



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

int Ind_Last = 1;
struct timespec st, fn, gap;
char *socket_path = "sock_kg";

int main(int argc, char *argv[]) {

  srand(time(0));
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

  printf("Following are the strings to be sent: \n");
  for(int j=1; j<=50;j++){
        for(int i=1; i<=5;i++){
            printf("%c", arr[j][i]);
        }
        if(j!=50) printf(" , ");
  }
  printf("\n\n");

  struct sockaddr_un addr;
  char buf[100];
  int fd,rc;
  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
     {perror("socket error");
    exit(-1); }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  
strncpy(addr.sun_path, socket_path, 
sizeof(addr.sun_path));  


if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("connect error");
    exit(-1);
  }

  int flag=0;
  clock_gettime(CLOCK_REALTIME, &st);
  
   while(!flag){
        if(fd == -1) {
			perror("Couldn't access sock_kg");
		}

		printf("Currently sending Strings Indexed from %d - %d\n", Ind_Last, Ind_Last + 4);
        int j=Ind_Last;
        int Flag_in=0;
        while(j<Ind_Last+5){
            int check=write(fd, arr[j], sizeof(arr[j])+1);
            sleep(2);	
            j++;
        }        

        
		int check = read(fd, buf, 120*(sizeof(char)));
		

        if(check == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}

        int Ind_final = atoi(buf);
 		printf("MAX ID ACKNOWLEDGED = %s\n\n", buf);

        Ind_Last = Ind_final+1;
		if(Ind_Last >= 50) {
            clock_gettime(CLOCK_REALTIME, &fn);
            sub_time(st, fn, &gap);
            printf("Time taken: %ld.%09ld\n", gap.tv_sec, gap.tv_nsec);
            exit(EXIT_SUCCESS);}

    }


  return 0;
}
