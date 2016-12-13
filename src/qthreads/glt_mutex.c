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
 //       int a = qthread_shep();
  //  printf("en glt_mutex_create con tid %d\n",a);
    qthread_unlock(*mutex);
}

GLT_func_prefix void glt_mutex_lock(GLT_mutex mutex) {
  //          int a = qthread_shep();
  //  printf("en glt_mutex_lock con tid %d\n",a);
    CHECK(qthread_lock(mutex),0);
}

GLT_func_prefix void glt_mutex_unlock(GLT_mutex mutex) {
  //          int a = qthread_shep();
  //  printf("en glt_mutex_unlock con tid %d\n",a);
    CHECK(qthread_unlock(mutex),0);
}

GLT_func_prefix void glt_mutex_free(GLT_mutex * mutex) {
}

GLT_func_prefix int glt_mutex_trylock(GLT_mutex mutex) {
    aligned_t res = qthread_cas(mutex, 0, 1);
    return (res == 0) ? 1 : 0;
}