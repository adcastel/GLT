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
#include <sys/time.h>
#include <sys/sysinfo.h>


#include <qthread/qthread.h>
# include <qthread/barrier.h>
#include <qthread/qtimer.h>


#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread aligned_t
#define GLT_mutex aligned_t
#define GLT_barrier  qt_barrier_t
#define GLT_cond aligned_t
#define GLT_timer qtimer_t

//Extended variables
#ifndef CORE
//ARGOBOTS
#define GLT_event_kind void *
#define GLT_event_cb_fn void *
#define GLT_future void *
#define GLT_promise void *
#define GLT_bool int
#define GLT_key void *
#define GLT_pool_def void *
#define GLT_pool_config void *
#define GLT_pool void *
#define GLT_pool_kind void *
#define GLT_pool_access void *
#define GLT_unit void *
#define GLT_sched void *
#define GLT_sched_config void *
#define GLT_sched_def void *
#define GLT_sched_predef void *
#define GLT_thread_state void *
#define GLT_tasklet_state void *
#define GLT_ult_state void *
#define GLT_ult_id int
#define GLT_ult_attr void *
#define GLT_unit_type void *


#define glt_scheduler_config_create 
#define glt_scheduler_config_read 
#endif


typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;


#define GLT_VERSION "You are using fast glt 0.1v over Qthreads (adcastel@uji.es)"
#define GLT_ERROR_ARG "Error: This feature is only supported by Argobots implementation and you are using MassiveThreads. Please use the query functions"

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
    int num_threads = get_nprocs();
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

static inline uint64_t glt_get_ult_id(GLT_ult ult)
{
    uint64_t id = qthread_id();
    return id;
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

static inline double glt_get_wtime() 
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return (time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
}

static inline void glt_timer_create(GLT_timer * timer) 
{
    *timer = qtimer_create();
}

static inline void glt_timer_free(GLT_timer * timer) 
{
    qtimer_destroy(*timer);
}

static inline void glt_timer_start(GLT_timer timer) 
{
    qtimer_start(timer);
}

static inline void glt_timer_stop(GLT_timer timer) 
{
    qtimer_stop(timer);
}

static inline void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    *secs = qtimer_secs(timer);
}

static inline int glt_get_num_threads() 
{
    return main_team->num_shepherds;
}

static inline int glt_get_thread_num() 
{
    return qthread_shep();
}

//Extended functions


//ARGOBOTS FUNCTIONS that are not supported by Qthreads

static inline int glt_can_event_functions()
{
    return 0;
}

static inline int glt_can_future_functions()
{
    return 0;
}

static inline int glt_can_promise_functions()
{
    return 0;
}
static inline int glt_can_tls_functions()
{
    return 0;
}

static inline int glt_can_extended_mutex()
{
    return 0;
}
static inline int glt_can_manage_pools()
{
    return 0;
}
static inline int glt_can_manage_scheduler()
{
    return 0;
}
static inline int glt_can_self()
{
    return 0;
}
static inline int glt_can_manage_threads()
{
    return 0;
}
static inline int can_extended_tasklets()
{
    return 0;
}
static inline int can_extended_ults()
{
    return 0;
}

#ifndef CORE

//HEADERS for ARGOBOTS extended functions
//Null codes
static inline void glt_get_error_str(int errno, char *str, size_t *len)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_event_del_callback(GLT_event_kind event, int cb_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_future_create(int nbytes, GLT_future *newfuture)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_future_free(GLT_future *future)
{
    printf("%s\n",GLT_ERROR_ARG);
}
static inline void glt_future_wait(GLT_future future, void **value)
{
    printf("%s\n",GLT_ERROR_ARG);
}
static inline void glt_future_set(GLT_future future, void *value, int nbytes)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_free(GLT_promise *promise)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_wait(GLT_promise promise)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_test(GLT_promise promise, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_set(GLT_promise promise, void * value)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_create(void(*destructor)(void *value), GLT_key *newkey)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_free(GLT_key *key)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_set(GLT_key key, void *value)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_get(GLT_key key, void **value)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_lock_low(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_trylock(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_spinlock(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_unlock_se(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_free(GLT_pool *pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_total_size(GLT_pool pool, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_size(GLT_pool pool, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_push(GLT_pool pool, GLT_unit p_unit)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_remove(GLT_pool pool, GLT_unit p_unit)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_set_data(GLT_pool pool, void *data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_data(GLT_pool pool, void **data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_add_sched(GLT_pool pool, GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_id(GLT_pool pool, int *id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_config_free(GLT_sched_config *config)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_create(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_free(GLT_sched *sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_finish(GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_exit(GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_set_data(GLT_sched sched, void *data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_data(GLT_sched sched, void **data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_size(GLT_sched sched, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_total_size(GLT_sched sched, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_get_type(GLT_unit_type *type)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_is_primary(GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_on_primary_xstream(GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_get_last_pool_id(int *pool_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_suspend(void)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_get_arg(void **arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_create(GLT_sched sched, GLT_thread *newthread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_start(GLT_thread thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_free(GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_join(GLT_thread thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_exit()
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_cancel(GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_self(GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_self_rank(int *rank)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_rank(GLT_thread thread, int *rank)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_num(int *num_xstreams)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_run_unit(GLT_unit unit, GLT_pool pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_check_events(GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}


static inline  void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_self(GLT_tasklet *tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_retain(GLT_tasklet tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_release(GLT_tasklet tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}
 
static inline  void glt_ult_exit()
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_cancel(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_self(GLT_ult *ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_last_pool_id(GLT_ult ult, int *id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_resume(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_retain(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_release(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_id(GLT_ult ult, GLT_ult_id *ult_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_arg(GLT_ult ult, void **arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_create (GLT_ult_attr *newattr)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_free(GLT_ult_attr *attr)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

#endif


#endif	/* FAST_GLT_H */

