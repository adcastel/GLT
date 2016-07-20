/* See COPYRIGHT in top-level directory. */
/*
 * Profiling and Loging functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_log_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_log_start() {
    CHECK(myth_log_start(),0);
}

GLT_func_prefix void glt_log_pause() {
    CHECK(myth_log_pause(),0);
}

GLT_func_prefix void glt_log_flush() {
    CHECK(myth_log_flush(),0);
}

GLT_func_prefix void glt_log_reset() {
    CHECK(myth_log_reset(),0);
}

GLT_func_prefix void glt_log_annotate_ult(GLT_ult ult, char *name) {
    CHECK(myth_log_annotate_thread(ult, name),0);
}
#endif

GLT_func_prefix int glt_can_prof_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_sched_prof_start() {
    CHECK(myth_sched_prof_start(),0);
}

GLT_func_prefix void glt_sched_prof_pause() {
    CHECK(myth_sched_prof_pause(),0);
}
#endif
