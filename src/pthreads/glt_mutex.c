/* See COPYRIGHT in glt_common.h file. */
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
    pthread_mutex_init(mutex,NULL);
}

GLT_func_prefix void glt_mutex_lock(GLT_mutex mutex) {
    pthread_mutex_lock(&mutex);
}

GLT_func_prefix void glt_mutex_unlock(GLT_mutex mutex) {
    pthread_mutex_unlock(&mutex);
}

GLT_func_prefix void glt_mutex_free(GLT_mutex * mutex) {
    pthread_mutex_destroy(mutex);
}

GLT_func_prefix void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex) {
    *locked = pthread_mutex_trylock(&mutex);
}