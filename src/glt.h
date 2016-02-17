/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef GLT_H
#define	GLT_H



#ifdef ARGOBOTS
#include <stdio.h>
#include <stdlib.h>
#include <abt.h>



#define GLT_ult ABT_thread
#define GLT_tasklet ABT_task
#define GLT_thread ABT_xstream
#define GLT_mutex ABT_mutex
#define GLT_barrier ABT_barrier

 
typedef struct glt_team {
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
} glt_team_t;


#endif
#ifdef MASSIVETHREADS
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


#define GLT_ult_attribute NULL

typedef struct glt_team {
    int num_workers;
} glt_team_t;

#endif

#ifdef QTHREADS
#include <stdio.h>
#include <stdlib.h>
#include <qthread/qthread.h>
# include <qthread/barrier.h>

#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread aligned_t
#define GLT_mutex aligned_t
#define GLT_barrier  qt_barrier_t


#define GLT_ult_attribute NULL

typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;

#endif

#define GLT_VERSION "You are using glt 0.1v (adcastel@uji.es)"
/* Main team structure*/

glt_team_t * main_team;


void __attribute__((constructor)) glt_start(void);
void __attribute__((destructor)) glt_end(void);


void glt_init(int argc, char * argv[]);
void glt_finalize();

GLT_ult * glt_ult_malloc(int number_of_ult);
GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets);

void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult);
void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest);

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult);
void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest);

void glt_yield();
void glt_yield_to(GLT_ult ult);

void glt_ult_join(GLT_ult *ult);
void glt_tasklet_join(GLT_tasklet *tasklet);

void glt_mutex_create(GLT_mutex * mutex);
void glt_mutex_lock(GLT_mutex mutex);
void glt_mutex_unlock(GLT_mutex mutex);
void glt_mutex_free(GLT_mutex * mutex);

void glt_barrier_create(int num_waiters, GLT_barrier *barrier);
void glt_barrier_free(GLT_barrier *barrier);

void glt_barrier_wait(GLT_barrier *barrier);


int glt_get_thread_num();
int glt_get_num_threads();

#endif	/* glt_H */

