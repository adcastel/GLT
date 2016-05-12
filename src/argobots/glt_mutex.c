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
    ABT_mutex_create(mutex);
}

GLT_func_prefix void glt_mutex_lock(GLT_mutex mutex) {
    ABT_mutex_lock(mutex);
}

GLT_func_prefix void glt_mutex_unlock(GLT_mutex mutex) {
    ABT_mutex_unlock(mutex);
}

GLT_func_prefix void glt_mutex_free(GLT_mutex * mutex) {
    ABT_mutex_free(mutex);
}

GLT_func_prefix void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex) {
    *locked = ABT_mutex_trylock(mutex);
}

//extended mutex functions
GLT_func_prefix int glt_can_extended_mutex() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_mutex_lock_low(GLT_mutex mutex) {
    GLT_LIB_ERROR;
}

GLT_func_prefix void glt_mutex_spinlock(GLT_mutex mutex) {
    ABT_mutex_spinlock(mutex);
}

GLT_func_prefix void glt_mutex_unlock_se(GLT_mutex mutex) {
    GLT_LIB_ERROR;
}

GLT_func_prefix void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result) {
    ABT_mutex_equal(mutex1, mutex2, result);
}
#endif
