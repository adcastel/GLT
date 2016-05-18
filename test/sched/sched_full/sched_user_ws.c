/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 * See COPYRIGHT in top-level directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "abt.h"
//#include "abttest.h"

#ifdef FASTGLT
#include <fast_glt.h>
#else
#include <glt.h>
#endif

/* This test creates a user-defined scheduler, which is a simple work-stealing
 * scheduler, and uses it for ESs. */

#define DEFAULT_NUM_XSTREAMS    4
#define DEFAULT_NUM_THREADS     4

static int num_xstreams = DEFAULT_NUM_XSTREAMS;
static int num_threads = DEFAULT_NUM_THREADS;

/* scheduler data structure and functions */
typedef struct {
    uint32_t event_freq;
} sched_data_t;

static inline sched_data_t *sched_data_get_ptr(void *data)
{
    return (sched_data_t *)data;
}

static int sched_init(GLT_sched sched, GLT_sched_config config)
{
    int ret = 0;

    sched_data_t *p_data = (sched_data_t *)calloc(1, sizeof(sched_data_t));

    /* Set the variables from the config */
    glt_scheduler_config_read(config, 1, &p_data->event_freq);
    //ABT_TEST_ERROR(ret, "ABT_sched_config_read");

    glt_scheduler_set_data(sched, (void *)p_data);

    return ret;
}

static void sched_run(GLT_sched sched)
{
    int ret = 0;
    uint32_t work_count = 0;
    void *data;
    sched_data_t *p_data;
    GLT_pool my_pool;
    size_t size;
    GLT_unit unit;
    uint32_t event_freq;
    int num_pools;
    GLT_pool *pools;
    int target;
    unsigned seed = time(NULL);

    glt_scheduler_get_data(sched, &data);
    p_data = sched_data_get_ptr(data);
    event_freq = p_data->event_freq;

    glt_pool_scheduler_get_num_pools(sched, &num_pools);
    //ABT_TEST_ERROR(ret, "ABT_sched_get_num_pools");

    pools = (GLT_pool *)malloc(sizeof(GLT_pool) * num_pools);
    glt_pool_scheduler_get_pools(sched, num_pools, 0, pools);
    //ABT_TEST_ERROR(ret, "ABT_sched_get_pools");
    my_pool = pools[0];

    while (1) {
//    printf("En el while\n");
        /* Execute one work unit from the scheduler's pool */
        glt_pool_pop(my_pool, &unit);
        if (unit != GLT_UNIT_NULL) {
//		printf("Tengo trabajo\n");
            glt_thread_run_unit(unit, my_pool);
//		printf("Tengo ejecutado\n");
        } else if (num_pools > 1) {
//		printf("No Tengo trabajo\n");
            /* Steal a work unit from other pools */
            target = (num_pools == 2) ? 1 : (rand_r(&seed) % (num_pools-1) + 1);
            GLT_pool tar_pool = pools[target];
            glt_pool_get_size(tar_pool, &size);
            if (size > 0) {
//		printf("Robo trabajo\n");
                /* Pop one work unit */
                glt_pool_pop(tar_pool, &unit);
                if (unit != GLT_UNIT_NULL) {
//			printf("ejecuto lo robao\n");
                    glt_thread_run_unit(unit, tar_pool);
                }
            }
        }

        if (++work_count >= event_freq) {
            GLT_bool stop;
            glt_scheduler_has_to_stop(sched, &stop);
            //ABT_TEST_ERROR(ret, "ABT_sched_has_to_stop");
            if (stop == GLT_TRUE) break;
            work_count = 0;
            glt_thread_check_events(sched);
        }
    }

    free(pools);
}

static int sched_free(GLT_sched sched)
{
    int ret = 0;
    void *data;

    glt_scheduler_get_data(sched, &data);
    sched_data_t *p_data = sched_data_get_ptr(data);
    free(p_data);

    return ret;
}

static GLT_pool *create_pools(int num)
{
    GLT_pool *pools;
    int i, ret;

    pools = (GLT_pool *)malloc(sizeof(GLT_pool) * num);
    for (i = 0; i < num; i++) {
        glt_pool_create_basic(GLT_POOL_FIFO, GLT_POOL_ACCESS_MPMC,
                                    GLT_TRUE, &pools[i]);
        //ABT_TEST_ERROR(ret, "ABT_pool_create_basic");
    }

    return pools;
}

static GLT_sched *create_scheds(int num, GLT_pool *pools)
{
    int i, k, ret;
    GLT_pool *my_pools;
    GLT_sched *scheds;
    GLT_sched_config config;

    GLT_sched_config_var cv_event_freq = {
        .idx = 0,
        .type = GLT_SCHED_CONFIG_INT
    };

    GLT_sched_def sched_def = {
        .type = GLT_SCHED_TYPE_ULT,
        .init = sched_init,
        .run = sched_run,
        .free = sched_free,
        .get_migr_pool = NULL
    };

    /* Create a scheduler config */
    /* NOTE: The same scheduler config can be used for all schedulers. */
    glt_scheduler_config_create(&config,
                                  cv_event_freq, 10,
                                  GLT_sched_config_var_end);
    //ABT_TEST_ERROR(ret, "ABT_sched_config_create");

    my_pools = (GLT_pool *)malloc(sizeof(GLT_pool) * num);
    scheds = (GLT_sched *)malloc(sizeof(GLT_sched) * num);
    for (i = 0; i < num; i++) {
        for (k = 0; k < num; k++) {
            my_pools[k] = pools[(i + k) % num];
        }

        glt_pool_create_scheduler(&sched_def, num, my_pools, config, &scheds[i]);
        //ABT_TEST_ERROR(ret, "ABT_sched_create");
    }
    free(my_pools);

    glt_scheduler_config_free(&config);
    //ABT_TEST_ERROR(ret, "ABT_sched_config_free");

    return scheds;
}

static void free_scheds(int num, GLT_sched *scheds)
{
    int i, ret;

    /* Free schedulers */
    /* Note that we do not need to free the scheduler for the primary ES,
     * i.e., xstreams[0], because its scheduler will be automatically freed in
     * ABT_finalize(). */
    for (i = 1; i < num; i++) {
        glt_scheduler_free(&scheds[i]);
        //ABT_TEST_ERROR(ret, "ABT_sched_free");
    }

    free(scheds);
}

static void thread_func(void *arg)
{
    //GLT_TEST_UNUSED(arg);
    int old_rank, cur_rank;
    GLT_ult self;
    GLT_ult_id id;
    char *msg;

    glt_thread_self_rank(&cur_rank);
    glt_ult_self(&self);
    glt_ult_get_id(&id,self);

    printf( "[U%lu:E%d] Hello, world!\n", id, cur_rank);

    glt_yield();

    old_rank = cur_rank;
    glt_thread_self_rank(&cur_rank);
    msg = (cur_rank == old_rank) ? "" : " (stolen)";
    printf( "[U%lu:E%d] Hello again #1.%s\n", id, cur_rank, msg);

    glt_yield();

    old_rank = cur_rank;
    glt_thread_self_rank(&cur_rank);
    msg = (cur_rank == old_rank) ? "" : " (stolen)";
    printf( "[U%lu:E%d] Hello again #2.%s\n", id, cur_rank, msg);

    glt_yield();

    old_rank = cur_rank;
    glt_thread_self_rank(&cur_rank);
    msg = (cur_rank == old_rank) ? "" : " (stolen)";
    printf( "[U%lu:E%d] Goodbye, world!%s\n", id, cur_rank, msg);
}

static void create_threads(void *arg)
{
    //GLT_TEST_UNUSED(arg);
    int i, rank;
    int ret;
    GLT_thread xstream;
    GLT_pool pool;
    GLT_ult self;
    GLT_ult *threads;
    GLT_ult_id id;

    glt_thread_self(&xstream);
    //ABT_TEST_ERROR(ret, "ABT_xstream_self");
    glt_thread_get_main_pools(xstream, 1, &pool);
    //ABT_TEST_ERROR(ret, "ABT_xstream_get_main_pools");

    glt_thread_get_rank(xstream, &rank);
    glt_ult_self(&self);
    glt_ult_get_id( &id,self);

    printf( "[U%lu:E%d] creating ULTs\n", id, rank);
    threads = (GLT_ult *)malloc(sizeof(GLT_ult) * num_threads);
    for (i = 0; i < num_threads; i++) {
        glt_ult_create_to_pool(pool,thread_func, NULL,
                                &threads[i]);
        //ABT_TEST_ERROR(ret, "ABT_thread_create");
    }

    glt_thread_get_rank(xstream, &rank);
    printf( "[U%lu:E%d] freeing ULTs\n", id, rank);
    for (i = 0; i < num_threads; i++) {
        glt_ult_join(&threads[i]);
	printf("%d freed\n",i);
        //ABT_TEST_ERROR(ret, "ABT_thread_free");
    }
    free(threads);
}

int main(int argc, char *argv[])
{
    int i, ret;
    GLT_thread *xstreams;
    GLT_sched *scheds;
    GLT_pool *pools;

    /* Initialize */
    glt_init(argc, argv);

   /* if (argc > 1) {
        num_xstreams = glt_test_get_arg_val(ABT_TEST_ARG_N_ES);
        num_threads  = glt_test_get_arg_val(ABT_TEST_ARG_N_ULT);
    }*/
    printf( "num_xstreams=%d num_threads=%d\n", num_xstreams,
                    num_threads);

    xstreams = (GLT_thread *)malloc(sizeof(GLT_thread) * num_xstreams);

    /* Create pools */
    pools = create_pools(num_xstreams);
printf("pools created\n");
    /* Create schedulers */
    scheds = create_scheds(num_xstreams, pools);
printf("scheds created\n");

    /* Create Execution Streams */
    glt_thread_self(&xstreams[0]);
    printf("1\n");
    //ABT_TEST_ERROR(ret, "ABT_xstream_self");
    glt_thread_set_main_sched(xstreams[0], scheds[0]);
    printf("2\n");
    //ABT_TEST_ERROR(ret, "ABT_xstream_set_main_sched");
    for (i = 1; i < num_xstreams; i++) {
        glt_thread_create(scheds[i], &xstreams[i]);
        //ABT_TEST_ERROR(ret, "ABT_xstream_create");
    }
    printf("3\n");

    /* Create ULTs */
    for (i = 0; i < num_xstreams; i++) {
       glt_ult_create_to_pool(pools[i],create_threads, NULL, NULL);
        //ABT_TEST_ERROR(ret, "ABT_thread_create");
    }
    printf("4\n");

    glt_yield();

    /* Join and free Execution Streams */
    for (i = 1; i < num_xstreams; i++) {
        glt_thread_join(xstreams[i]);
        //ABT_TEST_ERROR(ret, "ABT_xstream_join");
        glt_thread_free(&xstreams[i]);
        //ABT_TEST_ERROR(ret, "ABT_xstream_free");
    }
    printf("5\n");

    free_scheds(num_xstreams, scheds);
    printf("6\n");

    /* Finalize */
    //glt_finalize();

    free(xstreams);
    free(pools);

    return ret;
}

