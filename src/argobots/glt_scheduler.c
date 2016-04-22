/* See COPYRIGHT in glt_common.h file. */
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
    ABT_sched_config_free(config);
}

GLT_func_prefix void glt_scheduler_create(GLT_sched_def *def, int num_threads,
        int *threads_id, GLT_sched_config config, GLT_sched *newsched) {
    ABT_pool pools[num_threads];
    
    for (int i=0;i<num_threads;i++){
        ABT_xstream_get_main_pools(main_team->team[threads_id[i]],1,&pools[i]);
    }
    ABT_sched_create(def, num_threads, pools, config, newsched);
}

GLT_func_prefix void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_threads, int *threads_id, GLT_sched_config config,
        GLT_sched *newsched) {
    ABT_pool pools[num_threads];
    
    for (int i=0;i<num_threads;i++){
        ABT_xstream_get_main_pools(main_team->team[threads_id[i]],1,&pools[i]);
    }
    ABT_sched_create_basic(predef, num_threads, pools, config, newsched);
}

GLT_func_prefix void glt_scheduler_free(GLT_sched *sched) {
    ABT_sched_free(sched);
}

GLT_func_prefix void glt_scheduler_finish(GLT_sched sched) {
    ABT_sched_finish(sched);
}

GLT_func_prefix void glt_scheduler_exit(GLT_sched sched) {
    ABT_sched_exit(sched);
}

GLT_func_prefix void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop) {
    ABT_sched_has_to_stop(sched, stop);
}

GLT_func_prefix void glt_scheduler_set_data(GLT_sched sched, void *data) {
    ABT_sched_set_data(sched, data);
}

GLT_func_prefix void glt_scheduler_get_data(GLT_sched sched, void **data) {
    ABT_sched_get_data(sched, data);
}

GLT_func_prefix void glt_scheduler_get_size(GLT_sched sched, size_t *size) {
    ABT_sched_get_size(sched, size);
}

GLT_func_prefix void glt_scheduler_get_total_size(GLT_sched sched, size_t *size) {
    ABT_sched_get_total_size(sched, size);
}
/*
#endif
*/
