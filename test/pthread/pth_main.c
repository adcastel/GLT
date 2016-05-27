/* 
 * simple.c 
 * Simple multi-threaded program for debugging 
 */

#include <stdlib.h>
#include <stdio.h>
//#include <pthread.h>
#include "glt_pthreads.h"
#define N 36
void * func1(void *arg)
{
  printf("Hello from func1\n");
}

void * func2(void *arg)
{
  printf("Hello from func2\n");
}

int main(int argc, char *argv)
{
  pthread_t th1[N], th2[N];
  for (int i=0;i<N;i++){
      pthread_create(&th1[i], NULL, func1, NULL);
      pthread_create(&th2[i], NULL, func2, NULL);
  }
sched_yield();
  for (int i=0;i<N;i++){
      pthread_join(th1[i], NULL);
      pthread_join(th2[i], NULL);
  }
  return 0;
}
