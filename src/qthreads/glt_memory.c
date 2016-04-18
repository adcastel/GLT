/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_return 
#else
#define GLT_return static inline
#endif

GLT_return int glt_can_memory_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

GLT_return void * glt_memory_make_stat_map(const off_t filesize, void *addr,
        const char *filename, size_t itemsize, const size_t streams)
{
    return qalloc_makestatmap (filesize, addr, filename, itemsize, streams);
}

GLT_return void * glt_memory_make_dyn_map(const off_t filesize, void *addr,
        const char *filename,  const size_t streams)
{
    return qalloc_makedynmap (filesize, addr, filename, streams);
}

GLT_return void * glt_memory_load_map(const char *filename)
{
    return qalloc_loadmap (filename);
}

GLT_return void * glt_memory_malloc(void *map, size_t size)
{
    return qalloc_malloc (map,size);
}

GLT_return void * glt_memory_stat_malloc(struct mapinfo_s *map)
{
    return qalloc_statmalloc (map);
}

GLT_return void * glt_memory_dyn_malloc(struct dynmapinfo_s *map, size_t size)
{
    return qalloc_dynmalloc (map, size);
}

GLT_return void glt_memory_free(void *block, void * map)
{
     qalloc_free (block,map);
}

GLT_return void glt_memory_stat_free(void *block, struct mapinfo_s *map)
{
     qalloc_statfree (block,map);
}

GLT_return void glt_memory_dyn_free(void *block, struct dynmapinfo_s *map)
{
     qalloc_dynfree (block,map);
}

GLT_return void glt_memory_cleanup()
{
    qalloc_cleanup();
}

GLT_return void glt_memory_checkpoint()
{
    qalloc_checkpoint();
}

#endif