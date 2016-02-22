#include <glt.h>

void glt_cond_create(GLT_cond *cond)
{
    *cond =  myth_cond_create();
}

void glt_cond_free(GLT_cond *cond)
{
    myth_cond_destroy(*cond);
}

void glt_cond_signal(GLT_cond cond)
{
    myth_cond_signal(cond);
}

void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    myth_cond_wait(cond,mutex);
}

void glt_cond_broadcast(GLT_cond cond)
{
    myth_cond_broadcast(cond);
}