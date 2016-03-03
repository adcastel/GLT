/*
 * This file includes all the functions that are supported by Argobots but not 
 * by the other implementations. They are necessary for not obtaining a 
 * compilation error. However, they are empty functions.
 */
#include<glt.h>

int glt_can_event_functions()
{
    return 0;
}
int glt_can_future_functions()
{
    return 0;
}
int glt_can_promise_functions()
{
    return 0;
}
int glt_can_tls_functions()
{
    return 0;
}
int glt_can_extended_mutex()
{
    return 0;
}
int glt_can_manage_pools()
{
    return 0;
}
int glt_can_manage_scheduler()
{
    return 0;
}
int glt_can_self()
{
    return 0;
}
int glt_can_manage_threads()
{
    return 0;
}
int can_extended_tasklets()
{
    return 0;
}
int can_extended_ults()
{
    return 0;
}

#ifndef CORE

//HEADERS for ARGOBOTS extended functions
//Null codes
void glt_get_error_str(int errno, char *str, size_t *len)
{
    GLT_ERROR_ARG;
}

void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id)
{
    GLT_ERROR_ARG;
}

void glt_event_del_callback(GLT_event_kind event, int cb_id)
{
    GLT_ERROR_ARG;
}

void glt_future_create(int nbytes, GLT_future *newfuture)
{
    GLT_ERROR_ARG;
}

void glt_future_free(GLT_future *future)
{
    GLT_ERROR_ARG;
}
void glt_future_wait(GLT_future future, void **value)
{
    GLT_ERROR_ARG;
}
void glt_future_set(GLT_future future, void *value, int nbytes)
{
    GLT_ERROR_ARG;
}

void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    GLT_ERROR_ARG;
}

void glt_promise_free(GLT_promise *promise)
{
    GLT_ERROR_ARG;
}

void glt_promise_wait(GLT_promise promise)
{
    GLT_ERROR_ARG;
}

void glt_promise_test(GLT_promise promise, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

void glt_promise_set(GLT_promise promise, void * value)
{
    GLT_ERROR_ARG;
}

void glt_key_create(void(*destructor)(void *value), GLT_key *newkey)
{
    GLT_ERROR_ARG;
}

void glt_key_free(GLT_key *key)
{
    GLT_ERROR_ARG;
}

void glt_key_set(GLT_key key, void *value)
{
    GLT_ERROR_ARG;
}

void glt_key_get(GLT_key key, void **value)
{
    GLT_ERROR_ARG;
}

void glt_mutex_lock_low(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

void glt_mutex_trylock(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

void glt_mutex_spinlock(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

void glt_mutex_unlock_se(GLT_mutex mutex)
{
    GLT_ERROR_ARG;
}

void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result)
{
    GLT_ERROR_ARG;
}

void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool)
{
    GLT_ERROR_ARG;
}

void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    GLT_ERROR_ARG;
}

void glt_pool_free(GLT_pool *pool)
{
    GLT_ERROR_ARG;
}

void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access)
{
    GLT_ERROR_ARG;
}

void glt_pool_get_total_size(GLT_pool pool, size_t *size)
{
    GLT_ERROR_ARG;
}

void glt_pool_get_size(GLT_pool pool, size_t *size)
{
    GLT_ERROR_ARG;
}

void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit)
{
    GLT_ERROR_ARG;
}

void glt_pool_push(GLT_pool pool, GLT_unit p_unit)
{
    GLT_ERROR_ARG;
}

void glt_pool_remove(GLT_pool pool, GLT_unit p_unit)
{
    GLT_ERROR_ARG;
}

void glt_pool_set_data(GLT_pool pool, void *data)
{
    GLT_ERROR_ARG;
}

void glt_pool_get_data(GLT_pool pool, void **data)
{
    GLT_ERROR_ARG;
}

void glt_pool_add_sched(GLT_pool pool, GLT_sched sched)
{
    GLT_ERROR_ARG;
}

void glt_pool_get_id(GLT_pool pool, int *id)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_config_free(GLT_sched_config *config)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_create(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched)
{
    GLT_ERROR_ARG;
}

void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_free(GLT_sched *sched)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_finish(GLT_sched sched)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_exit(GLT_sched sched)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_set_data(GLT_sched sched, void *data)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_get_data(GLT_sched sched, void **data)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_get_size(GLT_sched sched, size_t *size)
{
    GLT_ERROR_ARG;
}

void glt_scheduler_get_total_size(GLT_sched sched, size_t *size)
{
    GLT_ERROR_ARG;
}

void glt_self_get_type(GLT_unit_type *type)
{
    GLT_ERROR_ARG;
}

void glt_self_is_primary(GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

void glt_self_on_primary_xstream(GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

void glt_self_get_last_pool_id(int *pool_id)
{
    GLT_ERROR_ARG;
}

void glt_self_suspend(void)
{
    GLT_ERROR_ARG;
}

void glt_self_get_arg(void **arg)
{
    GLT_ERROR_ARG;
}

void glt_thread_create(GLT_sched sched, GLT_thread *newthread)
{
    GLT_ERROR_ARG;
}

void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    GLT_ERROR_ARG;
}

void glt_thread_start(GLT_thread thread)
{
    GLT_ERROR_ARG;
}

void glt_thread_free(GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

void glt_thread_join(GLT_thread thread)
{
    GLT_ERROR_ARG;
}

void glt_thread_exit()
{
    GLT_ERROR_ARG;
}

void glt_thread_cancel(GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

void glt_thread_self(GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

void glt_thread_self_rank(int *rank)
{
    GLT_ERROR_ARG;
}

void glt_thread_get_rank(GLT_thread thread, int *rank)
{
    GLT_ERROR_ARG;
}

void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched)
{
    GLT_ERROR_ARG;
}

void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools)
{
    GLT_ERROR_ARG;
}

void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched)
{
    GLT_ERROR_ARG;
}

void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools)
{
    GLT_ERROR_ARG;
}

void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state)
{
    GLT_ERROR_ARG;
}

void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result)
{
    GLT_ERROR_ARG;
}

void glt_thread_get_num(int *num_xstreams)
{
    GLT_ERROR_ARG;
}

void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

void glt_thread_run_unit(GLT_unit unit, GLT_pool pool)
{
    GLT_ERROR_ARG;
}

void glt_thread_check_events(GLT_sched sched)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_retain(GLT_tasklet tasklet)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_release(GLT_tasklet tasklet)
{
    GLT_ERROR_ARG;
}

 void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg)
{
    GLT_ERROR_ARG;
}

 void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state)
{
    GLT_ERROR_ARG;
}

 void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool)
{
    GLT_ERROR_ARG;
}

 void glt_ult_get_last_pool_id(GLT_ult ult, int *id)
{
    GLT_ERROR_ARG;
}

 void glt_ult_resume(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

 void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread)
{
    GLT_ERROR_ARG;
}

 void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched)
{
    GLT_ERROR_ARG;
}

 void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool)
{
    GLT_ERROR_ARG;
}

 void glt_ult_migrate(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

 void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    GLT_ERROR_ARG;
}

 void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag)
{
    GLT_ERROR_ARG;
}

 void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

 void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag)
{
    GLT_ERROR_ARG;
}

 void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result)
{
    GLT_ERROR_ARG;
}

 void glt_ult_retain(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

 void glt_ult_release(GLT_ult ult)
{
    GLT_ERROR_ARG;
}

 void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize)
{
    GLT_ERROR_ARG;
}

 void glt_ult_get_arg(GLT_ult ult, void **arg)
{
    GLT_ERROR_ARG;
}

 void glt_ult_attr_create (GLT_ult_attr *newattr)
{
    GLT_ERROR_ARG;
}

 void glt_ult_attr_free(GLT_ult_attr *attr)
{
    GLT_ERROR_ARG;
}

 void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize)
{
    GLT_ERROR_ARG;
}

 void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize)
{
    GLT_ERROR_ARG;
}

 void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    GLT_ERROR_ARG;
}

 void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag)
{
    GLT_ERROR_ARG;
}

#endif
