#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_get_num_threads() 
{
    return main_team->num_xstreams;
}

GLT_func_prefix int glt_get_thread_num() 
{
    int rank;
    ABT_xstream_self_rank(&rank);
    return rank;
}


