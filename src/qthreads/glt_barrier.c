/* See COPYRIGHT in top-level directory. */
/*
 * Barrier functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix void glt_barrier_create(int num_waiters, GLT_barrier *barrier) {
//            int a = qthread_shep();
//    printf("en glt_barrier_create con tid %d\n",a);
    *barrier = qt_barrier_create(num_waiters, UPLOCK);
    //barrier = qthread_feb_barrier_create(num_waiters);
}

GLT_func_prefix void glt_barrier_free(GLT_barrier *barrier) {
//            int a = qthread_shep();
 //   printf("en glt_barrier_free con tid %d\n",a);
    CHECK(qt_barrier_destroy(*barrier),0);
    //qthread_feb_barrier_destroy(barrier);
}

GLT_func_prefix void glt_barrier_wait(GLT_barrier *barrier) {
 //           int a = qthread_shep();
 //   printf("en glt_barrier_wait con tid %d\n",a);
    CHECK(qt_barrier_enter(*barrier),0);
    //qthread_feb_barrier_enter(barrier);
}


