#ifndef AS_UTILS_CONTAINERS_H
#define AS_UTILS_CONTAINERS_H

#include "asmemory.h"
#include "ascontainers.h"


typedef struct _as_binary_tree_node
{
    void *key;

    void *payload;

    struct _as_binary_tree_node *left, *right;

} as_binary_tree_node;


    // Forward declared inside ascontainers.h
struct _as_binary_tree
{
    as_binary_tree_allocate_payload payload_constructor;
    as_binary_tree_release_payload  payload_destructor;

    as_binary_tree_duplicate_key key_duplicator;
    as_binary_tree_release_key   key_destructor;

    as_binary_tree_compare_keys  key_comparator;

    as_memory_pool node_pool;

    int param_is_memory_pool;
    void *ctor_param;

    as_binary_tree_node *root;
};

#endif
