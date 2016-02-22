#include <glt.h>


void glt_start() {
#ifdef ARGOBOTS
    printf("Starting with ARGOBOTS\n");
#endif
#ifdef MASSIVETHREADS
    printf("Starting with MASSIVETHREADS\n");
#endif
#ifdef QTHREADS
    printf("Starting with QTHREADS\n");
#endif
}

void glt_end() {
#ifdef ARGOBOTS
    printf("Ending with ARGOBOTS\n");
#endif
#ifdef MASSIVETHREADS
    printf("Ending with MASSIVETHREADS\n");
#endif
#ifdef QTHREADS
    printf("Ending with QTHREADS\n");
#endif
}

void glt_init(int argc, char * argv[]) {

    int num_threads = 1;

    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

#ifdef ARGOBOTS


    ABT_init(argc, argv);
    int num_pools = 1;
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
    }
    if (getenv("GLT_NUM_POOLS") != NULL) {
        num_pools = atoi(getenv("GLT_NUM_POOLS"));
    }

    main_team->num_xstreams = num_threads;
    main_team->num_pools = num_pools;
    printf("Argobots %d ES, %d Pools\n", num_threads, num_pools);
    ABT_xstream_self(&main_team->master);

    main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * num_threads);
    main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * num_pools);

    for (int i = 0; i < num_pools; i++) {
        ABT_pool_create_basic(ABT_POOL_FIFO, ABT_POOL_ACCESS_MPMC, ABT_TRUE,
                &main_team->pools[i]);
    }

    ABT_xstream_self(&main_team->team[0]);
    ABT_xstream_set_main_sched_basic(main_team->team[0], ABT_SCHED_DEFAULT,
            1, &main_team->pools[0]);
    for (int i = 1; i < num_threads; i++) {
        ABT_xstream_create_basic(ABT_SCHED_DEFAULT, 1,
                &main_team->pools[i % main_team->num_pools],
                ABT_SCHED_CONFIG_NULL, &main_team->team[i]);
        ABT_xstream_start(main_team->team[i]);
    }
#endif
#ifdef MASSIVETHREADS
    char buff[10];
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("MYTH_WORKER_NUM", buff, 1);
    } else
        num_threads = atoi(getenv("MYTH_WORKER_NUM"));

    setenv("MYTH_BIND_WORKERS", "1", 1);

    //printf("Massive %d Workers\n", num_threads);
    main_team->num_workers = num_threads;
    myth_init(); //MassiveThreads
#endif
#ifdef QTHREADS
    char buff[10];
    int num_workers_per_thread;
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("QTHREAD_NUM_SHEPHERDS", buff, 1);
    } else
        num_threads = atoi(getenv("QTHREAD_NUM_SHEPHERDS"));

    if (getenv("GLT_NUM_WORKERS_PER_THREAD") != NULL) {
        num_workers_per_thread = atoi(getenv("GLT_NUM_WORKERS_PER_THREAD"));
        sprintf(buff, "%d", num_workers_per_thread);
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", buff, 1);
    } else
        num_workers_per_thread = atoi(getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD"));
    if (num_threads == 1 && num_workers_per_thread > 1) {
        setenv("QTHREAD_SHEPHERDS_BOUNDARY", "node", 1);
        setenv("QTHREAD_WORKER_UNIT", "core", 1);
    }
    if (num_threads > 1) {
        setenv("QTHREAD_SHEPHERDS_BOUNDARY", "core", 1);
        setenv("QTHREAD_WORKER_UNIT", "core", 1);
    }
    setenv("QTHREAD_AFFINITY", "yes", 1);

    //printf("Qthreads %d Shepherds, %d Workers_per_shepherd\n", num_threads, num_workers_per_thread);

    main_team->num_shepherds = num_threads;
    main_team->num_workers_per_shepherd = num_workers_per_thread;
    qthread_initialize(); //qthreads
#endif
}

void glt_finalize() {

#ifdef ARGOBOTS

    for (int i = 1; i < main_team->num_xstreams; i++) {
        ABT_xstream_join(main_team->team[i]);
        ABT_xstream_free(&main_team->team[i]);
    }
    ABT_finalize();

#endif
#ifdef MASSIVETHREADS
    myth_fini(); //MassiveThreads
#endif
#ifdef QTHREADS
    qthread_finalize();
#endif        
}

