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



#ifndef CORE

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


#endif
