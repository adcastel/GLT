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
    CHECK(ABT_thread_free(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_join(GLT_tasklet *tasklet) {
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

// Extended functions
//tasklets functions
GLT_func_prefix int can_extended_tasklets() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread) {
    CHECK(ABT_task_get_xstream(tasklet, thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state) {
    CHECK(ABT_task_get_state(tasklet, state),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool) {
    CHECK(ABT_task_get_last_pool(tasklet, pool),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet, int *id) {
    CHECK(ABT_task_get_last_pool_id(tasklet, id),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag) {
    CHECK(ABT_task_set_migratable(tasklet, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_is_migratable(GLT_tasklet tasklet, GLT_bool *flag) {
    CHECK(ABT_task_is_migratable(tasklet, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result) {
    CHECK(ABT_task_equal(tasklet1, tasklet2, result),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_retain(GLT_tasklet tasklet) {
    CHECK(ABT_task_retain(tasklet),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_release(GLT_tasklet tasklet) {
    CHECK(ABT_task_release(tasklet),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg) {
    CHECK(ABT_task_get_arg(tasklet, arg),ABT_SUCCESS);
}

GLT_func_prefix void glt_tasklet_create_to_pool(GLT_pool pool, void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
        CHECK(ABT_task_create(pool, thread_func, arg, new_ult),ABT_SUCCESS);
}



#endif

// ult functions
GLT_func_prefix int can_extended_ults() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state) {
    CHECK(ABT_thread_get_state(ult, state),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool) {
    CHECK(ABT_thread_get_last_pool(ult, pool),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_get_last_pool_id(GLT_ult ult, int *id) {
    CHECK(ABT_thread_get_last_pool_id(ult, id),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_resume(GLT_ult ult) {
    CHECK(ABT_thread_resume(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread) {
    CHECK(ABT_thread_migrate_to_xstream(ult, thread),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched) {
    CHECK(ABT_thread_migrate_to_sched(ult, sched),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool) {
    CHECK(ABT_thread_migrate_to_pool(ult, pool),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_migrate(GLT_ult ult) {
    CHECK(ABT_thread_migrate(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_set_callback(GLT_ult ult, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg) {
    CHECK(ABT_thread_set_callback(ult, cb_func, cb_arg),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_set_migratable(GLT_ult ult, GLT_bool flag) {
    CHECK(ABT_thread_set_migratable(ult, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag) {
    CHECK(ABT_thread_is_migratable(ult, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag) {
    CHECK(ABT_thread_is_primary(ult, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result) {
    CHECK(ABT_thread_equal(ult1, ult2, result),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_retain(GLT_ult ult) {
    CHECK(ABT_thread_retain(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_release(GLT_ult ult) {
    CHECK(ABT_thread_release(ult),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize) {
    CHECK(ABT_thread_get_stacksize(ult, stacksize),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_get_arg(GLT_ult ult, void **arg) {
    CHECK(ABT_thread_get_arg(ult, arg),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_attr_create(GLT_ult_attr *newattr) {
    CHECK(ABT_thread_attr_create(newattr),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_attr_free(GLT_ult_attr *attr) {
    CHECK(ABT_thread_attr_free(attr),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_attr_set_stacksize(GLT_ult_attr attr, size_t stacksize) {
    CHECK(ABT_thread_attr_set_stacksize(attr, stacksize),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_attr_get_stacksize(GLT_ult_attr attr, size_t *stacksize) {
    CHECK(ABT_thread_attr_get_stacksize(attr, stacksize),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_attr_set_callback(GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg) {
    CHECK(ABT_thread_attr_set_callback(attr, cb_func, cb_arg),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_attr_set_migratable(GLT_ult_attr attr, GLT_bool flag) {
    CHECK(ABT_thread_attr_set_migratable(attr, flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_ult_create_to_pool(GLT_pool pool, void(*thread_func)(void *), void *arg, GLT_ult *new_ult) {
    CHECK(ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult),ABT_SUCCESS);
}
#endif /*#ifndef CORE*/
