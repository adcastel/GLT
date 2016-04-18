/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return int glt_can_extended_basic()
{
    return 0;
}

GLT_return int glt_can_atomic_functions()
{
    return 0;
}

GLT_return int glt_can_feb_functions()
{
    return 0;
}

GLT_return int glt_can_sinc_functions()
{
    return 0;
}

GLT_return int glt_can_loop_functions()
{
    return 0;
}

GLT_return int glt_can_util_functions()
{
    return 0;
}

GLT_return int glt_can_data_structures_functions()
{
    return 0;
}

GLT_return int glt_can_syscall_functions()
{
    return 0;
}

GLT_return int glt_can_extended_runtime()
{
    return 0;
}

GLT_return int glt_can_memory_functions()
{
    return 0;
}

#ifndef CORE


/*
GLT_return void glt_ult_creation_precond(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int npreconds, ...){
    qthread_fork_precond((void *)thread_func,arg,ult,npreconds,...);
}

GLT_return void glt_ult_creation_precond_to(void(*thread_func)(void *), void * arg,
        GLT_ult * ult, int dest,int npreconds, ...){
    qthread_fork_precond_to((void *)thread_func,arg,ult,dest,npreconds,...);
}
*/

GLT_return void glt_ult_creation_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar){
    GLT_ERROR_QTH;
}

GLT_return void glt_ult_creation_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest,int npreconds, ...){
    GLT_ERROR_QTH;
}

GLT_return void glt_ult_get_thread(GLT_thread *thread, int *worker)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ult_get_thread_unique(GLT_thread *thread, int *worker)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ult_get_tasklocal(void * pointer, unsigned int size)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ult_size_tasklocal(unsigned int *size)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ult_get_stack_left(size_t *size)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_atomic_incr(GLT_aligned * operand, int incr)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_atomic_fincr(float * operand, float incr)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_atomic_dincr(double * operand, double incr)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_atomic_cas(volatile GLT_aligned * addr, GLT_aligned oldval,
        GLT_aligned newval)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_atomic_cas_ptr(void * volatile * addr, void * oldval,
        void * newval)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_empty(const GLT_memory_state *dest)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_fill(const GLT_memory_state *dest)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_status(const GLT_memory_state *addr, int *status)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_readFE( GLT_memory_state *dst, const GLT_memory_state *src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_readFF( GLT_memory_state *dst, const GLT_memory_state *src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_writeEF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_writeEF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_writeF( GLT_memory_state * restrict dst, const GLT_memory_state * restrict src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_feb_writeF_const( GLT_memory_state *  dst,  GLT_memory_state src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_empty(GLT_syncvar *dest)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_fill(GLT_syncvar *dest)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_status(GLT_syncvar *addr, int *status)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_readFE( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_readFF( uint64_t * restrict dst, GLT_syncvar * restrict src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_writeEF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_writeEF_const( GLT_syncvar *  dst,  uint64_t src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_writeF( GLT_syncvar * restrict dst, const uint64_t * restrict src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syncvar_writeF_const( GLT_syncvar *  dst,  uint64_t src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_init(GLT_sinc *restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_destroy(GLT_sinc *sinc)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_fini(GLT_sinc * sinc)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_reset(GLT_sinc * sinc, size_t expect)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sinc_wait(GLT_sinc * restrict sinc,  void * restrict target)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_loop(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_loop_step(const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_step_f func, void * arg)
{
    GLT_ERROR_QTH;
}

// void glt_loop_future(const size_t start, const size_t end, 
//         const GLT_loop_f func, void * arg)
//{
//    GLT_ERROR_QTH;
//}
//
// void glt_loop_step_future(const size_t start, const size_t end, 
//        const size_t stride, const GLT_loop_step_f func, void * arg)
//{
//    GLT_ERROR_QTH;
//}

 GLT_return void glt_loop_balance(const size_t start, const size_t end, 
         const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

//void glt_loop_balance_future(const size_t start, const size_t end, 
//         const GLT_loop_f func, void * arg)
//{
//    GLT_ERROR_QTH;
//}

GLT_return void glt_loopaccum_balance(const size_t start, const size_t end, 
         size_t size, void *out, const GLT_loopr_f func, void * arg, GLT_accum_f acc)
{
    GLT_ERROR_QTH;
}

//void glt_loopaccum_balance_future(const size_t start, const size_t end, 
//size_t size, void *out, const GLT_loop_f func, void * arg, GLT_accum_f acc)
//{
//    GLT_ERROR_QTH;
//}


 GLT_return void glt_loop_queue_create(GLT_loop_queue * loop, GLT_loop_queue_kind kind,
        const size_t start, const size_t end, 
        const size_t stride, const GLT_loop_f func, void * arg)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_loop_queue_set_chunk(GLT_loop_queue * loop, size_t chunk)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_loop_queue_run(GLT_loop_queue * loop)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_loop_queue_run_there(GLT_loop_queue * loop, GLT_thread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_loop_queue_add_thread(GLT_loop_queue * loop, GLT_thread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_double_max(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_uint_max(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_int_max(int * res, const long int * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_double_min(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_uint_min(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_int_min(int * res, const long int * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_double_mult(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_uint_mult(unsigned int * res, 
        const long unsigned int * array, size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_int_mult(int * res, const long int * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_double_sum(double * res, double * array, 
        size_t lenght, int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_uint_sum(unsigned int * res, 
        const long unsigned int * array, size_t lenght, 
        int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_int_sum(int * res, const long int * array, size_t lenght, 
        int checkfeb)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_qsort(double * array, size_t lenght)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_util_mergesort(double * array, size_t lenght)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_pool_create(GLT_ds_pool *pool, const size_t item_size)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_pool_create_aligned(GLT_ds_pool *pool, 
        const size_t item_size, const size_t alignment)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_pool_destroy(GLT_ds_pool *pool)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_pool_alloc(GLT_ds_pool *pool)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_pool_free(GLT_ds_pool *restrict pool, 
        void * restrict mem)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_create(GLT_ds_array *array, const size_t count, 
        const size_t item_size)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_create_tight(GLT_ds_array *array, 
        const size_t count, const size_t item_size)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_create_configured(GLT_ds_array *array, 
        const size_t count, const size_t item_size, 
        const GLT_ds_array_distribution d, const char thight, const int seg_pages)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_destroy(GLT_ds_array *array)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_elem(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_elem_nomigrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_elem_migrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_thread_of(GLT_thread * id, const GLT_ds_array *array, 
        const size_t index)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_set_thread_of(GLT_ds_array *array, 
        const size_t index, GLT_thread id )
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_iter(GLT_ds_array *array, 
        const size_t start, const size_t stop, void(*thread_func)(void *))
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_iter_loop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, void * arg)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_iter_nb(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, 
        void * args, aligned_t *arg)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_iter_constloop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_cloop_f thread_func, 
        void * args)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_array_iter_loopaccum(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loopr_f thread_func, 
        void * args, void * ret, const size_t resize, GLT_accum_f acc )
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_lfqueue_create(GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_lfqueue_destroy(GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_lfqueue_enqueue(GLT_ds_lfqueue * lfqueue, void * elem)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_lfqueue_dequeue( void * elem, GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_lfqueue_empty(GLT_bool * empty, GLT_ds_lfqueue * lfqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dqueue_create(GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dqueue_destroy(GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dqueue_enqueue(GLT_ds_dqueue * dqueue, void * elem)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dqueue_enqueue_there(GLT_ds_dqueue * dqueue, 
        void * elem, GLT_thread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dqueue_dequeue( void * elem, GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dqueue_empty(GLT_bool * empty, GLT_ds_dqueue * dqueue)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_create(GLT_ds_dictionary * dictionary, 
        GLT_ds_dictionary_key_equals eq, 
        GLT_ds_dictionary_hash hash, GLT_ds_dictionary_cleanup cleanup)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_destroy(GLT_ds_dictionary * dictionary)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_put(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_put_if_absent(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_get(void * value, GLT_ds_dictionary * dictionary,
        void * key)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_delete(void * value, GLT_ds_dictionary * dictionary,
        void * key)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_end(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_it_create(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_it_destroy(GLT_ds_dictionary_it *it)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_it_next(void * entry, GLT_ds_dictionary_it *it)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_it_get(void * entry, GLT_ds_dictionary_it *it)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_it_equals(GLT_bool * eq, 
        GLT_ds_dictionary_it *it1, GLT_ds_dictionary_it *it2)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_ds_dictionary_it_copy(GLT_ds_dictionary_it *output, 
        GLT_ds_dictionary_it *input)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syscall_begin_blocking()
{
    GLT_ERROR_QTH;
}

GLT_return void glt_syscall_end_blocking()
{
    GLT_ERROR_QTH;
}

GLT_return int glt_syscall_accept(int socket, 
        struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return int glt_syscall_connect(int socket, 
        struct sockaddr *restrict address, socklen_t address_len)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return int glt_syscall_poll(struct pollfd fds[], nfds_t nfds, int timeout)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return size_t glt_syscall_pread(int filedes, void *buf, size_t nbyte, 
        off_t offset)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return size_t glt_syscall_read(int filedes, void *buf, size_t nbyte)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return size_t glt_syscall_pwrite(int filedes, void *buf, size_t nbyte, 
        off_t offset)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return size_t glt_syscall_write(int filedes, void *buf, size_t nbyte)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return int glt_syscall_select(int nfds, fd_set *restrict readfds, 
        fd_set *restrict writefds, fd_set *restrict errorfds, 
        struct timeval *restrict timeout)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return int glt_syscall_system(const char * command)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return int glt_syscall_wait4 (pid_t pid, int *stat_loc, int options, 
        struct rusage *rusage)
{
    GLT_ERROR_QTH;
    return -1;
}

GLT_return void glt_subthread_get_num(GLT_subthread *num)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_cacheline(int *cl)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sorted_threads(const GLT_thread * list)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_sorted_threads_remote(const GLT_thread * list, const GLT_thread src)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_debuglevel(size_t *level, const enum introspective_state type)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_readstate(size_t *value, const enum introspective_state type)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_thread_distance(int * dist, const GLT_thread src, const GLT_thread dst)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_thread_enable(GLT_thread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_thread_disable(GLT_bool *res, GLT_thread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_subthread_enable(GLT_subthread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_subthread_disable(GLT_bool *res, GLT_subthread id)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_thread_ok(GLT_bool *res)
{
    GLT_ERROR_QTH;
}

GLT_return void * glt_memory_make_stat_map(const off_t filesize, void *addr,
        const char *filename, size_t itemsize, const size_t streams)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

GLT_return void * glt_memory_make_dyn_map(const off_t filesize, void *addr,
        const char *filename,  const size_t streams)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

GLT_return void * glt_memory_load_map(const char *filename)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

GLT_return void * glt_memory_malloc(void *map, size_t size)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

GLT_return void * glt_memory_stat_malloc(struct mapinfo_s *map)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

GLT_return void * glt_memory_dyn_malloc(struct dynmapinfo_s *map, size_t size)
{
    void * err = NULL;
    GLT_ERROR_QTH;
    return err;
}

GLT_return void glt_memory_free(void *block, void * map)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_memory_stat_free(void *block, struct mapinfo_s *map)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_memory_dyn_free(void *block, struct dynmapinfo_s *map)
{
    GLT_ERROR_QTH;
}

GLT_return void glt_memory_cleanup()
{
    GLT_ERROR_QTH;
}

GLT_return void glt_memory_checkpoint()
{
    GLT_ERROR_QTH;
}

#endif