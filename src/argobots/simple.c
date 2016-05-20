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
	/* MYTH_NATIVE test 
  myth_thread_t th1;
  printf("init\n");
  myth_init();
  printf("create\n");
  th1 = myth_create(func1, 0x0);
  printf("join\n");
  myth_join(th1, NULL);
  printf("fini\n");
	myth_fini();
  printf("exit\n");
   */
  pthread_t th1[N], th2[N];
  for (int i=0;i<N;i++){
      pthread_create(&th1[i], NULL, func1, NULL);
      pthread_create(&th2[i], NULL, func2, NULL);
  }
printf("CREADAS\n");
sched_yield();
  for (int i=0;i<N;i++){
      pthread_join(th1[i], NULL);
      pthread_join(th2[i], NULL);
      printf("joined %d\n",i);
  }
printf("JOINED\n");
  return 0;
}
