/* See COPYRIGHT in glt_common.h file. */
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
    myth_log_start();
}

GLT_func_prefix void glt_log_pause() {
    myth_log_pause();
}

GLT_func_prefix void glt_log_flush() {
    myth_log_flush();
}

GLT_func_prefix void glt_log_reset() {
    myth_log_reset();
}

GLT_func_prefix void glt_log_annotate_ult(GLT_ult ult, char *name) {
    myth_log_annotate_thread(ult, name);
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
    myth_sched_prof_start();
}

GLT_func_prefix void glt_sched_prof_pause() {
    myth_sched_prof_pause();
}
#endif
