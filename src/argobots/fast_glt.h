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



#define GLT_ult ABT_thread
#define GLT_tasklet ABT_task
#define GLT_thread ABT_xstream
#define GLT_mutex ABT_mutex
#define GLT_barrier ABT_barrier
#define GLT_cond ABT_cond
//Extended variables
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
    main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * num_threads*2);
    main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * num_pools*2);

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

static inline void glt_get_error_str(int errno, char *str, size_t *len)
{
    ABT_error_get_str (errno,str,len);
}

static inline int glt_can_event_functions()
{
    return 1;
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

static inline int glt_can_future_functions()
{
    return 1;
}

static inline void glt_future_create (int nbytes, GLT_future *newfuture)
{
    ABT_eventual_create (nbytes, newfuture);
}

static inline glt_future_free (GLT_future *future)
{
    ABT_eventual_free (future);
}

static inline glt_future_wait (GLT_future future, void **value)
{
    ABT_eventual_wait (future, value);
}

static inline glt_future_set (GLT_future future, void *value, int nbytes)
{
    ABT_eventual_set (future, value, nbytes);
}

static inline int glt_can_promise_functions()
{
    return 1;
}

static inline void glt_promise_create (uint32_t compartments, 
        void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    ABT_future_create (compartments, cb_func(arg), newpromise);
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

static inline int glt_can_tls_functions()
{
    return 1;
}

static inline void glt_key_create (void(*destructor)(void *value), GLT_key *newkey)
{
    ABT_key_create ((destructor)(value),newkey);
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

static inline int glt_can_extended_mutex()
{
    return 1;
}

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

static inline int glt_can_manage_pools()
{
    return 1;
}

static inline void glt_pool_create (GLT_pool_def *def, Glt_pool_config config, 
        GLT_pool *newpool)
{
    ABT_pool_create (def, config, newpool);
    main_team->pools[num_pools]=newpool;
    num_pools++;
}

static inline void glt_pool_create_basic (GLT_pool_kind kind, 
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    ABT_pool_create_basic (kind, access, automatic, newpool);
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
#endif	/* FAST_GLT_H */

