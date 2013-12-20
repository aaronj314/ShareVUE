#ifndef _META_API_H_
#define _META_API_H_

#include <fasp/fasp_limits.h>
#include <fasp/fasp_policy.h>
#include <meta/aspx.h>
#include <utils/src/asfile.h>
#include <frameworks/c/faspcrypto/faspcrypto.h>

struct fasp_session_t;
struct transfer_t;

typedef struct meta_aspx_t {
    u_int8_t    ver;                // aspx format version 
    u_int8_t    unused1;            // alignment
    u_int16_t   crypto_blob_size;   // number of bytes following
    u_int32_t   unused3;            // alignment
    u_int64_t   filesize;           // reported file size 
    u_int64_t   contbytes;          // number of contiguous bytes written
    u_int32_t   lmtime;             // last modified time
    u_int16_t   csum_type;          // MD5 or something else
    u_int16_t   csum_level;         // full/sparse etc.
    char        csum[CSUM_SZ];      // checksum as hex text (NO NULL TERM.)
} meta_aspx_t;

typedef struct block_info {
    u_int32_t blk_size;
    u_int64_t blk_count;
    u_int64_t blks_rcvd;
    u_int64_t blks_left;
    u_int64_t blk_start;
    u_int64_t blk_stop;
} block_info_t;

typedef struct meta_attr_t {
    u_int64_t   file_size;       /* reported file size in bytes */
    u_int64_t   lmtime;          /* last modified time */
    u_int16_t   crypto_blob_size;
    u_int8_t    csum_type;       /* type of checksum */
    u_int8_t    csum_level;      /* level of checksum {full, sparse} */
    u_int8_t    ver_on_disk;
    char        csum[CSUM_SZ];   /* checksum in hex text (NO NULL TERM.) */
} meta_attr_t;

typedef struct meta_data_t {
    meta_attr_t     *src;
    block_info_t     bi;
    meta_aspx_t      rd_aspx;
    meta_aspx_t      wr_aspx;
    u_int8_t         resume_policy;
    as_filehandle_t  sink_fd;
    char            *sink_fname;
    u_int64_t        sink_fsize;
    int              writing_encrypted;
    u_int8_t        *crypto_blob;
    // u_int64_t        sink_contbytes;
    as_filehandle_t  aspx_fd;
    char             aspx_fname[FASP_FILENAME_MAXLEN+1];
    u_int32_t        aspx_fmode;
    int              move_range;
    u_int64_t        move_range_low;
    u_int64_t        move_range_high;
} meta_data_t;

enum meta_cmp_result {
    META_CMP_RES_XFER_WHOLE_FILE = 0,
    META_CMP_RES_XFER_PART_FILE = 1,
    META_CMP_RES_XFER_NOT_NEEDED = 2,
    META_CMP_RES_FILE_ERROR = 3,
};



/*
 * Extern declarations for routines.
 */
extern int
meta_calc_file_csum(
    char *file_name,
    as_filehandle_t file_handle,
    u_int64_t file_size,
    void *vsess,
    char *csum,                  /* output arg (NO NULL TERMINATION) */
    int *errnoval
);

/*
 * Compare two checksums.
 *
 * Return 0 if equal, -1/1 if different.
 */
extern int
meta_csum_compare(
    char *csum1,
    char *csum2
);

extern void
meta_set_params(
    meta_data_t *md,
    u_int8_t  resume_policy,
    u_int32_t block_size
);

extern void
meta_set_src_mdata(
    meta_data_t *md,
    meta_attr_t *src_mattrs
);

extern int
meta_set_sink_mdata(
    meta_data_t *md,
    char *sink_fname,
    as_filehandle_t sink_fd,
    as_filehandle_t aspx_fd,
    u_int32_t sink_fmode,
    int writing_encrypted,
    u_int8_t *crypto_blob,
    int move_range,
    u_int64_t move_range_low,
    u_int64_t move_range_high
);

extern enum meta_cmp_result
meta_cmp_srcsink_mdata(
    meta_data_t *md,
    u_int32_t usefilecache,
    int* errnoval
);

extern void
meta_init_xfer(
    struct transfer_t *xfer,
    meta_data_t *md
);

extern int
meta_update_aspx(
    struct transfer_t *xfer
);

extern void
meta_close_aspx(
    meta_data_t *md
);

extern void
meta_rm_aspx(
    meta_data_t *md
);

#endif /* _META_API_H_ */

