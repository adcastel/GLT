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
    CHECK(ABT_mutex_create(mutex),ABT_SUCCESS);
}

GLT_func_prefix void glt_mutex_lock(GLT_mutex mutex) {
    CHECK(ABT_mutex_lock(mutex),ABT_SUCCESS);
}

GLT_func_prefix void glt_mutex_unlock(GLT_mutex mutex) {
    CHECK(ABT_mutex_unlock(mutex),ABT_SUCCESS);
}

GLT_func_prefix void glt_mutex_free(GLT_mutex * mutex) {
    CHECK(ABT_mutex_free(mutex),ABT_SUCCESS);
}

GLT_func_prefix int glt_mutex_trylock(GLT_mutex mutex) {
    return ABT_mutex_trylock(mutex);
}

GLT_func_prefix void glt_mutex_spinlock(GLT_mutex mutex) {
    CHECK(ABT_mutex_spinlock(mutex),ABT_SUCCESS);
}
