/* See COPYRIGHT in top-level directory. */
/*
 * TLS functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif


GLT_func_prefix void glt_key_create(void(*destructor)(void *value), GLT_key *newkey) {
    CHECK(pthread_key_create(newkey, destructor),0);
}

GLT_func_prefix void glt_key_free(GLT_key *key) {
    CHECK(pthread_key_delete(*key),0);
}

GLT_func_prefix void glt_key_set(GLT_key key, void *value) {
    CHECK(pthread_setspecific(key, value),0);
}

GLT_func_prefix void glt_key_get(GLT_key key, void **value) {
    *value = pthread_getspecific(key);
}
