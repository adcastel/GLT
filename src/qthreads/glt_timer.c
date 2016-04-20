#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

#include <sys/time.h>

GLT_func_prefix double glt_get_wtime() 
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return (time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
}

GLT_func_prefix void glt_timer_create(GLT_timer * timer) 
{
    *timer = qtimer_create();
}

GLT_func_prefix void glt_timer_free(GLT_timer * timer) 
{
    qtimer_destroy(*timer);
}

GLT_func_prefix void glt_timer_start(GLT_timer timer) 
{
    qtimer_start(timer);
}

GLT_func_prefix void glt_timer_stop(GLT_timer timer) 
{
    qtimer_stop(timer);
}

GLT_func_prefix void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    *secs = qtimer_secs(timer);
}

