/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

//scheduler functions


GLT_return int glt_can_manage_scheduler()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE


/* void glt_scheduler_config_create(GLT_sched_config *config,...)
{
    va_list args;
    va_start(args, config);
    
    ABT_sched_config_create (config,...);	
    va_end(args);
    
}*/

/* void glt_scheduler_config_read(GLT_sched_config config, int num_vars, ...)
{
    ABT_sched_config_read (config, num_vars,...);
}*/

GLT_return void glt_scheduler_config_free (GLT_sched_config *config)
{ 	
    ABT_sched_config_free (config);
}

GLT_return void glt_scheduler_create (GLT_sched_def *def, int num_pools, 
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched)
{
    ABT_sched_create (def, num_pools, pools, config, newsched);
}

GLT_return void glt_schededuler_create_basic (GLT_sched_predef predef, 
        int num_pools, GLT_pool *pools, GLT_sched_config config, 
        GLT_sched *newsched)
{
    ABT_sched_create_basic (predef, num_pools, pools, config, newsched);
}

GLT_return void glt_scheduler_free (GLT_sched *sched)
{
    ABT_sched_free (sched);
}

GLT_return void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools)
{
    ABT_sched_get_num_pools ( sched, num_pools);
}

GLT_return void glt_scheduler_get_pools(GLT_sched sched, int max_pools, 
        int idx, GLT_pool *pools)
{
    ABT_sched_get_pools ( sched, max_pools, idx, pools);
}

GLT_return void glt_scheduler_finish (GLT_sched sched)
{
    ABT_sched_finish (sched);
}

GLT_return void glt_scheduler_exit (GLT_sched sched)
{
    ABT_sched_exit (sched);
}

GLT_return void glt_scheduler_has_to_stop (GLT_sched sched, GLT_bool *stop)
{
    ABT_sched_has_to_stop (sched, stop);
}

GLT_return void glt_scheduler_set_data (GLT_sched sched, void *data)
{
    ABT_sched_set_data (sched,data);
}

GLT_return void glt_scheduler_get_data(GLT_sched sched, void **data)
{
    ABT_sched_get_data (sched, data);
}

GLT_return void glt_scheduler_get_size (GLT_sched sched, size_t *size)
{
    ABT_sched_get_size (sched, size);
}

GLT_return void glt_scheduler_get_total_size(GLT_sched sched, size_t *size)
{
    ABT_sched_get_total_size (sched, size);
}
#endif