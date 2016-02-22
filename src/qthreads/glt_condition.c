#include <glt.h>

void glt_cond_create(GLT_cond *cond)
{
    cond = (GLT_cond *)malloc(sizeof(GLT_cond));
}

void glt_cond_free(GLT_cond *cond)
{
    free(cond);
}

void glt_cond_signal(GLT_cond cond)
{
    qthread_empty(&cond);
}

void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    /*Waits for memory to become empty and then fills it*/
    aligned_t fill=1;
    qthread_writeEF(&cond,&fill);
    qthread_lock(&mutex);
}

void glt_cond_broadcast(GLT_cond cond)
{
    qthread_empty(&cond);
}