/* See COPYRIGHT in top-level directory. */


/* Argobots implementation object file*/

#ifndef GLT_COMMON_H
#define GLT_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <abt.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define GLT_ult ABT_thread
#define GLT_tasklet ABT_task
#define GLT_thread ABT_xstream
#define GLT_mutex ABT_mutex
#define GLT_barrier ABT_barrier
#define GLT_cond ABT_cond
#define GLT_timer ABT_timer
#define GLT_bool ABT_bool
#define GLT_thread_id int
#define GLT_ult_id ABT_thread_id
#define GLT_sched ABT_sched
#define GLT_sched_config ABT_sched_config
#define GLT_sched_config_var ABT_sched_config_var
#define GLT_sched_config_var_end ABT_sched_config_var_end

#define glt_scheduler_config_create  ABT_sched_config_create
#define glt_scheduler_config_read  ABT_sched_config_read 

#define GLT_UNIT_NULL ABT_UNIT_NULL
#define GLT_TRUE    1
#define GLT_FALSE   0

/* ABT_sched_type*/
#define GLT_SCHED_TYPE_ULT ABT_SCHED_TYPE_ULT
#define GLT_SCHED_TYPE_TASK ABT_SCHED_TYPE_TASK


/* ABT_sched_def*/
#define GLT_sched_type ABT_sched_type /* ULT or tasklet */
#define GLT_sched_init_fn ABT_sched_init_fn
#define GLT_sched_run_fn ABT_sched_run_fn
#define GLT_sched_free_fn ABT_sched_free_fn
#define GLT_sched_get_migr_pool_fn ABT_sched_get_migr_pool_fn
#define GLT_sched_def ABT_sched_def

/* ABT_sched_predef*/
#define GLT_SCHED_DEFAULT ABT_SCHED_DEFAULT/* Default scheduler */
#define GLT_SCHED_BASIC ABT_SCHED_BASIC/* Basic scheduler */
#define GLT_SCHED_PRIO ABT_SCHED_PRIO/* Priority scheduler */
#define GLT_sched_predef ABT_sched_predef

/* ABT_pool_kind*/
#define GLT_POOL_FIFO ABT_POOL_FIFO
#define GLT_pool_kind ABT_pool_kind

/* ABT_pool_access*/
#define GLT_POOL_ACCESS_PRIV ABT_POOL_ACCESS_PRIV/* Used by only one ES */
#define GLT_POOL_ACCESS_SPSC ABT_POOL_ACCESS_SPSC/* Producers on ES1, consumers on ES2 */
#define GLT_POOL_ACCESS_MPSC ABT_POOL_ACCESS_MPSC/* Producers on any ES, consumers on the same ES */
#define GLT_POOL_ACCESS_SPMC ABT_POOL_ACCESS_SPMC/* Producers on the same ES, consumers on any ES */
#define GLT_POOL_ACCESS_MPMC ABT_POOL_ACCESS_MPMC/* Producers on any ES, consumers on any ES */
#define GLT_pool_access ABT_pool_access

/* ABT_sched_config_type*/
#define GLT_SCHED_CONFIG_INT  ABT_SCHED_CONFIG_INT/* Parameter of type int */
#define GLT_SCHED_CONFIG_DOUBLE ABT_SCHED_CONFIG_DOUBLE /* Parameter of type double */
#define GLT_SCHED_CONFIG_PTR ABT_SCHED_CONFIG_PTR /* Parameter of type pointer */
#define GLT_sched_config_type ABT_sched_config_type

//Extended variables
#ifndef CORE
#define GLT_event_kind ABT_event_kind
#define GLT_event_cb_fn ABT_event_cb_fn
#define GLT_future ABT_eventual
#define GLT_promise ABT_future
#define GLT_pool_def ABT_pool_def
#define GLT_pool_config ABT_pool_config
#define GLT_pool ABT_pool
#define GLT_pool_kind ABT_pool_kind
#define GLT_pool_access ABT_pool_access
#define GLT_unit ABT_unit
#define GLT_thread_state ABT_xstream_state
#define GLT_tasklet_state ABT_task_state
#define GLT_ult_state ABT_thread_state
#define GLT_ult_attr ABT_thread_attr
#define GLT_unit_type ABT_unit_type



//MASSIVETHREAD
typedef void* GLT_workunit_f;
typedef void* GLT_workunit_o;
typedef void* GLT_felock;
typedef int GLT_felock_status;
typedef void* GLT_pickle;
typedef void* GLT_wsapi_decide_f;
typedef void* GLT_wsapi_steal_f;
//Shared
#define GLT_key ABT_key

//QTHREADS
#include <sys/socket.h>
#include <poll.h>
#include <sys/resource.h>

#define aligned_t long unsigned int

typedef enum introspective_state {
    NOT_SUPPORTED
} introspective_state;


typedef void* GLT_syncvar;
typedef void* GLT_aligned;
typedef void* GLT_memory_state;
typedef void* GLT_sinc_op;
typedef void* GLT_sinc;
typedef void* GLT_loop_f;
typedef void* GLT_loopr_f;
typedef void* GLT_loop_step_f;
typedef void* GLT_accum_f;
typedef void* GLT_loop_queue;
typedef void* GLT_loop_queue_kind;
typedef void* GLT_ds_pool;
typedef void* GLT_ds_array;
typedef void* GLT_ds_array_distribution;
typedef void* GLT_ds_loop_f;
typedef void* GLT_ds_loopr_f;
typedef void* GLT_ds_cloop_f;
typedef void* GLT_ds_lfqueue;
typedef void* GLT_ds_dqueue;
typedef void* GLT_ds_dictionary;
typedef void* GLT_ds_dictionary_key_equals;
typedef void* GLT_ds_dictionary_hash;
typedef void* GLT_ds_dictionary_cleanup;
typedef void* GLT_ds_dictionary_it;
typedef void* GLT_subthread;

#define glt_ult_create_precond qthread_fork_precond
#define glt_ult_create_precond_to qthread_fork_precond_to

#endif

typedef struct glt_team {
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
    int max_elem;
} glt_team_t;

#define GLT_VERSION "You are using GLT 1.0v over Argobots (adcastel@uji.es) "
#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads implementation and you are using Argobots. Please use the query functions")
#define GLT_ERROR_MYTH printf("Error: This feature is only supported by MassiveThredashreads implementation and you are using Argobots. Please use the query functions")
#define GLT_LIB_ERROR printf("Error: This feature is in the API but it is not included in the Library\n")

#ifdef PARANOID
#define CHECK(x, y) do { \
  int retval = (x); \
  if (retval != (y);) { \
    printf("Runtime error: %s returned %d at %s:%d", #x, retval, __FILE__, __LINE__); \
  } \
} while (0)
#else
#define CHECK(x, y) do { \
  (x); \
} while (0)
#endif

glt_team_t * main_team;

#endif /* GLT_COMMON_H */
