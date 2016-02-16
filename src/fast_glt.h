/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H



#ifdef ARGOBOTS
#include <stdio.h>
#include <stdlib.h>
#include <abt.h>



#define GLT_ult ABT_thread
#define GLT_tasklet ABT_task
#define GLT_thread ABT_xstream

typedef struct glt_team {
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
} glt_team_t;


#endif
#ifdef MASSIVETHREADS
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <myth.h>

#define GLT_ult myth_thread_t
#define GLT_tasklet myth_thread_t
#define GLT_thread myth_thread_t
#define GLT_ult_attribute NULL

typedef struct glt_team {
    int num_workers;
} glt_team_t;

#endif

#ifdef QTHREADS
#include <stdio.h>
#include <stdlib.h>
#include <qthread/qthread.h>

#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread aligned_t
#define GLT_ult_attribute NULL

typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;

#endif

#define GLT_VERSION "You are using glt 0.1v (adcastel@uji.es)"
/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

static inline void glt_start() {
#ifdef ARGOBOTS
    //printf("Starting with ARGOBOTS\n");
#endif
#ifdef MASSIVETHREADS
    //printf("Starting with MASSIVETHREADS\n");
#endif
#ifdef QTHREADS
    //printf("Starting with QTHREADS\n");
#endif
}

static inline  void glt_end() {
#ifdef ARGOBOTS
    //printf("Ending with ARGOBOTS\n");
#endif
#ifdef MASSIVETHREADS
    //printf("Ending with MASSIVETHREADS\n");
#endif
#ifdef QTHREADS
    //printf("Ending with QTHREADS\n");
#endif
}

static inline  void glt_init(int argc, char * argv[]) {

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
    //printf("Argobots %d ES, %d Pools\n", num_threads, num_pools);
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

static inline void glt_finalize() {

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
}

static inline GLT_ult * glt_ult_malloc(int number_of_ult) {
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

static inline GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) {
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

static inline void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) {
#ifdef ARGOBOTS
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
#endif
#ifdef MASSIVETHREADS
    *new_ult = myth_create((void *) thread_func, arg);
#endif
#ifdef QTHREADS
    qthread_fork((void *) thread_func, arg, new_ult);
#endif
}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
#ifdef ARGOBOTS
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);
#endif
#ifdef MASSIVETHREADS
    glt_ult_creation(thread_func, arg, new_ult);
#endif
#ifdef QTHREADS
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
#endif
}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
#ifdef ARGOBOTS
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
#endif
#ifdef MASSIVETHREADS
    *new_ult = myth_create((void *) thread_func, arg);
#endif
#ifdef QTHREADS
    qthread_fork((void *) thread_func, arg, new_ult);
#endif
}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) {
#ifdef ARGOBOTS
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);
#endif
#ifdef MASSIVETHREADS
    glt_ult_creation(thread_func, arg, new_ult);
#endif
#ifdef QTHREADS
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
#endif
}

static inline void glt_yield() {
#ifdef ARGOBOTS
    ABT_thread_yield();
#endif
#ifdef MASSIVETHREADS
    myth_yield(0);
#endif
#ifdef QTHREADS
    qthread_yield();
#endif
}

static inline void glt_yield_to(GLT_ult ult) {
#ifdef ARGOBOTS
    ABT_thread_yield_to(ult);
#endif
#ifdef MASSIVETHREADS
    myth_yield(0);
#endif
#ifdef QTHREADS
    qthread_yield();
#endif
}

static inline void glt_ult_join(GLT_ult *ult) {
#ifdef ARGOBOTS
    ABT_thread_free(ult);
#endif
#ifdef MASSIVETHREADS
    myth_join(*ult, NULL);
#endif
#ifdef QTHREADS
    qthread_readFF(NULL, ult);
#endif
}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) {
#ifdef ARGOBOTS
    ABT_task_free(tasklet);
#endif
#ifdef MASSIVETHREADS
    myth_join(*tasklet, NULL);
#endif
#ifdef QTHREADS
    qthread_readFF(NULL, tasklet);
#endif
}

static inline int glt_get_num_threads() {
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

static inline int glt_get_thread_num() {
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




#endif	/* FAST_GLT_H */

