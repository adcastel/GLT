#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    ABT_barrier_create(num_waiters, barrier);
}

GLT_return void glt_barrier_free(GLT_barrier *barrier)
{
    ABT_barrier_free(barrier);
}

GLT_return void glt_barrier_wait(GLT_barrier *barrier)
{
    ABT_barrier_wait(*barrier);
}


