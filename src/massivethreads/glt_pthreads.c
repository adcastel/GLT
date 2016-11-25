/* See COPYRIGHT in top-level directory. */
/*
 * Pthread-like API file.
 */

#include<glt_pthreads.h>

void glt_pthread_start() {
    char buff[10];
    int num_threads = get_nprocs();
    int num_pools = 1;
    
    sprintf(buff, "%d", num_threads);
    setenv("GLT_NUM_THREADS", buff, 1);
    int argc = 0;
    char * argv;

    glt_init(argc, &argv);
}

void glt_pthread_end() {
    glt_finalize();
}

int gsched_yield(void) {
    glt_yield();
    return 0;
}

int gpthread_yield(void) {
    glt_yield();
    return 0;
}

pthread_t gpthread_self(void) {
    GLT_ult ult;
    glt_ult_self(&ult);
    return (pthread_t) ult;
}

int gpthread_create(pthread_t *pth, const pthread_attr_t * attr, void *(*func)(void*), void *args) {
    GLT_ult ult;
    glt_ult_create((void *) func, args, &ult);
    *pth = (pthread_t) ult;
    return 0;
}

int gpthread_join(pthread_t th, void**ret) {
    glt_ult_join((GLT_ult *) & th);
    return 0;
}

void gpthread_exit(void *ret) {
    glt_ult_exit();
    //To avoid warning, this code is unreachable
    while (1);
}

int gpthread_detach(pthread_t th) {
    glt_ult_cancel((GLT_ult) th);
    return 0;
}

int gpthread_setcancelstate(int state, int *oldstate) {
    return 0;
}

int gpthread_setcanceltype(int type, int *oldtype) {
    return 0;
}

int gpthread_cancel(pthread_t th) {
    glt_ult_cancel((GLT_ult) th);
    return 0;
}

void gpthread_testcancel(void) {

}

int gpthread_key_create(pthread_key_t *key, void (*destructor) (void *)) {
    glt_key_create(destructor, (GLT_key *) & key);
    return 0;
}

int gpthread_key_delete(pthread_key_t key) {
    glt_key_free((GLT_key *) & key);
    return 0;
}

void *gpthread_getspecific(pthread_key_t key) {
    void * value;
    glt_key_get(key, &value);
    return value;
}

int gpthread_setspecific(pthread_key_t key, const void *ptr) {
    glt_key_set(key, (void *) ptr);
    return 0;
}

//TODO:these functions are too linux-dependent, need to make more portable

int gpthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count) {
    glt_barrier_create(count, (GLT_barrier *) &barrier);
    return 0;
}

/* Destroy a previously dynamically initialized barrier BARRIER.  */

int gpthread_barrier_destroy(pthread_barrier_t *barrier) {
    glt_barrier_free((GLT_barrier *) barrier);
    return 0;
}

/* Wait on barrier BARRIER.  */

int gpthread_barrier_wait(pthread_barrier_t *barrier) {
    glt_barrier_wait((GLT_barrier *) &barrier);
    return 0;
}

int gpthread_mutex_init(pthread_mutex_t *mutex,
        const pthread_mutexattr_t *attr) {
    glt_mutex_create((GLT_mutex *) &mutex);
    return 0;
}

int gpthread_mutex_destroy(pthread_mutex_t *mutex) {
    glt_mutex_free((GLT_mutex *) &mutex);
    return 0;
}

int gpthread_mutex_trylock(pthread_mutex_t *mutex) {
    return glt_mutex_trylock((GLT_mutex) mutex);
}

int gpthread_mutex_lock(pthread_mutex_t *mutex) {
    glt_mutex_lock((GLT_mutex) mutex);
    return 0;
}

int gpthread_mutex_unlock(pthread_mutex_t *mutex) {
    glt_mutex_unlock((GLT_mutex) mutex);
    return 0;
}

int gpthread_cond_init(pthread_cond_t * c,
        const pthread_condattr_t *cond_attr) {
    glt_cond_create((GLT_cond *) &c);
    return 0;
}

int gpthread_cond_destroy(pthread_cond_t *c) {
    glt_cond_free((GLT_cond *) &c);
    return 0;
}

int gpthread_cond_signal(pthread_cond_t *c) {
    glt_cond_signal((GLT_cond) c);
    return 0;
}

int gpthread_cond_broadcast(pthread_cond_t *c) {
    glt_cond_broadcast((GLT_cond) c);
    return 0;
}

int gpthread_cond_wait(pthread_cond_t * c,
        pthread_mutex_t *mutex) {
    glt_cond_wait((GLT_cond) c, (GLT_mutex) mutex);
    return 0;
}
