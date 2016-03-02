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
#include <sys/time.h>
#include <sys/sysinfo.h>


#include <qthread/qthread.h>
#include <qthread/barrier.h>
#include <qthread/qtimer.h>
#include <qthread/sinc.h>
#include <qthread/qloop.h>
#include <qthread/qutil.h>
#include <qthread/qpool.h>
#include <qthread/qarray.h>
#include <qthread/qlfqueue.h>
#include <qthread/qdqueue.h>
#include <qthread/dictionary.h>








#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread qthread_shepherd_id_t
#define GLT_mutex aligned_t
#define GLT_barrier  qt_barrier_t
#define GLT_cond aligned_t
#define GLT_timer qtimer_t
#define GLT_bool int

//Extended variables
#ifndef CORE
#define GLT_syncvar syncvar_t
#define GLT_aligned aligned_t
#define GLT_memory_state aligned_t
#define GLT_sinc_op qt_sinc_op_f
#define GLT_sinc qt_sinc_t
#define GLT_loop_f qt_loop_f
#define GLT_loopr_f qt_loopr_f
#define GLT_loop_step_f qt_loop_step_f
#define GLT_accum_f qt_accum_f
#define GLT_loop_queue qqloop_handle_t
#define GLT_loop_queue_kind qt_loop_queue_type
#define GLT_ds_pool qpool
#define GLT_ds_array qarray
#define GLT_ds_array_distribution distribution_t
#define GLT_ds_loop_f qa_loop_f
#define GLT_ds_loopr_f qa_loopr_f
#define GLT_ds_cloop_f qa_cloop_f
#define GLT_ds_lfqueue qlfqueue_t
#define GLT_ds_dqueue qdqueue_t
#define GLT_ds_dictionary qt_dictionary
#define GLT_ds_dictionary_key_equals qt_dict_key_equals_f
#define GLT_ds_dictionary_hash qt_dict_hash_f
#define GLT_ds_dictionary_tag_cleanup qt_dict_tag_cleanup_f


//ARGOBOTS
#define GLT_event_kind void *
#define GLT_event_cb_fn void *
#define GLT_future void *
#define GLT_promise void *
#define GLT_key void *
#define GLT_pool_def void *
#define GLT_pool_config void *
#define GLT_pool void *
#define GLT_pool_kind void *
#define GLT_pool_access void *
#define GLT_unit void *
#define GLT_sched void *
#define GLT_sched_config void *
#define GLT_sched_def void *
#define GLT_sched_predef void *
#define GLT_thread_state void *
#define GLT_tasklet_state void *
#define GLT_ult_state void *
#define GLT_ult_id int
#define GLT_ult_attr void *
#define GLT_unit_type void *


#define glt_scheduler_config_create 
#define glt_scheduler_config_read

#define glt_ult_creation_precond(f,a,u,n,...) qthread_fork_precond(f,a,u,n,...)
#define glt_ult_creation_precond_to(f,a,u,d,n,...) qthread_fork_precond_to(f,a,u,d,n,...)

#endif


typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;


#define GLT_VERSION "You are using fast glt 0.1v over Qthreads (adcastel@uji.es)"
#define GLT_ERROR_ARG "Error: This feature is only supported by Argobots implementation and you are using MassiveThreads. Please use the query functions"

/* Main team structure*/
//void __attribute__((constructor)) glt_start(void);
//void __attribute__((destructor)) glt_end(void);

glt_team_t * main_team;

static inline void glt_start() 
{
    //printf("Starting with QTHREADS\n");
}

static inline  void glt_end() 
{
    //printf("Ending with QTHREADS\n");
}

static inline  void glt_init(int argc, char * argv[]) 
{
    int num_threads = get_nprocs();
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    int num_workers_per_thread;
    
    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("QTHREAD_NUM_SHEPHERDS", buff, 1);
    } else if (getenv("QTHREAD_NUM_SHEPHERDS") != NULL){
        num_threads = atoi(getenv("QTHREAD_NUM_SHEPHERDS"));
    } else {
        setenv("QTHREAD_NUM_SHEPHERDS", "1", 1);
    }

    if (getenv("GLT_NUM_WORKERS_PER_THREAD") != NULL) {
        num_workers_per_thread = atoi(getenv("GLT_NUM_WORKERS_PER_THREAD"));
        sprintf(buff, "%d", num_workers_per_thread);
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", buff, 1);
    } else if (getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD") != NULL) {
        num_workers_per_thread = atoi(getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD"));
    }
    else {
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", "1", 1);
    }
    
    if (num_threads == 1 && num_workers_per_thread > 1) {
        setenv("QTHREAD_SHEPHERDS_BOUNDARY", "node", 1);
        setenv("QTHREAD_WORKER_UNIT", "core", 1);
    }
    if (num_threads > 1) {
        setenv("QTHREAD_SHEPHERDS_BOUNDARY", "core", 1);
        setenv("QTHREAD_WORKER_UNIT", "core", 1);
    }
    setenv("QTHREAD_AFFINITY", "yes", 1);

    main_team->num_shepherds = num_threads;
    main_team->num_workers_per_shepherd = num_workers_per_thread;
    qthread_initialize(); //qthreads
}

static inline void glt_finalize() 
{
    qthread_finalize();
}

static inline GLT_ult * glt_ult_malloc(int number_of_ult) 
{
    GLT_ult * ults = (GLT_ult *) malloc(sizeof (GLT_ult) * number_of_ult);
    return ults;
}

static inline GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets) 
{
    GLT_tasklet * tasklets = (GLT_tasklet *) malloc(sizeof (GLT_tasklet) * number_of_tasklets);
    return tasklets;
}

static inline void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult) 
{
    qthread_fork((void *) thread_func, arg, new_ult);
}

static inline void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest) 
{
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

static inline void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult) 
{
    qthread_fork((void *) thread_func, arg, new_ult);
}

static inline void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest) 
{
    qthread_fork_to((void *) thread_func, arg, new_ult, dest);
}

static inline void glt_yield() 
{
    qthread_yield();
}

static inline void glt_yield_to(GLT_ult ult) 
{
    qthread_yield();
}

static inline void glt_ult_join(GLT_ult *ult) 
{
    qthread_readFF(NULL, ult);
}

static inline void glt_tasklet_join(GLT_tasklet *tasklet) 
{
    qthread_readFF(NULL, tasklet);
}

static inline uint64_t glt_get_ult_id(GLT_ult ult)
{
    uint64_t id = qthread_id();
    return id;
}

static inline void glt_mutex_create(GLT_mutex * mutex)
{
    mutex = (GLT_mutex *)malloc(sizeof(GLT_mutex));
}

static inline void glt_mutex_lock(GLT_mutex mutex)
{
    qthread_lock(&mutex);
}

static inline void glt_mutex_unlock(GLT_mutex mutex)
{
    qthread_unlock(&mutex);
}

static inline void glt_mutex_free(GLT_mutex * mutex)
{
    free(mutex);
}


static inline void glt_barrier_create(int num_waiters, GLT_barrier *barrier)
{
    barrier = qt_barrier_create(num_waiters, UPLOCK);
}

static inline void glt_barrier_free(GLT_barrier *barrier)
{
    qt_barrier_destroy(barrier);
}

static inline void glt_barrier_wait(GLT_barrier *barrier)
{
    qt_barrier_enter(barrier);
}

static inline void glt_cond_create(GLT_cond *cond)
{
    cond = (GLT_cond *)malloc(sizeof(GLT_cond));
}

static inline void glt_cond_free(GLT_cond *cond)
{
    free(cond);
}

static inline void glt_cond_signal(GLT_cond cond)
{
    qthread_empty(&cond);
}

static inline void glt_cond_wait(GLT_cond cond, GLT_mutex mutex)
{
    /*Waits for memory to become empty and then fills it*/
    aligned_t fill=1;
    qthread_writeEF(&cond,&fill);
    qthread_lock(&mutex);
}

static inline void glt_cond_broadcast(GLT_cond cond)
{
    qthread_empty(&cond);
}

static inline double glt_get_wtime() 
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return (time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
}

static inline void glt_timer_create(GLT_timer * timer) 
{
    *timer = qtimer_create();
}

static inline void glt_timer_free(GLT_timer * timer) 
{
    qtimer_destroy(*timer);
}

static inline void glt_timer_start(GLT_timer timer) 
{
    qtimer_start(timer);
}

static inline void glt_timer_stop(GLT_timer timer) 
{
    qtimer_stop(timer);
}

static inline void glt_timer_get_secs(GLT_timer timer, double *secs) 
{
    *secs = qtimer_secs(timer);
}

static inline int glt_get_num_threads() 
{
    return main_team->num_shepherds;
}

static inline int glt_get_thread_num() 
{
    return qthread_shep();
}

//Extended functions

static inline int glt_can_extended_basic()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}


/*static inline void glt_ult_creation_precond(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int npreconds, ...){
    qthread_fork_precond((void *)thread_func,arg,ult,npreconds,...);
}

static inline void glt_ult_creation_precond_to(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int dest,int npreconds, ...){
    qthread_fork_precond_to((void *)thread_func,arg,ult,dest,npreconds,...);
}
*/
static inline void glt_ult_creation_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar){
    qthread_fork_syncvar((void *)thread_func,arg,syncvar);
}

static inline void glt_ult_creation_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest,int npreconds, ...){
    qthread_fork_syncvar_to((void *)thread_func,arg,syncvar,dest);
}

static inline void glt_ult_get_thread(GLT_thread *thread, int *worker)
{
    *worker = qthread_worker(thread);
}

static inline void glt_ult_get_thread_unique(GLT_thread *thread, int *worker)
{
    *worker = qthread_worker_unique(thread);
}

static inline void glt_ult_get_tasklocal(void * pointer, unsigned int size)
{
    pointer = qthread_get_tasklocal(size);
}

static inline void glt_ult_size_tasklocal(unsigned int *size)
{
    *size = qthread_size_tasklocal();
}

static inline void glt_ult_migrate_self_to(int dest)
{
    qthread_migrate_to(dest);
}

static inline void glt_ult_get_stack_left(size_t *size)
{
    *size = qthread_stackleft();
}

static inline void glt_ult_retloc(GLT_ult * ult)
{
    ult = qthread_retloc();
}

static inline int glt_can_atomic_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

static inline void glt_atomic_incr(GLT_aligned * operand, int incr)
{
    qthread_incr(operand,incr);
}

static inline void glt_atomic_fincr(float * operand, float incr)
{
    qthread_fincr(operand,incr);
}

static inline void glt_atomic_dincr(double * operand, double incr)
{
    qthread_dincr(operand,incr);
}

static inline void glt_atomic_cas(volatile GLT_aligned * addr, GLT_aligned oldval,
        GLT_aligned newval)
{
    qthread_cas(addr,oldval,newval);
}

static inline void glt_atomic_cas_ptr(void * volatile * addr, void * oldval,
        void * newval)
{
    qthread_cas_ptr(addr,oldval,newval);
}

static inline int glt_can_feb_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

static inline void glt_feb_empty(const GLT_memory_state *dest)
{
    qthread_empty(dest);
}

static inline void glt_feb_fill(const GLT_memory_state *dest)
{
    qthread_fill(dest);
}

static inline void glt_feb_status(const GLT_memory_state *addr, int *status)
{
    *status = qthread_feb_status(addr);
}

static inline void glt_feb_readFE( GLT_memory_state *dst, const GLT_memory_state *src)
{
    qthread_readFE(dst,src);
}

static inline void glt_feb_readFF( GLT_memory_state *dst, const GLT_memory_state *src)
{
    qthread_readFF(dst,src);
}

static inline void glt_feb_writeEF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    qthread_writeEF(dst,src);
}

static inline void glt_feb_writeEF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    qthread_writeEF_const(dst,src);
}

static inline void glt_feb_writeF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    qthread_writeF(dst,src);
}

static inline void glt_feb_writeF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    qthread_writeF_const(dst,src);
}

static inline void glt_syncvar_empty(GLT_syncvar *dest)
{
    qthread_syncvar_empty(dest);
}

static inline void glt_syncvar_fill(GLT_syncvar *dest)
{
    qthread_syncvar_fill(dest);
}

static inline void glt_syncvar_status(GLT_syncvar *addr, int *status)
{
    *status = qthread_syncvar_status(addr);
}

static inline void glt_syncvar_readFE( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    qthread_syncvar_readFE(dst,src);
}

static inline void glt_syncvar_readFF( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    qthread_syncvar_readFF(dst,src);
}

static inline void glt_syncvar_writeEF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    qthread_syncvar_writeEF(dst,src);
}

static inline void glt_syncvar_writeEF_const( GLT_syncvar *  dst,  uint64_t src)
{
    qthread_syncvar_writeEF_const(dst,src);
}

static inline void glt_syncvar_writeF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    qthread_syncvar_writeF(dst,src);
}

static inline void glt_syncvar_writeF_const( GLT_syncvar *  dst,  uint64_t src)
{
    qthread_syncvar_writeF_const(dst,src);
}

static inline int glt_can_sinc_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

static inline void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    sinc = qt_sinc_create(sizeof_value, initial_value, op, expected);
}

static inline void glt_sinc_init(GLT_sinc *restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    qt_sinc_init(sinc, sizeof_value, initial_value, op, expected);
}

static inline void glt_sinc_destroy(GLT_sinc *sinc)
{
    qt_sinc_destroy(sinc);
}

static inline void glt_sinc_fini(GLT_sinc * sinc)
{
    qt_sinc_fini(sinc);
}

static inline void glt_sinc_reset(GLT_sinc * sinc, size_t expect)
{
    qt_sinc_reset(sinc,expect);
}

static inline void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value)
{
    qt_sinc_submit(sinc,value);
}

static inline void glt_sinc_wait(GLT_sinc * restrict sinc,  void * restrict target)
{
    qt_sinc_wait(sinc,target);
}

static inline int glt_can_loop_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

static inline void glt_loop(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop(start,end,func,arg);
}

static inline void glt_loop_step(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg){
    qt_loop_step(start,end,stride,func,arg);
}

/*static inline void glt_loop_future(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_future(start,end,func,arg);
}

static inline void glt_loop_step_future(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg){
    qt_loop_step_future(start,end,stride,func,arg);
}
*/
static inline void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_balance(start,end,func,arg);
}

/*static inline void glt_loop_balance_future(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg){
    qt_loop_balance_future(start,end,func,arg);
}
*/
static inline void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc){
    qt_loopaccum_balance(start,end,size,out,func,arg,acc);
}

/*static inline void glt_loopaccum_balance_future(const size_t start, const size_t end, 
size_t size, void *out, const GLT_loop_f func, void * arg, GLT_accum_f acc){
    qt_loop_balance_future(start,end,size,out,func,arg,acc);
}
*/

static inline void glt_loop_queue_create(GLT_loop_queue * loop, GLT_loop_queue_kind kind,
        const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_f func, void * arg)
{
    loop = qt_loop_queue_create(kind,start,end,stride,func,arg);
}

static inline void glt_loop_queue_set_chunk(GLT_loop_queue * loop, size_t chunk)
{
    qt_loop_queue_setchunk(loop, chunk);
}

static inline void glt_loop_queue_run(GLT_loop_queue * loop)
{
    qt_loop_queue_run(loop);
}

static inline void glt_loop_queue_run_there(GLT_loop_queue * loop, GLT_thread id)
{
    qt_loop_queue_run_there(loop,id);
}

static inline void glt_loop_queue_add_thread(GLT_loop_queue * loop, GLT_thread id)
{
    qt_loop_queue_addworker(loop,id);
}

static inline int glt_can_util_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

static inline void glt_util_double_max(double * res, double * array, 
        size_t lenght, int checkfeb){
    *res = qutil_double_max(array,lenght, checkfeb);
}

static inline void glt_util_uint_max(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb){
    *res = qutil_uint_max(array,lenght, checkfeb);
}

static inline void glt_util_int_max(int * res, const long int * array, 
        size_t lenght, int checkfeb){
    *res = qutil_int_max(array,lenght, checkfeb);
}

static inline void glt_util_double_min(double * res, double * array, 
        size_t lenght, int checkfeb){
    *res = qutil_double_min(array,lenght, checkfeb);
}

static inline void glt_util_uint_min(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb){
    *res = qutil_uint_min(array,lenght, checkfeb);
}

static inline void glt_util_int_min(int * res, const long int * array, 
        size_t lenght, int checkfeb){
    *res = qutil_int_min(array,lenght, checkfeb);
}

static inline void glt_util_double_mult(double * res, double * array, 
        size_t lenght, int checkfeb){
    *res = qutil_double_mult(array,lenght, checkfeb);
}

static inline void glt_util_uint_mult(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb){
    *res = qutil_uint_mult(array,lenght, checkfeb);
}

static inline void glt_util_int_mult(int * res, const long int * array, 
        size_t lenght, int checkfeb){
    *res = qutil_int_mult(array,lenght, checkfeb);
}

static inline void glt_util_double_sum(double * res, double * array, 
        size_t lenght, int checkfeb){
    *res = qutil_double_sum(array,lenght, checkfeb);
}

static inline void glt_util_uint_sum(unsigned int * res, 
        const long unsigned int * array, size_t lenght, 
        int checkfeb){
    *res = qutil_uint_sum(array,lenght, checkfeb);
}

static inline void glt_util_int_sum(int * res, const long int * array, size_t lenght, 
        int checkfeb){
    *res = qutil_int_sum(array,lenght, checkfeb);
}

static inline void glt_util_qsort(double * array, size_t lenght)
{
    qutil_qsort(array,lenght);
}

static inline void glt_util_mergesort(double * array, size_t lenght)
{
    qutil_mergesort(array,lenght);
}

static inline int glt_can_data_structures_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

static inline void glt_ds_pool_create(GLT_ds_pool *pool, const size_t item_size)
{
    pool = qpool_create(item_size);
}

static inline void glt_ds_pool_create_aligned(GLT_ds_pool *pool, 
        const size_t item_size, const size_t alignment)
{
    pool = qpool_create_aligned(item_size, alignment);
}

static inline void glt_ds_pool_destroy(GLT_ds_pool *pool)
{
    qpool_destroy(pool);
}

static inline void glt_ds_pool_alloc(GLT_ds_pool *pool)
{
    qpool_alloc(pool);
}

static inline void glt_ds_pool_free(GLT_ds_pool *restrict pool, 
        void * restrict mem)
{
    qpool_free(pool, mem);
}

static inline void glt_ds_array_create(GLT_ds_array *array, const size_t count, 
        const size_t item_size)
{
    array = qarray_create(count,item_size);
}

static inline void glt_ds_array_create_tight(GLT_ds_array *array, 
        const size_t count, const size_t item_size)
{
    array = qarray_create_tight(count,item_size);
}

static inline void glt_ds_array_create_configured(GLT_ds_array *array, 
        const size_t count, const size_t item_size, 
        const GLT_ds_array_distribution d, const char thight, const int seg_pages)
{
    array = qarray_create_configured(count, item_size, d, thight, seg_pages);
}

static inline void glt_ds_array_destroy(GLT_ds_array *array)
{
    qarray_destroy(array);
}

static inline void glt_ds_array_elem(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    elem = qarray_elem(array,index);
}

static inline void glt_ds_array_elem_nomigrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    elem = qarray_elem_nomigrate(array,index);
}

static inline void glt_ds_array_elem_migrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    elem = qarray_elem_migrate(array,index);
}

static inline void glt_ds_array_thread_of(GLT_thread * id, const GLT_ds_array *array, 
        const size_t index)
{
    *id = qarray_shepof(array,index);
}

static inline void glt_ds_array_set_thread_of(GLT_ds_array *array, 
        const size_t index, GLT_thread id )
{
    qarray_set_shepof(array,index,id);
}

static inline void glt_ds_array_iter(GLT_ds_array *array, 
        const size_t start, const size_t stop, void(*thread_func)(void *))
{
    qarray_iter(array,start,stop,(void *)thread_func);
}

static inline void glt_ds_array_iter_loop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, void * arg)
{
    qarray_iter_loop(array,start,stop,thread_func,arg);
}

static inline void glt_ds_array_iter_nb(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, 
        void * args, aligned_t *arg)
{
    qarray_iter_loop_nb(array,start,stop,thread_func,args,arg);
}

static inline void glt_ds_array_iter_constloop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_cloop_f thread_func, 
        void * args)
{
    qarray_iter_constloop(array,start,stop,thread_func,args);
}

static inline void glt_ds_array_iter_loopaccum(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loopr_f thread_func, 
        void * args, void * ret, const size_t resize, GLT_accum_f acc )
{
    qarray_iter_loopaccum(array,start,stop,thread_func,args,ret,resize,acc);
}

static inline void glt_ds_lfqueue_create(GLT_ds_lfqueue * lfqueue)
{
    lfqueue = qlfqueue_create();
}

static inline void glt_ds_lfqueue_destroy(GLT_ds_lfqueue * lfqueue)
{
    qlfqueue_destroy(lfqueue);
}

static inline void glt_ds_lfqueue_enqueue(GLT_ds_lfqueue * lfqueue, void * elem)
{
    qlfqueue_enqueue(lfqueue,elem);
}

static inline void glt_ds_lfqueue_dequeue( void * elem, GLT_ds_lfqueue * lfqueue)
{
    elem = qlfqueue_dequeue(lfqueue);
}

static inline void glt_ds_lfqueue_empty(GLT_bool * empty, GLT_ds_lfqueue * lfqueue)
{
    *empty = qlfqueue_empty(lfqueue);
}

static inline void glt_ds_dqueue_create(GLT_ds_dqueue * dqueue)
{
    dqueue = qdqueue_create();
}

static inline void glt_ds_dqueue_destroy(GLT_ds_dqueue * dqueue)
{
    qdqueue_destroy(dqueue);
}

static inline void glt_ds_dqueue_enqueue(GLT_ds_dqueue * dqueue, void * elem)
{
    qdqueue_enqueue(dqueue,elem);
}

static inline void glt_ds_dqueue_enqueue_there(GLT_ds_dqueue * dqueue, 
        void * elem, GLT_thread id)
{
    qdqueue_enqueue_there(dqueue,elem,id);
}

static inline void glt_ds_dqueue_dequeue( void * elem, GLT_ds_dqueue * dqueue)
{
    elem = qdqueue_dequeue(dqueue);
}

static inline void glt_ds_dqueue_empty(GLT_bool * empty, GLT_ds_dqueue * dqueue)
{
    *empty = qdqueue_empty(dqueue);
}

//ARGOBOTS FUNCTIONS that are not supported by Qthreads

static inline int glt_can_event_functions()
{
    return 0;
}

static inline int glt_can_future_functions()
{
    return 0;
}

static inline int glt_can_promise_functions()
{
    return 0;
}
static inline int glt_can_tls_functions()
{
    return 0;
}

static inline int glt_can_extended_mutex()
{
    return 0;
}
static inline int glt_can_manage_pools()
{
    return 0;
}
static inline int glt_can_manage_scheduler()
{
    return 0;
}
static inline int glt_can_self()
{
    return 0;
}
static inline int glt_can_manage_threads()
{
    return 0;
}
static inline int can_extended_tasklets()
{
    return 0;
}
static inline int can_extended_ults()
{
    return 0;
}

#ifndef CORE

//HEADERS for ARGOBOTS extended functions
//Null codes
static inline void glt_get_error_str(int errno, char *str, size_t *len)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_event_del_callback(GLT_event_kind event, int cb_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_future_create(int nbytes, GLT_future *newfuture)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_future_free(GLT_future *future)
{
    printf("%s\n",GLT_ERROR_ARG);
}
static inline void glt_future_wait(GLT_future future, void **value)
{
    printf("%s\n",GLT_ERROR_ARG);
}
static inline void glt_future_set(GLT_future future, void *value, int nbytes)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_free(GLT_promise *promise)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_wait(GLT_promise promise)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_test(GLT_promise promise, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_promise_set(GLT_promise promise, void * value)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_create(void(*destructor)(void *value), GLT_key *newkey)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_free(GLT_key *key)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_set(GLT_key key, void *value)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_key_get(GLT_key key, void **value)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_lock_low(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_trylock(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_spinlock(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_unlock_se(GLT_mutex mutex)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_free(GLT_pool *pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_total_size(GLT_pool pool, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_size(GLT_pool pool, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_push(GLT_pool pool, GLT_unit p_unit)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_remove(GLT_pool pool, GLT_unit p_unit)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_set_data(GLT_pool pool, void *data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_data(GLT_pool pool, void **data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_add_sched(GLT_pool pool, GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_pool_get_id(GLT_pool pool, int *id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_config_free(GLT_sched_config *config)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_create(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_free(GLT_sched *sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_finish(GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_exit(GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_set_data(GLT_sched sched, void *data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_data(GLT_sched sched, void **data)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_size(GLT_sched sched, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_scheduler_get_total_size(GLT_sched sched, size_t *size)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_get_type(GLT_unit_type *type)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_is_primary(GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_on_primary_xstream(GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_get_last_pool_id(int *pool_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_suspend(void)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_self_get_arg(void **arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_create(GLT_sched sched, GLT_thread *newthread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_start(GLT_thread thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_free(GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_join(GLT_thread thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_exit()
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_cancel(GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_self(GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_self_rank(int *rank)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_rank(GLT_thread thread, int *rank)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_get_num(int *num_xstreams)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_run_unit(GLT_unit unit, GLT_pool pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline void glt_thread_check_events(GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}


static inline  void glt_tasklet_cancel (GLT_tasklet tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_self(GLT_tasklet *tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_retain(GLT_tasklet tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_release(GLT_tasklet tasklet)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}
 
static inline  void glt_ult_exit()
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_cancel(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_self(GLT_ult *ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_last_pool_id(GLT_ult ult, int *id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_resume(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_migrate(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_retain(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_release(GLT_ult ult)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_id(GLT_ult ult, GLT_ult_id *ult_id)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_get_arg(GLT_ult ult, void **arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_create (GLT_ult_attr *newattr)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_free(GLT_ult_attr *attr)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg)
{
    printf("%s\n",GLT_ERROR_ARG);
}

static inline  void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag)
{
    printf("%s\n",GLT_ERROR_ARG);
}

#endif


#endif	/* FAST_GLT_H */

