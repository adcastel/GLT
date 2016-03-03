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
    qthread_fork((void *) thread_func, arg, new_ult);
}

void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    qthread_fork((void *) thread_func, arg, new_ult);
}

void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

void glt_yield() 
{
    qthread_yield();
}

void glt_yield_to(GLT_ult ult) 
{
    qthread_yield();
}

void glt_ult_join(GLT_ult *ult) 
{
    qthread_readFF(NULL, ult);
}

void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    qthread_readFF(NULL, tasklet);
}

void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult)
{
    *id = qthread_id();
}

void glt_workunit_get_thread_id(GLT_thread_id *id)
{
    *id = qthread_shep();
}

 void glt_ult_migrate_self_to(GLT_thread_id dest)
{
    qthread_migrate_to(dest);
}
 
void glt_ult_self(GLT_ult * ult)
{
    ult = qthread_retloc();
}
 
void glt_tasklet_self(GLT_ult * ult)
{
    ult = qthread_retloc();
}