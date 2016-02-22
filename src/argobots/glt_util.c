#include <glt.h>



int glt_get_num_threads() {
    return main_team->num_xstreams;
}

int glt_get_thread_num() {
    int rank;
    ABT_xstream_self_rank(&rank);
    return rank;
}


