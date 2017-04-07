/* See COPYRIGHT in top-level directory. */
/*
 * Work unit management file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix GLT_ult * glt_ult_malloc(int number_of_ult) {
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

GLT_func_prefix GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) {
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

GLT_func_prefix void glt_ult_create(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) {
    int rank;
    CHECK(ABT_xstream_self_rank(&rank),ABT_SUCCESS);
    CHECK(ABT_thread_create_on_xstream(main_team->team[rank], thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_create_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
    CHECK(ABT_thread_create_on_xstream(main_team->team[dest], thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult),ABT_SUCCESS);
}


GLT_func_prefix void glt_tasklet_create(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
    int rank;
    CHECK(ABT_xstream_self_rank(&rank),ABT_SUCCESS);
    CHECK(ABT_task_create_on_xstream(main_team->team[rank], thread_func, arg, new_ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_create_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) {
    CHECK(ABT_task_create_on_xstream(main_team->team[dest], thread_func, arg, new_ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_yield() {
    CHECK(ABT_thread_yield(),ABT_SUCCESS);
}

GLT_func_prefix void glt_yield_to(GLT_ult ult) {
    CHECK(ABT_thread_yield_to(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_join(GLT_ult *ult) {
    CHECK(ABT_thread_join(*ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_join(GLT_tasklet *tasklet) {
    CHECK(ABT_task_join(*tasklet),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_free(GLT_ult *ult) {
    CHECK(ABT_thread_free(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_free(GLT_tasklet *tasklet) {
    CHECK(ABT_task_free(tasklet),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult) {
    CHECK(ABT_thread_get_id(ult, id),ABT_SUCCESS);
}

GLT_func_prefix void glt_workunit_get_thread_id(GLT_thread_id *id) {
    CHECK(ABT_xstream_self_rank(id),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_migrate_self_to(GLT_thread_id id) {
    GLT_ult ult;
    CHECK(ABT_thread_self(&ult),ABT_SUCCESS);
    CHECK(ABT_thread_migrate_to_xstream(ult, main_team->team[id]),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_self(GLT_tasklet *tasklet) {
    CHECK(ABT_task_self(tasklet),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_self(GLT_ult *ult) {
    CHECK(ABT_thread_self(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_exit() {
    CHECK(ABT_thread_exit(),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_cancel(GLT_ult ult) {
    CHECK(ABT_thread_cancel(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_cancel(GLT_tasklet tasklet) {
    CHECK(ABT_task_cancel(tasklet),ABT_SUCCESS);
}

