
#include <glt.h>

void glt_cond_create(GLT_cond *cond){
#ifdef ARGOBOTS
    ABT_cond_create (cond);
#endif
#ifdef MASSIVETHREADS
    *cond =  myth_cond_create();
#endif
#ifdef QTHREADS
    cond = (GLT_cond *)malloc(sizeof(GLT_cond));
#endif
}

void glt_cond_free(GLT_cond *cond){
#ifdef ARGOBOTS
    ABT_cond_free (cond);
#endif
#ifdef MASSIVETHREADS
    myth_cond_destroy(*cond);
#endif
#ifdef QTHREADS
    free(cond);
#endif
}

void glt_cond_signal(GLT_cond cond){
#ifdef ARGOBOTS
    ABT_cond_signal (cond);
#endif
#ifdef MASSIVETHREADS
    myth_cond_signal(cond);
#endif
#ifdef QTHREADS
    qthread_empty(&cond);
#endif
}

void glt_cond_wait(GLT_cond cond, GLT_mutex mutex){
#ifdef ARGOBOTS
    ABT_cond_wait (cond, mutex);
#endif
#ifdef MASSIVETHREADS
    myth_cond_wait(cond,mutex);
#endif
#ifdef QTHREADS
    //Waits for memory to become empty and then fills it
    aligned_t fill=1;
    qthread_writeEF(&cond,&fill);
    qthread_lock(&mutex);
#endif
}

void glt_cond_broadcast(GLT_cond cond){
#ifdef ARGOBOTS
    ABT_cond_broadcast (cond);
#endif
#ifdef MASSIVETHREADS
    myth_cond_broadcast(cond);
#endif
#ifdef QTHREADS
    qthread_empty(&cond);
#endif
}