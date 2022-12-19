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


int Ind_max = 0;
char *socket_path = "sock_kg";
int main(int argc, char *argv[]) {

struct sockaddr_un addr;
char buf[100];
int fd,cl,rc;
  if (argc > 1) socket_path=argv[1];
  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(-1);  }
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  if (*socket_path == '\0') {
    *addr.sun_path = '\0';
   strncpy(addr.sun_path+1, socket_path+1, 
        sizeof(addr.sun_path)-2);
  } 
   else
     {
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    unlink(socket_path);  
}
if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)


 {   perror("bind error");
    exit(-1);  }

  if (listen(fd, 5) == -1) {perror("listen error");
    exit(-1); }

  if((cl = accept(fd, NULL, NULL)) == -1) {
    perror("accept error");
    exit(-1);  }
  int curr = Ind_max;

    int flag=0;
    while(!flag){

        while(curr < Ind_max + 5) {
            sleep(3);
			
            int in=0;
			int check = read(cl, buf, sizeof(buf));
            in++;
			if(check == -1) {	
				perror("Error in reading from sock_kg");
				exit(0);
			}
            curr=buf[0];
			printf("STRING RECEIVED: ");		
			
			for(int i = 1; i < 6; i++) {
				printf("%c", buf[i]);
			}
			
			sprintf(buf, "%d", curr);
			printf(": %s\n", buf);	
            
            printf("\n");
		}

		
		Ind_max = curr;
		
        int in1=0;
		int check = write(cl, buf, 120*(sizeof(char)));

        in1++;

		if(Ind_max >= 50) {exit(EXIT_SUCCESS);
        
        }
    }
  return 0;}
