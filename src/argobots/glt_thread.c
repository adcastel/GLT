/* See COPYRIGHT in top-level directory. */
/*
 * Thread management functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//threads functions
GLT_func_prefix int glt_can_malleability() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_thread_enable(){}
GLT_func_prefix void glt_thread_disable(){}
GLT_func_prefix void glt_thread_enable_id(int thread_id){}
GLT_func_prefix void glt_thread_disable_id(int thread_id){}
#endif