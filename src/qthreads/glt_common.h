/* Generic Lightweight Thread (GLT) library.
 * Developed by: 
 *      Adrian Castello (adcastel@uji.es) at Universitat Jaume I 
 * Supervised by:
 *      Antonio J. Peña (antonio.pena@bsc.es) at Barcelona Supercomputing Center
 *      Rafael Mayo Gual and Enrique S. Quintana-Ortí ({mayo,quintana}@uji.es)
 *      Sangmin Seo and Pavan Balaji ({sseo,balaji}@anl.gov) at Argonne National Laboratory
*/

/* Qthreads implementation object file*/

#ifndef GLT_COMMON_H
#define GLT_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/sysinfo.h>

#include <qthread/qthread.h>
#include <qthread/barrier.h>
#include <qthread/qtimer.h>
#include <qthread/sinc.h>
#include <qthread/qloop.h>
#include <qthread/qutil.h>
#include <qthread/qpool.h>
#include <qthread/qarray.h>
#include <qthread/qlfqueue.h>
#include <qthread/qdqueue.h>
#include <qthread/dictionary.h>
#include <qthread/io.h>
#include <qthread/qt_syscalls.h> 
#include <qthread/cacheline.h>
#include <qthread/qalloc.h>

#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread qthread_shepherd_id_t
#define GLT_mutex aligned_t *
#define GLT_barrier  qt_barrier_t
#define GLT_cond aligned_t
#define GLT_timer qtimer_t
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

//Extended variables
#ifndef CORE
#define GLT_syncvar syncvar_t
#define GLT_aligned aligned_t
#define GLT_memory_state aligned_t
#define GLT_sinc_op qt_sinc_op_f
#define GLT_sinc qt_sinc_t
#define GLT_loop_f qt_loop_f
#define GLT_loopr_f qt_loopr_f
#define GLT_loop_step_f qt_loop_step_f
#define GLT_accum_f qt_accum_f
#define GLT_loop_queue qqloop_handle_t
#define GLT_loop_queue_kind qt_loop_queue_type
#define GLT_ds_pool qpool
#define GLT_ds_array qarray
#define GLT_ds_array_distribution distribution_t
#define GLT_ds_loop_f qa_loop_f
#define GLT_ds_loopr_f qa_loopr_f
#define GLT_ds_cloop_f qa_cloop_f
#define GLT_ds_lfqueue qlfqueue_t
#define GLT_ds_dqueue qdqueue_t
#define GLT_ds_dictionary qt_dictionary
#define GLT_ds_dictionary_key_equals qt_dict_key_equals_f
#define GLT_ds_dictionary_hash qt_dict_hash_f
#define GLT_ds_dictionary_cleanup qt_dict_cleanup_f
#define GLT_ds_dictionary_it qt_dictionary_iterator
#define GLT_subthread qthread_worker_id_t

//ARGOBOTS
#define GLT_event_kind void *
#define GLT_event_cb_fn void *
#define GLT_future void *
#define GLT_promise void *
#define GLT_key void *
#define GLT_pool_def void *
#define GLT_pool_config void *
#define GLT_pool void *
#define GLT_pool_kind void *
#define GLT_pool_access void *
#define GLT_unit void *
#define GLT_thread_state void *
#define GLT_tasklet_state void *
#define GLT_ult_state void *
#define GLT_ult_id int
#define GLT_ult_attr void *
#define GLT_unit_type void *

//MASSIVETHREAD
#define GLT_workunit_f void *
#define GLT_workunit_o void *
#define GLT_felock void *
#define GLT_felock_status int
#define GLT_pickle void *
#define GLT_wsapi_decide_f void *
#define GLT_wsapi_steal_f void *

#define glt_ult_creation_precond qthread_fork_precond
#define glt_ult_creation_precond_to qthread_fork_precond_to

#endif

typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;


#define GLT_VERSION "You are using fast glt 0.1v over Qthreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots \
    implementation and you are using Qthreads. Please use the query functions\n")
#define GLT_ERROR_MYTH printf("Error: This feature is only supported by MassiveThredashreads \
    implementation and you are using Qthreads. Please use the query functions\n")
#define GLT_LIB_ERROR printf("Error: This feature is in the API but it is not \
    included in the Library\n")

glt_team_t * main_team;

#endif /* GLT_COMMON_H */

