/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H


#include <glt_common.h>

//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/sysinfo.h>
//#include <abt.h>
//
//#define MIN(a,b) (((a)<(b))?(a):(b))
//#define MAX(a,b) (((a)>(b))?(a):(b))
//
//#define GLT_ult ABT_thread
//#define GLT_tasklet ABT_task
//#define GLT_thread ABT_xstream
//#define GLT_mutex ABT_mutex
//#define GLT_barrier ABT_barrier
//#define GLT_cond ABT_cond
//#define GLT_timer ABT_timer
//#define GLT_bool ABT_bool
//#define GLT_thread_id int
//#define GLT_ult_id ABT_thread_id
//
//
////Extended variables
//#ifndef CORE
//#define GLT_event_kind ABT_event_kind
//#define GLT_event_cb_fn ABT_event_cb_fn
//#define GLT_future ABT_eventual
//#define GLT_promise ABT_future
//#define GLT_pool_def ABT_pool_def
//#define GLT_pool_config ABT_pool_config
//#define GLT_pool ABT_pool
//#define GLT_pool_kind ABT_pool_kind
//#define GLT_pool_access ABT_pool_access
//#define GLT_unit ABT_unit
//#define GLT_sched ABT_sched
//#define GLT_sched_config ABT_sched_config
//#define GLT_sched_def ABT_sched_def
//#define GLT_sched_predef ABT_sched_predef
//#define GLT_thread_state ABT_xstream_state
//#define GLT_tasklet_state ABT_task_state
//#define GLT_ult_state ABT_thread_state
//#define GLT_ult_attr ABT_thread_attr
//#define GLT_unit_type ABT_unit_type
// 
//
//#define glt_scheduler_config_create (config,...) ABT_sched_config_create(config,...)
//#define glt_scheduler_config_read (config, num_vars,...) ABT_sched_config_read (config, num_vars,...)
//
////MASSIVETHREAD
//#define GLT_workunit_f void *
//#define GLT_workunit_o void *
//#define GLT_felock void *
//#define GLT_felock_status int
//#define GLT_pickle void *
//#define GLT_wsapi_decide_f void *
//#define GLT_wsapi_steal_f void *
////Shared
//#define GLT_key ABT_key
//
//
////QTHREADS
//#include <sys/socket.h>
//#include <poll.h>
//#include <sys/resource.h>
//
//#define aligned_t long unsigned int
//typedef enum introspective_state {NOT_SUPPORTED} introspective_state;
//
//typedef struct mapinfo_s {
//    int not_supported;
//}mapinfo_s_t;
//
//typedef struct dynmapinfo_s {
//    int not_supported;
//}dynmapinfo_s_t;
//
//#define GLT_syncvar void *
//#define GLT_aligned void *
//#define GLT_memory_state void *
//#define GLT_sinc_op void *
//#define GLT_sinc void *
//#define GLT_loop_f void *
//#define GLT_loopr_f void *
//#define GLT_loop_step_f void *
//#define GLT_accum_f void *
//#define GLT_loop_queue void *
//#define GLT_loop_queue_kind void *
//#define GLT_ds_pool void *
//#define GLT_ds_array void *
//#define GLT_ds_array_distribution void *
//#define GLT_ds_loop_f void *
//#define GLT_ds_loopr_f void *
//#define GLT_ds_cloop_f void *
//#define GLT_ds_lfqueue void *
//#define GLT_ds_dqueue void *
//#define GLT_ds_dictionary void *
//#define GLT_ds_dictionary_key_equals void *
//#define GLT_ds_dictionary_hash void *
//#define GLT_ds_dictionary_cleanup void *
//#define GLT_ds_dictionary_it void *
//#define GLT_subthread void *
//
//#define glt_ult_creation_precond(f,a,u,n,...) qthread_fork_precond(f,a,u,n,...)
//#define glt_ult_creation_precond_to(f,a,u,d,n,...) qthread_fork_precond_to(f,a,u,d,n,...)
//
//#endif
//
//typedef struct glt_team {
//    ABT_xstream master;
//    ABT_xstream *team;
//    int num_xstreams;
//    int num_pools;
//    ABT_pool *pools;
//    int max_elem;
//} glt_team_t;
//
//
//
//#define GLT_VERSION "You are using fast glt 0.1v over Argobots(adcastel@uji.es)"
//
//#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads \
//    implementation and you are using Argobots. Please use the query functions")
//#define GLT_ERROR_MYTH printf("Error: This feature is only supported by MassiveThredashreads \
//    implementation and you are using Argobots. Please use the query functions")
/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

//glt_team_t * main_team;

//Core functions

#include <glt.c>
/*
static inline void glt_start() 
{
     printf("Starting with ARGOBOTS\n");
}
static inline  void glt_end() 
{
    printf("Ending with ARGOBOTS\n");
}

static inline void glt_init(int argc, char * argv[]) 
{
    int num_threads = get_nprocs();

    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));
    ABT_init(argc, argv);

    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
    }

    int num_pools = num_threads;

    if (getenv("GLT_NUM_POOLS") != NULL) {
        num_pools = atoi(getenv("GLT_NUM_POOLS"));
    }

    ABT_xstream_self(&main_team->master);

    main_team->num_xstreams = num_threads;
    main_team->num_pools = num_pools;
    main_team->max_elem= get_nprocs();//*2;
    main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * num_threads);
    main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * num_pools);

    for (int i = 0; i < num_pools; i++) {
        ABT_pool_create_basic(ABT_POOL_FIFO, ABT_POOL_ACCESS_MPMC, ABT_TRUE,
            &main_team->pools[i]);
    }

    ABT_xstream_self(&main_team->team[0]);
    ABT_xstream_set_main_sched_basic(main_team->team[0], ABT_SCHED_DEFAULT,
            1, &main_team->pools[0]);
    
    for (int i = 1; i < num_threads; i++) {
        ABT_xstream_create_basic(ABT_SCHED_DEFAULT, 1,
                &main_team->pools[i % main_team->num_pools],
                ABT_SCHED_CONFIG_NULL, &main_team->team[i]);
        ABT_xstream_start(main_team->team[i]);
    }

}

static inline void glt_finalize() 
{
    for (int i = 1; i < main_team->num_xstreams; i++) {
        ABT_xstream_join(main_team->team[i]);
        ABT_xstream_free(&main_team->team[i]);
    }
    ABT_finalize();
}
*/

#include <glt_wu.c>

/*
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
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
}

static inline void glt_yield() 
{
    ABT_thread_yield();
}

static inline void glt_yield_to(GLT_ult ult) 
{
    ABT_thread_yield_to(ult);
}

static inline void glt_ult_join(GLT_ult *ult) 
{
    ABT_thread_free(ult);
}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    ABT_task_free(tasklet);
}

static inline void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult)
{
    ABT_thread_get_id (ult, id);
}

static inline void glt_workunit_get_thread_id(GLT_thread_id *id)
{
    ABT_xstream_self_rank (id);
}

 static inline void glt_ult_migrate_self_to(GLT_thread_id id)
{
    GLT_ult ult;
    ABT_thread_self(&ult);
    ABT_thread_migrate_to_xstream (ult, main_team->team[id]);
}
 
static inline void glt_tasklet_self(GLT_tasklet *tasklet)
{
    ABT_task_self (tasklet);
}
static inline void glt_ult_self(GLT_ult *ult)
{
    ABT_thread_self (ult);
}


static inline void glt_ult_exit()
{
    ABT_thread_exit ();
}
static inline void glt_ult_cancel(GLT_ult ult)
{
    ABT_thread_cancel (ult);
}
static inline void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    ABT_task_cancel (tasklet);
}
*/

#include <glt_mutex.c>


/*
static inline void glt_mutex_create(GLT_mutex * mutex)
{
    ABT_mutex_create(mutex);
}

static inline void glt_mutex_lock(GLT_mutex mutex)
{
    ABT_mutex_lock(mutex);
}

static inline void glt_mutex_unlock(GLT_mutex mutex)
{
    ABT_mutex_unlock(mutex);
}

static inline void glt_mutex_free(GLT_mutex * mutex)
{
    ABT_mutex_free(mutex);
}

static inline void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex)
{
    *locked = ABT_mutex_trylock (mutex);
}
*/


#include <glt_barrier.c>

/*
static inline void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    ABT_barrier_create(num_waiters, barrier);
}

static inline void glt_barrier_free(GLT_barrier *barrier)
{
    ABT_barrier_free(barrier);
}

static inline void glt_barrier_wait(GLT_barrier *barrier)
{
    ABT_barrier_wait(*barrier);
}
*/

#include <glt_condition.c>
/*
static inline void glt_cond_create(GLT_cond *cond)
{
    ABT_cond_create (cond);
}

static inline void glt_cond_free(GLT_cond *cond)
{
    ABT_cond_free (cond);
}

static inline void glt_cond_signal(GLT_cond cond)
{
    ABT_cond_signal (cond);
}

static inline void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    ABT_cond_wait (cond, mutex);
}

static inline void glt_cond_broadcast(GLT_cond cond)
{
    ABT_cond_broadcast (cond);
}
*/

#include <glt_timer.c>

/*
static inline double glt_get_wtime() 
{
    return ABT_get_wtime();
}

static inline void glt_timer_create(GLT_timer * timer) 
{
    ABT_timer_create(timer);
}

static inline void glt_timer_free(GLT_timer * timer) 
{
    ABT_timer_free(timer);
}

static inline void glt_timer_start(GLT_timer timer) 
{
    ABT_timer_start(timer);
}

static inline void glt_timer_stop(GLT_timer timer) 
{
    ABT_timer_stop(timer);
}

static inline void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    ABT_timer_read(timer,secs);
}
*/

#include <glt_util.c>

/*
static inline int glt_get_num_threads() 
{
    return main_team->num_xstreams;
}

static inline int glt_get_thread_num() 
{
    int rank;
    ABT_xstream_self_rank(&rank);
    return rank;
}
*/
//Extended functions


//Event functions
#include <glt_event.c>

/*
static inline int glt_can_event_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
static inline void glt_get_error_str(int errno, char *str, size_t *len)
{
    ABT_error_get_str (errno,str,len);
}

static inline void glt_event_add_callbac (GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg, 
        int *cb_id)
{
    ABT_event_add_callback (event, ask_cb, ask_user_arg, act_cb, 
            act_user_arg, cb_id);
}

static inline void glt_event_del_callback (GLT_event_kind event, int cb_id)
{
    ABT_event_del_callback (event, cb_id);
}
#endif
*/

#include <glt_future_promise.c>

//future functions
/*
static inline int glt_can_future_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_future_create (int nbytes, GLT_future *newfuture)
{
    ABT_eventual_create (nbytes, newfuture);
}

static inline void glt_future_free (GLT_future *future)
{
    ABT_eventual_free (future);
}

static inline void glt_future_wait (GLT_future future, void **value)
{
    ABT_eventual_wait (future, value);
}

static inline void glt_future_set (GLT_future future, void *value, int nbytes)
{
    ABT_eventual_set (future, value, nbytes);
}
#endif

//promise functions
static inline int glt_can_promise_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_promise_create (uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    ABT_future_create (compartments, cb_func, newpromise);
}

static inline void glt_promise_free (GLT_promise *promise)
{
    ABT_future_free (promise);
}

static inline void glt_promise_wait (GLT_promise promise)
{
    ABT_future_wait (promise);
}

static inline void glt_promise_test (GLT_promise promise, GLT_bool *flag)
{
    ABT_future_test (promise,flag);
}

static inline void glt_promise_set (GLT_promise promise, void * value)
{
    ABT_future_set (promise,value);
}
#endif
*/
//tls functions

#include <glt_tls.c>
/*
static inline int glt_can_tls_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_key_create (void(*destructor)(void *value), GLT_key *newkey)
{
    ABT_key_create (destructor,newkey);
}

static inline void glt_key_free (GLT_key *key)
{
    ABT_key_free (key);
}

static inline void glt_key_set (GLT_key key, void *value)
{
    ABT_key_set (key,value);
}

static inline void glt_key_get (GLT_key key, void **value)
{
    ABT_key_get (key,value);
}
#endif
*/
//extended mutex functions

/*
static inline int glt_can_extended_mutex()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_mutex_lock_low(GLT_mutex mutex)
{
    //ABT_mutex_lock_low (mutex);
} 

static inline void glt_mutex_spinlock (GLT_mutex mutex)
{
    ABT_mutex_spinlock (mutex);
}

static inline void glt_mutex_unlock_se (GLT_mutex mutex)
{
    //ABT_mutex_unlock_se (mutex);
}

static inline void glt_mutex_equal (GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result)
{
    ABT_mutex_equal (mutex1, mutex2, result);
}
#endif

 */
//pools functions

#include <glt_pool.c>


/*
static inline int glt_can_manage_pools()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}
#ifndef CORE

static inline void glt_pool_create (GLT_pool_def *def, GLT_pool_config config, 
        GLT_pool *newpool)
{
    if(main_team->num_pools < main_team->max_elem){
        ABT_pool_create (def, config, newpool);
        main_team->pools[main_team->num_pools]=newpool;
        main_team->num_pools++;
    }
    else {
        printf("Error: There are not more sloots for pools\n");
    }
}

static inline void glt_pool_create_basic (GLT_pool_kind kind, 
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    if(main_team->num_pools < main_team->max_elem){
        ABT_pool_create_basic (kind, access, automatic, newpool);
        main_team->pools[main_team->num_pools]=newpool;
        main_team->num_pools++;
    }
    else {
        printf("Error: There are not more sloots for pools\n");
    }
}

static inline void glt_pool_free (GLT_pool *pool)
{
    ABT_pool_free (pool);
}

static inline void glt_pool_get_access (GLT_pool pool, GLT_pool_access *access)
{
    ABT_pool_get_access (pool, access);
}

static inline void glt_pool_get_total_size (GLT_pool pool, size_t *size)
{
    ABT_pool_get_total_size (pool, size);
}

static inline void glt_pool_get_size (GLT_pool pool, size_t *size)
{
    ABT_pool_get_size (pool, size);
}

static inline void glt_pool_pop (GLT_pool pool, GLT_unit *p_unit)
{
    ABT_pool_pop (pool,p_unit);
}

static inline void glt_pool_push (GLT_pool pool, GLT_unit p_unit)
{
    ABT_pool_push (pool,p_unit);
}

static inline void glt_pool_remove (GLT_pool pool, GLT_unit p_unit)
{
    ABT_pool_remove (pool,p_unit);
}

static inline void glt_pool_set_data (GLT_pool pool, void *data)
{
    ABT_pool_set_data (pool,data);
}

static inline void glt_pool_get_data (GLT_pool pool, void **data)
{
    ABT_pool_get_data (pool,data);
}

static inline void glt_pool_add_sched (GLT_pool pool, GLT_sched sched)
{
    ABT_pool_add_sched (pool, sched);
}

static inline void glt_pool_get_id (GLT_pool pool, int *id)
{
    ABT_pool_get_id (pool, id);
}
#endif
*/
//scheduler functions

#include <glt_scheduler.c>
/*
static inline int glt_can_manage_scheduler()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


//static inline void glt_scheduler_config_create(GLT_sched_config *config,...)
//{
//    va_list args;
//    va_start(args, config);
//    
//    ABT_sched_config_create (config,...);	
//    va_end(args);
//    
//}
//
//static inline void glt_scheduler_config_read(GLT_sched_config config, int num_vars, ...)
//{
//    ABT_sched_config_read (config, num_vars,...);
//}

static inline void glt_scheduler_config_free (GLT_sched_config *config)
{ 	
    ABT_sched_config_free (config);
}

static inline void glt_scheduler_create (GLT_sched_def *def, int num_pools, 
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched)
{
    ABT_sched_create (def, num_pools, pools, config, newsched);
}

static inline void glt_schededuler_create_basic (GLT_sched_predef predef, 
        int num_pools, GLT_pool *pools, GLT_sched_config config, 
        GLT_sched *newsched)
{
    ABT_sched_create_basic (predef, num_pools, pools, config, newsched);
}

static inline void glt_scheduler_free (GLT_sched *sched)
{
    ABT_sched_free (sched);
}

static inline void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools)
{
    ABT_sched_get_num_pools ( sched, num_pools);
}

static inline void glt_scheduler_get_pools(GLT_sched sched, int max_pools, 
        int idx, GLT_pool *pools)
{
    ABT_sched_get_pools ( sched, max_pools, idx, pools);
}

static inline void glt_scheduler_finish (GLT_sched sched)
{
    ABT_sched_finish (sched);
}

static inline void glt_scheduler_exit (GLT_sched sched)
{
    ABT_sched_exit (sched);
}

static inline void glt_scheduler_has_to_stop (GLT_sched sched, GLT_bool *stop)
{
    ABT_sched_has_to_stop (sched, stop);
}

static inline void glt_scheduler_set_data (GLT_sched sched, void *data)
{
    ABT_sched_set_data (sched,data);
}

static inline void glt_scheduler_get_data(GLT_sched sched, void **data)
{
    ABT_sched_get_data (sched, data);
}

static inline void glt_scheduler_get_size (GLT_sched sched, size_t *size)
{
    ABT_sched_get_size (sched, size);
}

static inline void glt_scheduler_get_total_size(GLT_sched sched, size_t *size)
{
    ABT_sched_get_total_size (sched, size);
}
#endif
*/
//self functions

#include<glt_self.c>

/*
static inline int glt_can_self()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_self_get_type (GLT_unit_type *type)
{
    ABT_self_get_type (type);
}
static inline void glt_self_is_primary (GLT_bool *flag)
{
    ABT_self_is_primary (flag);
}

static inline void glt_self_on_primary_xstream (GLT_bool *flag)
{
    ABT_self_on_primary_xstream (flag);
}

static inline void glt_self_get_last_pool_id (int *pool_id)
{
    ABT_self_get_last_pool_id (pool_id);
}

static inline void glt_self_suspend (void)
{
    ABT_self_suspend ();
}

static inline void glt_self_get_arg (void **arg)
{
    ABT_self_get_arg (arg);
}

#endif
*/
//threads functions
#include<glt_thread.c>
/*
static inline int glt_can_manage_threads()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_thread_create (GLT_sched sched, GLT_thread *newthread)
{

    if(main_team->num_xstreams < main_team->max_elem){
        ABT_xstream_create (sched, newthread);
        main_team->team[main_team->num_xstreams]=newthread;
        main_team->num_xstreams++;
    }
    else {
        printf("Error: There are not more sloots for threads\n");
    }
}

static inline void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    if(main_team->num_xstreams < main_team->max_elem){
        ABT_xstream_create_basic (predef, num_pools, pools, config, newthread);
        main_team->team[main_team->num_xstreams]=newthread;
        main_team->num_xstreams++;
    }
    else {
        printf("Error: There are not more sloots for threads\n");
    }
}

static inline void glt_thread_start(GLT_thread thread)
{
    ABT_xstream_start (thread);
}

static inline void glt_thread_free(GLT_thread *thread)
{
    ABT_xstream_free (thread);
}

static inline void glt_thread_join(GLT_thread thread)
{
    ABT_xstream_join (thread);
}

static inline void glt_thread_exit()
{
    ABT_xstream_exit ();
}

static inline void glt_thread_cancel(GLT_thread *thread)
{
    ABT_xstream_cancel (thread);
}

static inline void glt_thread_self(GLT_thread *thread)
{
    ABT_xstream_self (thread);
}

static inline void glt_thread_self_rank(int *rank)
{
    ABT_xstream_self_rank (rank);
}

static inline void glt_thread_get_rank(GLT_thread thread, int *rank)
{
    ABT_xstream_get_rank (thread, rank);
}

static inline void glt_thread_set_main_sched (GLT_thread thread, GLT_sched sched)
{
    ABT_xstream_set_main_sched (thread, sched);
}
static inline void glt_thread_set_main_sched_basic (GLT_thread thread, 
        GLT_sched_predef predef, int num_pools, GLT_pool *pools)
{
    ABT_xstream_set_main_sched_basic (thread, predef, num_pools, pools);
}

static inline void glt_thread_get_main_sched (GLT_thread thread, GLT_sched *sched)
{
    ABT_xstream_get_main_sched (thread, sched);
}

static inline void glt_thread_get_main_pools (GLT_thread thread, int max_pools, 
        GLT_pool *pools)
{
    ABT_xstream_get_main_pools (thread, max_pools, pools);
}

static inline void glt_thread_get_state (GLT_thread thread, GLT_thread_state *state)
{
    ABT_xstream_get_state (thread, state);
}

static inline void glt_thread_equal (GLT_thread thread1, GLT_thread thread2, GLT_bool *result)
{
    ABT_xstream_equal (thread1, thread2, result);
}

static inline void glt_thread_get_num (int *num_xstreams)
{
    ABT_xstream_get_num (num_xstreams);
}
 
static inline void glt_thread_is_primary (GLT_thread thread, GLT_bool *flag)
{
    ABT_xstream_is_primary (thread, flag);
}

static inline void glt_thread_run_unit (GLT_unit unit, GLT_pool pool)
{
    ABT_xstream_run_unit (unit,pool);
}

static inline void glt_thread_check_events(GLT_sched sched)
{
    ABT_xstream_check_events (sched);
}
#endif
*/
//tasklets functions
/*
static inline int can_extended_tasklets()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


static inline void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread)
{
    ABT_task_get_xstream (tasklet, thread);
}

static inline void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state)
{
    ABT_task_get_state (tasklet, state);
}
static inline void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool)
{
    ABT_task_get_last_pool (tasklet, pool);
}

static inline void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id)
{
    ABT_task_get_last_pool_id (tasklet, id);
}

static inline void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag)
{
    ABT_task_set_migratable (tasklet, flag);
}

static inline void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag)
{
    ABT_task_is_migratable (tasklet, flag);
}

static inline void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result)
{
    ABT_task_equal (tasklet1, tasklet2, result);
}

static inline void glt_tasklet_retain(GLT_tasklet tasklet)
{
    ABT_task_retain (tasklet);
}

static inline void glt_tasklet_release(GLT_tasklet tasklet)
{
    ABT_task_release (tasklet);
}

static inline void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg)
{
    ABT_task_get_arg (tasklet, arg);
}

#endif

// ult functions

static inline int can_extended_ults()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


static inline void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state)
{
    ABT_thread_get_state (ult, state);
}

static inline void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool)
{
    ABT_thread_get_last_pool (ult, pool);
}

static inline void glt_ult_get_last_pool_id(GLT_ult ult, int *id)
{
    ABT_thread_get_last_pool_id (ult, id);
}

static inline void glt_ult_resume(GLT_ult ult)
{
    ABT_thread_resume (ult);
}

static inline void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread)
{
    ABT_thread_migrate_to_xstream (ult, thread);
}

static inline void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched)
{
    ABT_thread_migrate_to_sched (ult, sched);
}

static inline void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool)
{
    ABT_thread_migrate_to_pool (ult, pool);
}

static inline void glt_ult_migrate(GLT_ult ult)
{
    ABT_thread_migrate (ult);
}

static inline void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    ABT_thread_set_callback (ult, cb_func, cb_arg);
}

static inline void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag)
{
    ABT_thread_set_migratable (ult, flag);
}

static inline void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag)
{
    ABT_thread_is_migratable (ult, flag);
}

static inline void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag)
{
    ABT_thread_is_primary (ult, flag);
}

static inline void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result)
{
    ABT_thread_equal (ult1, ult2, result);
}

static inline void glt_ult_retain(GLT_ult ult)
{
    ABT_thread_retain (ult);
}

static inline void glt_ult_release(GLT_ult ult)
{
    ABT_thread_release (ult);
}

static inline void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize)
{
    ABT_thread_get_stacksize (ult, stacksize);
}

static inline void glt_ult_get_arg(GLT_ult ult, void **arg)
{
    ABT_thread_get_arg (ult, arg);
}

static inline void glt_ult_attr_create (GLT_ult_attr *newattr)
{
    ABT_thread_attr_create (newattr);
}

static inline void glt_ult_attr_free(GLT_ult_attr *attr)
{
    ABT_thread_attr_free (attr);
}

static inline void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize)
{
    ABT_thread_attr_set_stacksize ( attr,  stacksize);
}

static inline void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize)
{
    ABT_thread_attr_get_stacksize ( attr, stacksize);
}

static inline void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{ 
    ABT_thread_attr_set_callback ( attr, cb_func, cb_arg);
}

static inline void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag)
{
    ABT_thread_attr_set_migratable ( attr,  flag);
}
#endif 
*/
//MASSIVETHREADS functions that are not supported by Argobots

#include <glt_massivethreads.c>
/*
static inline int glt_can_wsapi_functions()
{
    return 0;
}

static inline int glt_can_prof_functions()
{
    return 0;
}

static inline int glt_can_log_functions()
{
    return 0;
}

static inline int glt_can_serialize_functions()
{
    return 0;
}

static inline int can_felock_functions()
{
    return 0;
}

static inline int can_extended_workunits()
{
    return 0;
}

#ifndef CORE

static inline   void glt_wu_create_ex(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt)
  {
      GLT_ERROR_MYTH;
  }
  
static inline  void glt_wu_create_nosched(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_yield2()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_detach(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_set_cancel_state(int state, int *oldstate)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_set_cancel_type(int type, int *oldtype)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_test_cancel()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_set_def_stack_size(size_t newsize)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_steal(GLT_ult * ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_import(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_ext_import(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_release_stack(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wu_release_desc(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }
 
static inline   void glt_felock_create(GLT_felock * felock)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_felock_free(GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_felock_lock(GLT_bool *lock, GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_felock_wait_lock(GLT_bool *lock, GLT_felock felock, int val)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_felock_unlock(GLT_bool *unlock, GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_felock_status(GLT_felock_status *status, GLT_felock felock)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_felock_set_unlock(GLT_felock felock, int val)
  {
      GLT_ERROR_MYTH;
  }

static inline   void glt_serialize(GLT_ult ult, GLT_pickle pickle)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_deserialize(GLT_ult *ult, GLT_pickle pickle)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_ext_deserialize(GLT_ult *ult, GLT_pickle pickle)
  {
      GLT_ERROR_MYTH;
  }
 
static inline  void glt_log_start()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_log_pause()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_log_flush()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_log_reset()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_log_annotate_ult(GLT_ult ult, char *name)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_sched_prof_start()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_sched_prof_pause()
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_runqueue_peek(GLT_ult *ult, int victim,void *ptr,size_t *psize)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_get_hint_size(size_t *size, GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_get_hint_ptr(void *ptr, GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_set_hint(GLT_ult ult,void **data,size_t *size)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_rand(int * rand)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_randrr(int *ret, int n)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_runqueue_take(GLT_ult * ult, int victim,GLT_wsapi_decide_f decidefn,void *udata)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_runqueue_pass(GLT_bool *pass, int target,GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_runqueue_push(GLT_ult ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_runqueue_pop(GLT_ult * ult)
  {
      GLT_ERROR_MYTH;
  }

static inline  void glt_wsapi_rand2(int * rand_value, int min, int max)
  {
      GLT_ERROR_MYTH;
  }

 static inline void glt_wsapi_set_stealfunc(GLT_wsapi_steal_f *out, GLT_wsapi_steal_f fn)
  {
      GLT_ERROR_MYTH;
  }
 
#endif
*/
//QTHREADS functions that are not supported by Argobots

#include <glt_qthreads.c>
/*
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


//static inline void glt_ult_creation_precond(void(*thread_func)(void *), void * arg,
//        GLT_ult * ult, int npreconds, ...){
//    qthread_fork_precond((void *)thread_func,arg,ult,npreconds,...);
//}
//
//static inline void glt_ult_creation_precond_to(void(*thread_func)(void *), void * arg,
//        GLT_ult * ult, int dest,int npreconds, ...){
//    qthread_fork_precond_to((void *)thread_func,arg,ult,dest,npreconds,...);
//}
//
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

//static inline void glt_loop_future(const size_t start, const size_t end, 
//         const GLT_loop_f func, void * arg)
//{
//    GLT_ERROR_QTH;
//}
//
//static inline void glt_loop_step_future(const size_t start, const size_t end, 
//        const size_t stride, const GLT_loop_step_f func, void * arg)
//{
//    GLT_ERROR_QTH;
//}
//
static inline void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

//static inline void glt_loop_balance_future(const size_t start, const size_t end, 
//         const GLT_loop_f func, void * arg)
//{
//    GLT_ERROR_QTH;
//}
//
static inline void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc)
{
    GLT_ERROR_QTH;
}

//static inline void glt_loopaccum_balance_future(const size_t start, const size_t end, 
//size_t size, void *out, const GLT_loop_f func, void * arg, GLT_accum_f acc)
//{
//    GLT_ERROR_QTH;
//}
//

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
*/

#endif	/* FAST_GLT_H */

