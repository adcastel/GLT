/* See COPYRIGHT in top-level directory. */
/*
 * Function headers file.
 */


#ifndef GLT_H
#define GLT_H

/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif

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

/** \defgroup UTIL util functions
 * These functions return values from the environment set up.
 */

/** \defgroup SCHED Scheduler functions
 * These functions manages the configurable scheduler (just with Argobots).
 */

/** \defgroup KEY Key functions
 * These functions manage the GLT keys for the ULTs.
 */
#include <glt_common.h>
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

glt_team_t * glt_get_team();


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
void glt_ult_free(GLT_ult *ult);
void glt_tasklet_free(GLT_tasklet *tasklet);
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
int glt_mutex_trylock(GLT_mutex mutex);

/** @ingroup MUTEX
 * @brief Locks a mutex without contextswitch.
 *
 * \c glt_mutex_spinlock() locks (if possible) a mutex.
 * @param[in] mutex   Handle to the target \c GLT_mutex.
 */
void glt_mutex_spinlock(GLT_mutex mutex);


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
int glt_can_manage_scheduler();
int glt_can_malleability();


#ifndef CORE

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


void glt_get_error_str(int errno, char *str, size_t *len);

void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id);
void glt_event_del_callback(GLT_event_kind event, int cb_id);

void glt_future_create(int nbytes, GLT_future *newfuture);
void glt_future_free(GLT_future *future);
void glt_future_wait(GLT_future future, void **value);
void glt_future_set(GLT_future future, void *value, int nbytes);

//Malleability
void glt_thread_enable();
void glt_thread_disable();
void glt_thread_enable_id(int thread_id);
void glt_thread_disable_id(int thread_id);

#endif

#if defined(__cplusplus)
}
#endif

#endif /* glt_H */

