/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//threads functions


GLT_func_prefix int glt_can_manage_threads()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_thread_create (GLT_sched sched, GLT_thread *newthread)
{

    if(main_team->num_xstreams < main_team->max_elem){
        ABT_xstream_create (sched, newthread);
        main_team->team[main_team->num_xstreams]=newthread;
        main_team->num_xstreams++;
    }
    else {
        printf("Error: There are not more sloots for threads\n");
    }
}

GLT_func_prefix void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    if(main_team->num_xstreams < main_team->max_elem){
        ABT_xstream_create_basic (predef, num_pools, pools, config, newthread);
        main_team->team[main_team->num_xstreams]=newthread;
        main_team->num_xstreams++;
    }
    else {
        printf("Error: There are not more sloots for threads\n");
    }
}

GLT_func_prefix void glt_thread_start(GLT_thread thread)
{
    ABT_xstream_start (thread);
}

GLT_func_prefix void glt_thread_free(GLT_thread *thread)
{
    ABT_xstream_free (thread);
}

GLT_func_prefix void glt_thread_join(GLT_thread thread)
{
    ABT_xstream_join (thread);
}

GLT_func_prefix void glt_thread_exit()
{
    ABT_xstream_exit ();
}

GLT_func_prefix void glt_thread_cancel(GLT_thread *thread)
{
    ABT_xstream_cancel (thread);
}

GLT_func_prefix void glt_thread_self(GLT_thread *thread)
{
    ABT_xstream_self (thread);
}

GLT_func_prefix void glt_thread_self_rank(int *rank)
{
    ABT_xstream_self_rank (rank);
}

GLT_func_prefix void glt_thread_get_rank(GLT_thread thread, int *rank)
{
    ABT_xstream_get_rank (thread, rank);
}

GLT_func_prefix void glt_thread_set_main_sched (GLT_thread thread, GLT_sched sched)
{
    ABT_xstream_set_main_sched (thread, sched);
}

GLT_func_prefix void glt_thread_set_main_sched_basic (GLT_thread thread, 
        GLT_sched_predef predef, int num_pools, GLT_pool *pools)
{
    ABT_xstream_set_main_sched_basic (thread, predef, num_pools, pools);
}

GLT_func_prefix void glt_thread_get_main_sched (GLT_thread thread, GLT_sched *sched)
{
    ABT_xstream_get_main_sched (thread, sched);
}

GLT_func_prefix void glt_thread_get_main_pools (GLT_thread thread, int max_pools, 
        GLT_pool *pools)
{
    ABT_xstream_get_main_pools (thread, max_pools, pools);
}

GLT_func_prefix void glt_thread_get_state (GLT_thread thread, GLT_thread_state *state)
{
    ABT_xstream_get_state (thread, state);
}

GLT_func_prefix void glt_thread_equal (GLT_thread thread1, GLT_thread thread2, GLT_bool *result)
{
    ABT_xstream_equal (thread1, thread2, result);
}

GLT_func_prefix void glt_thread_get_num (int *num_xstreams)
{
    ABT_xstream_get_num (num_xstreams);
}
 
GLT_func_prefix void glt_thread_is_primary (GLT_thread thread, GLT_bool *flag)
{
    ABT_xstream_is_primary (thread, flag);
}

GLT_func_prefix void glt_thread_run_unit (GLT_unit unit, GLT_pool pool)
{
    ABT_xstream_run_unit (unit,pool);
}

GLT_func_prefix void glt_thread_check_events(GLT_sched sched)
{
    ABT_xstream_check_events (sched);
}
#endif