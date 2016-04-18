#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return void glt_cond_create(GLT_cond *cond)
{
    cond = (GLT_cond *)malloc(sizeof(GLT_cond));
}

GLT_return void glt_cond_free(GLT_cond *cond)
{
    free(cond);
}

GLT_return void glt_cond_signal(GLT_cond cond)
{
    qthread_empty(&cond);
}

GLT_return void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    /*Waits for memory to become empty and then fills it*/
    aligned_t fill=1;
    qthread_writeEF(&cond,&fill);
    qthread_lock(mutex);
}

GLT_return void glt_cond_broadcast(GLT_cond cond)
{
    qthread_empty(&cond);
}