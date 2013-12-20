#ifndef _AS_DIR_IMPL_H_
#define _AS_DIR_IMPL_H_

#include "asdir.h"

/* Implimentation details for asdir.c */

#ifdef __cplusplus
extern "C" {
#endif
    
struct as_dir_walk_handle_t {
    as_dir_t dir;
    char path[AS_MAX_PATH];
    struct as_dir_walk_handle_t *parent_handle;
};

struct as_dir_walk_t {
    struct as_dir_walk_handle_t *handle;
    int is_afile;
};

#ifdef __cplusplus
} /* extern "C" */
#endif 

#endif /* _AS_DIR_H_ */
