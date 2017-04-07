/* See COPYRIGHT in top-level directory. */
/*
 * Function header file.
 */


#ifndef GLT_H
#define GLT_H


/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif

#include <glt_common.h>


void __attribute__((constructor)) glt_start(void);
void __attribute__((destructor)) glt_end(void);


void glt_init(int argc, char * argv[]);
void glt_finalize();

glt_team_t * glt_get_team();

GLT_ult * glt_ult_malloc(int number_of_ult);
GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets);

void glt_ult_create(void(*thread_func)(void *), void *arg, GLT_ult *new_ult);
void glt_ult_create_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest);

void glt_tasklet_create(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult);
void glt_tasklet_create_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest);

void glt_yield();
void glt_yield_to(GLT_ult ult);

void glt_ult_join(GLT_ult *ult);
void glt_tasklet_join(GLT_tasklet *tasklet);
void glt_ult_free(GLT_ult *ult);
void glt_tasklet_free(GLT_tasklet *tasklet);

void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult);
void glt_workunit_get_thread_id(GLT_thread_id *id);
void glt_ult_migrate_self_to(GLT_thread_id id);

void glt_tasklet_self(GLT_tasklet *tasklet);
void glt_ult_self(GLT_ult *ult);

void glt_ult_exit();
void glt_ult_cancel(GLT_ult ult);
void glt_tasklet_cancel(GLT_tasklet tasklet);

void glt_mutex_create(GLT_mutex * mutex);
void glt_mutex_lock(GLT_mutex mutex);
void glt_mutex_unlock(GLT_mutex mutex);
void glt_mutex_free(GLT_mutex * mutex);
int glt_mutex_trylock(GLT_mutex mutex);
void glt_mutex_spinlock(GLT_mutex mutex);


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


void glt_key_create(void(*destructor)(void *value), GLT_key *newkey);
void glt_key_free(GLT_key *key);
void glt_key_set(GLT_key key, void *value);
void glt_key_get(GLT_key key, void **value);

int glt_can_event_functions();
int glt_can_future_functions();
int glt_can_scheduler();
int glt_can_malleability();


#ifndef CORE

void glt_scheduler_config_free(GLT_sched_config *config);
void glt_scheduler_create(GLT_sched_def *def, int num_threads,
        int *threads_id, GLT_sched_config config, GLT_sched *newsched);
void glt_scheduler_create_basic(GLT_sched_predef predef,
        int num_threads, int *threads_id, GLT_sched_config config,
        GLT_sched *newsched);
void glt_scheduler_free(GLT_sched *sched);
void glt_scheduler_finish(GLT_sched sched);
void glt_scheduler_exit(GLT_sched sched);
void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop);
void glt_scheduler_set_data(GLT_sched sched, void *data);
void glt_scheduler_get_data(GLT_sched sched, void **data);
void glt_scheduler_get_size(GLT_sched sched, size_t *size);
void glt_scheduler_get_total_size(GLT_sched sched, size_t *size);


void glt_get_error_str(int errno, char *str, size_t *len);
void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id);
void glt_event_del_callback(GLT_event_kind event, int cb_id);

void glt_future_create(int nbytes, GLT_future *newfuture);
void glt_future_free(GLT_future *future);
void glt_future_wait(GLT_future future, void **value);
void glt_future_set(GLT_future future, void *value, int nbytes);

void glt_key_create(void(*destructor)(void *value), GLT_key *newkey);
void glt_key_free(GLT_key *key);
void glt_key_set(GLT_key key, void *value);
void glt_key_get(GLT_key key, void **value);

void glt_thread_enable();
void glt_thread_disable();
void glt_thread_enable_id(int thread_id);
void glt_thread_disable_id(int thread_id);

#endif

#if defined(__cplusplus)
}
#endif

#endif /* glt_H */

