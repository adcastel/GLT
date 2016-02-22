
#include <glt.h>

void glt_cond_create(GLT_cond *cond){
    ABT_cond_create (cond);
}

void glt_cond_free(GLT_cond *cond){
    ABT_cond_free (cond);
}

void glt_cond_signal(GLT_cond cond){
    ABT_cond_signal (cond);
}

void glt_cond_wait(GLT_cond cond, GLT_mutex mutex){
    ABT_cond_wait (cond, mutex);
}

void glt_cond_broadcast(GLT_cond cond){
    ABT_cond_broadcast (cond);
}