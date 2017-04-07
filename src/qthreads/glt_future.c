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


GLT_func_prefix int glt_can_future_functions() {
    return 0;
}


#ifndef CORE


GLT_func_prefix void glt_future_create(int nbytes, GLT_future *newfuture) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_free(GLT_future *future) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_wait(GLT_future future, void **value) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_set(GLT_future future, void *value, int nbytes) {
    GLT_ERROR_ARG;
}


#endif
