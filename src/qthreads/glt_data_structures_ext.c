/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

  int glt_can_data_structures_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_ds_pool_create(GLT_ds_pool *pool, const size_t item_size)
{
    pool = qpool_create(item_size);
}

 void glt_ds_pool_create_aligned(GLT_ds_pool *pool, 
        const size_t item_size, const size_t alignment)
{
    pool = qpool_create_aligned(item_size, alignment);
}

 void glt_ds_pool_destroy(GLT_ds_pool *pool)
{
    qpool_destroy(pool);
}

 void glt_ds_pool_alloc(GLT_ds_pool *pool)
{
    qpool_alloc(pool);
}

 void glt_ds_pool_free(GLT_ds_pool *restrict pool, 
        void * restrict mem)
{
    qpool_free(pool, mem);
}

 void glt_ds_array_create(GLT_ds_array *array, const size_t count, 
        const size_t item_size)
{
    array = qarray_create(count,item_size);
}

 void glt_ds_array_create_tight(GLT_ds_array *array, 
        const size_t count, const size_t item_size)
{
    array = qarray_create_tight(count,item_size);
}

 void glt_ds_array_create_configured(GLT_ds_array *array, 
        const size_t count, const size_t item_size, 
        const GLT_ds_array_distribution d, const char thight, const int seg_pages)
{
    array = qarray_create_configured(count, item_size, d, thight, seg_pages);
}

 void glt_ds_array_destroy(GLT_ds_array *array)
{
    qarray_destroy(array);
}

 void glt_ds_array_elem(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    elem = qarray_elem(array,index);
}

 void glt_ds_array_elem_nomigrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    elem = qarray_elem_nomigrate(array,index);
}

 void glt_ds_array_elem_migrate(void * elem, const GLT_ds_array *array, 
        const size_t index)
{
    elem = qarray_elem_migrate(array,index);
}

 void glt_ds_array_thread_of(GLT_thread * id, const GLT_ds_array *array, 
        const size_t index)
{
    *id = qarray_shepof(array,index);
}

 void glt_ds_array_set_thread_of(GLT_ds_array *array, 
        const size_t index, GLT_thread id )
{
    qarray_set_shepof(array,index,id);
}

 void glt_ds_array_iter(GLT_ds_array *array, 
        const size_t start, const size_t stop, void(*thread_func)(void *))
{
    qarray_iter(array,start,stop,(void *)thread_func);
}

 void glt_ds_array_iter_loop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, void * arg)
{
    qarray_iter_loop(array,start,stop,thread_func,arg);
}

 void glt_ds_array_iter_nb(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loop_f thread_func, 
        void * args, aligned_t *arg)
{
    qarray_iter_loop_nb(array,start,stop,thread_func,args,arg);
}

 void glt_ds_array_iter_constloop(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_cloop_f thread_func, 
        void * args)
{
    qarray_iter_constloop(array,start,stop,thread_func,args);
}

 void glt_ds_array_iter_loopaccum(GLT_ds_array *array, 
        const size_t start, const size_t stop, GLT_ds_loopr_f thread_func, 
        void * args, void * ret, const size_t resize, GLT_accum_f acc )
{
    qarray_iter_loopaccum(array,start,stop,thread_func,args,ret,resize,acc);
}

 void glt_ds_lfqueue_create(GLT_ds_lfqueue * lfqueue)
{
    lfqueue = qlfqueue_create();
}

 void glt_ds_lfqueue_destroy(GLT_ds_lfqueue * lfqueue)
{
    qlfqueue_destroy(lfqueue);
}

 void glt_ds_lfqueue_enqueue(GLT_ds_lfqueue * lfqueue, void * elem)
{
    qlfqueue_enqueue(lfqueue,elem);
}

 void glt_ds_lfqueue_dequeue( void * elem, GLT_ds_lfqueue * lfqueue)
{
    elem = qlfqueue_dequeue(lfqueue);
}

 void glt_ds_lfqueue_empty(GLT_bool * empty, GLT_ds_lfqueue * lfqueue)
{
    *empty = qlfqueue_empty(lfqueue);
}

 void glt_ds_dqueue_create(GLT_ds_dqueue * dqueue)
{
    dqueue = qdqueue_create();
}

 void glt_ds_dqueue_destroy(GLT_ds_dqueue * dqueue)
{
    qdqueue_destroy(dqueue);
}

 void glt_ds_dqueue_enqueue(GLT_ds_dqueue * dqueue, void * elem)
{
    qdqueue_enqueue(dqueue,elem);
}

 void glt_ds_dqueue_enqueue_there(GLT_ds_dqueue * dqueue, 
        void * elem, GLT_thread id)
{
    qdqueue_enqueue_there(dqueue,elem,id);
}

 void glt_ds_dqueue_dequeue( void * elem, GLT_ds_dqueue * dqueue)
{
    elem = qdqueue_dequeue(dqueue);
}

 void glt_ds_dqueue_empty(GLT_bool * empty, GLT_ds_dqueue * dqueue)
{
    *empty = qdqueue_empty(dqueue);
}

 void glt_ds_dictionary_create(GLT_ds_dictionary * dictionary, 
        GLT_ds_dictionary_key_equals eq, 
        GLT_ds_dictionary_hash hash, GLT_ds_dictionary_cleanup cleanup)
{
    dictionary = qt_dictionary_create(eq, hash, cleanup);
}

 void glt_ds_dictionary_destroy(GLT_ds_dictionary * dictionary)
{
    qt_dictionary_destroy(dictionary);
}

 void glt_ds_dictionary_put(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value)
{
    next = qt_dictionary_put(dictionary, key, value);
}

 void glt_ds_dictionary_put_if_absent(void * next, GLT_ds_dictionary * dictionary,
        void * key, void *value)
{
    next = qt_dictionary_put_if_absent(dictionary, key, value);
}

 void glt_ds_dictionary_get(void * value, GLT_ds_dictionary * dictionary,
        void * key)
{
    value = qt_dictionary_get(dictionary, key);
}

 void glt_ds_dictionary_delete(void * value, GLT_ds_dictionary * dictionary,
        void * key)
{
    value = qt_dictionary_delete(dictionary, key);
}

 void glt_ds_dictionary_end(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary)
{
    it = qt_dictionary_end(dictionary);
}

 void glt_ds_dictionary_it_create(GLT_ds_dictionary_it *it, 
        GLT_ds_dictionary * dictionary)
{
    it = qt_dictionary_iterator_create(dictionary);
}

 void glt_ds_dictionary_it_destroy(GLT_ds_dictionary_it *it)
{
    qt_dictionary_iterator_destroy(it);
}

 void glt_ds_dictionary_it_next(void * entry, GLT_ds_dictionary_it *it)
{
    entry = qt_dictionary_iterator_next(it);
}

 void glt_ds_dictionary_it_get(void * entry, GLT_ds_dictionary_it *it)
{
    entry = qt_dictionary_iterator_get(it);
}

 void glt_ds_dictionary_it_equals(GLT_bool * eq, 
        GLT_ds_dictionary_it *it1, GLT_ds_dictionary_it *it2)
{
    *eq = qt_dictionary_iterator_equals(it1, it2);
}

 void glt_ds_dictionary_it_copy(GLT_ds_dictionary_it *output, 
        GLT_ds_dictionary_it *input)
{
    output = qt_dictionary_iterator_copy(input);
}
 
#endif