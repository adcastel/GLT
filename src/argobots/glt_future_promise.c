/* See COPYRIGHT in top-level directory. */
/*
 * Future and promise functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//future functions
GLT_func_prefix int glt_can_future_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_future_create(int nbytes, GLT_future *newfuture) {
    CHECK(ABT_eventual_create(nbytes, newfuture),ABT_SUCCESS);
}

GLT_func_prefix void glt_future_free(GLT_future *future) {
    CHECK(ABT_eventual_free(future),ABT_SUCCESS);
}

GLT_func_prefix void glt_future_wait(GLT_future future, void **value) {
    CHECK(ABT_eventual_wait(future, value),ABT_SUCCESS);
}

GLT_func_prefix void glt_future_set(GLT_future future, void *value, int nbytes) {
    CHECK(ABT_eventual_set(future, value, nbytes),ABT_SUCCESS);
}
#endif

//promise functions
GLT_func_prefix int glt_can_promise_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise) {
    CHECK(ABT_future_create(compartments, cb_func, newpromise),ABT_SUCCESS);
}

GLT_func_prefix void glt_promise_free(GLT_promise *promise) {
    CHECK(ABT_future_free(promise),ABT_SUCCESS);
}

GLT_func_prefix void glt_promise_wait(GLT_promise promise) {
    CHECK(ABT_future_wait(promise),ABT_SUCCESS);
}

GLT_func_prefix void glt_promise_test(GLT_promise promise, GLT_bool *flag) {
    CHECK(ABT_future_test(promise, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_promise_set(GLT_promise promise, void * value) {
    CHECK(ABT_future_set(promise, value),ABT_SUCCESS);
}
#endif
