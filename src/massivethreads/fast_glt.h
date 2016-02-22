/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <myth.h>

#define GLT_ult myth_thread_t
#define GLT_tasklet myth_thread_t
#define GLT_thread myth_thread_t
#define GLT_mutex myth_mutex_t
#define GLT_barrier myth_barrier_t
#define GLT_cond myth_cond_t


#define GLT_ult_attribute NULL

typedef struct glt_team {
    int num_workers;
} glt_team_t;



#define GLT_VERSION "You are using fast glt 0.1v over MassiveThreads (adcastel@uji.es)"
/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

static inline void glt_start() 
{
    //printf("Starting with MASSIVETHREADS\n");
}

static inline  void glt_end() 
{
    //printf("Ending with MASSIVETHREADS\n");
}

static inline void glt_init(int argc, char * argv[]) 
{
    int num_threads = 1;
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("MYTH_WORKER_NUM", buff, 1);
    } else if (getenv("MYTH_WORKER_NUM") != NULL) {
        num_threads = atoi(getenv("MYTH_WORKER_NUM"));
    }
    else{
        setenv("MYTH_WORKER_NUM","1",1);
    }

    setenv("MYTH_BIND_WORKERS", "1", 1);

    main_team->num_workers = num_threads;
    myth_init(); //MassiveThreads
}

static inline void glt_finalize() 
{
    myth_fini(); //MassiveThreads
}

static inline GLT_ult * glt_ult_malloc(int number_of_ult) 
{
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

static inline GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) 
{
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

static inline void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) 
{
    *new_ult = myth_create((void *) thread_func, arg);
}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    glt_ult_creation(thread_func, arg, new_ult);
}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    *new_ult = myth_create((void *) thread_func, arg);
}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    glt_ult_creation(thread_func, arg, new_ult);
}

static inline void glt_yield() 
{
    myth_yield(0);
}

static inline void glt_yield_to(GLT_ult ult) 
{
    myth_yield(0);
}

static inline void glt_ult_join(GLT_ult *ult) 
{
    myth_join(*ult, NULL);
}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    myth_join(*tasklet, NULL);
}

static inline void glt_mutex_create(GLT_mutex * mutex)
{
    *mutex = myth_mutex_create();
}

static inline void glt_mutex_lock(GLT_mutex mutex)
{
    myth_mutex_lock(mutex);
}
static inline void glt_mutex_unlock(GLT_mutex mutex)
{
    myth_mutex_unlock(mutex);
}

static inline void glt_mutex_free(GLT_mutex * mutex)
{
    myth_mutex_destroy(*mutex);
}

static inline void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    *barrier = myth_barrier_create(num_waiters);
}

static inline void glt_barrier_free(GLT_barrier *barrier)
{
    myth_barrier_destroy(*barrier);
}

static inline void glt_barrier_wait(GLT_barrier *barrier)
{
    myth_barrier_wait(*barrier);
}

static inline void glt_cond_create(GLT_cond *cond)
{
    *cond =  myth_cond_create();
}

static inline void glt_cond_free(GLT_cond *cond)
{
    myth_cond_destroy(*cond);
}

static inline void glt_cond_signal(GLT_cond cond)
{
    myth_cond_signal(cond);
}

static inline void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    myth_cond_wait(cond,mutex);
}

static inline void glt_cond_broadcast(GLT_cond cond)
{
    myth_cond_broadcast(cond);
}

static inline int glt_get_num_threads() 
{
    return main_team->num_workers;
}

static inline int glt_get_thread_num() 
{
    return myth_get_worker_num();
}

#endif	/* FAST_GLT_H */

