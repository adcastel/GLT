/* See COPYRIGHT in top-level directory. */
/*
 * Event functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//Event functions
GLT_func_prefix int glt_can_event_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE
GLT_func_prefix void glt_get_error_str(int errno, char *str, size_t *len) {
    CHECK(ABT_error_get_str(errno, str, len),ABT_SUCCESS);
}

GLT_func_prefix void glt_event_add_callbac(GLT_event_kind event, GLT_event_cb_fn ask_cb,
        void *ask_user_arg, GLT_event_cb_fn act_cb, void *act_user_arg,
        int *cb_id) {
    CHECK(ABT_event_add_callback(event, ask_cb, ask_user_arg, act_cb,
            act_user_arg, cb_id),ABT_SUCCESS);
}

GLT_func_prefix void glt_event_del_callback(GLT_event_kind event, int cb_id) {
    CHECK(ABT_event_del_callback(event, cb_id),ABT_SUCCESS);
}
#endif