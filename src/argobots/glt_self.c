/* See COPYRIGHT in top-level directory. */
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
    CHECK(ABT_self_get_type(type),ABT_SUCCESS);
}

GLT_func_prefix void glt_self_is_primary(GLT_bool *flag) {
    CHECK(ABT_self_is_primary(flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_self_on_primary_xstream(GLT_bool *flag) {
    CHECK(ABT_self_on_primary_xstream(flag),ABT_SUCCESS);
}

GLT_func_prefix void glt_self_get_last_pool_id(int *pool_id) {
    CHECK(ABT_self_get_last_pool_id(pool_id),ABT_SUCCESS);
}

GLT_func_prefix void glt_self_suspend(void) {
    CHECK(ABT_self_suspend(),ABT_SUCCESS);
}

GLT_func_prefix void glt_self_get_arg(void **arg) {
    CHECK(ABT_self_get_arg(arg),ABT_SUCCESS);
}

#endif