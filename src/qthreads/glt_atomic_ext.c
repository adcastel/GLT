/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

  int glt_can_atomic_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_atomic_incr(GLT_aligned * operand, int incr)
{
    qthread_incr(operand,incr);
}

 void glt_atomic_fincr(float * operand, float incr)
{
    qthread_fincr(operand,incr);
}

 void glt_atomic_dincr(double * operand, double incr)
{
    qthread_dincr(operand,incr);
}

 void glt_atomic_cas(volatile GLT_aligned * addr, GLT_aligned oldval,
        GLT_aligned newval)
{
    qthread_cas(addr,oldval,newval);
}

 void glt_atomic_cas_ptr(void * volatile * addr, void * oldval,
        void * newval)
{
    qthread_cas_ptr(addr,oldval,newval);
}

#endif