/* See COPYRIGHT in top-level directory. */
/*
 * Future and promise functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//future functions
GLT_func_prefix int glt_can_future_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_future_create(int nbytes, GLT_future *newfuture) {
    CHECK(ABT_eventual_create(nbytes, newfuture),ABT_SUCCESS);
}

GLT_func_prefix void glt_future_free(GLT_future *future) {
    CHECK(ABT_eventual_free(future),ABT_SUCCESS);
}

GLT_func_prefix void glt_future_wait(GLT_future future, void **value) {
    CHECK(ABT_eventual_wait(future, value),ABT_SUCCESS);
}

GLT_func_prefix void glt_future_set(GLT_future future, void *value, int nbytes) {
    CHECK(ABT_eventual_set(future, value, nbytes),ABT_SUCCESS);
}
#endif
