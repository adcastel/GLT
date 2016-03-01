/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */


#ifndef GLT_H
#define	GLT_H


#include <stdio.h>
#include <stdlib.h>
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

#define GLT_VERSION "You are using glt 0.1v over Qthreads (adcastel@uji.es)"
#define GLT_ERROR_ARG "Error: This feature is only supported by Argobots implementation and you are using MassiveThreads. Please use the query functions"

/* Main team structure*/

glt_team_t * main_team;


void __attribute__((constructor)) glt_start(void);
void __attribute__((destructor)) glt_end(void);


void glt_init(int argc, char * argv[]);
void glt_finalize();

GLT_ult * glt_ult_malloc(int number_of_ult);
GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets);

void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult);
void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest);

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult);
void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest);

void glt_yield();
void glt_yield_to(GLT_ult ult);

void glt_ult_join(GLT_ult *ult);
void glt_tasklet_join(GLT_tasklet *tasklet);

uint64_t glt_get_ult_id(GLT_ult ult);

void glt_mutex_create(GLT_mutex * mutex);
void glt_mutex_lock(GLT_mutex mutex);
void glt_mutex_unlock(GLT_mutex mutex);
void glt_mutex_free(GLT_mutex * mutex);

void glt_barrier_create(int num_waiters, GLT_barrier *barrier);
void glt_barrier_free(GLT_barrier *barrier);
void glt_barrier_wait(GLT_barrier *barrier);

void glt_cond_create(GLT_cond *cond);
void glt_cond_free(GLT_cond *cond);
void glt_cond_signal(GLT_cond cond);
void glt_cond_wait(GLT_cond cond, GLT_mutex mutex);
void glt_cond_broadcast(GLT_cond cond);

double glt_get_wtime();
void glt_timer_create(GLT_timer * timer);
void glt_timer_free(GLT_timer * timer);
void glt_timer_start(GLT_timer timer);
void glt_timer_stop(GLT_timer timer);
void glt_timer_get_secs(GLT_timer timer, double *secs);

int glt_get_thread_num();
int glt_get_num_threads();

//QUERY functions for ARGOBOTS
//Always return 0;
int glt_can_event_functions();
int glt_can_future_functions();
int glt_can_promise_functions();
int glt_can_tls_functions();
int glt_can_extended_mutex();
int glt_can_manage_pools();
int glt_can_manage_scheduler();
int glt_can_self();
int glt_can_manage_threads();
int can_extended_tasklets();
int can_extended_ults();






#ifndef CORE

//HEADERS for ARGOBOTS extended functions
//Null codes
void glt_get_error_str(int errno, char *str, size_t *len);
void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id);
void glt_event_del_callback(GLT_event_kind event, int cb_id);

void glt_future_create(int nbytes, GLT_future *newfuture);
void glt_future_free(GLT_future *future);
void glt_future_wait(GLT_future future, void **value);
void glt_future_set(GLT_future future, void *value, int nbytes);

void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise);
void glt_promise_free(GLT_promise *promise);
void glt_promise_wait(GLT_promise promise);
void glt_promise_test(GLT_promise promise, GLT_bool *flag);
void glt_promise_set(GLT_promise promise, void * value);

void glt_key_create(void(*destructor)(void *value), GLT_key *newkey);
void glt_key_free(GLT_key *key);
void glt_key_set(GLT_key key, void *value);
void glt_key_get(GLT_key key, void **value);

void glt_mutex_lock_low(GLT_mutex mutex);
void glt_mutex_trylock(GLT_mutex mutex);
void glt_mutex_spinlock(GLT_mutex mutex);
void glt_mutex_unlock_se(GLT_mutex mutex);
void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result);

void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool);
void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool);
void glt_pool_free(GLT_pool *pool);
void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access);
void glt_pool_get_total_size(GLT_pool pool, size_t *size);
void glt_pool_get_size(GLT_pool pool, size_t *size);
void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit);
void glt_pool_push(GLT_pool pool, GLT_unit p_unit);
void glt_pool_remove(GLT_pool pool, GLT_unit p_unit);
void glt_pool_set_data(GLT_pool pool, void *data);
void glt_pool_get_data(GLT_pool pool, void **data);
void glt_pool_add_sched(GLT_pool pool, GLT_sched sched);
void glt_pool_get_id(GLT_pool pool, int *id);

void glt_scheduler_config_free(GLT_sched_config *config);
void glt_scheduler_create(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched);
void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched);
void glt_scheduler_free(GLT_sched *sched);
void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools);
void glt_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools);
void glt_scheduler_finish(GLT_sched sched);
void glt_scheduler_exit(GLT_sched sched);
void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop);
void glt_scheduler_set_data(GLT_sched sched, void *data);
void glt_scheduler_get_data(GLT_sched sched, void **data);
void glt_scheduler_get_size(GLT_sched sched, size_t *size);
void glt_scheduler_get_total_size(GLT_sched sched, size_t *size);

void glt_self_get_type(GLT_unit_type *type);
void glt_self_is_primary(GLT_bool *flag);
void glt_self_on_primary_xstream(GLT_bool *flag);
void glt_self_get_last_pool_id(int *pool_id);
void glt_self_suspend(void);
void glt_self_get_arg(void **arg);

void glt_thread_create(GLT_sched sched, GLT_thread *newthread);
void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread);
void glt_thread_start(GLT_thread thread);
void glt_thread_free(GLT_thread *thread);
void glt_thread_join(GLT_thread thread);
void glt_thread_exit();
void glt_thread_cancel(GLT_thread *thread);
void glt_thread_self(GLT_thread *thread);
void glt_thread_self_rank(int *rank);
void glt_thread_get_rank(GLT_thread thread, int *rank);
void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched);
void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools);
void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched);
void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools);
void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state);
void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result);
void glt_thread_get_num(int *num_xstreams);
void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag);
void glt_thread_run_unit(GLT_unit unit, GLT_pool pool);
void glt_thread_check_events(GLT_sched sched);

 void glt_tasklet_cancel (GLT_tasklet tasklet);
 void glt_tasklet_self(GLT_tasklet *tasklet);
 void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread);
 void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state);
 void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool);
 void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id);
 void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag);
 void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag);
 void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result);
 void glt_tasklet_retain(GLT_tasklet tasklet);
 void glt_tasklet_release(GLT_tasklet tasklet);
 void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg);
 
 void glt_ult_exit();
 void glt_ult_cancel(GLT_ult ult);
 void glt_ult_self(GLT_ult *ult);
 void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state);
 void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool);
 void glt_ult_get_last_pool_id(GLT_ult ult, int *id);
 void glt_ult_resume(GLT_ult ult);
 void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread);
 void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched);
 void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool);
 void glt_ult_migrate(GLT_ult ult);
 void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg);
 void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag);
 void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag);
 void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag);
 void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result);
 void glt_ult_retain(GLT_ult ult);
 void glt_ult_release(GLT_ult ult);
 void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize);
 void glt_ult_get_id(GLT_ult ult, GLT_ult_id *ult_id);
 void glt_ult_get_arg(GLT_ult ult, void **arg);
 void glt_ult_attr_create (GLT_ult_attr *newattr);
 void glt_ult_attr_free(GLT_ult_attr *attr);
 void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize);
 void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize);
 void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg);
 void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag);
#endif

#endif	/* glt_H */

