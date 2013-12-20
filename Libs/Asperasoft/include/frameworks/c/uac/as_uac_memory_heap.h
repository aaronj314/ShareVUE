/*
 * memory_heap.h
 *
 * Stack like memory handler.  So you can allocate a bunch of stuff without having to
 * keep track of individual pointers and free the lot of it all at once.
 *
 */

#ifndef __ASPERA_MEMORY_HEAP_H__
#define __ASPERA_MEMORY_HEAP_H__

#ifdef __cplusplus
extern "C" {
#endif

struct _memory_heap;
typedef struct _memory_heap *memory_heap;

void *memory_heap_malloc_from_special( memory_heap *p_heap, int bytes, int alignment );
void *memory_heap_malloc( int bytes, int alignment );
void *memory_heap_calloc_from_special( memory_heap *p_heap, int bytes, int alignment );
void *memory_heap_calloc( int bytes, int alignment );
char *memory_heap_strdup_from_special( memory_heap *p_heap, const char *source );
char *memory_heap_strdup( const char *source );

void memory_heap_pop_special( memory_heap heap, int bytes );
void memory_heap_pop( int bytes );

int memory_heap_lock( void );
int memory_heap_unlock( void );

#define memory_heap_create_special() ( (memory_heap) 0 )

void memory_heap_release_special( memory_heap *p_heap );
void memory_heap_release( void );
int memory_heap_allocated_heaps( void );

memory_heap *memory_heap_default_heap( void );

#ifdef __cplusplus
}
#endif

#endif
