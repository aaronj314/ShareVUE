#ifndef ASMEMORY_H
#define ASMEMORY_H

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Memory Pool
 *
 * A set of like sized memory objects that can be quickly allocated and freed.
 *
 */

typedef enum
{
        // Clear all allocations to zero.
    as_memory_pool_clear_allocations = 0x01,

        // Put mutexes around accesses.
    as_memory_pool_thread_safe = 0x02
}
as_memory_pool_flags_e;

struct _as_memory_pool;
typedef struct _as_memory_pool *as_memory_pool;

    // size is the size of each element, granularity is the number
    // of elements to allocate in one shot as the pool grows.
as_memory_pool as_memory_pool_create( size_t element_size, size_t granularity, as_memory_pool_flags_e flags );
void as_memory_pool_destroy( as_memory_pool pool );

    // malloc and free, basically.
void *as_memory_pool_allocate( as_memory_pool pool );
void *as_memory_pool_access_member( as_memory_pool pool, int _index );
int as_memory_pool_free( as_memory_pool pool, void *item );

u_int32_t as_memory_pool_active_members( as_memory_pool pool );

    // General purpose fast "count the bits set in a 32 bit int" routine.
    // I couldn't find an obvious place to put it, so I left it here.
u_int32_t as_count_set_bits_32(u_int32_t u);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ASPATH_H
