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
    printf("Starting with MASSIVETHREADS\n");
}

GLT_func_prefix void glt_end() {
    printf("Ending with MASSIVETHREADS\n");
}

GLT_func_prefix glt_team_t * glt_get_team(){
    return main_team;
}

GLT_func_prefix void glt_init(int argc, char * argv[]) {
    int num_threads = get_nprocs();
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));
    char buff[10];
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("MYTH_WORKER_NUM", buff, 1);
    } else if (getenv("MYTH_WORKER_NUM") != NULL) {
        num_threads = atoi(getenv("MYTH_WORKER_NUM"));
    } else {
        sprintf(buff, "%d", num_threads);
        setenv("MYTH_WORKER_NUM", buff, 1);
    }

    setenv("MYTH_BIND_WORKERS", "1", 1);
    main_team->num_workers = num_threads;
    CHECK(myth_init(),0); 
}

GLT_func_prefix void glt_finalize() {
    CHECK(myth_fini(),0); 
}

