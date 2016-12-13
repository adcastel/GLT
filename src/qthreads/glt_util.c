/* See COPYRIGHT in top-level directory. */
/*
 * Util functions file.
 */
#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix int glt_get_num_threads() {
    return main_team->num_shepherds;
}

GLT_func_prefix int glt_get_thread_num() {
    int a = qthread_shep();
    //printf("en glt_get_thread_num devolviendo %d\n",a);
    return a;
}

GLT_func_prefix int glt_can_util_functions() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_func_prefix void glt_util_double_max(double * res, double * array,
        size_t lenght, int checkfeb) {
    *res = qutil_double_max(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_uint_max(unsigned int * res,
        const long unsigned int * array, size_t lenght, int checkfeb) {
    *res = qutil_uint_max(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_int_max(int * res, const long int * array,
        size_t lenght, int checkfeb) {
    *res = qutil_int_max(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_double_min(double * res, double * array,
        size_t lenght, int checkfeb) {
    *res = qutil_double_min(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_uint_min(unsigned int * res,
        const long unsigned int * array, size_t lenght, int checkfeb) {
    *res = qutil_uint_min(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_int_min(int * res, const long int * array,
        size_t lenght, int checkfeb) {
    *res = qutil_int_min(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_double_mult(double * res, double * array,
        size_t lenght, int checkfeb) {
    *res = qutil_double_mult(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_uint_mult(unsigned int * res,
        const long unsigned int * array, size_t lenght, int checkfeb) {
    *res = qutil_uint_mult(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_int_mult(int * res, const long int * array,
        size_t lenght, int checkfeb) {
    *res = qutil_int_mult(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_double_sum(double * res, double * array,
        size_t lenght, int checkfeb) {
    *res = qutil_double_sum(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_uint_sum(unsigned int * res,
        const long unsigned int * array, size_t lenght,
        int checkfeb) {
    *res = qutil_uint_sum(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_int_sum(int * res, const long int * array, size_t lenght,
        int checkfeb) {
    *res = qutil_int_sum(array, lenght, checkfeb);
}

GLT_func_prefix void glt_util_qsort(double * array, size_t lenght) {
    qutil_qsort(array, lenght);
}

GLT_func_prefix void glt_util_mergesort(double * array, size_t lenght) {
    qutil_mergesort(array, lenght);
}

#endif

