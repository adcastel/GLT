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
    *new_ult = myth_create((void *) thread_func, arg);
}

GLT_func_prefix void glt_ult_create_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
    glt_ult_create(thread_func, arg, new_ult);
}

GLT_func_prefix void glt_tasklet_create(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
    *new_ult = myth_create((void *) thread_func, arg);
}

GLT_func_prefix void glt_tasklet_create_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) {
    glt_ult_create(thread_func, arg, new_ult);
}

GLT_func_prefix void glt_yield() {
    myth_yield(0);
}

GLT_func_prefix void glt_yield_to(GLT_ult ult) {
    myth_yield(0);
}

GLT_func_prefix void glt_ult_join(GLT_ult *ult) {
    CHECK(myth_join(*ult, NULL),0);
}

GLT_func_prefix void glt_tasklet_join(GLT_tasklet *tasklet) {
    CHECK(myth_join(*tasklet, NULL),0);
}

GLT_func_prefix void glt_ult_free(GLT_ult *ult) {
    CHECK(myth_join(*ult, NULL),0);
}

GLT_func_prefix void glt_tasklet_free(GLT_tasklet *tasklet) {
    CHECK(myth_join(*tasklet, NULL),0);
}

GLT_func_prefix void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult) {
    printf("Warning: this feature is not supported in MassiveThreads\n");
    *id = -1;
}

GLT_func_prefix void glt_workunit_get_thread_id(GLT_thread_id *id) {
    *id = myth_get_worker_num();
}

GLT_func_prefix void glt_ult_migrate_self_to(GLT_thread_id id) {
    printf("Warning: this feature is not supported in MassiveThreads\n");
}

GLT_func_prefix void glt_tasklet_self(GLT_tasklet *tasklet) {
    *tasklet = myth_self();
}

GLT_func_prefix void glt_ult_self(GLT_ult *ult) {
    *ult = myth_self();
}

GLT_func_prefix void glt_ult_exit() {
    void *ret;
    CHECK(myth_exit(ret),0);
}

GLT_func_prefix void glt_ult_cancel(GLT_ult ult) {
    CHECK(myth_cancel(ult),0);
}

GLT_func_prefix void glt_tasklet_cancel(GLT_tasklet tasklet) {
    CHECK(myth_cancel(tasklet),0);
}

GLT_func_prefix int can_extended_workunits() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_wu_create_ex(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt) {
    *ult = myth_create_ex(func, arg, opt);
}

GLT_func_prefix void glt_yield2() {
    myth_yield2();
}

GLT_func_prefix void glt_wu_detach(GLT_ult ult) {
    CHECK(myth_detach(ult),0);
}

GLT_func_prefix void glt_wu_set_cancel_state(int state, int *oldstate) {
    CHECK(myth_setcancelstate(state, oldstate),0);
}

GLT_func_prefix void glt_wu_set_cancel_type(int type, int *oldtype) {
    CHECK(myth_setcanceltype(type, oldtype),0);
}

GLT_func_prefix void glt_wu_test_cancel() {
    CHECK(myth_testcancel(),0);
}

GLT_func_prefix void glt_wu_set_def_stack_size(size_t newsize) {
    CHECK(myth_set_def_stack_size(newsize),0);
}

#endif