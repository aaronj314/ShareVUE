#ifndef ASCONTAINERS_H
#define ASCONTAINERS_H

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////
//                           //
//  Unbalanced binary trees  //
//                           //
///////////////////////////////

    // Forward declaration of binary tree type.  Implementation details are hidden in ascontainers.c.
struct _as_binary_tree;
typedef struct _as_binary_tree *as_binary_tree_t;

    // Callback types used by the tree objects.  See "Allocate a binary tree" below for discussion.
typedef void * (*as_binary_tree_allocate_payload)( void *param );
typedef void   (*as_binary_tree_release_payload)( void *param, void *payload );

typedef void * (*as_binary_tree_duplicate_key)( const void *);
typedef void   (*as_binary_tree_release_key)( void *key );

typedef int    (*as_binary_tree_compare_keys)( const void *left, const void *right );

    // Create a binary tree that uses a char * for a key (using strcmp to traverse).
    // The node payloads are automatically blank buffers of size payload_size.
    // "destructor" is optional and should call as_binary_tree_free_pool_memory()
    // before returning if overridden with something other than NULL.
ASUTILS_API as_binary_tree_t as_binary_tree_create_string_key_blank_payload( size_t payload_size, as_binary_tree_release_payload destructor );

    // Destructor used by default by above tree type.  You will need to call it
    // by hand if you supply your own destructor.  Think of it as a C++ base
    // destructor for payloads.
ASUTILS_API void as_binary_tree_free_pool_memory( void *param, void *payload );

    //
    // Allocate a binary tree.  Callback parameters are:
    //
    // constructor:     Allocates a payload for a node.  Is given
    //                  "constructor_param" and nothing else.  Returns a void *.
    // destructor:      Release a payload for a node.  Is given "constructor_param"
    //                  and a pointer to the payload.
    // key_duplicator:  Is given a key and should return a copy of it.  If you
    //                  know that the key is static, you can just return the
    //                  pointer you are given.
    // comparator:      Compares two keys strcmp style (returns <0, 0 or >0).
    //

ASUTILS_API as_binary_tree_t as_binary_tree_create( as_binary_tree_allocate_payload constructor,
              as_binary_tree_release_payload destructor, as_binary_tree_duplicate_key key_duplicator,
              as_binary_tree_release_key key_destructor, as_binary_tree_compare_keys comparator,
              void *constructor_param );

    // Returns the number of nodes automatically destroyed.
ASUTILS_API int as_binary_tree_destroy( as_binary_tree_t tree );

    // Find a node.  If allow_allocate is non-zero, will allocate a node
    // using the "constructor" callback if none is found.  Otherwise
    // returns NULL.
ASUTILS_API void *as_binary_tree_find_node( as_binary_tree_t tree, const void *key, int allow_allocate );
ASUTILS_API int   as_binary_tree_delete_node_by_key(  as_binary_tree_t tree, const void *key );


/////////////////////////////////////////////////////////
//                                                     //
//  Trees with string keys and string payloads.        //
//                                                     //
//  Basically the same as an STL map<string, string>.  //
//                                                     //
/////////////////////////////////////////////////////////

    // Create a tree that uses a string for a key and has static string payloads.
    // The payload pointer is kept (a copy of the payload string is not made), but
    // a copy of the key string IS made.  Use with as_binary_tree_set_node_string()
    // and as_binary_tree_get_node_string.
ASUTILS_API as_binary_tree_t as_binary_tree_create_string_key_char_ptr_payload( void );

    // Same as as_binary_tree_create_string_key_char_ptr_payload, only the key is
    // not duplicated (the caller is required to keep the pointer valid).  Also
    // used with as_binary_tree_set_node_string and as_binary_tree_get_node_string.
ASUTILS_API as_binary_tree_t as_binary_tree_create_static_string_key_char_ptr_payload( void );

    // These functions work with both types of string trees.
ASUTILS_API void as_binary_tree_set_node_string( as_binary_tree_t tree, const char *key, const char *value );
ASUTILS_API void as_binary_tree_set_node_string_once( as_binary_tree_t tree, const char *key, const char *value );
ASUTILS_API void as_binary_tree_set_node_pointer( as_binary_tree_t tree, const char *key, char *value );

ASUTILS_API const char *as_binary_tree_get_node_string( const as_binary_tree_t tree, const char *key );

ASUTILS_API ssize_t as_parse_variables_into_string( const char *src, char *dst, size_t dst_size, const as_binary_tree_t tree );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ASCONTAINERS_H
