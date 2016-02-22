#include <glt.h>

int glt_get_num_threads() 
{
    return main_team->num_workers;
}

int glt_get_thread_num() 
{
    return myth_get_worker_num();
}


