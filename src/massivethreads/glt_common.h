/* See COPYRIGHT in top-level directory. */

/* MassiveThreads implementation object file*/

#ifndef GLT_COMMON_H
#define GLT_COMMON_H

#if __STDC_VERSION__ < 199901L
#define restrict /* nothing */
#endif

/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#endif

#include <sys/time.h>
#include <sys/sysinfo.h>

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <myth.h>

typedef struct myth_timer {
    struct timeval start;
    struct timeval end;
} myth_timer_t;

#define GLT_ult myth_thread_t
#define GLT_tasklet myth_thread_t
#define GLT_thread myth_thread_t
#define GLT_mutex myth_mutex_t
#define GLT_barrier myth_barrier_t
#define GLT_cond myth_cond_t
#define GLT_timer myth_timer_t
#define GLT_bool int
#define GLT_thread_id int
#define GLT_ult_id int
#define GLT_key myth_key_t



#define GLT_UNIT_NULL NULL
#define GLT_NULL NULL
#define GLT_TRUE    1
#define GLT_FALSE   0

#define GLT_SUCCESS 0


#ifndef CORE

typedef void * GLT_sched;
typedef void * GLT_sched_config;

#define glt_scheduler_config_create  
#define glt_scheduler_config_read   

typedef enum {
    GLT_SCHED_CONFIG_INT = 0, /* Parameter of type int */
    GLT_SCHED_CONFIG_DOUBLE = 1, /* Parameter of type double */
    GLT_SCHED_CONFIG_PTR = 2, /* Parameter of type pointer */
} GLT_sched_config_type;

typedef struct GLT_sched_config_var {
    int idx;
    GLT_sched_config_type type;
} GLT_sched_config_var;

#define GLT_sched_config_var_end NULL


typedef int (*GLT_sched_init_fn)(GLT_sched, GLT_sched_config);
typedef void (*GLT_sched_run_fn)(GLT_sched);
typedef int (*GLT_sched_free_fn)(GLT_sched);
typedef void * (*GLT_sched_get_migr_pool_fn)(GLT_sched);

typedef enum {
    GLT_SCHED_TYPE_ULT, /* can yield */
    GLT_SCHED_TYPE_TASK /* cannot yield */
} GLT_sched_type;

typedef struct {
    GLT_sched_type type; /* ULT or tasklet */
    GLT_sched_init_fn init;
    GLT_sched_run_fn run;
    GLT_sched_free_fn free;
    GLT_sched_get_migr_pool_fn get_migr_pool;
} GLT_sched_def;

 typedef enum  {
    GLT_SCHED_DEFAULT,   /* Default scheduler */
    GLT_SCHED_BASIC,     /* Basic scheduler */
    GLT_SCHED_PRIO       /* Priority scheduler */
}GLT_sched_predef;


typedef void*  GLT_event_kind; 
typedef void*  GLT_event_cb_fn; 
typedef void*  GLT_future; 


#endif

typedef struct glt_team {
    int num_workers;
} glt_team_t;


#define GLT_VERSION "You are using GLT GLT 2.0v over MassiveThreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots implementation and you are using MassiveThreads. Please use the query functions\n")
#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads implementation and you are using MassiveThreads. Please use the query functions\n")
#define GLT_LIB_ERROR printf("Error: This feature is in the API but it is not included in the Library\n")



#ifdef PARANOID
#define CHECK(x, y) do { \
  (x); \
} while (0)
#else
#define CHECK(x, y) do { \
  (x); \
} while (0)
#endif

extern glt_team_t * main_team;

#if defined(__cplusplus)
}
#endif

#endif /* GLT_COMMON_H */

