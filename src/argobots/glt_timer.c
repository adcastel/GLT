#include <glt.h>


double glt_get_wtime() 
{
    return ABT_get_wtime();
}

void glt_timer_create(GLT_timer * timer) 
{
    ABT_timer_create(timer);
}

void glt_timer_free(GLT_timer * timer) 
{
    ABT_timer_free(timer);
}

void glt_timer_start(GLT_timer timer) 
{
    ABT_timer_start(timer);
}

void glt_timer_stop(GLT_timer timer) 
{
    ABT_timer_stop(timer);
}

void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    ABT_timer_read(timer,secs);
}

