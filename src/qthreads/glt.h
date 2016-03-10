/* 
 * File:   glt.h
 * Author: adcastel
 *
 * Created on 11 de febrero de 2016, 16:20
 */


#ifndef GLT_H
#define	GLT_H


#include <stdio.h>
#include <stdlib.h>
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
#include <qthread/io.h>
#include <qthread/qt_syscalls.h> 
#include <qthread/cacheline.h>
#include <qthread/qalloc.h>







#define GLT_ult aligned_t
#define GLT_tasklet aligned_t
#define GLT_thread qthread_shepherd_id_t
#define GLT_mutex aligned_t
#define GLT_barrier  qt_barrier_t
#define GLT_cond aligned_t
#define GLT_timer qtimer_t
#define GLT_bool int
#define GLT_thread_id int
#define GLT_ult_id int

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
#define GLT_ds_dictionary_cleanup qt_dict_cleanup_f
#define GLT_ds_dictionary_it qt_dictionary_iterator
#define GLT_subthread qthread_worker_id_t

//MASSIVETHREAD
#define GLT_workunit_f void *
#define GLT_workunit_o void *
#define GLT_felock void *
#define GLT_felock_status int
#define GLT_pickle void *
#define GLT_wsapi_decide_f void *
#define GLT_wsapi_steal_f void *


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


#define glt_scheduler_config_create (config,...) ABT_sched_config_create(config,...)
#define glt_scheduler_config_read (config, num_vars,...) ABT_sched_config_read (config, num_vars,...)

#define glt_ult_creation_precond(f,a,u,n,...) qthread_fork_precond(f,a,u,n,...)
#define glt_ult_creation_precond_to(f,a,u,d,n,...) qthread_fork_precond_to(f,a,u,d,n,...)

#endif

typedef struct glt_team {
    int num_shepherds;
    int num_workers_per_shepherd;
} glt_team_t;

#define GLT_VERSION "You are using glt 0.1v over Qthreads (adcastel@uji.es)"
#define GLT_ERROR_ARG printf("Error: This feature is only supported by Argobots \
    implementation and you are using Qthreads. Please use the query functions\n")
#define GLT_ERROR_MYTH printf("Error: This feature is only supported by MassiveThredashreads \
    implementation and you are using Qthreads. Please use the query functions\n")
#define GLT_LIB_ERROR printf("Error: This feature is in the API but it is not \
    included in the Library\n")

/* Main team structure*/

glt_team_t * main_team;


void __attribute__((constructor)) glt_start(void);
void __attribute__((destructor)) glt_end(void);


void glt_init(int argc, char * argv[]);
void glt_finalize();

GLT_ult * glt_ult_malloc(int number_of_ult);
GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets);

void glt_ult_creation(void(*thread_func)(void *), void *arg, GLT_ult *new_ult);
void glt_ult_creation_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest);

void glt_tasklet_creation(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult);
void glt_tasklet_creation_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest);

void glt_yield();
void glt_yield_to(GLT_ult ult);

void glt_ult_join(GLT_ult *ult);
void glt_tasklet_join(GLT_tasklet *tasklet);

void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult);
void glt_workunit_get_thread_id(GLT_thread_id *id);
 void glt_ult_migrate_self_to(GLT_thread_id dest);
void glt_ult_self(GLT_ult * ult);
void glt_tasklet_self(GLT_ult * ult);
void glt_ult_exit();
void glt_ult_cancel(GLT_ult ult);
void glt_tasklet_cancel (GLT_tasklet tasklet);

void glt_mutex_create(GLT_mutex * mutex);
void glt_mutex_lock(GLT_mutex mutex);
void glt_mutex_unlock(GLT_mutex mutex);
void glt_mutex_free(GLT_mutex * mutex);
void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex);

void glt_barrier_create(int num_waiters, GLT_barrier *barrier);
void glt_barrier_free(GLT_barrier *barrier);
void glt_barrier_wait(GLT_barrier *barrier);

void glt_cond_create(GLT_cond *cond);
void glt_cond_free(GLT_cond *cond);
void glt_cond_signal(GLT_cond cond);
void glt_cond_wait(GLT_cond cond, GLT_mutex mutex);
void glt_cond_broadcast(GLT_cond cond);

double glt_get_wtime();
void glt_timer_create(GLT_timer * timer);
void glt_timer_free(GLT_timer * timer);
void glt_timer_start(GLT_timer timer);
void glt_timer_stop(GLT_timer timer);
void glt_timer_get_secs(GLT_timer timer, double *secs);

int glt_get_thread_num();
int glt_get_num_threads();

int glt_can_extended_basic();
int glt_can_atomic_functions();
 int glt_can_feb_functions();
  int glt_can_sinc_functions();
   int glt_can_loop_functions();
 int glt_can_util_functions();
  int glt_can_data_structures_functions();
 int glt_can_syscall_functions();
  int glt_can_extended_runtime();
   int glt_can_memory_functions();




//QUERY functions for ARGOBOTS
//Always return 0;
int glt_can_event_functions();
int glt_can_future_functions();
int glt_can_promise_functions();
int glt_can_tls_functions();
int glt_can_extended_mutex();
int glt_can_manage_pools();
int glt_can_manage_scheduler();
int glt_can_self();
int glt_can_manage_threads();
int can_extended_tasklets();
int can_extended_ults();

 //QUERY functions for MAssiveThreads
 //Always return 0;
 int glt_can_wsapi_functions();
 int glt_can_prof_functions();
 int glt_can_log_functions();
 int glt_can_serialize_functions();
 int can_felock_functions();
 int can_extended_workunits();




#ifndef CORE

void glt_ult_creation_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar);
 void glt_ult_creation_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest,int npreconds, ...);
 void glt_ult_get_thread(GLT_thread *thread, int *worker);
 void glt_ult_get_thread_unique(GLT_thread *thread, int *worker);
 void glt_ult_get_tasklocal(void * pointer, unsigned int size);
 void glt_ult_size_tasklocal(unsigned int *size);
 void glt_ult_get_stack_left(size_t *size);
 void glt_ult_retloc(GLT_ult * ult);
 
 void glt_atomic_incr(GLT_aligned * operand, int incr);
 void glt_atomic_fincr(float * operand, float incr);
 void glt_atomic_dincr(double * operand, double incr);
 void glt_atomic_cas(volatile GLT_aligned * addr, GLT_aligned oldval,
        GLT_aligned newval);
 void glt_atomic_cas_ptr(void * volatile * addr, void * oldval,
        void * newval);
 
 void glt_feb_empty(const GLT_memory_state *dest);
 void glt_feb_fill(const GLT_memory_state *dest);
 void glt_feb_status(const GLT_memory_state *addr, int *status);
 void glt_feb_readFE( GLT_memory_state *dst, const GLT_memory_state *src);
 void glt_feb_readFF( GLT_memory_state *dst, const GLT_memory_state *src);
 void glt_feb_writeEF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src);
 void glt_feb_writeEF_const( GLT_memory_state *  dst,  GLT_memory_state src);
 void glt_feb_writeF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src);
 void glt_feb_writeF_const( GLT_memory_state *  dst,  GLT_memory_state src);
 void glt_syncvar_empty(GLT_syncvar *dest);
 void glt_syncvar_fill(GLT_syncvar *dest);
 void glt_syncvar_status(GLT_syncvar *addr, int *status);
 void glt_syncvar_readFE( uint64_t * restrict dst, GLT_syncvar * restrict src);
 void glt_syncvar_readFF( uint64_t * restrict dst, GLT_syncvar * restrict src);
 void glt_syncvar_writeEF( GLT_syncvar * restrict dst, const uint64_t * restrict src);
 void glt_syncvar_writeEF_const( GLT_syncvar *  dst,  uint64_t src);
 void glt_syncvar_writeF( GLT_syncvar * restrict dst, const uint64_t * restrict src);
 void glt_syncvar_writeF_const( GLT_syncvar *  dst,  uint64_t src);
 
 void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected);
 void glt_sinc_init(GLT_sinc *restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected);
 void glt_sinc_destroy(GLT_sinc *sinc);
 void glt_sinc_fini(GLT_sinc * sinc);
 void glt_sinc_reset(GLT_sinc * sinc, size_t expect);
 void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value);
 void glt_sinc_wait(GLT_sinc * restrict sinc,  void * restrict target);
 
 void glt_loop(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg);
 //void glt_loop_step(const size_t start, const size_t end, 
 //       const size_t stride, const GLT_loop_step_f func, void * arg);
 void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg);
 void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc);
 void glt_loop_queue_create(GLT_loop_queue * loop, GLT_loop_queue_kind kind,
        const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_f func, void * arg);
 void glt_loop_queue_set_chunk(GLT_loop_queue * loop, size_t chunk);
 void glt_loop_queue_run(GLT_loop_queue * loop);
 void glt_loop_queue_run_there(GLT_loop_queue * loop, GLT_thread id);
 void glt_loop_queue_add_thread(GLT_loop_queue * loop, GLT_thread id);
 
 void glt_util_double_max(double * res, double * array, 
        size_t lenght, int checkfeb);
 void glt_util_uint_max(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb);
 void glt_util_int_max(int * res, const long int * array, 
        size_t lenght, int checkfeb);
 void glt_util_double_min(double * res, double * array, 
        size_t lenght, int checkfeb);
 void glt_util_uint_min(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb);
 void glt_util_int_min(int * res, const long int * array, 
        size_t lenght, int checkfeb);
 void glt_util_double_mult(double * res, double * array, 
        size_t lenght, int checkfeb);
 void glt_util_uint_mult(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb);
 void glt_util_int_mult(int * res, const long int * array, 
        size_t lenght, int checkfeb);
 void glt_util_double_sum(double * res, double * array, 
        size_t lenght, int checkfeb);
 void glt_util_uint_sum(unsigned int * res, 
        const long unsigned int * array, size_t lenght, 
        int checkfeb);
 void glt_util_int_sum(int * res, const long int * array, size_t lenght, 
        int checkfeb);
 void glt_util_qsort(double * array, size_t lenght);
 void glt_util_mergesort(double * array, size_t lenght);
 
  void glt_ds_pool_create(GLT_ds_pool *pool, const size_t item_size);
 void glt_ds_pool_create_aligned(GLT_ds_pool *pool, 
        const size_t item_size, const size_t alignment);
 void glt_ds_pool_destroy(GLT_ds_pool *pool);
 void glt_ds_pool_alloc(GLT_ds_pool *pool);
 void glt_ds_pool_free(GLT_ds_pool *restrict pool, void * restrict mem);
 void glt_ds_array_create(GLT_ds_array *array, const size_t count, 
        const size_t item_size);
 void glt_ds_array_create_tight(GLT_ds_array *array, const size_t count, 
         const size_t item_size);
 void glt_ds_array_create_configured(GLT_ds_array *array, 
        const size_t count, const size_t item_size, 
        const GLT_ds_array_distribution d, const char thight, const int seg_pages);
 void glt_ds_array_destroy(GLT_ds_array *array);
 void glt_ds_array_elem(void * elem, const GLT_ds_array *array, 
        const size_t index);
 void glt_ds_array_elem_nomigrate(void * elem, const GLT_ds_array *array, 
        const size_t index);
 void glt_ds_array_elem_migrate(void * elem, const GLT_ds_array *array, 
        const size_t index);
 void glt_ds_array_thread_of(GLT_thread * id, const GLT_ds_array *array, 
        const size_t index);
 void glt_ds_array_set_thread_of(GLT_ds_array *array, 
        const size_t index, GLT_thread id );
 void glt_ds_array_iter(GLT_ds_array *array, 
        const size_t start, const size_t stop, void(*thread_func)(void *));
 void glt_ds_array_iter_loop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, void * arg);
 void glt_ds_array_iter_nb(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, 
        void * args, aligned_t *arg);
 void glt_ds_array_iter_constloop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_cloop_f thread_func, 
        void * args);
 void glt_ds_array_iter_loopaccum(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loopr_f thread_func, 
        void * args, void * ret, const size_t resize, GLT_accum_f acc );
 void glt_ds_lfqueue_create(GLT_ds_lfqueue * lfqueue);
 void glt_ds_lfqueue_destroy(GLT_ds_lfqueue * lfqueue);
 void glt_ds_lfqueue_enqueue(GLT_ds_lfqueue * lfqueue, void * elem);
 void glt_ds_lfqueue_dequeue( void * elem, GLT_ds_lfqueue * lfqueue);
 void glt_ds_lfqueue_empty(GLT_bool * empty, GLT_ds_lfqueue * lfqueue);
 void glt_ds_dqueue_create(GLT_ds_dqueue * dqueue);
 void glt_ds_dqueue_destroy(GLT_ds_dqueue * dqueue);
 void glt_ds_dqueue_enqueue(GLT_ds_dqueue * dqueue, void * elem);
 void glt_ds_dqueue_enqueue_there(GLT_ds_dqueue * dqueue, 
        void * elem, GLT_thread id);
 void glt_ds_dqueue_dequeue( void * elem, GLT_ds_dqueue * dqueue);
 void glt_ds_dqueue_empty(GLT_bool * empty, GLT_ds_dqueue * dqueue);
 void glt_ds_dictionary_create(GLT_ds_dictionary * dictionary, 
        GLT_ds_dictionary_key_equals eq, 
        GLT_ds_dictionary_hash hash, GLT_ds_dictionary_cleanup cleanup);
 void glt_ds_dictionary_destroy(GLT_ds_dictionary * dictionary);
 void glt_ds_dictionary_put(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value);
 void glt_ds_dictionary_put_if_absent(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value);
 void glt_ds_dictionary_get(void * value, GLT_ds_dictionary * dictionary,
        void * key);
 void glt_ds_dictionary_delete(void * value, GLT_ds_dictionary * dictionary,
        void * key);
 void glt_ds_dictionary_end(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary);
 void glt_ds_dictionary_it_create(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary);
 void glt_ds_dictionary_it_destroy(GLT_ds_dictionary_it *it);
 void glt_ds_dictionary_it_next(void * entry, GLT_ds_dictionary_it *it);
 void glt_ds_dictionary_it_get(void * entry, GLT_ds_dictionary_it *it);
 void glt_ds_dictionary_it_equals(GLT_bool * eq, 
        GLT_ds_dictionary_it *it1, GLT_ds_dictionary_it *it2);
 void glt_ds_dictionary_it_copy(GLT_ds_dictionary_it *output, 
        GLT_ds_dictionary_it *input);
 
 void glt_syscall_begin_blocking();
 void glt_syscall_end_blocking();
 int glt_syscall_accept(int socket, 
        struct sockaddr *restrict address, socklen_t *restrict address_len);
 int glt_syscall_connect(int socket, 
        struct sockaddr *restrict address, socklen_t address_len);
 int glt_syscall_poll(struct pollfd fds[], nfds_t nfds, int timeout);
 size_t glt_syscall_pread(int filedes, void *buf, size_t nbyte, 
        off_t offset);
 size_t glt_syscall_read(int filedes, void *buf, size_t nbyte);
 size_t glt_syscall_pwrite(int filedes, void *buf, size_t nbyte, 
        off_t offset);
 size_t glt_syscall_write(int filedes, void *buf, size_t nbyte);
 int glt_syscall_select(int nfds, fd_set *restrict readfds, 
        fd_set *restrict writefds, fd_set *restrict errorfds, 
        struct timeval *restrict timeout);
 int glt_syscall_system(const char * command);
 int glt_syscall_wait4 (pid_t pid, int *stat_loc, int options, 
        struct rusage *rusage);
 
  void glt_subthread_get_num(GLT_subthread *num);
 void glt_cacheline(int *cl);
 void glt_sorted_threads(const GLT_thread * list);
 void glt_sorted_threads_remote(const GLT_thread * list, const GLT_thread src);
 void glt_debuglevel(size_t *level, const enum introspective_state type);
 void glt_readstate(size_t *value, const enum introspective_state type);
 void glt_thread_distance(int * dist, const GLT_thread src, const GLT_thread dst);
 void glt_thread_enable(GLT_thread id);
 void glt_thread_disable(GLT_bool *res, GLT_thread id);
 void glt_subthread_enable(GLT_subthread id);
 void glt_subthread_disable(GLT_bool *res, GLT_subthread id);
 void glt_thread_ok(GLT_bool *res);
 
 void * glt_memory_make_stat_map(const off_t filesize, void *addr,
        const char *filename, size_t itemsize, const size_t streams);
 void * glt_memory_make_dyn_map(const off_t filesize, void *addr,
        const char *filename,  const size_t streams);
 void * glt_memory_load_map(const char *filename);
 void * glt_memory_malloc(void *map, size_t size);
 void * glt_memory_stat_malloc(struct mapinfo_s *map);
 void * glt_memory_dyn_malloc(struct dynmapinfo_s *map, size_t size);
 void glt_memory_free(void *block, void * map);
 void glt_memory_stat_free(void *block, struct mapinfo_s *map);
 void glt_memory_dyn_free(void *block, struct dynmapinfo_s *map);
 void glt_memory_cleanup();
 void glt_memory_checkpoint();
//HEADERS for ARGOBOTS extended functions
//Null codes
void glt_get_error_str(int errno, char *str, size_t *len);
void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id);
void glt_event_del_callback(GLT_event_kind event, int cb_id);

void glt_future_create(int nbytes, GLT_future *newfuture);
void glt_future_free(GLT_future *future);
void glt_future_wait(GLT_future future, void **value);
void glt_future_set(GLT_future future, void *value, int nbytes);

void glt_promise_create(uint32_t compartments, void(*cb_func)(void **arg), GLT_promise *newpromise);
void glt_promise_free(GLT_promise *promise);
void glt_promise_wait(GLT_promise promise);
void glt_promise_test(GLT_promise promise, GLT_bool *flag);
void glt_promise_set(GLT_promise promise, void * value);

void glt_key_create(void(*destructor)(void *value), GLT_key *newkey);
void glt_key_free(GLT_key *key);
void glt_key_set(GLT_key key, void *value);
void glt_key_get(GLT_key key, void **value);

void glt_mutex_lock_low(GLT_mutex mutex);
void glt_mutex_spinlock(GLT_mutex mutex);
void glt_mutex_unlock_se(GLT_mutex mutex);
void glt_mutex_equal(GLT_mutex mutex1, GLT_mutex mutex2, GLT_bool *result);

void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool);
void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool);
void glt_pool_free(GLT_pool *pool);
void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access);
void glt_pool_get_total_size(GLT_pool pool, size_t *size);
void glt_pool_get_size(GLT_pool pool, size_t *size);
void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit);
void glt_pool_push(GLT_pool pool, GLT_unit p_unit);
void glt_pool_remove(GLT_pool pool, GLT_unit p_unit);
void glt_pool_set_data(GLT_pool pool, void *data);
void glt_pool_get_data(GLT_pool pool, void **data);
void glt_pool_add_sched(GLT_pool pool, GLT_sched sched);
void glt_pool_get_id(GLT_pool pool, int *id);

void glt_scheduler_config_free(GLT_sched_config *config);
void glt_scheduler_create(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched);
void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched);
void glt_scheduler_free(GLT_sched *sched);
void glt_scheduler_get_num_pools(GLT_sched sched, int *num_pools);
void glt_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools);
void glt_scheduler_finish(GLT_sched sched);
void glt_scheduler_exit(GLT_sched sched);
void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop);
void glt_scheduler_set_data(GLT_sched sched, void *data);
void glt_scheduler_get_data(GLT_sched sched, void **data);
void glt_scheduler_get_size(GLT_sched sched, size_t *size);
void glt_scheduler_get_total_size(GLT_sched sched, size_t *size);

void glt_self_get_type(GLT_unit_type *type);
void glt_self_is_primary(GLT_bool *flag);
void glt_self_on_primary_xstream(GLT_bool *flag);
void glt_self_get_last_pool_id(int *pool_id);
void glt_self_suspend(void);
void glt_self_get_arg(void **arg);

void glt_thread_create(GLT_sched sched, GLT_thread *newthread);
void glt_thread_create_basic(GLT_sched_predef predef, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_thread *newthread);
void glt_thread_start(GLT_thread thread);
void glt_thread_free(GLT_thread *thread);
void glt_thread_join(GLT_thread thread);
void glt_thread_exit();
void glt_thread_cancel(GLT_thread *thread);
void glt_thread_self(GLT_thread *thread);
void glt_thread_self_rank(int *rank);
void glt_thread_get_rank(GLT_thread thread, int *rank);
void glt_thread_set_main_sched(GLT_thread thread, GLT_sched sched);
void glt_thread_set_main_sched_basic(GLT_thread thread,
        GLT_sched_predef predef, int num_pools, GLT_pool *pools);
void glt_thread_get_main_sched(GLT_thread thread, GLT_sched *sched);
void glt_thread_get_main_pools(GLT_thread thread, int max_pools,
        GLT_pool *pools);
void glt_thread_get_state(GLT_thread thread, GLT_thread_state *state);
void glt_thread_equal(GLT_thread thread1, GLT_thread thread2, GLT_bool *result);
void glt_thread_get_num(int *num_xstreams);
void glt_thread_is_primary(GLT_thread thread, GLT_bool *flag);
void glt_thread_run_unit(GLT_unit unit, GLT_pool pool);
void glt_thread_check_events(GLT_sched sched);

 void glt_tasklet_cancel (GLT_tasklet tasklet);
 void glt_tasklet_self(GLT_tasklet *tasklet);
 void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread);
 void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state);
 void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool);
 void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet,int *id);
 void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag);
 void glt_tasklet_is_migratable(GLT_tasklet tasklet,GLT_bool *flag);
 void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result);
 void glt_tasklet_retain(GLT_tasklet tasklet);
 void glt_tasklet_release(GLT_tasklet tasklet);
 void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg);
 
 void glt_ult_exit();
 void glt_ult_cancel(GLT_ult ult);
 void glt_ult_self(GLT_ult *ult);
 void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state);
 void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool);
 void glt_ult_get_last_pool_id(GLT_ult ult, int *id);
 void glt_ult_resume(GLT_ult ult);
 void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread);
 void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched);
 void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool);
 void glt_ult_migrate(GLT_ult ult);
 void glt_ult_set_callback(GLT_ult ult,void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg);
 void glt_ult_set_migratable (GLT_ult ult, GLT_bool flag);
 void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag);
 void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag);
 void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result);
 void glt_ult_retain(GLT_ult ult);
 void glt_ult_release(GLT_ult ult);
 void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize);
 void glt_ult_get_arg(GLT_ult ult, void **arg);
 void glt_ult_attr_create (GLT_ult_attr *newattr);
 void glt_ult_attr_free(GLT_ult_attr *attr);
 void glt_ult_attr_set_stacksize (GLT_ult_attr attr, size_t stacksize);
 void glt_ult_attr_get_stacksize (GLT_ult_attr attr, size_t *stacksize);
 void glt_ult_attr_set_callback (GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg);
 void glt_ult_attr_set_migratable (GLT_ult_attr attr, GLT_bool flag);

 //HEADERS for MASSIVETHREADS extended functions
//Null codes
   void glt_wu_create_ex(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt);
 void glt_wu_create_nosched(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt);
 void glt_yield2();
 void glt_wu_detach(GLT_ult ult);
 void glt_wu_set_cancel_state(int state, int *oldstate);
 void glt_wu_set_cancel_type(int type, int *oldtype);
 void glt_wu_test_cancel();
 void glt_wu_set_def_stack_size(size_t newsize);
 void glt_wu_steal(GLT_ult * ult);
 void glt_wu_import(GLT_ult ult);
 void glt_wu_ext_import(GLT_ult ult);
 void glt_wu_release_stack(GLT_ult ult);
 void glt_wu_release_desc(GLT_ult ult);
 
  void glt_felock_create(GLT_felock * felock);
 void glt_felock_free(GLT_felock felock);
 void glt_felock_lock(GLT_bool *lock, GLT_felock felock);
 void glt_felock_wait_lock(GLT_bool *lock, GLT_felock felock, int val);
 void glt_felock_unlock(GLT_bool *unlock, GLT_felock felock);
 void glt_felock_status(GLT_felock_status *status, GLT_felock felock);
 void glt_felock_set_unlock(GLT_felock felock, int val);
 
  void glt_key_create (void(*destructor)(void *value), GLT_key *newkey);
 void glt_key_free (GLT_key *key);
 void glt_key_set (GLT_key key, void *value);
 void glt_key_get (GLT_key key, void **value);
 
  void glt_serialize(GLT_ult ult, GLT_pickle pickle);
 void glt_deserialize(GLT_ult *ult, GLT_pickle pickle);
 void glt_ext_deserialize(GLT_ult *ult, GLT_pickle pickle);
 
 void glt_log_start();
 void glt_log_pause();
 void glt_log_flush();
 void glt_log_reset();
 void glt_log_annotate_ult(GLT_ult ult, char *name);
 void glt_sched_prof_start();
 void glt_sched_prof_pause();
 
 void glt_wsapi_runqueue_peek(GLT_ult *ult, int victim,void *ptr,size_t *psize);
 void glt_wsapi_get_hint_size(size_t *size, GLT_ult ult);
 void glt_wsapi_get_hint_ptr(void *ptr, GLT_ult ult);
 void glt_wsapi_set_hint(GLT_ult ult,void **data,size_t *size);
 void glt_wsapi_rand(int * rand);
 void glt_wsapi_randrr(int *ret, int n);
 void glt_wsapi_runqueue_take(GLT_ult * ult, int victim,GLT_wsapi_decide_f decidefn,void *udata);
 void glt_wsapi_runqueue_pass(GLT_bool *pass, int target,GLT_ult ult);
 void glt_wsapi_runqueue_push(GLT_ult ult);
 void glt_wsapi_runqueue_pop(GLT_ult * ult);
 void glt_wsapi_rand2(int * rand_value, int min, int max);
 void glt_wsapi_set_stealfunc(GLT_wsapi_steal_f *out, GLT_wsapi_steal_f fn);


#endif

#endif	/* glt_H */

