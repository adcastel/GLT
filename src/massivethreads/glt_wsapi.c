/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_wsapi_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
GLT_func_prefix void glt_wsapi_runqueue_peek(GLT_ult *ult, int victim,void *ptr,size_t *psize)
{
    *ult = myth_wsapi_runqueue_peek(victim,ptr,psize);
}

GLT_func_prefix void glt_wsapi_get_hint_size(size_t *size, GLT_ult ult)
{
    *size = myth_wsapi_get_hint_size(ult);
}

GLT_func_prefix void glt_wsapi_get_hint_ptr(void *ptr, GLT_ult ult)
{
    ptr = myth_wsapi_get_hint_ptr(ult);
}

GLT_func_prefix void glt_wsapi_set_hint(GLT_ult ult,void **data,size_t *size)
{
    myth_wsapi_set_hint(ult,data,size);
}

GLT_func_prefix void glt_wsapi_rand(int * rand)
{
    *rand = myth_wsapi_rand();
}

GLT_func_prefix void glt_wsapi_randrr(int *ret, int n)
{
    myth_wsapi_randarr(ret,n);
}

GLT_func_prefix void glt_wsapi_runqueue_take(GLT_ult * ult, int victim,GLT_wsapi_decide_f decidefn,void *udata)
{
    *ult = myth_wsapi_runqueue_take(victim,decidefn,udata);
}

GLT_func_prefix void glt_wsapi_runqueue_pass(GLT_bool *pass, int target,GLT_ult ult)
{
    *pass = myth_wsapi_runqueue_pass(target,ult);
}

GLT_func_prefix void glt_wsapi_runqueue_push(GLT_ult ult)
{
    myth_wsapi_runqueue_push(ult);
}

GLT_func_prefix void glt_wsapi_runqueue_pop(GLT_ult * ult)
{
    *ult = myth_wsapi_runqueue_pop();
}

/*
GLT_func_prefix void glt_wsapi_rand2(int * rand_value, int min, int max)
{
     GLT_LIB_ERROR;
         //This function is found in the header but not in the static or dynamic massivethreads libraries
    //*rand_value = myth_wsapi_rand2(min,max);
}
*/

GLT_func_prefix void glt_wsapi_set_stealfunc(GLT_wsapi_steal_f *out, GLT_wsapi_steal_f fn)
{
    *out = myth_wsapi_set_stealfunc(fn);
}

#endif