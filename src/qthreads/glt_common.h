/* See COPYRIGHT in top-level directory. */


/* Qthreads implementation object file*/

#ifndef GLT_COMMON_H
#define GLT_COMMON_H



/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/sysinfo.h>

#include <qthread/qthread.h>
#include <qthread/barrier.h>
//#include <qthread/feb_barrier.h>
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

//#if __STDC_VERSION__ < 199901L
//#ifndef restrict
//#define restrict /* nothing */
//#endif
//#endif  
  
    
#define QTH_TLS_KEY_SIZE 256

typedef unsigned int qth_key_t;

typedef struct qth_tls_entry
{
	aligned_t th;
	qth_key_t key;
	void *value;
}qth_tls_entry,*qth_tls_entry_t;

extern aligned_t g_qth_tls_lock;
extern qth_tls_entry *g_qth_tls_list;
extern int g_qth_tls_list_size;
extern int g_qth_tls_key_status[QTH_TLS_KEY_SIZE];


//#define GLT_ult aligned_t
//#define GLT_tasklet aligned_t
typedef aligned_t GLT_ult;
typedef aligned_t GLT_tasklet;
#define GLT_thread qthread_shepherd_id_t
typedef aligned_t* GLT_mutex;
typedef qt_barrier_t* GLT_barrier;
#define GLT_cond aligned_t
#define GLT_timer qtimer_t
#define GLT_bool int
#define GLT_thread_id int
#define GLT_ult_id int
#define GLT_key qth_key_t
 
typedef void* GLT_sched;
typedef void* GLT_sched_config;

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

#define GLT_SUCCESS 0

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
typedef void*  GLT_event_kind; 
typedef void*  GLT_event_cb_fn; 
typedef void*  GLT_future; 
typedef void*  GLT_promise; 
typedef void*  GLT_pool_def; 
typedef void*  GLT_pool_config; 
typedef void*  GLT_pool; 
typedef void*  GLT_unit; 
typedef void*  GLT_thread_state; 
typedef void*  GLT_tasklet_state; 
typedef void*  GLT_ult_state; 
typedef void*  GLT_ult_attr; 
typedef void*  GLT_unit_type; 

//MASSIVETHREAD
typedef void* GLT_workunit_f;
typedef void*  GLT_workunit_o;
typedef void*  GLT_felock;
typedef int  GLT_felock_status; 
typedef void*  GLT_pickle; 
typedef void*  GLT_wsapi_decide_f;
typedef void*  GLT_wsapi_steal_f; 


#define glt_ult_create_precond qthread_fork_precond
#define glt_ult_create_precond_to qthread_fork_precond_to

#endif

typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;


#define GLT_VERSION "You are using GLT 2.0v over Qthreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots implementation and you are using Qthreads. Please use the query functions\n")
#define GLT_ERROR_MYTH printf("Error: This feature is only supported by MassiveThredashreads implementation and you are using Qthreads. Please use the query functions\n")
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

extern glt_team_t * main_team;

#if defined(__cplusplus)
}
#endif

#endif /* GLT_COMMON_H */

