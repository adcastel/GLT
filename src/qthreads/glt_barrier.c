#include <glt.h>

void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    barrier = qt_barrier_create(num_waiters, UPLOCK);
}

void glt_barrier_free(GLT_barrier *barrier)
{
    qt_barrier_destroy(barrier);
}


void glt_barrier_wait(GLT_barrier *barrier)
{
    qt_barrier_enter(barrier);
}


