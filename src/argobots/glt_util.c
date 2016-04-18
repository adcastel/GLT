#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return int glt_get_num_threads() 
{
    return main_team->num_xstreams;
}

GLT_return int glt_get_thread_num() 
{
    int rank;
    ABT_xstream_self_rank(&rank);
    return rank;
}


