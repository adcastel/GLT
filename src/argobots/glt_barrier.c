#include <glt.h>

void glt_barrier_create(int num_waiters, GLT_barrier *barrier){
    ABT_barrier_create(num_waiters, barrier);
}

void glt_barrier_free(GLT_barrier *barrier){
    ABT_barrier_free(barrier);
}


void glt_barrier_wait(GLT_barrier *barrier){
    ABT_barrier_wait(*barrier);
}


