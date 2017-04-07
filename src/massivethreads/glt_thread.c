/* See COPYRIGHT in top-level directory. */
/*
 * Argobots library functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif


GLT_func_prefix int glt_can_malleability() {
    return 0;
}


#ifndef CORE


GLT_func_prefix void glt_thread_enable(){}
GLT_func_prefix void glt_thread_disable(){}
GLT_func_prefix void glt_thread_enable_id(int thread_id){}
GLT_func_prefix void glt_thread_disable_id(int thread_id){}


#endif
