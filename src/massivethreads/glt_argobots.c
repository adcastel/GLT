/* See COPYRIGHT in top-level directory. */
/*
 * Argobots library functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_event_functions() {
    return 0;
}

GLT_func_prefix int glt_can_future_functions() {
    return 0;
}

GLT_func_prefix int glt_can_malleability() {
    return 0;
}


#ifndef CORE

//HEADERS for ARGOBOTS extended functions
GLT_func_prefix void glt_get_error_str(int errno, char *str, size_t *len) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_event_del_callback(GLT_event_kind event, int cb_id) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_create(int nbytes, GLT_future *newfuture) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_free(GLT_future *future) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_wait(GLT_future future, void **value) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_future_set(GLT_future future, void *value, int nbytes) {
    GLT_ERROR_ARG;
}

GLT_func_prefix void glt_thread_enable(){}
GLT_func_prefix void glt_thread_disable(){}
GLT_func_prefix void glt_thread_enable_id(int thread_id){}
GLT_func_prefix void glt_thread_disable_id(int thread_id){}


#endif
