/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_can_extended_runtime() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_subthread_get_num(GLT_subthread *num) {
    *num = qthread_num_workers();
}

GLT_func_prefix void glt_cacheline(int *cl) {
    *cl = qthread_cacheline();
}

GLT_func_prefix void glt_sorted_threads(const GLT_thread * list) {
    list = qthread_sorted_sheps();
}

GLT_func_prefix void glt_sorted_threads_remote(const GLT_thread * list, const GLT_thread src) {
    list = qthread_sorted_sheps_remote(src);
}

GLT_func_prefix void glt_debuglevel(size_t *level, const enum introspective_state type) {
    *level = qthread_debuglevel(type);
}

GLT_func_prefix void glt_readstate(size_t *value, const enum introspective_state type) {
    *value = qthread_readstate(type);
}

GLT_func_prefix void glt_thread_distance(int * dist, const GLT_thread src, const GLT_thread dst) {
    *dist = qthread_distance(src, dst);
}

GLT_func_prefix void glt_thread_enable(GLT_thread id) {
    qthread_enable_shepherd(id);
}

GLT_func_prefix void glt_thread_disable(GLT_bool *res, GLT_thread id) {
    *res = qthread_disable_shepherd(id);
}

GLT_func_prefix void glt_subthread_enable(GLT_subthread id) {
    qthread_enable_worker(id);
}

GLT_func_prefix void glt_subthread_disable(GLT_bool *res, GLT_subthread id) {
    *res = qthread_disable_worker(id);
}

GLT_func_prefix void glt_thread_ok(GLT_bool *res) {
    *res = qthread_shep_ok();
}

#endif
