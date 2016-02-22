/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */




#ifndef FAST_GLT_H
#define	FAST_GLT_H



#include <stdio.h>
#include <stdlib.h>
#include <abt.h>



#define GLT_ult ABT_thread
#define GLT_tasklet ABT_task
#define GLT_thread ABT_xstream
#define GLT_mutex ABT_mutex
#define GLT_barrier ABT_barrier
#define GLT_cond ABT_cond

 
typedef struct glt_team {
    ABT_xstream master;
    ABT_xstream *team;
    int num_xstreams;
    int num_pools;
    ABT_pool *pools;
} glt_team_t;



#define GLT_VERSION "You are using fast glt 0.1v over Argobots(adcastel@uji.es)"
/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

static inline void glt_start() {
    //printf("Starting with ARGOBOTS\n");

}
static inline  void glt_end() {
    //printf("Ending with ARGOBOTS\n");

}

static inline  void glt_init(int argc, char * argv[]) {

    int num_threads = 1;
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));



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

}

static inline void glt_finalize() {


    for (int i = 1; i < main_team->num_xstreams; i++) {
        ABT_xstream_join(main_team->team[i]);
        ABT_xstream_free(&main_team->team[i]);
    }
    ABT_finalize();


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
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);

}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) {
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_thread_create(pool, thread_func, arg, ABT_THREAD_ATTR_NULL, new_ult);

}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) {
    ABT_xstream xstream;
    ABT_xstream_self(&xstream);
    ABT_pool pool;
    ABT_xstream_get_main_pools(xstream, 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);

}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) {
    ABT_pool pool;
    ABT_xstream_get_main_pools(main_team->team[dest], 1, &pool);
    ABT_task_create(pool, thread_func, arg, new_ult);

}

static inline void glt_yield() {
    ABT_thread_yield();
}

static inline void glt_yield_to(GLT_ult ult) {
    ABT_thread_yield_to(ult);

}

static inline void glt_ult_join(GLT_ult *ult) {
    ABT_thread_free(ult);

}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) {
    ABT_task_free(tasklet);

}

static inline void glt_mutex_create(GLT_mutex * mutex){
    ABT_mutex_create(mutex);

}
static inline void glt_mutex_lock(GLT_mutex mutex){
    ABT_mutex_lock(mutex);

}
static inline void glt_mutex_unlock(GLT_mutex mutex){
    ABT_mutex_unlock(mutex);

}

static inline void glt_mutex_free(GLT_mutex * mutex){
    ABT_mutex_free(mutex);

}


static inline void glt_barrier_create(int num_waiters, GLT_barrier *barrier){
    ABT_barrier_create(num_waiters, barrier);

}

static inline void glt_barrier_free(GLT_barrier *barrier){
    ABT_barrier_free(barrier);

}

static inline void glt_barrier_wait(GLT_barrier *barrier){

    ABT_barrier_wait(*barrier);

}

static inline void glt_cond_create(GLT_cond *cond){
    ABT_cond_create (cond);

}

static inline void glt_cond_free(GLT_cond *cond){
    ABT_cond_free (cond);
}

static inline void glt_cond_signal(GLT_cond cond){
    ABT_cond_signal (cond);

}

static inline void glt_cond_wait(GLT_cond cond, GLT_mutex mutex){
    ABT_cond_wait (cond, mutex);
}

static inline void glt_cond_broadcast(GLT_cond cond){
    ABT_cond_broadcast (cond);

}

static inline int glt_get_num_threads() {
    return main_team->num_xstreams;

}

static inline int glt_get_thread_num() {
    int rank;
    ABT_xstream_self_rank(&rank);
    return rank;

}




#endif	/* FAST_GLT_H */

