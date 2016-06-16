/* See COPYRIGHT in top-level directory. */
/*
 * Timer functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix double glt_get_wtime() {
    return ABT_get_wtime();
}

GLT_func_prefix void glt_timer_create(GLT_timer * timer) {
    CHECK(ABT_timer_create(timer),ABT_SUCCESS);
}

GLT_func_prefix void glt_timer_free(GLT_timer * timer) {
    CHECK(ABT_timer_free(timer),ABT_SUCCESS);
}

GLT_func_prefix void glt_timer_start(GLT_timer timer) {
    CHECK(ABT_timer_start(timer),ABT_SUCCESS);
}

GLT_func_prefix void glt_timer_stop(GLT_timer timer) {
    CHECK(ABT_timer_stop(timer),ABT_SUCCESS);
}

GLT_func_prefix void glt_timer_get_secs(GLT_timer timer, double *secs) {
    CHECK(ABT_timer_read(timer, secs),ABT_SUCCESS);
}
