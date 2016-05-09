/* See COPYRIGHT in glt_common.h file. */
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
    *barrier = myth_barrier_create(num_waiters);
}

GLT_func_prefix void glt_barrier_free(GLT_barrier *barrier) {
    myth_barrier_destroy(*barrier);
}

GLT_func_prefix void glt_barrier_wait(GLT_barrier *barrier) {
    myth_barrier_wait(*barrier);
}
