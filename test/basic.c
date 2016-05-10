#include <stdio.h>
#ifdef FASTGLT
#include <fast_glt.h>
#else
#include <glt.h>
#endif
#define N 72


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>

void func1(void * arg){

printf("Hola soy el thread %d/%d (CPU %d)\n",glt_get_thread_num(),glt_get_num_threads(),sched_getcpu());
}

int main(int argc, char *argv[]){

glt_init(argc,argv);

GLT_ult * ults;

ults = glt_ult_malloc(N);

for (int i = 0; i < N; i++){
	glt_ult_creation_to(func1,NULL,&ults[i],i%glt_get_num_threads());
}

glt_yield();

for (int i = 0; i < N; i++){
	glt_ult_join(&ults[i]);
}
glt_finalize();


}
