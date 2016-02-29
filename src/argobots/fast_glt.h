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
#include <abt.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define GLT_ult ABT_thread
#define GLT_tasklet ABT_task
#define GLT_thread ABT_xstream
#define GLT_mutex ABT_mutex
#define GLT_barrier ABT_barrier
#define GLT_cond ABT_cond
//Extended variables
#ifndef CORE
#define GLT_event_kind ABT_event_kind
#define GLT_event_cb_fn ABT_event_cb_fn
#define GLT_future ABT_eventual
#define GLT_promise ABT_future
#define GLT_bool ABT_bool
#define GLT_key ABT_key
#define GLT_pool_def ABT_pool_def
#define GLT_pool_config ABT_pool_config
#define GLT_pool ABT_pool
#define GLT_pool_kind ABT_pool_kind
#define GLT_pool_access ABT_pool_access
#define GLT_unit ABT_unit
#define GLT_sched ABT_sched
#define GLT_sched_config ABT_sched_config
#define GLT_sched_def ABT_sched_def
#define GLT_sched_predef ABT_sched_predef
#define GLT_thread_state ABT_xstream_state
#define GLT_tasklet_state ABT_task_state
#define GLT_ult_state ABT_thread_state
#define GLT_ult_id ABT_thread_id
#define GLT_ult_attr ABT_thread_attr
#define GLT_timer ABT_timer
#define GLT_unit_type ABT_unit_type
 

#define glt_scheduler_config_create ABT_sched_config_create
#define glt_scheduler_config_read ABT_sched_config_read
#endif

typedef struct glt_team {
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
} glt_team_t;



#define GLT_VERSION "You are using fast glt 0.1v over Argobots(adcastel@uji.es)"
/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

//Core functions


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
    int num_threads = 1;
    int num_pools = 1;

    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    ABT_init(argc, argv);

    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
    }

    if (getenv("GLT_NUM_POOLS") != NULL) {
        num_pools = atoi(getenv("GLT_NUM_POOLS"));
    }

    ABT_xstream_self(&main_team->master);

    main_team->num_xstreams = num_threads;
    main_team->num_pools = num_pools;
    main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * MIN(num_threads,36));
    main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * MIN(num_threads,36));

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

static inline uint64_t glt_get_ult_id(GLT_ult ult)
{
    uint64_t id;
    ABT_thread_get_id (ult, &id);
    return id;
}

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

//Extended functions


//Event functions
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

//future functions
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

//tls functions
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

//extended mutex functions
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
    ABT_mutex_lock_low (mutex);
} 

static inline void glt_mutex_trylock(GLT_mutex mutex)
{
    ABT_mutex_trylock (mutex);
}

static inline void glt_mutex_spinlock (GLT_mutex mutex)
{
    ABT_mutex_spinlock (mutex);
}

static inline void glt_mutex_unlock_se (GLT_mutex mutex)
{
    ABT_mutex_unlock_se (mutex);
}

static inline void glt_mutex_equal (GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result)
{
    ABT_mutex_equal (mutex1, mutex2, result);
}
#endif

//pools functions

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
    ABT_pool_create (def, config, newpool);
    main_team->pools[main_team->num_pools]=newpool;
    main_team->num_pools++;
}

static inline void glt_pool_create_basic (GLT_pool_kind kind, 
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    ABT_pool_create_basic (kind, access, automatic, newpool);
    main_team->pools[main_team->num_pools]=newpool;
    main_team->num_pools++;
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

//scheduler functions


static inline int glt_can_manage_scheduler()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


/*static inline void glt_scheduler_config_create(GLT_sched_config *config,...)
{
    va_list args;
    va_start(args, config);
    
    ABT_sched_config_create (config,...);	
    va_end(args);
    
}*/

/*static inline void glt_scheduler_config_read(GLT_sched_config config, int num_vars, ...)
{
    ABT_sched_config_read (config, num_vars,...);
}*/

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

static inline void glt_scheduler_get_data(ABT_sched sched, void **data)
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

//self functions

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

//threads functions


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
    ABT_xstream_create (sched, newthread);
    main_team->team[main_team->num_xstreams]=newthread;
    main_team->num_xstreams++;
}

static inline void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    ABT_xstream_create_basic (predef, num_pools, pools, config, newthread);
    main_team->team[main_team->num_xstreams]=newthread;
    main_team->num_xstreams++;
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

//tasklets functions

static inline int can_extended_tasklets()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

static inline void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    ABT_task_cancel (tasklet);
}

static inline void glt_tasklet_self(GLT_tasklet *tasklet)
{
    ABT_task_self (tasklet);
}

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
static inline void glt_ult_exit()
{
    ABT_thread_exit ();
}

static inline void glt_ult_cancel(GLT_ult ult)
{
    ABT_thread_cancel (ult);
}

static inline void glt_ult_self(GLT_ult *ult)
{
    ABT_thread_self (ult);
}

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

static inline void glt_ult_get_id(GLT_ult ult, GLT_ult_id *ult_id)
{
    ABT_thread_get_id (ult, ult_id);
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
#endif /*#ifndef CORE*/

#endif	/* FAST_GLT_H */

