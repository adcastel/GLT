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

//pools functions
GLT_func_prefix int glt_can_manage_pools() {
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}
#ifndef CORE

GLT_func_prefix void glt_pool_create(GLT_pool_def *def, GLT_pool_config config,
        GLT_pool *newpool) {
    if (main_team->num_pools < main_team->max_elem) {
        ABT_pool_create(def, config, newpool);
        main_team->pools[main_team->num_pools] = newpool;
        main_team->num_pools++;
    } else {
        printf("Error: There are not more sloots for pools\n");
    }
}

GLT_func_prefix void glt_pool_create_basic(GLT_pool_kind kind,
        GLT_pool_access access, GLT_bool automatic, GLT_pool *newpool) {
    if (main_team->num_pools < main_team->max_elem) {
        ABT_pool_create_basic(kind, access, automatic, newpool);
        main_team->pools[main_team->num_pools] = newpool;
        main_team->num_pools++;
    } else {
        printf("Error: There are not more sloots for pools\n");
    }
}

GLT_func_prefix void glt_pool_free(GLT_pool *pool) {
    ABT_pool_free(pool);
}

GLT_func_prefix void glt_pool_get_access(GLT_pool pool, GLT_pool_access *access) {
    ABT_pool_get_access(pool, access);
}

GLT_func_prefix void glt_pool_get_total_size(GLT_pool pool, size_t *size) {
    ABT_pool_get_total_size(pool, size);
}

GLT_func_prefix void glt_pool_get_size(GLT_pool pool, size_t *size) {
    ABT_pool_get_size(pool, size);
}

GLT_func_prefix void glt_pool_pop(GLT_pool pool, GLT_unit *p_unit) {
    ABT_pool_pop(pool, p_unit);
}

GLT_func_prefix void glt_pool_push(GLT_pool pool, GLT_unit p_unit) {
    ABT_pool_push(pool, p_unit);
}

GLT_func_prefix void glt_pool_remove(GLT_pool pool, GLT_unit p_unit) {
    ABT_pool_remove(pool, p_unit);
}

GLT_func_prefix void glt_pool_set_data(GLT_pool pool, void *data) {
    ABT_pool_set_data(pool, data);
}

GLT_func_prefix void glt_pool_get_data(GLT_pool pool, void **data) {
    ABT_pool_get_data(pool, data);
}

GLT_func_prefix void glt_pool_add_sched(GLT_pool pool, GLT_sched sched) {
    ABT_pool_add_sched(pool, sched);
}

GLT_func_prefix void glt_pool_get_id(GLT_pool pool, int *id) {
    ABT_pool_get_id(pool, id);
}
#endif
