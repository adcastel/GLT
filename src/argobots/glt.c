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


static int __kmp_abt_sched_init(ABT_sched sched, ABT_sched_config config);
static void __kmp_abt_sched_run_es0(ABT_sched sched);
static void __kmp_abt_sched_run(ABT_sched sched);
static int __kmp_abt_sched_free(ABT_sched sched);


glt_team_t * main_team;

GLT_func_prefix void glt_start() {
    //printf("Starting with ARGOBOTS\n");
}

GLT_func_prefix void glt_end() {
    //printf("Ending with ARGOBOTS\n");
}

GLT_func_prefix glt_team_t * glt_get_team(){
    return main_team;
}

GLT_func_prefix void glt_init(int argc, char * argv[]) {
    int num_threads = get_nprocs();
   
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));
    CHECK(ABT_init(argc, argv),ABT_SUCCESS);
    if(getenv("GLTO_NUM_THREADS") != NULL){
        num_threads = atoi(getenv("GLTO_NUM_THREADS"));
        int num_pools = num_threads;
        main_team->num_xstreams = num_threads;
        main_team->num_pools = num_pools;
        main_team->max_elem = get_nprocs();
        main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * num_threads);//main_team->max_elem);
        main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * num_pools);//main_team->max_elem);
        main_team->spools = (ABT_pool *) malloc(sizeof (ABT_pool) * num_pools);//main_team->max_elem);
        main_team->sched = (ABT_sched *) malloc(num_threads * sizeof(ABT_sched));
        main_team->glto =1;
        for (int i = 0; i < num_threads; i++) {
            ABT_pool_create_basic(ABT_POOL_FIFO, ABT_POOL_ACCESS_MPSC, ABT_TRUE,
                                       &main_team->pools[i]);
        //KMP_CHECK_SYSFAIL( "ABT_pool_create_basic", status );
            ABT_pool_create_basic(ABT_POOL_FIFO, ABT_POOL_ACCESS_MPMC, ABT_TRUE,
                                       &main_team->spools[i]);
        //KMP_CHECK_SYSFAIL( "ABT_pool_create_basic", status );
        }
        
            /* Create a scheduler for ES0 */
        ABT_sched_config_var cv_freq = {
            .idx = 0,
            .type = ABT_SCHED_CONFIG_INT
        };

        ABT_sched_config config;
        int freq = (num_threads < 100) ? 100 : num_threads;
        ABT_sched_config_create(&config, cv_freq, freq, ABT_sched_config_var_end);

        ABT_sched_def sched_def = {
            .type = ABT_SCHED_TYPE_ULT,
            .init = __kmp_abt_sched_init,
            .run  = __kmp_abt_sched_run_es0,
            .free = __kmp_abt_sched_free,
            .get_migr_pool = NULL
        };

        ABT_pool *my_pools = (ABT_pool *)malloc((num_threads+1) * sizeof(ABT_pool));
        my_pools[0] = main_team->pools[0];
        for (int k = 0; k < num_threads; k++) {
            my_pools[k+1] = main_team->spools[k];
        }
        ABT_sched_create(&sched_def, num_threads+1, my_pools,
                              config, &main_team->sched[0]);
    //KMP_CHECK_SYSFAIL( "ABT_sched_create", status );

    /* Create schedulers for other ESs */
        sched_def.run = __kmp_abt_sched_run;
        for (int i = 1; i < num_threads; i++) {
            my_pools[0] = main_team->pools[i];
            for (int k = 0; k < num_threads; k++) {
                my_pools[k+1] = main_team->spools[(i + k) % num_threads];
            }
            ABT_sched_create(&sched_def, num_threads+1, my_pools,
                                  config, &main_team->sched[i]);
       // KMP_CHECK_SYSFAIL( "ABT_sched_create", status );
        }
       
        free(my_pools);
        ABT_sched_config_free(&config);

       /* Create ESs */
        ABT_xstream_self(&main_team->team[0]);
    //KMP_CHECK_SYSFAIL( "ABT_xstream_self", status );
        ABT_xstream_set_main_sched(main_team->team[0], main_team->sched[0]);
    //KMP_CHECK_SYSFAIL( "ABT_xstream_set_main_sched", status );
        for (int i = 1; i < num_threads; i++) {
            ABT_xstream_create(main_team->sched[i], &main_team->team[i]);
        //KMP_CHECK_SYSFAIL( "ABT_xstream_create", status );
        }
    }
    else{

        if (getenv("GLT_NUM_THREADS") != NULL) {
            num_threads = atoi(getenv("GLT_NUM_THREADS"));
        }
        //printf("voy a comportarme como glt\n"); 

        int num_pools = num_threads;

        if (getenv("GLT_NUM_POOLS") != NULL) {
            num_pools = atoi(getenv("GLT_NUM_POOLS"));
        }

        CHECK(ABT_xstream_self(&main_team->master),ABT_SUCCESS);

        main_team->num_xstreams = num_threads;
        main_team->num_pools = num_pools;
        main_team->max_elem = get_nprocs();
        main_team->team = (ABT_xstream *) malloc(sizeof (ABT_xstream) * num_threads);//main_team->max_elem);
        main_team->pools = (ABT_pool *) malloc(sizeof (ABT_pool) * num_pools);//main_team->max_elem);
        main_team->glto =0;

        for (int i = 0; i < num_pools; i++) {
            CHECK(ABT_pool_create_basic(ABT_POOL_FIFO, ABT_POOL_ACCESS_MPMC, ABT_TRUE,
                &main_team->pools[i]),ABT_SUCCESS);
        }

        CHECK(ABT_xstream_self(&main_team->team[0]),ABT_SUCCESS);
        CHECK(ABT_xstream_set_main_sched_basic(main_team->team[0], ABT_SCHED_DEFAULT,
            1, &main_team->pools[0]),ABT_SUCCESS);

        for (int i = 1; i < num_threads; i++) {
            CHECK(ABT_xstream_create_basic(ABT_SCHED_DEFAULT, 1,
                &main_team->pools[i % main_team->num_pools],
                ABT_SCHED_CONFIG_NULL, &main_team->team[i]),ABT_SUCCESS);
            CHECK(ABT_xstream_start(main_team->team[i]),ABT_SUCCESS);
        }
    }
}

GLT_func_prefix void glt_finalize() {
    for (int i = 1; i < main_team->num_xstreams; i++) {
        CHECK(ABT_xstream_join(main_team->team[i]),ABT_SUCCESS);
        CHECK(ABT_xstream_free(&main_team->team[i]),ABT_SUCCESS);
    }
    CHECK(ABT_finalize(),ABT_SUCCESS);
}



typedef struct {
    uint32_t event_freq;
} __kmp_abt_sched_data_t;

static int __kmp_abt_sched_init(ABT_sched sched, ABT_sched_config config)
{
    __kmp_abt_sched_data_t *p_data;
    p_data = (__kmp_abt_sched_data_t *)calloc(1, sizeof(__kmp_abt_sched_data_t));

    ABT_sched_config_read(config, 1, &p_data->event_freq);
    ABT_sched_set_data(sched, (void *)p_data);

    return ABT_SUCCESS;
}

static void __kmp_abt_sched_run_es0(ABT_sched sched)
{
    uint32_t work_count = 0;
    __kmp_abt_sched_data_t *p_data;
    int num_pools;
    ABT_pool *pools;
    ABT_unit unit;
    int target;
    ABT_bool stop;
    unsigned seed = time(NULL);
    size_t size;

    int run_cnt = 0;
#ifdef ABT_USE_SCHED_SLEEP
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = 128;
#endif

    ABT_sched_get_data(sched, (void **)&p_data);
    ABT_sched_get_num_pools(sched, &num_pools);
    pools = (ABT_pool *)malloc(num_pools * sizeof(ABT_pool));
    ABT_sched_get_pools(sched, num_pools, 0, pools);

    while (1) {
        run_cnt = 0;

        /* Execute one work unit from the private pool */
        ABT_pool_get_size(pools[0], &size);
        if (size > 0) {
            ABT_pool_pop(pools[0], &unit);
            if (unit != ABT_UNIT_NULL) {
                ABT_xstream_run_unit(unit, pools[0]);
                run_cnt++;
            }
        }

        /* shared pool */
        ABT_pool_get_size(pools[1], &size);
        if (size > 0) {
            ABT_pool_pop(pools[1], &unit);
            if (unit != ABT_UNIT_NULL) {
                ABT_xstream_run_unit(unit, pools[1]);
                run_cnt++;
            }
        }

        if (run_cnt == 0 && num_pools > 2) {
            /* Steal a work unit from other pools */
            target = rand_r(&seed) % (num_pools-2) + 2;
            ABT_pool_get_size(pools[target], &size);
            if (size > 0) {
                ABT_pool_pop(pools[target], &unit);
                if (unit != ABT_UNIT_NULL) {
                    ABT_unit_set_associated_pool(unit, pools[1]);
                    ABT_xstream_run_unit(unit, pools[1]);
                    run_cnt++;
                }
            }
        }

        if (++work_count >= p_data->event_freq) {
            ABT_xstream_check_events(sched);
            ABT_sched_has_to_stop(sched, &stop);
            if (stop == ABT_TRUE) break;
            work_count = 0;
#ifdef ABT_USE_SCHED_SLEEP
            if (run_cnt == 0) {
                nanosleep(&sleep_time, NULL);
                if (sleep_time.tv_nsec < 1048576) {
                    sleep_time.tv_nsec <<= 2;
                }
            } else {
                sleep_time.tv_nsec = 128;
                run_cnt = 0;
            }
#endif /* ABT_USE_SCHED_SLEEP */
        }
    }
    free(pools);
}

static void __kmp_abt_sched_run(ABT_sched sched)
{
    uint32_t work_count = 0;
    __kmp_abt_sched_data_t *p_data;
    int num_pools;
    ABT_pool *pools;
    ABT_unit unit;
    int target;
    ABT_bool stop;
    unsigned seed = time(NULL);
    size_t size;

    int run_cnt = 0;
#ifdef ABT_USE_SCHED_SLEEP
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = 128;
#endif

    ABT_sched_get_data(sched, (void **)&p_data);
    ABT_sched_get_num_pools(sched, &num_pools);
    pools = (ABT_pool *)malloc(num_pools * sizeof(ABT_pool));
    ABT_sched_get_pools(sched, num_pools, 0, pools);

    while (1) {
#ifdef ABT_USE_PRIVATE_POOLS
        run_cnt = 0;

        /* Execute one work unit from the private pool */
        ABT_pool_get_size(pools[0], &size);
        if (size > 0) {
            ABT_pool_pop(pools[0], &unit);
            if (unit != ABT_UNIT_NULL) {
                ABT_xstream_run_unit(unit, pools[0]);
                run_cnt++;
            }
        }

        /* shared pool */
        ABT_pool_get_size(pools[1], &size);
        if (size > 0) {
            ABT_pool_pop(pools[1], &unit);
            if (unit != ABT_UNIT_NULL) {
                ABT_xstream_run_unit(unit, pools[1]);
                run_cnt++;
         }
        }

        /* Steal a work unit from other pools */
        if (run_cnt == 0) {
            target = rand_r(&seed) % (num_pools-2) + 2;
            ABT_pool_get_size(pools[target], &size);
            if (size > 0) {
                ABT_pool_pop(pools[target], &unit);
                if (unit != ABT_UNIT_NULL) {
                    ABT_unit_set_associated_pool(unit, pools[1]);
                    ABT_xstream_run_unit(unit, pools[1]);
                    run_cnt++;
                }
            }
        }
#else /* ABT_USE_PRIVATE_POOLS */
        /* Execute one work unit from the scheduler's pool */
        ABT_pool_get_size(pools[0], &size);
        if (size > 0) {
            ABT_pool_pop(pools[0], &unit);
            if (unit != ABT_UNIT_NULL) {
                ABT_xstream_run_unit(unit, pools[0]);
                run_cnt++;
            }
        }

        /* Steal a work unit from other pools */
        target = rand_r(&seed) % (num_pools-1) + 1;
        ABT_pool_get_size(pools[target], &size);
        if (size > 0) {
            ABT_pool_pop(pools[target], &unit);
            if (unit != ABT_UNIT_NULL) {
                ABT_unit_set_associated_pool(unit, pools[0]);
                ABT_xstream_run_unit(unit, pools[0]);
                run_cnt++;
            }
        }
#endif /* ABT_USE_PRIVATE_POOLS */

        if (++work_count >= p_data->event_freq) {
            ABT_xstream_check_events(sched);
            ABT_sched_has_to_stop(sched, &stop);
            if (stop == ABT_TRUE) break;
            work_count = 0;
#ifdef ABT_USE_SCHED_SLEEP
            if (run_cnt == 0) {
                nanosleep(&sleep_time, NULL);
                if (sleep_time.tv_nsec < 1048576) {
                    sleep_time.tv_nsec <<= 2;
                }
            } else {
                sleep_time.tv_nsec = 128;
                run_cnt = 0;
            }
#endif /* ABT_USE_SCHED_SLEEP */
        }
    }

    free(pools);
}

static int __kmp_abt_sched_free(ABT_sched sched)
{
    __kmp_abt_sched_data_t *p_data;

    ABT_sched_get_data(sched, (void **)&p_data);
    free(p_data);

    return ABT_SUCCESS;
}

