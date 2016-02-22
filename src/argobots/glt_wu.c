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
