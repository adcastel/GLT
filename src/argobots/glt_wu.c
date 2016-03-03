#include <glt.h>



GLT_ult * glt_ult_malloc(int number_of_ult) 
{
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) 
{
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) 
{
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
}

void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
}

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
}

void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
}

void glt_yield() 
{
    ABT_thread_yield();
}

void glt_yield_to(GLT_ult ult) 
{
    ABT_thread_yield_to(ult);
}

void glt_ult_join(GLT_ult *ult) 
{
    ABT_thread_free(ult);
}

void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    ABT_task_free(tasklet);
}

void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult)
{
    ABT_thread_get_id (ult, id);
}

void glt_workunit_get_thread_id(GLT_thread_id *id)
{
    ABT_xstream_self_rank (id);
}

 void glt_ult_migrate_self_to(GLT_thread_id id)
{
    GLT_ult ult;
    ABT_thread_self(&ult);
    ABT_thread_migrate_to_xstream (ult, main_team->team[id]);
}
 
void glt_tasklet_self(GLT_tasklet *tasklet)
{
    ABT_task_self (tasklet);
}
 void glt_ult_self(GLT_ult *ult)
{
    ABT_thread_self (ult);
}

// Extended functions

//tasklets functions

 int can_extended_tasklets()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    ABT_task_cancel (tasklet);
}

 void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread)
{
    ABT_task_get_xstream (tasklet, thread);
}

 void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state)
{
    ABT_task_get_state (tasklet, state);
}
 void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool)
{
    ABT_task_get_last_pool (tasklet, pool);
}

 void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id)
{
    ABT_task_get_last_pool_id (tasklet, id);
}

 void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag)
{
    ABT_task_set_migratable (tasklet, flag);
}

 void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag)
{
    ABT_task_is_migratable (tasklet, flag);
}

 void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result)
{
    ABT_task_equal (tasklet1, tasklet2, result);
}

 void glt_tasklet_retain(GLT_tasklet tasklet)
{
    ABT_task_retain (tasklet);
}

 void glt_tasklet_release(GLT_tasklet tasklet)
{
    ABT_task_release (tasklet);
}

 void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg)
{
    ABT_task_get_arg (tasklet, arg);
}

#endif

// ult functions

 int can_extended_ults()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
 void glt_ult_exit()
{
    ABT_thread_exit ();
}

 void glt_ult_cancel(GLT_ult ult)
{
    ABT_thread_cancel (ult);
}

 

 void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state)
{
    ABT_thread_get_state (ult, state);
}

 void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool)
{
    ABT_thread_get_last_pool (ult, pool);
}

 void glt_ult_get_last_pool_id(GLT_ult ult, int *id)
{
    ABT_thread_get_last_pool_id (ult, id);
}

 void glt_ult_resume(GLT_ult ult)
{
    ABT_thread_resume (ult);
}

 void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread)
{
    ABT_thread_migrate_to_xstream (ult, thread);
}

 void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched)
{
    ABT_thread_migrate_to_sched (ult, sched);
}

 void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool)
{
    ABT_thread_migrate_to_pool (ult, pool);
}

 void glt_ult_migrate(GLT_ult ult)
{
    ABT_thread_migrate (ult);
}

 void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    ABT_thread_set_callback (ult, cb_func, cb_arg);
}

 void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag)
{
    ABT_thread_set_migratable (ult, flag);
}

 void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag)
{
    ABT_thread_is_migratable (ult, flag);
}

 void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag)
{
    ABT_thread_is_primary (ult, flag);
}

 void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result)
{
    ABT_thread_equal (ult1, ult2, result);
}

 void glt_ult_retain(GLT_ult ult)
{
    ABT_thread_retain (ult);
}

 void glt_ult_release(GLT_ult ult)
{
    ABT_thread_release (ult);
}

 void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize)
{
    ABT_thread_get_stacksize (ult, stacksize);
}


 void glt_ult_get_arg(GLT_ult ult, void **arg)
{
    ABT_thread_get_arg (ult, arg);
}

 void glt_ult_attr_create (GLT_ult_attr *newattr)
{
    ABT_thread_attr_create (newattr);
}

 void glt_ult_attr_free(GLT_ult_attr *attr)
{
    ABT_thread_attr_free (attr);
}

 void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize)
{
    ABT_thread_attr_set_stacksize ( attr,  stacksize);
}

 void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize)
{
    ABT_thread_attr_get_stacksize ( attr, stacksize);
}

 void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{ 
    ABT_thread_attr_set_callback ( attr, cb_func, cb_arg);
}

 void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag)
{
    ABT_thread_attr_set_migratable ( attr,  flag);
}
#endif /*#ifndef CORE*/