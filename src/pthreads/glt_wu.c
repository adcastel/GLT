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
    cpu_set_t cpuset;
    pthread_getaffinity_np(pthread_self(), sizeof (cpu_set_t), &cpuset);
    pthread_create(new_ult, NULL,(void *) thread_func, arg);
    pthread_setaffinity_np(*new_ult, sizeof (cpu_set_t), &cpuset);
    main_team->num_workers++;
}

GLT_func_prefix void glt_ult_create_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    dest=dest%main_team->max_workers;
    CPU_SET(dest, &cpuset);
    pthread_create(new_ult, NULL,(void *) thread_func, arg);
    pthread_setaffinity_np(*new_ult, sizeof (cpu_set_t), &cpuset);
    main_team->num_workers++;
}

GLT_func_prefix void glt_tasklet_create(void(*thread_func)(void *), void *arg, GLT_tasklet *new_tasklet) {
    cpu_set_t cpuset;
    pthread_getaffinity_np(pthread_self(), sizeof (cpu_set_t), &cpuset);
    pthread_create(new_tasklet, NULL,(void *) thread_func, arg);
    pthread_setaffinity_np(*new_tasklet, sizeof (cpu_set_t), &cpuset);
    main_team->num_workers++;
}

GLT_func_prefix void glt_tasklet_create_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_tasklet, int dest) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    dest=dest%main_team->max_workers;
    CPU_SET(dest, &cpuset);
    pthread_create(new_tasklet, NULL,(void *) thread_func, arg);
    pthread_setaffinity_np(*new_tasklet, sizeof (cpu_set_t), &cpuset);
    main_team->num_workers++;
}

GLT_func_prefix void glt_yield() {
    pthread_yield();
}

GLT_func_prefix void glt_yield_to(GLT_ult ult) {
    pthread_yield();
}

GLT_func_prefix void glt_ult_join(GLT_ult *ult) {
    pthread_join(*ult, NULL);
    main_team->num_workers--;
}

GLT_func_prefix void glt_tasklet_join(GLT_tasklet *tasklet) {
    pthread_join(*tasklet, NULL);
    main_team->num_workers--;
}

GLT_func_prefix void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult) {
    printf("Warning: this feature is not supported in MassiveThreads\n");
    *id = pthread_self();
}

GLT_func_prefix void glt_workunit_get_thread_id(GLT_thread_id *id) {
    *id = sched_getcpu();
}

GLT_func_prefix void glt_ult_migrate_self_to(GLT_thread_id id) {
    printf("Warning: this feature is not supported in MassiveThreads\n");
}

GLT_func_prefix void glt_tasklet_self(GLT_tasklet *tasklet) {
    *tasklet = pthread_self();
}

GLT_func_prefix void glt_ult_self(GLT_ult *ult) {
    *ult = pthread_self();
}

GLT_func_prefix void glt_ult_exit() {
    void *ret;
    pthread_exit(ret);
    main_team->num_workers--;
}

GLT_func_prefix void glt_ult_cancel(GLT_ult ult) {
    pthread_cancel(ult);
    main_team->num_workers--;
}

GLT_func_prefix void glt_tasklet_cancel(GLT_tasklet tasklet) {
    pthread_cancel(tasklet);
    main_team->num_workers--;
}