#include <stdio.h>
#include <stdlib.h>
#include <qthread/qthread.h>
#include <qthread/qloop.h>
//#include <fast_glt.h>
//#include <glt.h>

#define N 100
aligned_t func1(void * arg){

printf("Hola soy el thread %d\n",qthread_shep());

return 0;
}

int main(int argc, char *argv[]){

//glt_init(argc,argv);
    qthread_initialize(); //qthreads

//GLT_ult * ults;

//ults = glt_ult_malloc(N);
aligned_t * ults = (aligned_t *) malloc(sizeof (aligned_t) * N);
for (int i = 0; i < N; i++){
       qthread_fork_to((void *) func1, NULL, &ults[i], i%8);

	//glt_ult_creation_to(func1,NULL,&ults[i],i%glt_get_num_threads());
}

//qt_loop_step(0,12,2,(qt_loop_step_f)func1,NULL);
qt_loop(0,12,(qt_loop_f)func1,NULL);

qthread_yield();

for (int i = 0; i < N; i++){
	//glt_ult_join(&ults[i]);
    qthread_readFF(NULL, &ults[i]);

}
//glt_finalize();
    qthread_finalize();


}
