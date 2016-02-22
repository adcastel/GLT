/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */


#ifndef GLT_H
#define	GLT_H


#include <stdio.h>
#include <stdlib.h>
#include <qthread/qthread.h>
# include <qthread/barrier.h>

#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread aligned_t
#define GLT_mutex aligned_t
#define GLT_barrier  qt_barrier_t
#define GLT_cond aligned_t

typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;

#define GLT_VERSION "You are using glt 0.1v over Qthreads (adcastel@uji.es)"
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

void glt_cond_create(GLT_cond *cond);
void glt_cond_free(GLT_cond *cond);
void glt_cond_signal(GLT_cond cond);
void glt_cond_wait(GLT_cond cond, GLT_mutex mutex);
void glt_cond_broadcast(GLT_cond cond);

int glt_get_thread_num();
int glt_get_num_threads();

#endif	/* glt_H */

