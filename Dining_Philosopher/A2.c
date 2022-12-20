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

#define E 0
#define H 1
#define T 2
sem_t S[5];
int phil[] = {0, 1, 2, 3, 4};
sem_t lock;

int count_p = 5;
int st[5];
int check = 0;

#define R (((n - 4) % 5) + count_p) % 5
#define L (((n - 1) % 5) + count_p) % 5

void Test(int n) {
  if (st[R] != E && st[L] != E && st[n] == H) {
    int phil_no = n + 1;
    st[n] = E;
    sleep(3);
    int left = L + 1;
    printf("philosopher %d takes fork %d and %d\n", phil_no, phil_no, left);
    printf("philosopher %d is eating\n", phil_no);
    int x = sem_post(&S[n]);
    if (x != 0) {
      printf("Error: sem_post failed\n");
      check = -1;
      exit(1);
    }
  }
}
void tk_fork(int n) {
  int u = sem_wait(&lock);
  if (u != 0) {
    printf("%d: sem_wait error %d\n", n, u);
    check = -1;
  }
  st[n] = H;
  int phil_no = n + 1;
  printf("philosopher %d is hungry\n", phil_no);

  Test(n);
  int x = sem_post(&lock);
  int y = sem_wait(&S[n]);
  if (x != 0 || y != 0) {
    printf("Error: sem_post failed\n");
    check = -1;
    exit(1);
  }
  sleep(1);
}

void pt_fork(int n) {
  int t = sem_wait(&lock);
  if (t != 0) {
    printf("Error: sem_post failed\n");
    check = -1;
    exit(1);
  }
  int left = L + 1;
  st[n] = T;
  int phil_no = n + 1;
  printf("philosopher %d putting fork %d and %d down\n", phil_no, phil_no,
         left);
  check = 1;
  printf("philosopher %d is thinking\n", phil_no);
  check = 0;
  Test(R);
  check = 2;
  Test(L);
  int q = sem_post(&lock);
  if (q != 0) {
    printf("Error: sem_post failed\n");
    check = -1;
    exit(1);
  }
}

void *Philosopher(void *num) {
  int flag = 0;
  while (!flag) {
    check = 0;
    int *i = num;

    sleep(1);
    check = 1;
    tk_fork(*i);
    check = 2;
    pt_fork(*i);
    check = 3;
  }
}

int main() {
  pthread_t p1, p2, p3, p4, p5;
  int i = 0;
  pthread_t thr_id[5] = {p1, p2, p3, p4, p5};
  int x = sem_init(&lock, 0, 1);
  if (x != 0) {
    printf("Error: %s\n", strerror(errno));
    check = -1;
    exit(1);
  }

  int count = 0;
  int j = 0;
  while (j <= 4) {
    if (sem_init(&S[count], 0, 0) != 0) {
      printf("sem_init failed\n");
      exit(1);
    }
    j++;
  }

  while (i <= (count_p - 1)) {
    int r = pthread_create(&thr_id[i], NULL, Philosopher, &phil[i]);
    if (r != 0) {
      printf("Error: %d\n", r);
      check = -1;
      exit(1);
    }

    count++;
    printf("philosopher %d is thinking\n", i + 1);
    i++;
  }
  // printf("%d",check);
  i = 0;
  while (i < count_p) {
    int p = pthread_join(thr_id[i], NULL);
    if (p != 0) {
      printf("Error: %d\n", p);
      check = -1;
      exit(1);
    }
    i++;
  }
}
