#include <glt.h>




void glt_mutex_create(GLT_mutex * mutex){
#ifdef ARGOBOTS
    ABT_mutex_create(mutex);
#endif
#ifdef MASSIVETHREADS
    *mutex = myth_mutex_create();
#endif
#ifdef QTHREADS
    mutex = (GLT_mutex *)malloc(sizeof(GLT_mutex));

#endif
}
void glt_mutex_lock(GLT_mutex mutex){
#ifdef ARGOBOTS
    ABT_mutex_lock(mutex);
#endif
#ifdef MASSIVETHREADS
    myth_mutex_lock(mutex);
#endif
#ifdef QTHREADS
    qthread_lock(&mutex);
#endif    
}
void glt_mutex_unlock(GLT_mutex mutex){
#ifdef ARGOBOTS
    ABT_mutex_unlock(mutex);
#endif
#ifdef MASSIVETHREADS
    myth_mutex_unlock(mutex);
#endif
#ifdef QTHREADS
    qthread_unlock(&mutex);
#endif     
}

void glt_mutex_free(GLT_mutex * mutex){
#ifdef ARGOBOTS
    ABT_mutex_free(mutex);
#endif
#ifdef MASSIVETHREADS
    myth_mutex_destroy(*mutex);
#endif
#ifdef QTHREADS
    free(mutex);
#endif     
}

