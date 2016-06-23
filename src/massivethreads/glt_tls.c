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
    myth_key_create(newkey, destructor);
}

GLT_func_prefix void glt_key_free(GLT_key *key) {
    myth_key_delete(*key);
}

GLT_func_prefix void glt_key_set(GLT_key key, void *value) {
    myth_setspecific(key, value);
}

GLT_func_prefix void glt_key_get(GLT_key key, void **value) {
    *value = myth_getspecific(key);
}
