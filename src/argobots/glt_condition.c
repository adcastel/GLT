/* See COPYRIGHT in top-level directory. */
/*
 * Condition functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix void glt_cond_create(GLT_cond *cond) {
    CHECK(ABT_cond_create(cond),ABT_SUCCESS);
}

GLT_func_prefix void glt_cond_free(GLT_cond *cond) {
    CHECK(ABT_cond_free(cond),ABT_SUCCESS);
}

GLT_func_prefix void glt_cond_signal(GLT_cond cond) {
    CHECK(ABT_cond_signal(cond),ABT_SUCCESS);
}

GLT_func_prefix void glt_cond_wait(GLT_cond cond, GLT_mutex mutex) {
    CHECK(ABT_cond_wait(cond, mutex),ABT_SUCCESS);
}

GLT_func_prefix void glt_cond_broadcast(GLT_cond cond) {
    CHECK(ABT_cond_broadcast(cond),ABT_SUCCESS);
}