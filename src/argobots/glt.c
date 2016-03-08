#include <glt.h>


void glt_start() 
{
    printf("Starting with ARGOBOTS\n");
}

void glt_end() 
{
    printf("Ending with ARGOBOTS\n");
}

void glt_init(int argc, char * argv[]) 
{
    int num_threads = get_nprocs();
    

    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    ABT_init(argc, argv);

    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
    }
    
    int num_pools = num_threads;
    
    if (getenv("GLT_NUM_POOLS") != NULL) {
        num_pools = atoi(getenv("GLT_NUM_POOLS"));
    }

    ABT_xstream_self(&main_team->master);

    main_team->num_xstreams = num_threads;
    main_team->num_pools = num_pools;
    main_team->max_elem= get_nprocs()*2;
    main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * MAX(num_threads,get_nprocs()*2));
    main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * MAX(num_threads,get_nprocs()*2));

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
}

void glt_finalize() 
{
    for (int i = 1; i < main_team->num_xstreams; i++) {
        ABT_xstream_join(main_team->team[i]);
        ABT_xstream_free(&main_team->team[i]);
    }
    ABT_finalize();
}

