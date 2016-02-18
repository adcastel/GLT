#include <glt.h>



GLT_ult * glt_ult_malloc(int number_of_ult) {
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) {
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) {
#ifdef ARGOBOTS
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
#endif
#ifdef MASSIVETHREADS
    *new_ult = myth_create((void *) thread_func, arg);
#endif
#ifdef QTHREADS
    qthread_fork((void *) thread_func, arg, new_ult);
#endif
}

void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
#ifdef ARGOBOTS
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
#endif
#ifdef MASSIVETHREADS
    glt_ult_creation(thread_func, arg, new_ult);
#endif
#ifdef QTHREADS
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
#endif
}

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
#ifdef ARGOBOTS
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
#endif
#ifdef MASSIVETHREADS
    *new_ult = myth_create((void *) thread_func, arg);
#endif
#ifdef QTHREADS
    qthread_fork((void *) thread_func, arg, new_ult);
#endif
}

void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) {
#ifdef ARGOBOTS
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
#endif
#ifdef MASSIVETHREADS
    glt_ult_creation(thread_func, arg, new_ult);
#endif
#ifdef QTHREADS
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
#endif
}

void glt_yield() {
#ifdef ARGOBOTS
    ABT_thread_yield();
#endif
#ifdef MASSIVETHREADS
    myth_yield(0);
#endif
#ifdef QTHREADS
    qthread_yield();
#endif
}

void glt_yield_to(GLT_ult ult) {
#ifdef ARGOBOTS
    ABT_thread_yield_to(ult);
#endif
#ifdef MASSIVETHREADS
    myth_yield(0);
#endif
#ifdef QTHREADS
    qthread_yield();
#endif
}

void glt_ult_join(GLT_ult *ult) {
#ifdef ARGOBOTS
    ABT_thread_free(ult);
#endif
#ifdef MASSIVETHREADS
    myth_join(*ult, NULL);
#endif
#ifdef QTHREADS
    qthread_readFF(NULL, ult);
#endif
}

void glt_tasklet_join(GLT_tasklet *tasklet) {
#ifdef ARGOBOTS
    ABT_task_free(tasklet);
#endif
#ifdef MASSIVETHREADS
    myth_join(*tasklet, NULL);
#endif
#ifdef QTHREADS
    qthread_readFF(NULL, tasklet);
#endif
}
/*
void glt_ult_migrate(GLT_ult ult){
#ifdef ARGOBOTS
    ABT_task_free(tasklet);
#endif
#ifdef MASSIVETHREADS
    myth_join(*tasklet, NULL);
#endif
#ifdef QTHREADS
    qthread_readFF(NULL, tasklet);
#endif
}
void glt_ult_migrate_to(GLT_ult ult, int dest){
#ifdef ARGOBOTS
    ABT_task_free(tasklet);
#endif
#ifdef MASSIVETHREADS
    myth_join(*tasklet, NULL);
#endif
#ifdef QTHREADS
    qthread_readFF(NULL, tasklet);
#endif   
}
void glt_ult_get_id(GLT_ult ult, GLT_ult_id * id){
#ifdef ARGOBOTS
    ABT_thread_get_id (ult, id);
#endif
#ifdef MASSIVETHREADS
    
#endif
#ifdef QTHREADS
    *id=qthread_id();
#endif   
}
*/