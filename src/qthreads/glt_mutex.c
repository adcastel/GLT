#include <glt.h>

void glt_mutex_create(GLT_mutex * mutex)
{
    mutex = (GLT_mutex *)malloc(sizeof(GLT_mutex));
}

void glt_mutex_lock(GLT_mutex mutex)
{
    qthread_lock(&mutex);
}
void glt_mutex_unlock(GLT_mutex mutex)
{
    qthread_unlock(&mutex);
}

void glt_mutex_free(GLT_mutex * mutex)
{
    free(mutex);
}

