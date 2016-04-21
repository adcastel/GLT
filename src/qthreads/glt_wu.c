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

GLT_func_prefix void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) {
    qthread_fork((void *) thread_func, arg, new_ult);
}

GLT_func_prefix void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

GLT_func_prefix void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
    qthread_fork((void *) thread_func, arg, new_ult);
}

GLT_func_prefix void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) {
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

GLT_func_prefix void glt_yield() {
    qthread_yield();
}

GLT_func_prefix void glt_yield_to(GLT_ult ult) {
    qthread_yield();
}

GLT_func_prefix void glt_ult_join(GLT_ult *ult) {
    qthread_readFF(NULL, ult);
}

GLT_func_prefix void glt_tasklet_join(GLT_tasklet *tasklet) {
    qthread_readFF(NULL, tasklet);
}

GLT_func_prefix void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult) {
    *id = qthread_id();
}

GLT_func_prefix void glt_workunit_get_thread_id(GLT_thread_id *id) {
    *id = qthread_shep();
}

GLT_func_prefix void glt_ult_migrate_self_to(GLT_thread_id dest) {
    qthread_migrate_to(dest);
}

GLT_func_prefix void glt_ult_self(GLT_ult * ult) {
    ult = qthread_retloc();
}

GLT_func_prefix void glt_tasklet_self(GLT_ult * ult) {
    ult = qthread_retloc();
}

GLT_func_prefix void glt_ult_exit() {
    printf("Warning: this feature is not supported in Qthreads\n");

}

GLT_func_prefix void glt_ult_cancel(GLT_ult ult) {
    printf("Warning: this feature is not supported in Qthreads\n");
}

GLT_func_prefix void glt_tasklet_cancel(GLT_tasklet tasklet) {
    printf("Warning: this feature is not supported in Qthreads\n");
}