/* See COPYRIGHT in top-level directory. */
/*
 * Scheduler functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//scheduler functions
/*
GLT_func_prefix int glt_can_manage_scheduler() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
*/

GLT_func_prefix void glt_scheduler_config_free(GLT_sched_config *config) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_create(GLT_sched_def *def, int num_threads,
        int *threads_id, GLT_sched_config config, GLT_sched *newsched) {
        GLT_ERROR_ARG;
}

GLT_func_prefix void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_threads, int *threads_id, GLT_sched_config config,
        GLT_sched *newsched) {
        GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_free(GLT_sched *sched) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_finish(GLT_sched sched) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_exit(GLT_sched sched) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_set_data(GLT_sched sched, void *data) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_get_data(GLT_sched sched, void **data) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_get_size(GLT_sched sched, size_t *size) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_scheduler_get_total_size(GLT_sched sched, size_t *size) {
    GLT_ERROR_ARG;
}
/*
#endif
*/
