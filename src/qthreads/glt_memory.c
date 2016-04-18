/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_memory_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void * glt_memory_make_stat_map(const off_t filesize, void *addr,
        const char *filename, size_t itemsize, const size_t streams)
{
    return qalloc_makestatmap (filesize, addr, filename, itemsize, streams);
}

 void * glt_memory_make_dyn_map(const off_t filesize, void *addr,
        const char *filename,  const size_t streams)
{
    return qalloc_makedynmap (filesize, addr, filename, streams);
}

 void * glt_memory_load_map(const char *filename)
{
    return qalloc_loadmap (filename);
}

 void * glt_memory_malloc(void *map, size_t size)
{
    return qalloc_malloc (map,size);
}

 void * glt_memory_stat_malloc(struct mapinfo_s *map)
{
    return qalloc_statmalloc (map);
}

 void * glt_memory_dyn_malloc(struct dynmapinfo_s *map, size_t size)
{
    return qalloc_dynmalloc (map, size);
}

 void glt_memory_free(void *block, void * map)
{
     qalloc_free (block,map);
}

 void glt_memory_stat_free(void *block, struct mapinfo_s *map)
{
     qalloc_statfree (block,map);
}

 void glt_memory_dyn_free(void *block, struct dynmapinfo_s *map)
{
     qalloc_dynfree (block,map);
}

 void glt_memory_cleanup()
{
    qalloc_cleanup();
}

 void glt_memory_checkpoint()
{
    qalloc_checkpoint();
}

#endif