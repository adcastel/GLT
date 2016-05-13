/* See COPYRIGHT in top-level directory. */
/*
 * Basic functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_extended_basic() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_ult_create_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar) {
    qthread_fork_syncvar((void *) thread_func, arg, syncvar);
}

GLT_func_prefix void glt_ult_create_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest, int npreconds, ...) {
    qthread_fork_syncvar_to((void *) thread_func, arg, syncvar, dest);
}

GLT_func_prefix void glt_ult_get_thread(GLT_thread *thread, int *worker) {
    *worker = qthread_worker(thread);
}

GLT_func_prefix void glt_ult_get_thread_unique(GLT_thread *thread, int *worker) {
    *worker = qthread_worker_unique(thread);
}

GLT_func_prefix void glt_ult_get_tasklocal(void * pointer, unsigned int size) {
    pointer = qthread_get_tasklocal(size);
}

GLT_func_prefix void glt_ult_size_tasklocal(unsigned int *size) {
    *size = qthread_size_tasklocal();
}

GLT_func_prefix void glt_ult_get_stack_left(size_t *size) {
    *size = qthread_stackleft();
}

#endif
