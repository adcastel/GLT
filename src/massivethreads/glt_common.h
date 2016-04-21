/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   glt_common.h
 * Author: adcastel
 *
 * Created on 20 de abril de 2016, 14:36
 */

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
#define GLT_pool_kind void *
#define GLT_pool_access void *
#define GLT_unit void *
#define GLT_sched void *
#define GLT_sched_config void *
#define GLT_sched_def void *
#define GLT_sched_predef void *
#define GLT_sched_config_var void *
#define GLT_sched_config_var_end void *
#define GLT_thread_state void *
#define GLT_tasklet_state void *
#define GLT_ult_state void *
#define GLT_ult_attr void *
#define GLT_unit_type void *

#define glt_scheduler_config_create  ABT_sched_config_create
#define glt_scheduler_config_read  ABT_sched_config_read 

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


#define GLT_VERSION "You are using glt 0.1v overMassiveThreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots \
    implementation and you are using MassiveThreads. Please use the query functions\n")
#define GLT_ERROR_QTH printf("Error: This feature is only supported by Qthreads \
    implementation and you are using MassiveThreads. Please use the query functions\n")
#define GLT_LIB_ERROR printf("Error: This feature is in the API but it is not \
    included in the Library\n")

/* Main team structure*/
glt_team_t * main_team;


#endif /* GLT_COMMON_H */

