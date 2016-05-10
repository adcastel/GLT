/* See COPYRIGHT in glt_common.h file. */
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
    pthread_cond_init(cond,NULL);
}

GLT_func_prefix void glt_cond_free(GLT_cond *cond) {
    pthread_cond_destroy(cond);
}

GLT_func_prefix void glt_cond_signal(GLT_cond cond) {
    pthread_cond_signal(&cond);
}

GLT_func_prefix void glt_cond_wait(GLT_cond cond, GLT_mutex mutex) {
    pthread_cond_wait(&cond, &mutex);
}

GLT_func_prefix void glt_cond_broadcast(GLT_cond cond) {
    pthread_cond_broadcast(&cond);
}