#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define R (((k - 4) % 5) + count) % 5
#define L (((k - 1) % 5) + count) % 5
int count=5;
int k=0;
pthread_mutex_t lock;
int phil[] = {1, 2, 3, 4, 5};

void Philosopher(int num) {
    printf( "Philosopher %d is thinking\n", 1);
    printf( "Philosopher %d is thinking\n", 2);
    printf( "Philosopher %d is thinking\n", 3);
    printf( "Philosopher %d is thinking\n", 4);
    printf( "Philosopher %d is thinking\n", 5);
    while(1){
        for(int i=0;i<num-2;i++){
            // printf("Philosopher %d is thinking\n", phil[i]);
            if(i==0)
            {k=i; //1st phil, ie. k=0
             printf("Philosopher %d has picked up fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is eating\n",phil[k]);
             k=i+2;//3rd phil, ie. k=2
             printf("Philosopher %d has picked up fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is eating\n",phil[k]);  
                sleep(1);
             k=i;//1st phil, ie. k=0
             printf("Philosopher %d has put down fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is thinking\n",phil[k]);
             k=i+2;//3rd phil, ie. k=2
             printf("Philosopher %d has put down fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is thinking\n",phil[k]);
                }
            else if(i==1){
               k=i; //2nd phil, ie. k=1
             printf("Philosopher %d has picked up fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is eating\n",phil[k]);
             k=i+2;//4th phil, ie. k=3
             printf("Philosopher %d has picked up fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is eating\n",phil[k]);  
                sleep(1);
             k=i;//2nd phil, ie. k=1
             printf("Philosopher %d has put down fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is thinking\n",phil[k]);
             k=i+2;//4th phil, ie. k=3
             printf("Philosopher %d has put down fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is thinking\n",phil[k]);
            }
            else if(i==2){
             k=i+2;//5th phil, ie. k=4
             printf("Philosopher %d has picked up fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is eating\n",phil[k]);
             sleep(1);
             printf("Philosopher %d has put down fork %d and %d\n",phil[k],phil[k],R+1);
             printf("Philosopher %d is thinking\n",phil[k]);
             
                
        }
    }
}
    }

int main() {
  pthread_t p1, p2, p3, p4, p5;
  pthread_t thr_id[5] = {p1, p2, p3, p4, p5};
  Philosopher(5);
  
  return 0;
  }
