/* See COPYRIGHT in top-level directory. */
/*
 * Util functions file.
 */
#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_get_num_threads() {
    return main_team->num_shepherds;
}

GLT_func_prefix int glt_get_thread_num() {
    int a = qthread_shep();
    //printf("en glt_get_thread_num devolviendo %d\n",a);
    return a;
}

#endif

