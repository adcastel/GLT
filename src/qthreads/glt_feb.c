/* See COPYRIGHT in top-level directory. */
/*
 * FEB functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_feb_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_feb_empty(const GLT_memory_state *dest) {
    CHECK(qthread_empty(dest),0);
}

GLT_func_prefix void glt_feb_fill(const GLT_memory_state *dest) {
    CHECK(qthread_fill(dest),0);
}

GLT_func_prefix void glt_feb_status(const GLT_memory_state *addr, int *status) {
    *status = qthread_feb_status(addr);
}

GLT_func_prefix void glt_feb_readFE(GLT_memory_state *dst, const GLT_memory_state *src) {
    CHECK(qthread_readFE(dst, src),0);
}

GLT_func_prefix void glt_feb_readFF(GLT_memory_state *dst, const GLT_memory_state *src) {
    CHECK(qthread_readFF(dst, src),0);
}

GLT_func_prefix void glt_feb_writeEF(GLT_memory_state * restrict dst, const GLT_memory_state * restrict src) {
    CHECK(qthread_writeEF(dst, src),0);
}

GLT_func_prefix void glt_feb_writeEF_const(GLT_memory_state * dst, GLT_memory_state src) {
    CHECK(qthread_writeEF_const(dst, src),0);
}

GLT_func_prefix void glt_feb_writeF(GLT_memory_state * restrict dst, const GLT_memory_state * restrict src) {
    CHECK(qthread_writeF(dst, src),0);
}

GLT_func_prefix void glt_feb_writeF_const(GLT_memory_state * dst, GLT_memory_state src) {
    CHECK(qthread_writeF_const(dst, src),0);
}

GLT_func_prefix void glt_syncvar_empty(GLT_syncvar *dest) {
    CHECK(qthread_syncvar_empty(dest),0);
}

GLT_func_prefix void glt_syncvar_fill(GLT_syncvar *dest) {
    CHECK(qthread_syncvar_fill(dest),0);
}

GLT_func_prefix void glt_syncvar_status(GLT_syncvar *addr, int *status) {
    *status = qthread_syncvar_status(addr);
}

GLT_func_prefix void glt_syncvar_readFE(uint64_t * restrict dst, GLT_syncvar * restrict src) {
    CHECK(qthread_syncvar_readFE(dst, src),0);
}

GLT_func_prefix void glt_syncvar_readFF(uint64_t * restrict dst, GLT_syncvar * restrict src) {
    CHECK(qthread_syncvar_readFF(dst, src),0);
}

GLT_func_prefix void glt_syncvar_writeEF(GLT_syncvar * restrict dst, const uint64_t * restrict src) {
    CHECK(qthread_syncvar_writeEF(dst, src),0);
}

GLT_func_prefix void glt_syncvar_writeEF_const(GLT_syncvar * dst, uint64_t src) {
    CHECK(qthread_syncvar_writeEF_const(dst, src),0);
}

GLT_func_prefix void glt_syncvar_writeF(GLT_syncvar * restrict dst, const uint64_t * restrict src) {
    CHECK(qthread_syncvar_writeF(dst, src),0);
}

GLT_func_prefix void glt_syncvar_writeF_const(GLT_syncvar * dst, uint64_t src) {
    CHECK(qthread_syncvar_writeF_const(dst, src),0);
}

#endif