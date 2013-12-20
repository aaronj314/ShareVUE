
#ifndef _FASP_DS_DBFMAP_H_
#define _FASP_DS_DBFMAP_H_

#include <ds/fasp_ds_types.h>

extern int
dbfmap_handle_valid(
    dbfmap_handle_t handle
);

extern void
dbfmap_init(
    void
);

extern unsigned int
dbfmap_size(
    void
);

extern unsigned int
dbfmap_count(
    void
);

extern unsigned int
dbfmap_space(
    void
);

extern void
dbfmap_fastlookup_ctx_init(
    dbfmap_fastlookup_ctx_t *lookup_ctx,
    char *modname
);

extern dbfmap_handle_t
dbfmap_add(
    int ds_id,
    void *ds,
    void *xfer,
    u_int64_t begin_blk,
    u_int64_t end_blk,
    as_filehandle_t file_fd
);

extern dbfmap_handle_t
dbfmap_search_dsid(
    int ds_id
);

extern int
dbfmap_lookup_dsid(
    dbfmap_handle_t handle
);

extern void *
dbfmap_search_xfer(
    int ds_id
);

extern void
dbfmap_set_block_range(
    dbfmap_handle_t handle,
    u_int64_t begin_blk,
    u_int64_t end_blk
);

extern int
dbfmap_lookup_block_range(
    dbfmap_handle_t handle,
    u_int64_t *begin_blk,
    u_int64_t *end_blk
);

extern as_filehandle_t
dbfmap_search_block2fd(
    u_int64_t block,
    dbfmap_handle_t *handle
);

extern as_filehandle_t
dbfmap_fastlookup_block2fd(
    dbfmap_fastlookup_ctx_t *lookup_ctx,
    u_int64_t block
);

extern void *
dbfmap_search_block2ds(
    u_int64_t block,
    dbfmap_handle_t *handle
);

extern void *
dbfmap_fastlookup_block2ds(
    dbfmap_fastlookup_ctx_t *lookup_ctx,
    u_int64_t block
);

extern void *
dbfmap_search_block2xfer(
    u_int64_t block,
    dbfmap_handle_t *handle
);

extern void *
dbfmap_fastlookup_block2xfer(
    dbfmap_fastlookup_ctx_t *lookup_ctx,
    u_int64_t block
);

extern void *
dbfmap_search_block2xfer(
    u_int64_t block,
    dbfmap_handle_t *handle
);

extern void
dbfmap_set_filefd(
    dbfmap_handle_t handle,
    as_filehandle_t file_fd
);

extern as_filehandle_t
dbfmap_lookup_filefd(
    dbfmap_handle_t handle
);

extern void *
dbfmap_lookup_ds(
    dbfmap_handle_t handle
);

extern void
dbfmap_remove(
    dbfmap_handle_t handle
);

extern void
dbfmap_foreach(
    void (* func)(void *data, void *arg1, void *arg2),
    void *arg1,
    void *arg2
);

extern int
dbfmap_ds_list(
    void **dsarray,
    unsigned int array_siz
);

extern void
dbfmap_iterator_reset(
    map_iterator_t *mapiter
);

extern map_dbf_entry_t *
dbfmap_iterate(
    map_iterator_t *mapiter
);

extern void
dbfmap_show_map(
    dbf_xfer_showfunc_t xfer_show_func
);

extern void
dbfmap_show_fastlookup_stats(
    dbfmap_fastlookup_ctx_t *lookup_ctx
);

#endif /* _FASP_DS_DBFMAP_H_ */

