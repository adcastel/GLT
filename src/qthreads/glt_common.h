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
#include <qthread/qtimer.h>


  
    
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



typedef aligned_t GLT_ult;
typedef aligned_t GLT_tasklet;
#define GLT_thread qthread_shepherd_id_t
typedef aligned_t * GLT_mutex;
typedef qt_barrier_t* GLT_barrier;
#define GLT_cond aligned_t
#define GLT_timer qtimer_t
#define GLT_bool int
#define GLT_thread_id int
#define GLT_ult_id int
#define GLT_key qth_key_t
 


#define GLT_UNIT_NULL 0
#define GLT_NULL NULL
#define GLT_TRUE    1
#define GLT_FALSE   0

#define GLT_SUCCESS 0


//Extended variables
#ifndef CORE
 
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
 

typedef void*  GLT_event_kind; 
typedef void*  GLT_event_cb_fn; 
typedef void*  GLT_future; 

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

