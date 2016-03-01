#include <glt.h>

void glt_start() 
{
    printf("Starting with MASSIVETHREADS\n");
}

void glt_end() 
{
    printf("Ending with MASSIVETHREADS\n");
}

void glt_init(int argc, char * argv[]) 
{
    int num_threads = get_nprocs();
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("MYTH_WORKER_NUM", buff, 1);
    } else if (getenv("MYTH_WORKER_NUM") != NULL) {
        num_threads = atoi(getenv("MYTH_WORKER_NUM"));
    }
    else{
        setenv("MYTH_WORKER_NUM","1",1);
    }

    setenv("MYTH_BIND_WORKERS", "1", 1);

    main_team->num_workers = num_threads;
    myth_init(); //MassiveThreads
}

void glt_finalize() 
{
    myth_fini(); //MassiveThreads
}

