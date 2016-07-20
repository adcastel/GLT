/* See COPYRIGHT in top-level directory. */
/*
 * Function headers file.
 */


#ifndef GLT_H
#define GLT_H

/** \defgroup LIB Library functions
 * These functions start/stop and open/close the underlying GLT 
 * libraries. They are used in dynamic and static implementations.
 */

/** \defgroup BARRIER Barrier functions
 * These functions manage the GLT barriers for the ULTs.
 */

/** \defgroup CONDITION Condition functions
 * These functions manage the GLT conditions for the ULTs.
 */

/** \defgroup MUTEX Mutex functions
 * These functions manage the GLT mutexes for the ULTs.
 */

/** \defgroup WORKUNIT Work-units functions
 * These functions create, map, schedule, join, and execute work-units.
 */

/** \defgroup TIMER Timer functions
 * These functions simplify the use of timers.
 */

/** \defgroup UTIL Util functions
 * These functions return values from the environment set up.
 */

/** \defgroup SCHED Scheduler functions
 * These functions manages the configurable scheduler (just with Argobots).
 */

/** \defgroup KEY Key functions
 * These functions manage the GLT keys for the ULTs.
 */

/**
 * @ingroup LIB
 * @brief   Entry point for the GLT dynamic library.
 *
 * \c glt_start() is the first called function when the GLT dynamic library is
 * loaded
 */
void __attribute__((constructor)) glt_start(void);

/**
 * @ingroup LIB
 * @brief   Ending point for the GLT dynamic library.
 *
 * \c glt_end() is the last called function when the GLT dynamic library is
 * unloaded
 */
void __attribute__((destructor)) glt_end(void);

/**
 * @ingroup LIB
 * @brief   GLT initialization function.
 *
 * \c glt_init() sets the GLT environment up. It is mandatory and needs to be 
 * the first GLT function call.
 * @param[in]  argc  
 * @param[in]  argv      
 */
void glt_init(int argc, char * argv[]);

/**
 * @ingroup LIB
 * @brief   GLT finalization function.
 *
 * \c glt_finalize() destroys the GLT environment. It is not mandatory and should 
 * be the last GLT function call.      
 */
void glt_finalize();

/**
 * @ingroup WORKUNIT
 * @brief   ULT allocation.
 *
 * \c glt_ult_malloc() allocates memory for a given number of \c GLT_ult.
 * @param[in] number_of_ult Indicates the total number of \c GLT_ult that needs
 * to be allocated.
 * @return The pointer to the allocated memory.      
 */
GLT_ult * glt_ult_malloc(int number_of_ult);

/**
 * @ingroup WORKUNIT
 * @brief   ULT allocation.
 *
 * \c glt_tasklet_malloc() allocates memory for a given number of \c GLT_tasklet.
 * @param[in] number_of_tasklets Indicates the total number of \c GLT_tasklets that needs
 * to be allocated.
 * @return The pointer to the allocated memory.      
 */
GLT_tasklet * glt_tasklet_malloc(int number_of_tasklets);

/**
 * @ingroup WORKUNIT
 * @brief   ULT creation.
 *
 * \c glt_ult_create() creates a \c GLT_ult.
 * @param[in] thread_func Is the function pointer to be executed by the \c GLT_ult.
 * @param[in] arg Are the arguments for thread_func.
 * @param[out] new_ult Handle to a newly created \c GLT_ult.
 */
void glt_ult_create(void(*thread_func)(void *), void *arg, GLT_ult *new_ult);

/**
 * @ingroup WORKUNIT
 * @brief   ULT creation in a given destination.
 *
 * \c glt_ult_create_to() creates a \c GLT_ult in a particular destination.
 * @param[in] thread_func Is the function pointer to be executed by the \c GLT_ult.
 * @param[in] arg Are the arguments for thread_func.
 * @param[out] new_ult Handle to a newly created \c GLT_ult.
 * @param[in] dest Number of the \c GLT_thread that should execute the newly created \c GLT_ult.
 */
void glt_ult_create_to(void(*thread_func)(void *), void *arg, GLT_ult *new_ult, int dest);

/**
 * @ingroup WORKUNIT
 * @brief   Tasklet creation.
 *
 * \c glt_tasklet_create() creates a \c GLT_tasklet.
 * @param[in] thread_func Is the function pointer to be executed by the \c GLT_tasklet.
 * @param[in] arg Are the arguments for thread_func.
 * @param[out] new_ult Handle to a newly created \c GLT_tasklet.
 */
void glt_tasklet_create(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult);

/**
 * @ingroup WORKUNIT
 * @brief   Tasklet creation.
 *
 * \c glt_tasklet_create() creates a \c GLT_tasklet.
 * @param[in] thread_func Is the function pointer to be executed by the \c GLT_tasklet.
 * @param[in] arg Are the arguments for thread_func.
 * @param[out] new_ult Handle to a newly created \c GLT_tasklet.
 * @param[in] dest Number of the \c GLT_thread that should execute the newly created \c GLT_tasklet.
 */
void glt_tasklet_create_to(void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult, int dest);

/**
 * @ingroup WORKUNIT
 * @brief   ULT yields to another ready ULT.
 *
 * \c glt_yield() puts the current \c GLT_ult in the ready queue and allows another 
 * ready \c GLT_ult to be executed.
 */
void glt_yield();

/**
 * @ingroup WORKUNIT
 * @brief   ULT yields to an specific ULT.
 *
 * \c glt_yield_to() puts the current \c GLT_ult in the ready queue and allows an  
 * specific ready \c GLT_ult to be executed.
 * @param[in] ult Handle to the target \c GLT_ult.
 */
void glt_yield_to(GLT_ult ult);

/**
 * @ingroup WORKUNIT
 * @brief   Joins an specific ULT.
 *
 * \c glt_ult_join() joins a given \c GLT_ult.
 * @param[in] ult Handle to the target \c GLT_ult.
 */
void glt_ult_join(GLT_ult *ult);

/**
 * @ingroup WORKUNIT
 * @brief   Joins an specific Tasklet.
 *
 * \c glt_tasklet_join() joins a given \c GLT_tasklet.
 * @param[in] tasklet Handle to the target \c GLT_tasklet.
 */
void glt_tasklet_join(GLT_tasklet *tasklet);

/**
 * @ingroup WORKUNIT
 * @brief   Return the unique id of a ULT.
 *
 * \c glt_ult_get_id() returns the id of a given \c GLT_ult.
 * @param[in] ult Handle to the target \c GLT_ult.
 * @param[out] id Identifier if the the target \c GLT_ult.
 */
void glt_ult_get_id(GLT_ult_id * id, GLT_ult ult);

/**
 * @ingroup WORKUNIT
 * @brief   Return the unique id of a thread.
 *
 * \c glt_workunit_get_thread_id() returns the id of the current \c GLT_thread.
 * @param[out] id Identifier of the the current \c GLT_thread.
 */
void glt_workunit_get_thread_id(GLT_thread_id *id);

/**
 * @ingroup WORKUNIT
 * @brief   Migrates the current ULT to another thread ready queue.
 *
 * \c glt_ult_migrate_self_to() moves the current \c GLT_ult to another 
 * \c GLT_thread ready queue.
 * @param[in] The identifier of the the \c GLT_thread destination.
 */
void glt_ult_migrate_self_to(GLT_thread_id id);

/**
 * @ingroup WORKUNIT
 * @brief   Obtains the current ULT handle.
 *
 * \c glt_ult_self() returns the current \c GLT_ult handler.
 * @param[out] ult Handler of the the current \c GLT_ult.
 */
void glt_ult_self(GLT_ult *ult);

/**
 * @ingroup WORKUNIT
 * @brief   Obtains the current Tasklet handle.
 *
 * \c glt_tasklet_self() returns the current \c GLT_tasklet handler.
 * @param[out] tasklet Handler of the the current \c GLT_tasklet.
 */
void glt_tasklet_self(GLT_tasklet *tasklet);

/**
 * @ingroup WORKUNIT
 * @brief   Cancels an specific ULT.
 *
 * \c glt_ult_cancel() cancels a given \c GLT_ult.
 * @param[in] ult Handle to the target \c GLT_ult.
 */
void glt_ult_cancel(GLT_ult ult);

/**
 * @ingroup WORKUNIT
 * @brief   Cancels an specific Tasklet.
 *
 * \c glt_tasklet_cancel() cancels a given \c GLT_tasklet.
 * @param[in] tasklet Handle to the target \c GLT_tasklet.
 */
void glt_tasklet_cancel(GLT_tasklet tasklet);

/**
 * @ingroup WORKUNIT
 * @brief   Exits the current ULT.
 *
 * \c glt_ult_exit() cancels the current \c GLT_ult.
 */
void glt_ult_exit();

 /** @ingroup MUTEX
 * @brief Creates a mutex.
 *
 * \c glt_mutex_create() creates a mutex for ULTs.
 * @param[in,out] mutex   Hande to newly created \c GLT_mutex
 */
void glt_mutex_create(GLT_mutex * mutex);

 /** @ingroup MUTEX
 * @brief Locks a mutex.
 *
 * \c glt_mutex_lock() locks (if possible) a mutex.
 * @param[in] mutex   Handle to the target \c GLT_mutex.
 */
void glt_mutex_lock(GLT_mutex mutex);

 /** @ingroup MUTEX
 * @brief Unlocks a mutex.
 *
 * \c glt_mutex_unlock() unlocks a mutex.
 * @param[in] mutex   Handle to the target \c GLT_mutex.
 */
void glt_mutex_unlock(GLT_mutex mutex);

/** @ingroup MUTEX
 * @brief Destroys a mutex.
 *
 * \c glt_mutex_free() destroys a mutex for ULTs.
 * @param[in]  mutex  Handle to the target \c GLT_mutex.
 */
void glt_mutex_free(GLT_mutex * mutex);

/** @ingroup MUTEX
 * @brief Tries to lock a mutex.
 *
 * \c glt_mutex_trylock() tries to lock a mutex.
 * @param[in]  mutex  Handle to the target \c GLT_mutex.
 * @param[out] locked  \c GLT_bool with the value 1 if the mutex has been locked
 * or 0 if it was not possible.
 */
void glt_mutex_trylock(GLT_bool * locked, GLT_mutex mutex);

 /** @ingroup BARRIER
 * @brief Creates a barrier.
 *
 * \c glt_barrier_create() creates a barrier for ULTs.
 * @param[in]  num_waiters  Indicates the number of ULTs requested to continue
 * @param[in,out] barrier   Hande to newly created \c GLT_barrier
 */
void glt_barrier_create(int num_waiters, GLT_barrier *barrier);

 /** @ingroup BARRIER
 * @brief Destroys a barrier.
 *
 * \c glt_barrier_free() destroys a barier for ULTs.
 * @param[in]  barrier  Handle to the target \c GLT_barrier.
 */
void glt_barrier_free(GLT_barrier *barrier);

 /** @ingroup BARRIER
 * @brief Waits into a barrier.
 *
 * \c glt_barrier_wait() Executed by a ULT, it waits until the number of waiters
  * is achieved.
 * @param[in]  barrier  Handle to the target \c GLT_barrier.
 */
void glt_barrier_wait(GLT_barrier *barrier);

/** @ingroup CONDITION
 * @brief Creates a condition.
 *
 * \c glt_cond_create() creates a condition for ULTs.
 * @param[in,out] cond   Hande to newly created \c GLT_condition
 */
void glt_cond_create(GLT_cond *cond);

 /** @ingroup CONDITION
 * @brief Destroys a condition.
 *
 * \c glt_cond_free() destroys a condition for ULTs.
 * @param[in]  cond  Handle to the target \c GLT_condition.
 */
void glt_cond_free(GLT_cond *cond);

 /** @ingroup CONDITION
 * @brief Sends a signal for a condition.
 *
 * \c glt_cond_signal() sends a signal for ULTs.
 * @param[in]  cond  Handle to the target \c GLT_condition.
 */
void glt_cond_signal(GLT_cond cond);

 /** @ingroup CONDITION
 * @brief A ULT waits in this point for a signal.
 *
 * \c glt_cond_wait() a ULT waits at this point for a signal to access the mutex.
 * @param[in]  cond  Handle to the target \c GLT_condition.
 * @param[in]  mutex  Handle to the target \c GLT_mutex.
 */
void glt_cond_wait(GLT_cond cond, GLT_mutex mutex);

 /** @ingroup CONDITION
 * @brief Broadcast a signal for a condition.
 *
 * \c glt_cond_broadcast() broadcasts a signal for ULTs.
 * @param[in]  cond  Handle to the target \c GLT_condition.
 */
void glt_cond_broadcast(GLT_cond cond);

 /** @ingroup TIMER
 * @brief Returns the current time.
 *
 * \c glt_get_wtime() returns the time.
 * @return The time in seconds.      
 */
double glt_get_wtime();

/** @ingroup TIMER
 * @brief Creates a timer.
 *
 * \c glt_timer_create() creates a timer.
 * @param[in,out] timer   Hande to newly created \c GLT_timer.
 */
void glt_timer_create(GLT_timer * timer);

 /** @ingroup TIMER
 * @brief Destroys a timer.
 *
 * \c glt_timer_free() destroys a timer.
 * @param[in]  timer  Handle to the target \c GLT_timer.
 */
void glt_timer_free(GLT_timer * timer);

 /** @ingroup TIMER
 * @brief Inits a timer.
 *
 * \c glt_timer_start() inits a timer.
 * @param[in]  timer  Handle to the target \c GLT_timer.
 */
void glt_timer_start(GLT_timer timer);

 /** @ingroup TIMER
 * @brief Stops a timer.
 *
 * \c glt_timer_stop() stops a timer.
 * @param[in]  timer  Handle to the target \c GLT_timer.
 */
void glt_timer_stop(GLT_timer timer);

/** @ingroup TIMER
 * @brief Obtains the elapsed time.
 *
 * \c glt_timer_get_secs() given a timer. It calculates the elapsed time in seconds.
 * @param[in]  timer  Handle to the target \c GLT_timer.
 * @param[out]  secs  Seconds.
 */
void glt_timer_get_secs(GLT_timer timer, double *secs);

/** @ingroup UTIL
 * @brief Obtains the number of the current thread.
 *
 * \c glt_get_thread_num() returns the number of the current thread.
 * @return  The number of the current c\ GLT_thread.
 */
int glt_get_thread_num();

/** @ingroup UTIL
 * @brief Returns the total number of threads.
 *
 * \c glt_get_num_threads() returns the number threads.
 * @return  The number of c\ GLT_threads.
 */
int glt_get_num_threads();

/** @ingroup SCHED
 * @brief Destroys the scheduler configuration.
 *
 * \c glt_scheduler_config_free() deletes the scheduler configuration.
 * @param[in]  config Handle of the target c\ GLT_sched_config.
 */
void glt_scheduler_config_free(GLT_sched_config *config);

/** @ingroup SCHED
 * @brief Creates a new scheduler.
 *
 * \c glt_scheduler_create() creates a new scheduler for some threads.
 * @param[in]  def Handle of the target c\ GLT_sched_def.
 * @param[in]  num_threads number of \c GLT_thread affected by this scheduler.
 * @param[in]  threads_id pointer to an array of c\ GLT_threads_id.
 * @param[in]  config Handle of the target c\ GLT_sched_config.
 * @param[out]  newsched Handle of new c\ GLT_sched.
 */
void glt_scheduler_create(GLT_sched_def *def, int num_threads,
        int *threads_id, GLT_sched_config config, GLT_sched *newsched);

/** @ingroup SCHED
 * @brief Creates a new scheduler with predefined behaviour.
 *
 * \c glt_schededuler_create_basic() creates a new scheduler for some threads with
 * a predefined behaviour.
 * @param[in]  def Handle of the target c\ GLT_sched_predef.
 * @param[in]  num_threads number of \c GLT_thread affected by this scheduler.
 * @param[in]  threads_id pointer to an array of c\ GLT_threads_id.
 * @param[in]  config Handle of the target c\ GLT_sched_config.
 * @param[out]  newsched Handle of new c\ GLT_sched.
 */
void glt_schededuler_create_basic(GLT_sched_predef predef,
        int num_threads, int *threads_id, GLT_sched_config config,
        GLT_sched *newsched);

/** @ingroup SCHED
 * @brief Destroys a scheduler.
 *
 * \c glt_scheduler_free() destroys a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 */

void glt_scheduler_free(GLT_sched *sched);

/** @ingroup SCHED
 * @brief Finalizes a scheduler.
 *
 * \c glt_scheduler_finish() finalizes a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 */
void glt_scheduler_finish(GLT_sched sched);

/** @ingroup SCHED
 * @brief Stops a scheduler.
 *
 * \c glt_scheduler_exit() Stops a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 */
void glt_scheduler_exit(GLT_sched sched);

/** @ingroup SCHED
 * @brief Requires to a scheduler to stop.
 *
 * \c glt_scheduler_has_to_stop() Requires a scheduler to stop.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 * @param[out]  stop shows the answer of the scheduler.
 */
void glt_scheduler_has_to_stop(GLT_sched sched, GLT_bool *stop);

/** @ingroup SCHED
 * @brief Sets new data to a scheduler.
 *
 * \c glt_scheduler_set_data() Sets data to a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 * @param[in]  data to be set.
 */
void glt_scheduler_set_data(GLT_sched sched, void *data);

/** @ingroup SCHED
 * @brief gets data from a scheduler.
 *
 * \c glt_scheduler_get_data() gets data from a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 * @param[out] data obtained.
 */
void glt_scheduler_get_data(GLT_sched sched, void **data);

/** @ingroup SCHED
 * @brief gets the current size from the scheduler.
 *
 * \c glt_scheduler_get_size() gets size from a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 * @param[out] size obtained.
 */
void glt_scheduler_get_size(GLT_sched sched, size_t *size);

/** @ingroup SCHED
 * @brief gets the total size from the scheduler.
 *
 * \c glt_scheduler_get_total_size() gets the total size from a scheduler.
 * @param[in]  sched Handle of the target c\ GLT_sched.
 * @param[out] size obtained.
 */
void glt_scheduler_get_total_size(GLT_sched sched, size_t *size);

/** @ingroup KEY
 * @brief Creates a key.
 *
 * \c glt_key_create() creates a key.
 * @param[in] destructor Hande to newly created \c GLT_ult.
 * @param[out] newkey   Hande to newly created \c GLT_key.
 */
void glt_key_create(void(*destructor)(void *value), GLT_key *newkey);

 /** @ingroup KEY
 * @brief Destroys a key.
 *
 * \c glt_key_free() destroys a key for ULTs.
 * @param[in]  key  Handle to the target \c GLT_key.
 */
void glt_key_free(GLT_key *key);

/** @ingroup KEY
 * @brief Sets new value to a key.
 *
 * \c glt_key_set() Sets value to a key.
 * @param[in]  key Handle of the target c\ GLT_key.
 * @param[in]  value to be set.
 */
void glt_key_set(GLT_key key, void *value);

/** @ingroup KEY
 * @brief Gets value from a key.
 *
 * \c glt_key_get() Gets value from a key.
 * @param[in]  key Handle of the target c\ GLT_key.
 * @param[out]  value obtained value.
 */
void glt_key_get(GLT_key key, void **value);

int glt_can_event_functions();
int glt_can_future_functions();
int glt_can_promise_functions();
//int glt_can_tls_functions();
int glt_can_extended_mutex();
int glt_can_manage_pools();
//int glt_can_manage_scheduler();
int glt_can_self();
int glt_can_manage_threads();
int can_extended_tasklets();
int can_extended_ults();

//QUERY functions for QTHREADS
//Always return 0;
int glt_can_extended_basic();
int glt_can_atomic_functions();
int glt_can_feb_functions();
int glt_can_sinc_functions();
int glt_can_loop_functions();
int glt_can_util_functions();
int glt_can_data_structures_functions();
int glt_can_syscall_functions();
int glt_can_extended_runtime();

//QUERY functions for MAssiveThreads
//Always return 0;
int glt_can_wsapi_functions();
int glt_can_prof_functions();
int glt_can_log_functions();
int can_felock_functions();
int can_extended_workunits();

#ifndef CORE
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
void glt_pool_create_scheduler(GLT_sched_def *def, int num_pools,
        GLT_pool *pools, GLT_sched_config config, GLT_sched *newsched);
void glt_pool_create_basic_scheduler(GLT_sched_predef predef,
        int num_pools, GLT_pool *pools, GLT_sched_config config,
        GLT_sched *newsched);
void glt_pool_scheduler_get_pools(GLT_sched sched, int max_pools,
        int idx, GLT_pool *pools);
void glt_pool_scheduler_get_num_pools(GLT_sched sched, int *num_pools);

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

void glt_tasklet_get_thread(GLT_tasklet tasklet, GLT_thread *thread);
void glt_tasklet_get_state(GLT_tasklet tasklet, GLT_tasklet_state *state);
void glt_tasklet_get_last_pool(GLT_tasklet tasklet, GLT_pool *pool);
void glt_tasklet_get_last_pool_id(GLT_tasklet tasklet, int *id);
void glt_tasklet_set_migratable(GLT_tasklet tasklet, GLT_bool flag);
void glt_tasklet_is_migratable(GLT_tasklet tasklet, GLT_bool *flag);
void glt_tasklet_equal(GLT_tasklet tasklet1, GLT_tasklet tasklet2, GLT_bool *result);
void glt_tasklet_retain(GLT_tasklet tasklet);
void glt_tasklet_release(GLT_tasklet tasklet);
void glt_tasklet_get_arg(GLT_tasklet tasklet, void **arg);
void glt_tasklet_create_to_pool(GLT_pool pool, void(*thread_func)(void *), void *arg, GLT_tasklet *new_ult);

void glt_ult_create_to_pool(GLT_pool pool, void(*thread_func)(void *), void *arg, GLT_ult *new_ult);
void glt_ult_get_state(GLT_ult ult, GLT_ult_state *state);
void glt_ult_get_last_pool(GLT_ult ult, GLT_pool *pool);
void glt_ult_get_last_pool_id(GLT_ult ult, int *id);
void glt_ult_resume(GLT_ult ult);
void glt_ult_migrate_to_thread(GLT_ult ult, GLT_thread thread);
void glt_ult_migrate_to_scheduler(GLT_ult ult, GLT_sched sched);
void glt_ult_migrate_to_pool(GLT_ult ult, GLT_pool pool);
void glt_ult_migrate(GLT_ult ult);
void glt_ult_set_callback(GLT_ult ult, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg);
void glt_ult_set_migratable(GLT_ult ult, GLT_bool flag);
void glt_ult_is_migratable(GLT_ult ult, GLT_bool *flag);
void glt_ult_is_primary(GLT_ult ult, GLT_bool *flag);
void glt_ult_equal(GLT_ult ult1, GLT_ult ult2, GLT_bool * result);
void glt_ult_retain(GLT_ult ult);
void glt_ult_release(GLT_ult ult);
void glt_ult_get_stacksize(GLT_ult ult, size_t *stacksize);
void glt_ult_get_arg(GLT_ult ult, void **arg);
void glt_ult_attr_create(GLT_ult_attr *newattr);
void glt_ult_attr_free(GLT_ult_attr *attr);
void glt_ult_attr_set_stacksize(GLT_ult_attr attr, size_t stacksize);
void glt_ult_attr_get_stacksize(GLT_ult_attr attr, size_t *stacksize);
void glt_ult_attr_set_callback(GLT_ult_attr attr, void(*cb_func)(GLT_ult ult, void *cb_arg), void *cb_arg);
void glt_ult_attr_set_migratable(GLT_ult_attr attr, GLT_bool flag);

//HEADERS for QTHREADS extended functions
void glt_ult_create_syncvar(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar);
void glt_ult_create_syncvar_to(void(*thread_func)(void *), void * arg,
        GLT_syncvar *syncvar, int dest, int npreconds, ...);
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
void glt_feb_readFE(GLT_memory_state *dst, const GLT_memory_state *src);
void glt_feb_readFF(GLT_memory_state *dst, const GLT_memory_state *src);
void glt_feb_writeEF(GLT_memory_state * restrict dst, const GLT_memory_state * restrict src);
void glt_feb_writeEF_const(GLT_memory_state * dst, GLT_memory_state src);
void glt_feb_writeF(GLT_memory_state * restrict dst, const GLT_memory_state * restrict src);
void glt_feb_writeF_const(GLT_memory_state * dst, GLT_memory_state src);
void glt_syncvar_empty(GLT_syncvar *dest);
void glt_syncvar_fill(GLT_syncvar *dest);
void glt_syncvar_status(GLT_syncvar *addr, int *status);
void glt_syncvar_readFE(uint64_t * restrict dst, GLT_syncvar * restrict src);
void glt_syncvar_readFF(uint64_t * restrict dst, GLT_syncvar * restrict src);
void glt_syncvar_writeEF(GLT_syncvar * restrict dst, const uint64_t * restrict src);
void glt_syncvar_writeEF_const(GLT_syncvar * dst, uint64_t src);
void glt_syncvar_writeF(GLT_syncvar * restrict dst, const uint64_t * restrict src);
void glt_syncvar_writeF_const(GLT_syncvar * dst, uint64_t src);
void glt_sinc_create(GLT_sinc *sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected);
void glt_sinc_init(GLT_sinc *restrict sinc, size_t sizeof_value,
        const void * initial_value, GLT_sinc_op op, size_t expected);
void glt_sinc_destroy(GLT_sinc *sinc);
void glt_sinc_fini(GLT_sinc * sinc);
void glt_sinc_reset(GLT_sinc * sinc, size_t expect);
void glt_sinc_submit(GLT_sinc * restrict sinc, const void * restrict value);
void glt_sinc_wait(GLT_sinc * restrict sinc, void * restrict target);
void glt_loop(const size_t start, const size_t end,
        const GLT_loop_f func, void * arg);


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
void glt_ds_pool_free(GLT_ds_pool *restrict pool,
        void * restrict mem);
void glt_ds_array_create(GLT_ds_array *array, const size_t count,
        const size_t item_size);
void glt_ds_array_create_tight(GLT_ds_array *array,
        const size_t count, const size_t item_size);
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
        const size_t index, GLT_thread id);
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
        void * args, void * ret, const size_t resize, GLT_accum_f acc);
void glt_ds_lfqueue_create(GLT_ds_lfqueue * lfqueue);
void glt_ds_lfqueue_destroy(GLT_ds_lfqueue * lfqueue);
void glt_ds_lfqueue_enqueue(GLT_ds_lfqueue * lfqueue, void * elem);
void glt_ds_lfqueue_dequeue(void * elem, GLT_ds_lfqueue * lfqueue);
void glt_ds_lfqueue_empty(GLT_bool * empty, GLT_ds_lfqueue * lfqueue);
void glt_ds_dqueue_create(GLT_ds_dqueue * dqueue);
void glt_ds_dqueue_destroy(GLT_ds_dqueue * dqueue);
void glt_ds_dqueue_enqueue(GLT_ds_dqueue * dqueue, void * elem);
void glt_ds_dqueue_enqueue_there(GLT_ds_dqueue * dqueue,
        void * elem, GLT_thread id);
void glt_ds_dqueue_dequeue(void * elem, GLT_ds_dqueue * dqueue);
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
int glt_syscall_wait4(pid_t pid, int *stat_loc, int options,
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

//HEADERS for MASSIVETHREADS extended functions
void glt_wu_create_ex(GLT_ult * ult, GLT_workunit_f func, void * arg,
        GLT_workunit_o opt);

void glt_yield2();
void glt_wu_detach(GLT_ult ult);
void glt_wu_set_cancel_state(int state, int *oldstate);
void glt_wu_set_cancel_type(int type, int *oldtype);
void glt_wu_test_cancel();
void glt_wu_set_def_stack_size(size_t newsize);

void glt_felock_create(GLT_felock * felock);
void glt_felock_free(GLT_felock felock);
void glt_felock_lock(GLT_bool *lock, GLT_felock felock);
void glt_felock_wait_lock(GLT_bool *lock, GLT_felock felock, int val);
void glt_felock_unlock(GLT_bool *unlock, GLT_felock felock);
void glt_felock_status(GLT_felock_status *status, GLT_felock felock);
void glt_felock_set_unlock(GLT_felock felock, int val);

void glt_key_create(void(*destructor)(void *value), GLT_key *newkey);
void glt_key_free(GLT_key *key);
void glt_key_set(GLT_key key, void *value);
void glt_key_get(GLT_key key, void **value);

void glt_log_start();
void glt_log_pause();
void glt_log_flush();
void glt_log_reset();
void glt_log_annotate_ult(GLT_ult ult, char *name);
void glt_sched_prof_start();
void glt_sched_prof_pause();

void glt_wsapi_runqueue_peek(GLT_ult *ult, int victim, void *ptr, size_t *psize);
void glt_wsapi_get_hint_size(size_t *size, GLT_ult ult);
void glt_wsapi_get_hint_ptr(void *ptr, GLT_ult ult);
void glt_wsapi_set_hint(GLT_ult ult, void **data, size_t *size);
void glt_wsapi_rand(int * rand);
void glt_wsapi_randrr(int *ret, int n);
void glt_wsapi_runqueue_take(GLT_ult * ult, int victim, GLT_wsapi_decide_f decidefn, void *udata);
void glt_wsapi_runqueue_pass(GLT_bool *pass, int target, GLT_ult ult);
void glt_wsapi_runqueue_push(GLT_ult ult);
void glt_wsapi_runqueue_pop(GLT_ult * ult);
void glt_wsapi_set_stealfunc(GLT_wsapi_steal_f *out, GLT_wsapi_steal_f fn);

#endif

#endif /* glt_H */

