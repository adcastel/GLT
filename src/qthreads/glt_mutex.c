#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif
GLT_return void glt_mutex_create(GLT_mutex * mutex)
{
   // mutex = (GLT_mutex *)malloc(sizeof(GLT_mutex));
}

GLT_return void glt_mutex_lock(GLT_mutex mutex)
{
    qthread_lock(mutex);
}

GLT_return void glt_mutex_unlock(GLT_mutex mutex)
{
    qthread_unlock(mutex);
}

GLT_return void glt_mutex_free(GLT_mutex * mutex)
{
    //free(mutex);
}

GLT_return void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex)
{
    aligned_t res = qthread_cas(mutex,0,1);
    *locked = (res==0)? 1 : 0;        
}