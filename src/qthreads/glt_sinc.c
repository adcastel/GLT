/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_sinc_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    sinc = qt_sinc_create(sizeof_value, initial_value, op, expected);
}

 void glt_sinc_init(GLT_sinc *restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    qt_sinc_init(sinc, sizeof_value, initial_value, op, expected);
}

 void glt_sinc_destroy(GLT_sinc *sinc)
{
    qt_sinc_destroy(sinc);
}

 void glt_sinc_fini(GLT_sinc * sinc)
{
    qt_sinc_fini(sinc);
}

 void glt_sinc_reset(GLT_sinc * sinc, size_t expect)
{
    qt_sinc_reset(sinc,expect);
}

 void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value)
{
    qt_sinc_submit(sinc,value);
}

 void glt_sinc_wait(GLT_sinc * restrict sinc,  void * restrict target)
{
    qt_sinc_wait(sinc,target);
}

#endif