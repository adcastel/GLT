#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return double glt_get_wtime() 
{
    return ABT_get_wtime();
}

GLT_return void glt_timer_create(GLT_timer * timer) 
{
    ABT_timer_create(timer);
}

GLT_return void glt_timer_free(GLT_timer * timer) 
{
    ABT_timer_free(timer);
}

GLT_return void glt_timer_start(GLT_timer timer) 
{
    ABT_timer_start(timer);
}

GLT_return void glt_timer_stop(GLT_timer timer) 
{
    ABT_timer_stop(timer);
}

GLT_return void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    ABT_timer_read(timer,secs);
}

