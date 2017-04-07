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

GLT_func_prefix int glt_can_manage_scheduler() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


GLT_func_prefix void glt_scheduler_config_free(GLT_sched_config *config) {
    CHECK(ABT_sched_config_free(config),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_create(GLT_sched_def *def, int num_threads,
        int *threads_id, GLT_sched_config config, GLT_sched *newsched) {
    ABT_pool pools[num_threads];
    
    for (int i=0;i<num_threads;i++){
        CHECK(ABT_xstream_get_main_pools(main_team->team[threads_id[i]],1,&pools[i]),ABT_SUCCESS);
    }
    CHECK(ABT_sched_create(def, num_threads, pools, config, newsched),ABT_SUCCESS);
}

GLT_func_prefix void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_threads, int *threads_id, GLT_sched_config config,
        GLT_sched *newsched) {
    ABT_pool pools[num_threads];
    
    for (int i=0;i<num_threads;i++){
        CHECK(ABT_xstream_get_main_pools(main_team->team[threads_id[i]],1,&pools[i]),ABT_SUCCESS);
    }
    CHECK(ABT_sched_create_basic(predef, num_threads, pools, config, newsched),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_free(GLT_sched *sched) {
    CHECK(ABT_sched_free(sched),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_finish(GLT_sched sched) {
    CHECK(ABT_sched_finish(sched),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_exit(GLT_sched sched) {
    CHECK(ABT_sched_exit(sched),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop) {
    CHECK(ABT_sched_has_to_stop(sched, stop),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_set_data(GLT_sched sched, void *data) {
    CHECK(ABT_sched_set_data(sched, data),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_get_data(GLT_sched sched, void **data) {
    CHECK(ABT_sched_get_data(sched, data),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_get_size(GLT_sched sched, size_t *size) {
    CHECK(ABT_sched_get_size(sched, size),ABT_SUCCESS);
}

GLT_func_prefix void glt_scheduler_get_total_size(GLT_sched sched, size_t *size) {
    CHECK(ABT_sched_get_total_size(sched, size),ABT_SUCCESS);
}

#endif

