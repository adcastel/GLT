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

GLT_func_prefix int glt_can_loop_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_loop(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop(start,end,func,arg);
}


GLT_func_prefix void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_balance(start,end,func,arg);
}


GLT_func_prefix void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc){
    qt_loopaccum_balance(start,end,size,out,func,arg,acc);
}



GLT_func_prefix void glt_loop_queue_create(GLT_loop_queue * loop, GLT_loop_queue_kind kind,
        const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_f func, void * arg)
{
    loop = qt_loop_queue_create(kind,start,end,stride,func,arg);
}

GLT_func_prefix void glt_loop_queue_set_chunk(GLT_loop_queue * loop, size_t chunk)
{
    qt_loop_queue_setchunk(loop, chunk);
}

GLT_func_prefix void glt_loop_queue_run(GLT_loop_queue * loop)
{
    qt_loop_queue_run(loop);
}

GLT_func_prefix void glt_loop_queue_run_there(GLT_loop_queue * loop, GLT_thread id)
{
    qt_loop_queue_run_there(loop,id);
}

GLT_func_prefix void glt_loop_queue_add_thread(GLT_loop_queue * loop, GLT_thread id)
{
    qt_loop_queue_addworker(loop,id);
}

#endif
