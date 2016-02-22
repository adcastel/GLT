#include <glt.h>

int glt_get_num_threads() 
{
    return main_team->num_shepherds;
}

int glt_get_thread_num() 
{
    return qthread_shep();
}


