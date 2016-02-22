/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H

#include <stdio.h>
#include <stdlib.h>
#include <qthread/qthread.h>
# include <qthread/barrier.h>

#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread aligned_t
#define GLT_mutex aligned_t
#define GLT_barrier  qt_barrier_t
#define GLT_cond aligned_t


typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;


#define GLT_VERSION "You are using fast glt 0.1v over Qthreads (adcastel@uji.es)"
/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

static inline void glt_start() 
{
    //printf("Starting with QTHREADS\n");
}

static inline  void glt_end() 
{
    //printf("Ending with QTHREADS\n");
}

static inline  void glt_init(int argc, char * argv[]) 
{
    int num_threads = 1;
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    int num_workers_per_thread;
    
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("QTHREAD_NUM_SHEPHERDS", buff, 1);
    } else if (getenv("QTHREAD_NUM_SHEPHERDS") != NULL){
        num_threads = atoi(getenv("QTHREAD_NUM_SHEPHERDS"));
    } else {
        setenv("QTHREAD_NUM_SHEPHERDS", "1", 1);
    }

    if (getenv("GLT_NUM_WORKERS_PER_THREAD") != NULL) {
        num_workers_per_thread = atoi(getenv("GLT_NUM_WORKERS_PER_THREAD"));
        sprintf(buff, "%d", num_workers_per_thread);
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", buff, 1);
    } else if (getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD") != NULL) {
        num_workers_per_thread = atoi(getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD"));
    }
    else {
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", "1", 1);
    }
    
    if (num_threads == 1 && num_workers_per_thread > 1) {
        setenv("QTHREAD_SHEPHERDS_BOUNDARY", "node", 1);
        setenv("QTHREAD_WORKER_UNIT", "core", 1);
    }
    if (num_threads > 1) {
        setenv("QTHREAD_SHEPHERDS_BOUNDARY", "core", 1);
        setenv("QTHREAD_WORKER_UNIT", "core", 1);
    }
    setenv("QTHREAD_AFFINITY", "yes", 1);

    main_team->num_shepherds = num_threads;
    main_team->num_workers_per_shepherd = num_workers_per_thread;
    qthread_initialize(); //qthreads
}

static inline void glt_finalize() 
{
    qthread_finalize();
}

static inline GLT_ult * glt_ult_malloc(int number_of_ult) 
{
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

static inline GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) 
{
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

static inline void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) 
{
    qthread_fork((void *) thread_func, arg, new_ult);
}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    qthread_fork((void *) thread_func, arg, new_ult);
}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

static inline void glt_yield() 
{
    qthread_yield();
}

static inline void glt_yield_to(GLT_ult ult) 
{
    qthread_yield();
}

static inline void glt_ult_join(GLT_ult *ult) 
{
    qthread_readFF(NULL, ult);
}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    qthread_readFF(NULL, tasklet);
}

static inline void glt_mutex_create(GLT_mutex * mutex)
{
    mutex = (GLT_mutex *)malloc(sizeof(GLT_mutex));
}

static inline void glt_mutex_lock(GLT_mutex mutex)
{
    qthread_lock(&mutex);
}

static inline void glt_mutex_unlock(GLT_mutex mutex)
{
    qthread_unlock(&mutex);
}

static inline void glt_mutex_free(GLT_mutex * mutex)
{
    free(mutex);
}


static inline void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    barrier = qt_barrier_create(num_waiters, UPLOCK);
}

static inline void glt_barrier_free(GLT_barrier *barrier)
{
    qt_barrier_destroy(barrier);
}

static inline void glt_barrier_wait(GLT_barrier *barrier)
{
    qt_barrier_enter(barrier);
}

static inline void glt_cond_create(GLT_cond *cond)
{
    cond = (GLT_cond *)malloc(sizeof(GLT_cond));
}

static inline void glt_cond_free(GLT_cond *cond)
{
    free(cond);
}

static inline void glt_cond_signal(GLT_cond cond)
{
    qthread_empty(&cond);
}

static inline void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    /*Waits for memory to become empty and then fills it*/
    aligned_t fill=1;
    qthread_writeEF(&cond,&fill);
    qthread_lock(&mutex);
}

static inline void glt_cond_broadcast(GLT_cond cond)
{
    qthread_empty(&cond);
}

static inline int glt_get_num_threads() 
{
    return main_team->num_shepherds;
}

static inline int glt_get_thread_num() 
{
    return qthread_shep();
}

#endif	/* FAST_GLT_H */

