/* See COPYRIGHT in top-level directory. */
/*
 * Atomic functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_atomic_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_atomic_incr(GLT_aligned * operand, int incr) {
    CHECK(qthread_incr(operand, incr),0);
}

GLT_func_prefix void glt_atomic_fincr(float * operand, float incr) {
    CHECK(qthread_fincr(operand, incr),0);
}

GLT_func_prefix void glt_atomic_dincr(double * operand, double incr) {
    CHECK(qthread_dincr(operand, incr),0);
}

GLT_func_prefix void glt_atomic_cas(volatile GLT_aligned * addr, GLT_aligned oldval,
        GLT_aligned newval) {
    CHECK(qthread_cas(addr, oldval, newval),0);
}

GLT_func_prefix void glt_atomic_cas_ptr(void * volatile * addr, void * oldval,
        void * newval) {
    CHECK(qthread_cas_ptr(addr, oldval, newval),0);
}

#endif