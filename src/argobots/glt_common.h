/* See COPYRIGHT in top-level directory. */


/* Argobots implementation object file*/

#ifndef GLT_COMMON_H
#define GLT_COMMON_H

#if __STDC_VERSION__ < 199901L
#define restrict /* nothing */
#endif

/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif

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
#define GLT_key ABT_key

#define GLT_sched ABT_sched
#define GLT_sched_config ABT_sched_config
#define GLT_sched_config_var ABT_sched_config_var
#define GLT_sched_config_var_end ABT_sched_config_var_end

#define glt_scheduler_config_create  ABT_sched_config_create
#define glt_scheduler_config_read  ABT_sched_config_read 

#define GLT_UNIT_NULL ABT_UNIT_NULL
#define GLT_NULL NULL

#define GLT_TRUE    1
#define GLT_FALSE   0

#define GLT_SUCCESS 0
    


//Extended variables
#ifndef CORE
    
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

/* ABT_sched_config_type*/
#define GLT_SCHED_CONFIG_INT  ABT_SCHED_CONFIG_INT/* Parameter of type int */
#define GLT_SCHED_CONFIG_DOUBLE ABT_SCHED_CONFIG_DOUBLE /* Parameter of type double */
#define GLT_SCHED_CONFIG_PTR ABT_SCHED_CONFIG_PTR /* Parameter of type pointer */
#define GLT_sched_config_type ABT_sched_config_type    
    
    
#define GLT_event_kind ABT_event_kind
#define GLT_event_cb_fn ABT_event_cb_fn
#define GLT_future ABT_eventual






#define aligned_t long unsigned int

#endif

typedef struct glt_team {
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
    int max_elem;
} glt_team_t;

#define GLT_VERSION "You are using GLT 2.0v over Argobots (adcastel@uji.es) "
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

extern glt_team_t * main_team;

#if defined(__cplusplus)
}
#endif


#endif /* GLT_COMMON_H */
