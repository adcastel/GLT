/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <sys/time.h>
#include <sys/sysinfo.h>
       

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <myth.h>

typedef struct myth_timer {
    struct timeval start;
    struct timeval end;
} myth_timer_t;

#define GLT_ult myth_thread_t
#define GLT_tasklet myth_thread_t
#define GLT_thread myth_thread_t
#define GLT_mutex myth_mutex_t
#define GLT_barrier myth_barrier_t
#define GLT_cond myth_cond_t
#define GLT_timer myth_timer_t
#define GLT_bool int

//Extended variables
#ifndef CORE
#include <sys/socket.h>
#include <poll.h>
#include <sys/resource.h>

#define aligned_t long unsigned int
typedef enum introspective_state {NOT_SUPPORTED} introspective_state;

typedef struct mapinfo_s {
    int not_supported;
}mapinfo_s_t;

typedef struct dynmapinfo_s {
    int not_supported;
}dynmapinfo_s_t;
//ARGOBOTS
#define GLT_event_kind void *
#define GLT_event_cb_fn void *
#define GLT_future void *
#define GLT_promise void *
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
//QTHREADS
#define GLT_syncvar void *
#define GLT_aligned void *
#define GLT_memory_state void *
#define GLT_sinc_op void *
#define GLT_sinc void *
#define GLT_loop_f void *
#define GLT_loopr_f void *
#define GLT_loop_step_f void *
#define GLT_accum_f void *
#define GLT_loop_queue void *
#define GLT_loop_queue_kind void *
#define GLT_ds_pool void *
#define GLT_ds_array void *
#define GLT_ds_array_distribution void *
#define GLT_ds_loop_f void *
#define GLT_ds_loopr_f void *
#define GLT_ds_cloop_f void *
#define GLT_ds_lfqueue void *
#define GLT_ds_dqueue void *
#define GLT_ds_dictionary void *
#define GLT_ds_dictionary_key_equals void *
#define GLT_ds_dictionary_hash void *
#define GLT_ds_dictionary_cleanup void *
#define GLT_ds_dictionary_it void *
#define GLT_subthread void *

#define glt_scheduler_config_create 
#define glt_scheduler_config_read

#define glt_ult_creation_precond(f,a,u,n,...) qthread_fork_precond(f,a,u,n,...)
#define glt_ult_creation_precond_to(f,a,u,d,n,...) qthread_fork_precond_to(f,a,u,d,n,...)

#endif

typedef struct glt_team {
    int num_workers;
} glt_team_t;



#define GLT_VERSION "You are using fast glt 0.1v over MassiveThreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots \
    implementation and you are using MassiveThreads. Please use the query functions")
#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads \
    implementation and you are using MassiveThreads. Please use the query functions")

/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

static inline void glt_start() 
{
    //printf("Starting with MASSIVETHREADS\n");
}

static inline  void glt_end() 
{
    //printf("Ending with MASSIVETHREADS\n");
}

static inline void glt_init(int argc, char * argv[]) 
{
    int num_threads = get_nprocs();
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("MYTH_WORKER_NUM", buff, 1);
    } else if (getenv("MYTH_WORKER_NUM") != NULL) {
        num_threads = atoi(getenv("MYTH_WORKER_NUM"));
    }
    else{
        setenv("MYTH_WORKER_NUM","1",1);
    }

    setenv("MYTH_BIND_WORKERS", "1", 1);

    main_team->num_workers = num_threads;
    myth_init(); //MassiveThreads
}

static inline void glt_finalize() 
{
    myth_fini(); //MassiveThreads
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
    *new_ult = myth_create((void *) thread_func, arg);
}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    glt_ult_creation(thread_func, arg, new_ult);
}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    *new_ult = myth_create((void *) thread_func, arg);
}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    glt_ult_creation(thread_func, arg, new_ult);
}

static inline void glt_yield() 
{
    myth_yield(0);
}

static inline void glt_yield_to(GLT_ult ult) 
{
    myth_yield(0);
}

static inline void glt_ult_join(GLT_ult *ult) 
{
    myth_join(*ult, NULL);
}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    myth_join(*tasklet, NULL);
}

static inline uint64_t glt_get_ult_id(GLT_ult ult){
    printf("Warning: this feature is not supported in MassiveThreads\n");
    return 0;
}

static inline void glt_mutex_create(GLT_mutex * mutex)
{
    *mutex = myth_mutex_create();
}

static inline void glt_mutex_lock(GLT_mutex mutex)
{
    myth_mutex_lock(mutex);
}
static inline void glt_mutex_unlock(GLT_mutex mutex)
{
    myth_mutex_unlock(mutex);
}

static inline void glt_mutex_free(GLT_mutex * mutex)
{
    myth_mutex_destroy(*mutex);
}

static inline void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    *barrier = myth_barrier_create(num_waiters);
}

static inline void glt_barrier_free(GLT_barrier *barrier)
{
    myth_barrier_destroy(*barrier);
}

static inline void glt_barrier_wait(GLT_barrier *barrier)
{
    myth_barrier_wait(*barrier);
}

static inline void glt_cond_create(GLT_cond *cond)
{
    *cond =  myth_cond_create();
}

static inline void glt_cond_free(GLT_cond *cond)
{
    myth_cond_destroy(*cond);
}

static inline void glt_cond_signal(GLT_cond cond)
{
    myth_cond_signal(cond);
}

static inline void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    myth_cond_wait(cond,mutex);
}

static inline void glt_cond_broadcast(GLT_cond cond)
{
    myth_cond_broadcast(cond);
}

static inline double glt_get_wtime() 
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return (time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
}

static inline void glt_timer_create(GLT_timer * timer) 
{
    timer = (GLT_timer *)malloc (sizeof(GLT_timer));
}

static inline void glt_timer_free(GLT_timer * timer) 
{
    free(timer);
}

static inline void glt_timer_start(GLT_timer timer) 
{
    gettimeofday(&timer.start,NULL);
}

static inline void glt_timer_stop(GLT_timer timer) 
{
    gettimeofday(&timer.end,NULL);
}

static inline void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    *secs = ((timer.end.tv_sec * 1000000 + timer.end.tv_usec)
		  - (timer.start.tv_sec * 1000000 + timer.start.tv_usec))/1000000.0;
}

static inline int glt_get_num_threads() 
{
    return main_team->num_workers;
}

static inline int glt_get_thread_num() 
{
    return myth_get_worker_num();
}


//ARGOBOTS FUNCTIONS that are not supported by Massivethreads

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
    GLT_ERROR_ARG;
}

static inline void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id)
{
    GLT_ERROR_ARG;
}

static inline void glt_event_del_callback(GLT_event_kind event, int cb_id)
{
    GLT_ERROR_ARG;
}

static inline void glt_future_create(int nbytes, GLT_future *newfuture)
{
    GLT_ERROR_ARG;
}

static inline void glt_future_free(GLT_future *future)
{
    GLT_ERROR_ARG;
}
static inline void glt_future_wait(GLT_future future, void **value)
{
    GLT_ERROR_ARG;
}
static inline void glt_future_set(GLT_future future, void *value, int nbytes)
{
    GLT_ERROR_ARG;
}

static inline void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    GLT_ERROR_ARG;
}

static inline void glt_promise_free(GLT_promise *promise)
{
    GLT_ERROR_ARG;
}

static inline void glt_promise_wait(GLT_promise promise)
{
    GLT_ERROR_ARG;
}

static inline void glt_promise_test(GLT_promise promise, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline void glt_promise_set(GLT_promise promise, void * value)
{
    GLT_ERROR_ARG;
}

static inline void glt_key_create(void(*destructor)(void *value), GLT_key *newkey)
{
    GLT_ERROR_ARG;
}

static inline void glt_key_free(GLT_key *key)
{
    GLT_ERROR_ARG;
}

static inline void glt_key_set(GLT_key key, void *value)
{
    GLT_ERROR_ARG;
}

static inline void glt_key_get(GLT_key key, void **value)
{
    GLT_ERROR_ARG;
}

static inline void glt_mutex_lock_low(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

static inline void glt_mutex_trylock(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

static inline void glt_mutex_spinlock(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

static inline void glt_mutex_unlock_se(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

static inline void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_free(GLT_pool *pool)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_get_total_size(GLT_pool pool, size_t *size)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_get_size(GLT_pool pool, size_t *size)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_push(GLT_pool pool, GLT_unit p_unit)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_remove(GLT_pool pool, GLT_unit p_unit)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_set_data(GLT_pool pool, void *data)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_get_data(GLT_pool pool, void **data)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_add_sched(GLT_pool pool, GLT_sched sched)
{
    GLT_ERROR_ARG;
}

static inline void glt_pool_get_id(GLT_pool pool, int *id)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_config_free(GLT_sched_config *config)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_create(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched)
{
    GLT_ERROR_ARG;
}

static inline void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_free(GLT_sched *sched)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_finish(GLT_sched sched)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_exit(GLT_sched sched)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_set_data(GLT_sched sched, void *data)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_get_data(GLT_sched sched, void **data)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_get_size(GLT_sched sched, size_t *size)
{
    GLT_ERROR_ARG;
}

static inline void glt_scheduler_get_total_size(GLT_sched sched, size_t *size)
{
    GLT_ERROR_ARG;
}

static inline void glt_self_get_type(GLT_unit_type *type)
{
    GLT_ERROR_ARG;
}

static inline void glt_self_is_primary(GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline void glt_self_on_primary_xstream(GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline void glt_self_get_last_pool_id(int *pool_id)
{
    GLT_ERROR_ARG;
}

static inline void glt_self_suspend(void)
{
    GLT_ERROR_ARG;
}

static inline void glt_self_get_arg(void **arg)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_create(GLT_sched sched, GLT_thread *newthread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_start(GLT_thread thread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_free(GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_join(GLT_thread thread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_exit()
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_cancel(GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_self(GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_self_rank(int *rank)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_get_rank(GLT_thread thread, int *rank)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_get_num(int *num_xstreams)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_run_unit(GLT_unit unit, GLT_pool pool)
{
    GLT_ERROR_ARG;
}

static inline void glt_thread_check_events(GLT_sched sched)
{
    GLT_ERROR_ARG;
}


static inline  void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_self(GLT_tasklet *tasklet)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_retain(GLT_tasklet tasklet)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_release(GLT_tasklet tasklet)
{
    GLT_ERROR_ARG;
}

static inline  void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg)
{
    GLT_ERROR_ARG;
}
 
static inline  void glt_ult_exit()
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_cancel(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_self(GLT_ult *ult)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_get_last_pool_id(GLT_ult ult, int *id)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_resume(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_migrate(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_retain(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_release(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_get_id(GLT_ult ult, GLT_ult_id *ult_id)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_get_arg(GLT_ult ult, void **arg)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_attr_create (GLT_ult_attr *newattr)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_attr_free(GLT_ult_attr *attr)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    GLT_ERROR_ARG;
}

static inline  void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag)
{
    GLT_ERROR_ARG;
}

#endif

//QTHREADS functions that are not supported by MassiveThreads

static inline int glt_can_extended_basic()
{
    return 0;
}

static inline int glt_can_atomic_functions()
{
    return 0;
}

static inline int glt_can_feb_functions()
{
    return 0;
}

static inline int glt_can_sinc_functions()
{
    return 0;
}

static inline int glt_can_loop_functions()
{
    return 0;
}

static inline int glt_can_util_functions()
{
    return 0;
}
static inline int glt_can_data_structures_functions()
{
    return 0;
}
static inline int glt_can_syscall_functions()
{
    return 0;
}
static inline int glt_can_extended_runtime()
{
    return 0;
}
static inline int glt_can_memory_functions()
{
    return 0;
}

#ifndef CORE


/*static inline void glt_ult_creation_precond(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int npreconds, ...){
    qthread_fork_precond((void *)thread_func,arg,ult,npreconds,...);
}

static inline void glt_ult_creation_precond_to(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int dest,int npreconds, ...){
    qthread_fork_precond_to((void *)thread_func,arg,ult,dest,npreconds,...);
}
*/
static inline void glt_ult_creation_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar){
    GLT_ERROR_QTH;
}

static inline void glt_ult_creation_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest,int npreconds, ...){
    GLT_ERROR_QTH;
}

static inline void glt_ult_get_thread(GLT_thread *thread, int *worker)
{
    GLT_ERROR_QTH;
}

static inline void glt_ult_get_thread_unique(GLT_thread *thread, int *worker)
{
    GLT_ERROR_QTH;
}

static inline void glt_ult_get_tasklocal(void * pointer, unsigned int size)
{
    GLT_ERROR_QTH;
}

static inline void glt_ult_size_tasklocal(unsigned int *size)
{
    GLT_ERROR_QTH;
}

static inline void glt_ult_migrate_self_to(int dest)
{
    GLT_ERROR_QTH;
}

static inline void glt_ult_get_stack_left(size_t *size)
{
    GLT_ERROR_QTH;
}

static inline void glt_ult_retloc(GLT_ult * ult)
{
    GLT_ERROR_QTH;
}

static inline void glt_atomic_incr(GLT_aligned * operand, int incr)
{
    GLT_ERROR_QTH;
}

static inline void glt_atomic_fincr(float * operand, float incr)
{
    GLT_ERROR_QTH;
}

static inline void glt_atomic_dincr(double * operand, double incr)
{
    GLT_ERROR_QTH;
}

static inline void glt_atomic_cas(volatile GLT_aligned * addr, GLT_aligned oldval,
        GLT_aligned newval)
{
    GLT_ERROR_QTH;
}

static inline void glt_atomic_cas_ptr(void * volatile * addr, void * oldval,
        void * newval)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_empty(const GLT_memory_state *dest)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_fill(const GLT_memory_state *dest)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_status(const GLT_memory_state *addr, int *status)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_readFE( GLT_memory_state *dst, const GLT_memory_state *src)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_readFF( GLT_memory_state *dst, const GLT_memory_state *src)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_writeEF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_writeEF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_writeF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    GLT_ERROR_QTH;
}

static inline void glt_feb_writeF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_empty(GLT_syncvar *dest)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_fill(GLT_syncvar *dest)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_status(GLT_syncvar *addr, int *status)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_readFE( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_readFF( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_writeEF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_writeEF_const( GLT_syncvar *  dst,  uint64_t src)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_writeF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    GLT_ERROR_QTH;
}

static inline void glt_syncvar_writeF_const( GLT_syncvar *  dst,  uint64_t src)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_init(GLT_sinc *restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_destroy(GLT_sinc *sinc)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_fini(GLT_sinc * sinc)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_reset(GLT_sinc * sinc, size_t expect)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value)
{
    GLT_ERROR_QTH;
}

static inline void glt_sinc_wait(GLT_sinc * restrict sinc,  void * restrict target)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop_step(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg)
{
    GLT_ERROR_QTH;
}

/*static inline void glt_loop_future(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop_step_future(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg)
{
    GLT_ERROR_QTH;
}
*/
static inline void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

/*static inline void glt_loop_balance_future(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}
*/
static inline void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc)
{
    GLT_ERROR_QTH;
}

/*static inline void glt_loopaccum_balance_future(const size_t start, const size_t end, 
size_t size, void *out, const GLT_loop_f func, void * arg, GLT_accum_f acc)
{
    GLT_ERROR_QTH;
}
*/

static inline void glt_loop_queue_create(GLT_loop_queue * loop, GLT_loop_queue_kind kind,
        const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop_queue_set_chunk(GLT_loop_queue * loop, size_t chunk)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop_queue_run(GLT_loop_queue * loop)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop_queue_run_there(GLT_loop_queue * loop, GLT_thread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_loop_queue_add_thread(GLT_loop_queue * loop, GLT_thread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_double_max(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_uint_max(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_int_max(int * res, const long int * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_double_min(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_uint_min(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_int_min(int * res, const long int * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_double_mult(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_uint_mult(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_int_mult(int * res, const long int * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_double_sum(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_uint_sum(unsigned int * res, 
        const long unsigned int * array, size_t lenght, 
        int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_int_sum(int * res, const long int * array, size_t lenght, 
        int checkfeb)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_qsort(double * array, size_t lenght)
{
    GLT_ERROR_QTH;
}

static inline void glt_util_mergesort(double * array, size_t lenght)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_pool_create(GLT_ds_pool *pool, const size_t item_size)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_pool_create_aligned(GLT_ds_pool *pool, 
        const size_t item_size, const size_t alignment)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_pool_destroy(GLT_ds_pool *pool)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_pool_alloc(GLT_ds_pool *pool)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_pool_free(GLT_ds_pool *restrict pool, 
        void * restrict mem)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_create(GLT_ds_array *array, const size_t count, 
        const size_t item_size)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_create_tight(GLT_ds_array *array, 
        const size_t count, const size_t item_size)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_create_configured(GLT_ds_array *array, 
        const size_t count, const size_t item_size, 
        const GLT_ds_array_distribution d, const char thight, const int seg_pages)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_destroy(GLT_ds_array *array)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_elem(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_elem_nomigrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_elem_migrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_thread_of(GLT_thread * id, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_set_thread_of(GLT_ds_array *array, 
        const size_t index, GLT_thread id )
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_iter(GLT_ds_array *array, 
        const size_t start, const size_t stop, void(*thread_func)(void *))
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_iter_loop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, void * arg)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_iter_nb(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, 
        void * args, aligned_t *arg)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_iter_constloop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_cloop_f thread_func, 
        void * args)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_array_iter_loopaccum(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loopr_f thread_func, 
        void * args, void * ret, const size_t resize, GLT_accum_f acc )
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_lfqueue_create(GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_lfqueue_destroy(GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_lfqueue_enqueue(GLT_ds_lfqueue * lfqueue, void * elem)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_lfqueue_dequeue( void * elem, GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_lfqueue_empty(GLT_bool * empty, GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dqueue_create(GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dqueue_destroy(GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dqueue_enqueue(GLT_ds_dqueue * dqueue, void * elem)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dqueue_enqueue_there(GLT_ds_dqueue * dqueue, 
        void * elem, GLT_thread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dqueue_dequeue( void * elem, GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dqueue_empty(GLT_bool * empty, GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_create(GLT_ds_dictionary * dictionary, 
        GLT_ds_dictionary_key_equals eq, 
        GLT_ds_dictionary_hash hash, GLT_ds_dictionary_cleanup cleanup)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_destroy(GLT_ds_dictionary * dictionary)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_put(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_put_if_absent(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_get(void * value, GLT_ds_dictionary * dictionary,
        void * key)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_delete(void * value, GLT_ds_dictionary * dictionary,
        void * key)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_end(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_it_create(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_it_destroy(GLT_ds_dictionary_it *it)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_it_next(void * entry, GLT_ds_dictionary_it *it)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_it_get(void * entry, GLT_ds_dictionary_it *it)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_it_equals(GLT_bool * eq, 
        GLT_ds_dictionary_it *it1, GLT_ds_dictionary_it *it2)
{
    GLT_ERROR_QTH;
}

static inline void glt_ds_dictionary_it_copy(GLT_ds_dictionary_it *output, 
        GLT_ds_dictionary_it *input)
{
    GLT_ERROR_QTH;
}


static inline void glt_syscall_begin_blocking()
{
    GLT_ERROR_QTH;
}

static inline void glt_syscall_end_blocking()
{
    GLT_ERROR_QTH;
}

static inline int glt_syscall_accept(int socket, 
        struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline int glt_syscall_connect(int socket, 
        struct sockaddr *restrict address, socklen_t address_len)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline int glt_syscall_poll(struct pollfd fds[], nfds_t nfds, int timeout)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline size_t glt_syscall_pread(int filedes, void *buf, size_t nbyte, 
        off_t offset)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline size_t glt_syscall_read(int filedes, void *buf, size_t nbyte)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline size_t glt_syscall_pwrite(int filedes, void *buf, size_t nbyte, 
        off_t offset)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline size_t glt_syscall_write(int filedes, void *buf, size_t nbyte)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline int glt_syscall_select(int nfds, fd_set *restrict readfds, 
        fd_set *restrict writefds, fd_set *restrict errorfds, 
        struct timeval *restrict timeout)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline int glt_syscall_system(const char * command)
{
    GLT_ERROR_QTH;
    return -1;
}

static inline int glt_syscall_wait4 (pid_t pid, int *stat_loc, int options, 
        struct rusage *rusage)
{
    GLT_ERROR_QTH;
    return -1;
}


static inline void glt_subthread_get_num(GLT_subthread *num)
{
    GLT_ERROR_QTH;
}

static inline void glt_cacheline(int *cl)
{
    GLT_ERROR_QTH;
}

static inline void glt_sorted_threads(const GLT_thread * list)
{
    GLT_ERROR_QTH;
}

static inline void glt_sorted_threads_remote(const GLT_thread * list, const GLT_thread src)
{
    GLT_ERROR_QTH;
}

static inline void glt_debuglevel(size_t *level, const enum introspective_state type)
{
    GLT_ERROR_QTH;
}

static inline void glt_readstate(size_t *value, const enum introspective_state type)
{
    GLT_ERROR_QTH;
}

static inline void glt_thread_distance(int * dist, const GLT_thread src, const GLT_thread dst)
{
    GLT_ERROR_QTH;
}

static inline void glt_thread_enable(GLT_thread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_thread_disable(GLT_bool *res, GLT_thread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_subthread_enable(GLT_subthread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_subthread_disable(GLT_bool *res, GLT_subthread id)
{
    GLT_ERROR_QTH;
}

static inline void glt_thread_ok(GLT_bool *res)
{
    GLT_ERROR_QTH;
}


static inline void * glt_memory_make_stat_map(const off_t filesize, void *addr,
        const char *filename, size_t itemsize, const size_t streams)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

static inline void * glt_memory_make_dyn_map(const off_t filesize, void *addr,
        const char *filename,  const size_t streams)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

static inline void * glt_memory_load_map(const char *filename)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

static inline void * glt_memory_malloc(void *map, size_t size)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

static inline void * glt_memory_stat_malloc(struct mapinfo_s *map)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

static inline void * glt_memory_dyn_malloc(struct dynmapinfo_s *map, size_t size)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

static inline void glt_memory_free(void *block, void * map)
{
    GLT_ERROR_QTH;
}

static inline void glt_memory_stat_free(void *block, struct mapinfo_s *map)
{
    GLT_ERROR_QTH;
}

static inline void glt_memory_dyn_free(void *block, struct dynmapinfo_s *map)
{
    GLT_ERROR_QTH;
}

static inline void glt_memory_cleanup()
{
    GLT_ERROR_QTH;
}

static inline void glt_memory_checkpoint()
{
    GLT_ERROR_QTH;
}

#endif


#endif	/* FAST_GLT_H */

