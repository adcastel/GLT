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

GLT_return int glt_can_feb_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_return void glt_feb_empty(const GLT_memory_state *dest)
{
    qthread_empty(dest);
}

GLT_return void glt_feb_fill(const GLT_memory_state *dest)
{
    qthread_fill(dest);
}

GLT_return void glt_feb_status(const GLT_memory_state *addr, int *status)
{
    *status = qthread_feb_status(addr);
}

GLT_return void glt_feb_readFE( GLT_memory_state *dst, const GLT_memory_state *src)
{
    qthread_readFE(dst,src);
}

GLT_return void glt_feb_readFF( GLT_memory_state *dst, const GLT_memory_state *src)
{
    qthread_readFF(dst,src);
}

GLT_return void glt_feb_writeEF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    qthread_writeEF(dst,src);
}

GLT_return void glt_feb_writeEF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    qthread_writeEF_const(dst,src);
}

GLT_return void glt_feb_writeF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    qthread_writeF(dst,src);
}

GLT_return void glt_feb_writeF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    qthread_writeF_const(dst,src);
}

GLT_return void glt_syncvar_empty(GLT_syncvar *dest)
{
    qthread_syncvar_empty(dest);
}

GLT_return void glt_syncvar_fill(GLT_syncvar *dest)
{
    qthread_syncvar_fill(dest);
}

GLT_return void glt_syncvar_status(GLT_syncvar *addr, int *status)
{
    *status = qthread_syncvar_status(addr);
}

GLT_return void glt_syncvar_readFE( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    qthread_syncvar_readFE(dst,src);
}

GLT_return void glt_syncvar_readFF( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    qthread_syncvar_readFF(dst,src);
}

GLT_return void glt_syncvar_writeEF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    qthread_syncvar_writeEF(dst,src);
}

GLT_return void glt_syncvar_writeEF_const( GLT_syncvar *  dst,  uint64_t src)
{
    qthread_syncvar_writeEF_const(dst,src);
}

GLT_return void glt_syncvar_writeF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    qthread_syncvar_writeF(dst,src);
}

GLT_return void glt_syncvar_writeF_const( GLT_syncvar *  dst,  uint64_t src)
{
    qthread_syncvar_writeF_const(dst,src);
}

#endif