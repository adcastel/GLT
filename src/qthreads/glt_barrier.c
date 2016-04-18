#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif
GLT_return void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    barrier = qt_barrier_create(num_waiters, UPLOCK);
}

GLT_return void glt_barrier_free(GLT_barrier *barrier)
{
    qt_barrier_destroy(barrier);
}

GLT_return void glt_barrier_wait(GLT_barrier *barrier)
{
    qt_barrier_enter(barrier);
}


