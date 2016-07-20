/* See COPYRIGHT in top-level directory. */
/*
 * Sinc functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_sinc_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected) {
    sinc = qt_sinc_create(sizeof_value, initial_value, op, expected);
}

GLT_func_prefix void glt_sinc_init(GLT_sinc * restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected) {
    CHECK(qt_sinc_init(sinc, sizeof_value, initial_value, op, expected),0);
}

GLT_func_prefix void glt_sinc_destroy(GLT_sinc *sinc) {
    CHECK(qt_sinc_destroy(sinc),0);
}

GLT_func_prefix void glt_sinc_fini(GLT_sinc * sinc) {
    CHECK(qt_sinc_fini(sinc),0);
}

GLT_func_prefix void glt_sinc_reset(GLT_sinc * sinc, size_t expect) {
    CHECK(qt_sinc_reset(sinc, expect),0);
}

GLT_func_prefix void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value) {
    CHECK(qt_sinc_submit(sinc, value),0);
}

GLT_func_prefix void glt_sinc_wait(GLT_sinc * restrict sinc, void * restrict target) {
    CHECK(qt_sinc_wait(sinc, target),0);
}

#endif