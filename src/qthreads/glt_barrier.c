/* See COPYRIGHT in top-level directory. */
/*
 * Barrier functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix void glt_barrier_create(int num_waiters, GLT_barrier *barrier) {
    *barrier = qt_barrier_create(num_waiters, UPLOCK);
}

GLT_func_prefix void glt_barrier_free(GLT_barrier *barrier) {
    CHECK(qt_barrier_destroy(*barrier),0);
}

GLT_func_prefix void glt_barrier_wait(GLT_barrier *barrier) {
    CHECK(qt_barrier_enter(*barrier),0);
}


