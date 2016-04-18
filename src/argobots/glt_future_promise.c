/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

//future functions
GLT_return int glt_can_future_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_return void glt_future_create (int nbytes, GLT_future *newfuture)
{
    ABT_eventual_create (nbytes, newfuture);
}

GLT_return void glt_future_free (GLT_future *future)
{
    ABT_eventual_free (future);
}

GLT_return void glt_future_wait (GLT_future future, void **value)
{
    ABT_eventual_wait (future, value);
}

GLT_return void glt_future_set (GLT_future future, void *value, int nbytes)
{
    ABT_eventual_set (future, value, nbytes);
}
#endif

//promise functions
GLT_return int glt_can_promise_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_return void glt_promise_create (uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    ABT_future_create (compartments, cb_func, newpromise);
}

GLT_return void glt_promise_free (GLT_promise *promise)
{
    ABT_future_free (promise);
}

GLT_return void glt_promise_wait (GLT_promise promise)
{
    ABT_future_wait (promise);
}

GLT_return void glt_promise_test (GLT_promise promise, GLT_bool *flag)
{
    ABT_future_test (promise,flag);
}

GLT_return void glt_promise_set (GLT_promise promise, void * value)
{
    ABT_future_set (promise,value);
}
#endif
