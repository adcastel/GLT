#include <glt.h>
#include <sys/time.h>

double glt_get_wtime() 
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return (time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
}

void glt_timer_create(GLT_timer * timer) 
{
    timer = (GLT_timer *)malloc (sizeof(GLT_timer));
}

void glt_timer_free(GLT_timer * timer) 
{
    free(timer);
}

void glt_timer_start(GLT_timer timer) 
{
    gettimeofday(&timer.start,NULL);
}

void glt_timer_stop(GLT_timer timer) 
{
    gettimeofday(&timer.end,NULL);
}

void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    *secs = ((timer.end.tv_sec * 1000000 + timer.end.tv_usec)
		  - (timer.start.tv_sec * 1000000 + timer.start.tv_usec))/1000000.0;
}

