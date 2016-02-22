#include <glt.h>




void glt_mutex_create(GLT_mutex * mutex)
{
    ABT_mutex_create(mutex);
}
void glt_mutex_lock(GLT_mutex mutex)
{
    ABT_mutex_lock(mutex);
}
void glt_mutex_unlock(GLT_mutex mutex)
{
    ABT_mutex_unlock(mutex);
}

void glt_mutex_free(GLT_mutex * mutex)
{
    ABT_mutex_free(mutex);
}

