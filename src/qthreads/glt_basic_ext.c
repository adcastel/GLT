/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_extended_basic()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


/* void glt_ult_creation_precond(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int npreconds, ...){
    qthread_fork_precond((void *)thread_func,arg,ult,npreconds,...);
}

 void glt_ult_creation_precond_to(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int dest,int npreconds, ...){
    qthread_fork_precond_to((void *)thread_func,arg,ult,dest,npreconds,...);
}
*/
 void glt_ult_creation_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar){
    qthread_fork_syncvar((void *)thread_func,arg,syncvar);
}

 void glt_ult_creation_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest,int npreconds, ...){
    qthread_fork_syncvar_to((void *)thread_func,arg,syncvar,dest);
}

 void glt_ult_get_thread(GLT_thread *thread, int *worker)
{
    *worker = qthread_worker(thread);
}

 void glt_ult_get_thread_unique(GLT_thread *thread, int *worker)
{
    *worker = qthread_worker_unique(thread);
}

 void glt_ult_get_tasklocal(void * pointer, unsigned int size)
{
    pointer = qthread_get_tasklocal(size);
}

 void glt_ult_size_tasklocal(unsigned int *size)
{
    *size = qthread_size_tasklocal();
}

 void glt_ult_migrate_self_to(int dest)
{
    qthread_migrate_to(dest);
}

 void glt_ult_get_stack_left(size_t *size)
{
    *size = qthread_stackleft();
}

 void glt_ult_retloc(GLT_ult * ult)
{
    ult = qthread_retloc();
}

#endif
