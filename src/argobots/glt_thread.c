/* See COPYRIGHT in top-level directory. */
/*
 * Thread management functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//threads functions
GLT_func_prefix int glt_can_manage_threads() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_thread_create(GLT_sched sched, GLT_thread *newthread) {

    if (main_team->num_xstreams < main_team->max_elem) {
        CHECK(ABT_xstream_create(sched, newthread),ABT_SUCCESS);
        main_team->team[main_team->num_xstreams] = newthread;
        main_team->num_xstreams++;
                printf("Creado nuevo thread y con esta llevamos %d\n",main_team->num_xstreams);

    } else {
        printf("Error: There are not more sloots for threads\n");
    }
}

GLT_func_prefix void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread) {
    if (main_team->num_xstreams < main_team->max_elem) {
        CHECK(ABT_xstream_create_basic(predef, num_pools, pools, config, newthread),ABT_SUCCESS);
        main_team->team[main_team->num_xstreams] = newthread;
        main_team->num_xstreams++;
                        printf("Creado nuevo basic thread y con esta llevamos %d\n",main_team->num_xstreams);

    } else {
        printf("Error: There are not more sloots for threads\n");
    }
}

GLT_func_prefix void glt_thread_start(GLT_thread thread) {
    CHECK(ABT_xstream_start(thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_free(GLT_thread *thread) {
    CHECK(ABT_xstream_free(thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_join(GLT_thread thread) {
    CHECK(ABT_xstream_join(thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_exit() {
    CHECK(ABT_xstream_exit(),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_cancel(GLT_thread *thread) {
    CHECK(ABT_xstream_cancel(thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_self(GLT_thread *thread) {
    CHECK(ABT_xstream_self(thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_self_rank(int *rank) {
    CHECK(ABT_xstream_self_rank(rank),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_get_rank(GLT_thread thread, int *rank) {
    CHECK(ABT_xstream_get_rank(thread, rank),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched) {
    CHECK(ABT_xstream_set_main_sched(thread, sched),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools) {
    CHECK(ABT_xstream_set_main_sched_basic(thread, predef, num_pools, pools),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched) {
    CHECK(ABT_xstream_get_main_sched(thread, sched),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools) {
    CHECK(ABT_xstream_get_main_pools(thread, max_pools, pools),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state) {
    CHECK(ABT_xstream_get_state(thread, state),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result) {
    CHECK(ABT_xstream_equal(thread1, thread2, result),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_get_num(int *num_xstreams) {
    CHECK(ABT_xstream_get_num(num_xstreams),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag) {
    CHECK(ABT_xstream_is_primary(thread, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_run_unit(GLT_unit unit, GLT_pool pool) {
    CHECK(ABT_xstream_run_unit(unit, pool),ABT_SUCCESS);
}

GLT_func_prefix void glt_thread_check_events(GLT_sched sched) {
    CHECK(ABT_xstream_check_events(sched),ABT_SUCCESS);
}
#endif