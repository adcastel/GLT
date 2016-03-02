/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_loop_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_loop(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop(start,end,func,arg);
}

 void glt_loop_step(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg){
    qt_loop_step(start,end,stride,func,arg);
}

/* void glt_loop_future(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_future(start,end,func,arg);
}

 void glt_loop_step_future(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg){
    qt_loop_step_future(start,end,stride,func,arg);
}
*/
 void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_balance(start,end,func,arg);
}

/* void glt_loop_balance_future(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_balance_future(start,end,func,arg);
}
*/
 void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc){
    qt_loopaccum_balance(start,end,size,out,func,arg,acc);
}

/* void glt_loopaccum_balance_future(const size_t start, const size_t end, 
size_t size, void *out, const GLT_loop_f func, void * arg, GLT_accum_f acc){
    qt_loop_balance_future(start,end,size,out,func,arg,acc);
}
*/

 void glt_loop_queue_create(GLT_loop_queue * loop, GLT_loop_queue_kind kind,
        const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_f func, void * arg)
{
    loop = qt_loop_queue_create(kind,start,end,stride,func,arg);
}

 void glt_loop_queue_set_chunk(GLT_loop_queue * loop, size_t chunk)
{
    qt_loop_queue_setchunk(loop, chunk);
}

 void glt_loop_queue_run(GLT_loop_queue * loop)
{
    qt_loop_queue_run(loop);
}

 void glt_loop_queue_run_there(GLT_loop_queue * loop, GLT_thread id)
{
    qt_loop_queue_run_there(loop,id);
}

 void glt_loop_queue_add_thread(GLT_loop_queue * loop, GLT_thread id)
{
    qt_loop_queue_addworker(loop,id);
}

#endif
