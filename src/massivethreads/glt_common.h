/* Generic Lightweight Thread (GLT) library.
 * Developed by: 
 *      Adrian Castello (adcastel@uji.es) at Universitat Jaume I 
 * Supervised by:
 *      Antonio J. Peña (antonio.pena@bsc.es) at Barcelona Supercomputing Center
 *      Rafael Mayo Gual and Enrique S. Quintana-Ortí ({mayo,quintana}@uji.es)
 *      Sangmin Seo and Pavan Balaji ({sseo,balaji}@anl.gov) at Argonne National Laboratory
*/

/* MassiveThreads implementation object file*/

#ifndef GLT_COMMON_H
#define GLT_COMMON_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE             /* See feature_test_macros(7) */

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
//#define GLT_sched void *
typedef void * GLT_sched;
//#define GLT_sched_config void *
typedef void * GLT_sched_config;

//#define GLT_sched_def void *
//#define GLT_sched_predef void *

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

#define GLT_UNIT_NULL NULL
#define GLT_TRUE    1
#define GLT_FALSE   0

typedef enum  {
    GLT_POOL_FIFO 
 } GLT_pool_kind;

typedef enum  {
       GLT_POOL_ACCESS_PRIV, /* Used by only one ES */
       GLT_POOL_ACCESS_SPSC, /* Producers on ES1, consumers on ES2 */
       GLT_POOL_ACCESS_MPSC, /* Producers on any ES, consumers on the same ES */
       GLT_POOL_ACCESS_SPMC, /* Producers on the same ES, consumers on any ES */
       GLT_POOL_ACCESS_MPMC  /* Producers on any ES, consumers on any ES */
 } GLT_pool_access;



#ifndef CORE

#define GLT_workunit_f myth_func_t
#define GLT_workunit_o myth_thread_option_t
#define GLT_felock myth_felock_t
#define GLT_felock_status int
#define GLT_pickle myth_pickle_t
#define GLT_wsapi_decide_f myth_wsapi_decidefn_t
#define GLT_wsapi_steal_f myth_steal_func_t
//Shared
#define GLT_key myth_key_t

#include <sys/socket.h>
#include <poll.h>
#include <sys/resource.h>

#define aligned_t long unsigned int

typedef enum introspective_state {
    NOT_SUPPORTED
} introspective_state;

typedef struct mapinfo_s {
    int not_supported;
} mapinfo_s_t;

typedef struct dynmapinfo_s {
    int not_supported;
} dynmapinfo_s_t;

//ARGOBOTS
#define GLT_event_kind void *
#define GLT_event_cb_fn void *
#define GLT_future void *
#define GLT_promise void *
#define GLT_pool_def void *
#define GLT_pool_config void *
#define GLT_pool void *
//#define GLT_pool_kind void *
//#define GLT_pool_access void *
#define GLT_unit void *
#define GLT_thread_state void *
#define GLT_tasklet_state void *
#define GLT_ult_state void *
#define GLT_ult_attr void *
#define GLT_unit_type void *


//QTHREADS
#define GLT_syncvar void *
#define GLT_aligned void *
#define GLT_memory_state void *
#define GLT_sinc_op void *
#define GLT_sinc void *
#define GLT_loop_f void *
#define GLT_loopr_f void *
#define GLT_loop_step_f void *
#define GLT_accum_f void *
#define GLT_loop_queue void *
#define GLT_loop_queue_kind void *
#define GLT_ds_pool void *
#define GLT_ds_array void *
#define GLT_ds_array_distribution void *
#define GLT_ds_loop_f void *
#define GLT_ds_loopr_f void *
#define GLT_ds_cloop_f void *
#define GLT_ds_lfqueue void *
#define GLT_ds_dqueue void *
#define GLT_ds_dictionary void *
#define GLT_ds_dictionary_key_equals void *
#define GLT_ds_dictionary_hash void *
#define GLT_ds_dictionary_cleanup void *
#define GLT_ds_dictionary_it void *
#define GLT_subthread void *

#define glt_ult_creation_precond qthread_fork_precond
#define glt_ult_creation_precond_to qthread_fork_precond_to

#endif

typedef struct glt_team {
    int num_workers;
} glt_team_t;


#define GLT_VERSION "You are using glt 0.1v over MassiveThreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots \
    implementation and you are using MassiveThreads. Please use the query functions\n")
#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads \
    implementation and you are using MassiveThreads. Please use the query functions\n")
#define GLT_LIB_ERROR printf("Error: This feature is in the API but it is not \
    included in the Library\n")

/* Main team structure*/
glt_team_t * main_team;


#endif /* GLT_COMMON_H */

