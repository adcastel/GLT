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

//tls functions
GLT_func_prefix int glt_can_tls_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_key_create(void(*destructor)(void *value), GLT_key *newkey) {
    CHECK(ABT_key_create(destructor, newkey),ABT_SUCCESS);
}

GLT_func_prefix void glt_key_free(GLT_key *key) {
    CHECK(ABT_key_free(key),ABT_SUCCESS);
}

GLT_func_prefix void glt_key_set(GLT_key key, void *value) {
    CHECK(ABT_key_set(key, value),ABT_SUCCESS);
}

GLT_func_prefix void glt_key_get(GLT_key key, void **value) {
    CHECK(ABT_key_get(key, value),ABT_SUCCESS);
}
#endif