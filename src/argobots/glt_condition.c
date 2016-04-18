#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return void glt_cond_create(GLT_cond *cond)
{
    ABT_cond_create (cond);
}

GLT_return void glt_cond_free(GLT_cond *cond)
{
    ABT_cond_free (cond);
}

GLT_return void glt_cond_signal(GLT_cond cond)
{
    ABT_cond_signal (cond);
}

GLT_return void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    ABT_cond_wait (cond, mutex);
}

GLT_return void glt_cond_broadcast(GLT_cond cond)
{
    ABT_cond_broadcast (cond);
}