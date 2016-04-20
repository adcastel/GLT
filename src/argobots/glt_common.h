/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   glt_common.h
 * Author: adcastel
 *
 * Created on 18 de abril de 2016, 14:32
 */

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
#define GLT_sched ABT_sched
#define GLT_sched_config ABT_sched_config
#define GLT_sched_config_var ABT_sched_config_var
#define GLT_sched_config_var_end ABT_sched_config_var_end
#define GLT_sched_def ABT_sched_def
#define GLT_sched_predef ABT_sched_predef
#define GLT_thread_state ABT_xstream_state
#define GLT_tasklet_state ABT_task_state
#define GLT_ult_state ABT_thread_state
#define GLT_ult_attr ABT_thread_attr
#define GLT_unit_type ABT_unit_type


#define glt_scheduler_config_create  ABT_sched_config_create
#define glt_scheduler_config_read  ABT_sched_config_read 

//MASSIVETHREAD
#define GLT_workunit_f void *
#define GLT_workunit_o void *
#define GLT_felock void *
#define GLT_felock_status int
#define GLT_pickle void *
#define GLT_wsapi_decide_f void *
#define GLT_wsapi_steal_f void *
//Shared
#define GLT_key ABT_key


//QTHREADS

#include <sys/socket.h>
#include <poll.h>
#include <sys/resource.h>

#define aligned_t long unsigned int
typedef enum introspective_state {NOT_SUPPORTED} introspective_state;

typedef struct mapinfo_s {
    int not_supported;
}mapinfo_s_t;

typedef struct dynmapinfo_s {
    int not_supported;
}dynmapinfo_s_t;

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
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
    int max_elem;
} glt_team_t;




#define GLT_VERSION "You are using glt 0.1v over Argobots (adcastel@uji.es) "

#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads \
    implementation and you are using Argobots. Please use the query functions")
#define GLT_ERROR_MYTH printf("Error: This feature is only supported by MassiveThredashreads \
    implementation and you are using Argobots. Please use the query functions")


glt_team_t * main_team;

#endif /* GLT_COMMON_H */

