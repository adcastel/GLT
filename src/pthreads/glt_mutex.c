/* See COPYRIGHT in top-level directory. */
/*
 * Mutex functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix void glt_mutex_create(GLT_mutex * mutex) {
    CHECK(pthread_mutex_init(mutex,NULL),0);
}

GLT_func_prefix void glt_mutex_lock(GLT_mutex mutex) {
    CHECK(pthread_mutex_lock(&mutex),0);
}

GLT_func_prefix void glt_mutex_unlock(GLT_mutex mutex) {
    CHECK(pthread_mutex_unlock(&mutex),0);
}

GLT_func_prefix void glt_mutex_free(GLT_mutex * mutex) {
    CHECK(pthread_mutex_destroy(mutex),0);
}

GLT_func_prefix int glt_mutex_trylock(GLT_mutex mutex) {
    return pthread_mutex_trylock(&mutex);
}