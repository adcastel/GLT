/* See COPYRIGHT in glt_common.h file. */
/*
 * Self functions file.
 */


#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

//self functions
GLT_func_prefix int glt_can_self() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_self_get_type(GLT_unit_type *type) {
    ABT_self_get_type(type);
}

GLT_func_prefix void glt_self_is_primary(GLT_bool *flag) {
    ABT_self_is_primary(flag);
}

GLT_func_prefix void glt_self_on_primary_xstream(GLT_bool *flag) {
    ABT_self_on_primary_xstream(flag);
}

GLT_func_prefix void glt_self_get_last_pool_id(int *pool_id) {
    ABT_self_get_last_pool_id(pool_id);
}

GLT_func_prefix void glt_self_suspend(void) {
    ABT_self_suspend();
}

GLT_func_prefix void glt_self_get_arg(void **arg) {
    ABT_self_get_arg(arg);
}

#endif