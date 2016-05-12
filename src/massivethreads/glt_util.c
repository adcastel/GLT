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
    return main_team->num_workers;
}

GLT_func_prefix int glt_get_thread_num() {
    return myth_get_worker_num();
}


