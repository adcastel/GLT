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
    *new_ult = myth_create((void *) thread_func, arg);
}

void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    glt_ult_creation(thread_func, arg, new_ult);
}

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    *new_ult = myth_create((void *) thread_func, arg);
}

void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    glt_ult_creation(thread_func, arg, new_ult);
}

void glt_yield() 
{
    myth_yield(0);
}

void glt_yield_to(GLT_ult ult) 
{
    myth_yield(0);
}

void glt_ult_join(GLT_ult *ult) 
{
    myth_join(*ult, NULL);
}

void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    myth_join(*tasklet, NULL);
}

void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult)
{
    printf("Warning: this feature is not supported in MassiveThreads\n");
    *id = -1;
}

void glt_workunit_get_thread_id(GLT_thread_id *id)
{
    myth_thread_t thread = myth_self();
    printf("Warning: this feature is not supported in MassiveThreads\n");
    *id = -1;
}

 void glt_ult_migrate_self_to(GLT_thread_id id)
{
    printf("Warning: this feature is not supported in MassiveThreads\n");
}