/* See COPYRIGHT in top-level directory. */
/*
 * Main functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

glt_team_t * main_team;

GLT_func_prefix void glt_start() {
    printf("Starting with PTHREADS\n");
}

GLT_func_prefix void glt_end() {
    printf("Ending with PTHREADS\n");
}

GLT_func_prefix void glt_init(int argc, char * argv[]) {
    int num_threads = get_nprocs();
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
    }

    main_team->num_workers = 1;
    main_team->max_workers = num_threads;
}

GLT_func_prefix void glt_finalize() {
}

