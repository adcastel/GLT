#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix void glt_cond_create(GLT_cond *cond) {
    *cond = myth_cond_create();
}

GLT_func_prefix void glt_cond_free(GLT_cond *cond) {
    myth_cond_destroy(*cond);
}

GLT_func_prefix void glt_cond_signal(GLT_cond cond) {
    myth_cond_signal(cond);
}

GLT_func_prefix void glt_cond_wait(GLT_cond cond, GLT_mutex mutex) {
    myth_cond_wait(cond, mutex);
}

GLT_func_prefix void glt_cond_broadcast(GLT_cond cond) {
    myth_cond_broadcast(cond);
}