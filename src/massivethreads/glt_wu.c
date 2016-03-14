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
    *id = myth_get_worker_num();
}

 void glt_ult_migrate_self_to(GLT_thread_id id)
{
    printf("Warning: this feature is not supported in MassiveThreads\n");
}
 
 void glt_tasklet_self(GLT_tasklet *tasklet)
{
    *tasklet = myth_self();
}
 void glt_ult_self(GLT_ult *ult)
{
    *ult = myth_self();
}
 
void glt_ult_exit()
{
    void *ret;
    myth_exit(ret);
}

 void glt_ult_cancel(GLT_ult ult)
{
    myth_cancel (ult);
}

 void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    myth_cancel (tasklet);
}
 
  int can_extended_workunits(){
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
 void glt_wu_create_ex(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt)
{
    *ult = myth_create_ex(func,arg,opt);
}
/*
 void glt_wu_create_nosched(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt)
{
        GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
         //*ult = myth_create_nosched(func,arg,opt);
}
*/

 void glt_yield2()
{
    myth_yield2();
}

 void glt_wu_detach(GLT_ult ult)
{
    myth_detach(ult);
}

 void glt_wu_set_cancel_state(int state, int *oldstate)
{
    myth_setcancelstate(state,oldstate);
}

 void glt_wu_set_cancel_type(int type, int *oldtype)
{
    myth_setcanceltype(type, oldtype);
}

 void glt_wu_test_cancel()
{
    myth_testcancel();
}

 void glt_wu_set_def_stack_size(size_t newsize)
{
    myth_set_def_stack_size(newsize);
}

/*
 void glt_wu_steal(GLT_ult * ult)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //*ult = myth_steal();
}

 void glt_wu_import(GLT_ult ult)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //myth_import(ult);
}

 void glt_wu_ext_import(GLT_ult ult)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //myth_ext_import(ult);
}

 void glt_wu_release_stack(GLT_ult ult)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //myth_release_stack(ult);
}
    
 void glt_wu_release_desc(GLT_ult ult)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //myth_release_desc(ult);
}
*/
#endif