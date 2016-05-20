/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   glt_pthreads.h
 * Author: adcastel
 *
 * Created on 16 de mayo de 2016, 17:15
 */

#ifndef GLT_PTHREADS_H
#define GLT_PTHREADS_H

#ifdef __cplusplus
extern "C" {
#endif
#include <assert.h>
#include <dlfcn.h>
#include <fast_glt.h>
#include <pthread.h>
    
    void __attribute__((constructor)) glt_pthread_start(void);
    void __attribute__((destructor)) glt_pthread_end(void);

    int gpthread_create(pthread_t *pth, const pthread_attr_t * attr, void *(*func)(void*), void *args);
    int gpthread_join(pthread_t th, void**ret);
    int gsched_yield(void);
    pthread_t gpthread_self(void);
    void gpthread_exit(void *ret);
    int gpthread_detach(pthread_t th);
    int gpthread_setcancelstate(int state, int *oldstate);
    int gpthread_setcanceltype(int type, int *oldtype);
    int gpthread_cancel(pthread_t th);
    void gpthread_testcancel(void);
    int gpthread_key_create(pthread_key_t *key, void (*destructor) (void *));
    int gpthread_key_delete(pthread_key_t key);
    void *gpthread_getspecific(pthread_key_t key);
    int gpthread_setspecific(pthread_key_t key, const void *ptr);
    int gpthread_barrier_init(pthread_barrier_t *barrier,
            const pthread_barrierattr_t *attr, unsigned int count);
    int gpthread_barrier_destroy(pthread_barrier_t *barrier);
    int gpthread_barrier_wait(pthread_barrier_t *barrier);
    int gpthread_mutex_init(pthread_mutex_t *mutex,
            const pthread_mutexattr_t *attr);
    int gpthread_mutex_destroy(pthread_mutex_t *mutex);
    int gpthread_mutex_trylock(pthread_mutex_t *mutex);
    int gpthread_mutex_lock(pthread_mutex_t *mutex);
    int gpthread_mutex_unlock(pthread_mutex_t *mutex);
    int gpthread_cond_init(pthread_cond_t * c,
            const pthread_condattr_t *cond_attr);
    int gpthread_cond_destroy(pthread_cond_t *c);
    int gpthread_cond_signal(pthread_cond_t *c);
    int gpthread_cond_broadcast(pthread_cond_t *c);
    int gpthread_cond_wait(pthread_cond_t * c,
            pthread_mutex_t *mutex);

#define pthread_create gpthread_create
#define pthread_join gpthread_join
#define sched_yield gsched_yield 
#define pthread_self gpthread_self
#define pthread_exit gpthread_exit
#define pthread_detach gpthread_detach
#define pthread_setcancelstate gpthread_setcancelstate
#define pthread_setcanceltype gpthread_setcanceltype
#define pthread_cancel gpthread_cancel
#define pthread_testcancel gpthread_testcancel
#define pthread_key_create gpthread_key_create
#define pthread_key_delete gpthread_key_delete
#define pthread_getspecific gpthread_getspecific
#define pthread_setspecific gpthread_setspecific 
#define pthread_barrier_init gpthread_barrier_init 
#define pthread_barrier_destroy gpthread_barrier_destroy
#define pthread_barrier_wait gpthread_barrier_wait
#define pthread_mutex_init gpthread_mutex_init
#define pthread_mutex_destroy gpthread_mutex_destroy
#define pthread_mutex_trylock gpthread_mutex_trylock
#define pthread_mutex_lock gpthread_mutex_lock
#define pthread_mutex_unlock gpthread_mutex_unlock
#define pthread_cond_init gpthread_cond_init
#define pthread_cond_destroy gpthread_cond_destroy
#define pthread_cond_signal gpthread_cond_signal
#define pthread_cond_broadcast gpthread_cond_broadcast
#define pthread_cond_wait gpthread_cond_wait 

#ifdef __cplusplus
}
#endif

#endif /* GLT_PTHREADS_H */

