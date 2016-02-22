#include <glt.h>



int glt_get_num_threads() {
#ifdef ARGOBOTS
    return main_team->num_xstreams;
#endif
#ifdef MASSIVETHREADS
    return main_team->num_workers;
#endif
#ifdef QTHREADS
    return main_team->num_shepherds;
#endif
}

int glt_get_thread_num() {
#ifdef ARGOBOTS
    int rank;
    ABT_xstream_self_rank(&rank);
    return rank;
#endif
#ifdef MASSIVETHREADS
    return myth_get_worker_num();
#endif
#ifdef QTHREADS
    return qthread_shep();
#endif
}


