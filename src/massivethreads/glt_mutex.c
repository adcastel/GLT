#include <glt.h>

void glt_mutex_create(GLT_mutex * mutex)
{
    *mutex = myth_mutex_create();
}
void glt_mutex_lock(GLT_mutex mutex)
{
    myth_mutex_lock(mutex);
}
void glt_mutex_unlock(GLT_mutex mutex)
{
    myth_mutex_unlock(mutex);
}

void glt_mutex_free(GLT_mutex * mutex)
{
    myth_mutex_destroy(*mutex);
}

void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex)
{
    *locked = myth_mutex_trylock(mutex);
}