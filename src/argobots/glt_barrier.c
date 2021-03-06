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
    CHECK(ABT_barrier_create(num_waiters, barrier),ABT_SUCCESS);
}

GLT_func_prefix void glt_barrier_free(GLT_barrier *barrier) {
    CHECK(ABT_barrier_free(barrier),ABT_SUCCESS);
}

GLT_func_prefix void glt_barrier_wait(GLT_barrier *barrier) {
    CHECK(ABT_barrier_wait(*barrier),ABT_SUCCESS);
}