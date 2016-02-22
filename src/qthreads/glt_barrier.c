#include <glt.h>

void glt_barrier_create(int num_waiters, GLT_barrier *barrier){
#ifdef ARGOBOTS
    ABT_barrier_create(num_waiters, barrier);
#endif
#ifdef MASSIVETHREADS
    *barrier = myth_barrier_create(num_waiters);
#endif
#ifdef QTHREADS
    barrier = qt_barrier_create(num_waiters, UPLOCK);
#endif     
}

void glt_barrier_free(GLT_barrier *barrier){
#ifdef ARGOBOTS
    ABT_barrier_free(barrier);
#endif
#ifdef MASSIVETHREADS
    myth_barrier_destroy(*barrier);
#endif
#ifdef QTHREADS
    qt_barrier_destroy(barrier);
#endif     
}


void glt_barrier_wait(GLT_barrier *barrier){
#ifdef ARGOBOTS
    ABT_barrier_wait(*barrier);
#endif
#ifdef MASSIVETHREADS
    myth_barrier_wait(*barrier);
#endif
#ifdef QTHREADS
    qt_barrier_enter(barrier);
#endif     
}


