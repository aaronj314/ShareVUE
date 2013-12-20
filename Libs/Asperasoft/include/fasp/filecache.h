/* A file cache to minimize seeks when writing to disk */

#ifndef FILECACHE_H
#define FILECACHE_H

#include <utils/src/asutils.h>
#include <fasp/rex.h>

#ifdef ISILON
/* FIXME: filecache calculatio must be fixed, then remove this special case */
#define IO_WRITE_SZ_DEF          (1 * 1024 * 1024)
#define IO_WRITE_MAX_CACHE_SZ    (1452 * 1024 * 256) // Must be multiple of IO_WRITE_SZ
#else
#define IO_WRITE_SZ_DEF             65536
#define IO_WRITE_MAX_CACHE_SZ    16777216   // Must be multiple of IO_WRITE_SZ
#define IO_WRITE_REX_TARGET           400
#endif
#define IO_WRITE_SZ_MAX         (IO_WRITE_MAX_CACHE_SZ / 2)

typedef struct {
    u_int64_t       target_rate;
    unsigned int    total_bl;
    unsigned int    rex_avg;
    unsigned int    rex_rto; 
    unsigned int    last_too_low;
} fc_tuning_t;

typedef struct {
    as_filehandle_t fh;             // handle of the file we are writing
    u_int64_t seekidx;
    u_int64_t fc_idx;               // position where the cache begins within file
    u_int64_t left_idx;             // left most (first) byte in the circular cache buffer
    u_int64_t write_idx;            // greatest (right most) byte index in the circular cache buffer
    u_int64_t hi_wmark;             // highwatermark - max no. bytes in cache before write through to disk
    unsigned int    file_iowritesz; // intended batch size for writes in bytes 
    unsigned int    wr_sz;          // current batch size for writes in bytes 
    unsigned int    fc_sz;          // cache size in bytes
    unsigned int    ah_sz;          // number of bytes to move the cache ahead
    u_int64_t file_sz;              // the file size in bytes
    unsigned int    bl_sz;          // block size in bytes
    char*           cache;          // pointer to an array of memory for storing cached blocks
    unsigned int    stats_too_far_behind;
    unsigned int    stats_too_far_ahead;
    unsigned int    stats_flush_time;
    fc_tuning_t     tuning;
    void           *xfer;
    void           *sess;
    rex_t          *rex;
} fc_t;

typedef struct {
    u_int64_t  op_write;
    u_int64_t  op_writethru;
    u_int64_t  op_flush;
    u_int64_t  op_moveahead;
    u_int64_t  op_tune;
    u_int64_t  op_freshen;
    u_int64_t  op_set_start;
    u_int64_t  op_buf_alloc;
    u_int64_t  op_buf_free;
    int64_t    buf_count;
    u_int64_t  op_write_too_far_behind;
    u_int64_t  op_write_too_far_ahead;
    u_int64_t  op_write_within_cache_bounds;

    u_int64_t  op_write_sz_fciowritesz;
    u_int64_t  op_write_sz_fileiowritesz;
    u_int64_t  op_write_sz_smaller;
    u_int64_t  op_write_sz_larger;

    u_int64_t  hi_wmark_count[10];
    u_int64_t  hi_wmark_count_too_low; 
    u_int64_t  hi_wmark_count_too_high;
#define FC_STAT_INCR(fc,counter) ((fc)->counter)++
#define FC_STAT_DECR(fc,counter) ((fc)->counter)--
#define FC_STAT(fc,counter)      ((fc)->counter)
} fc_instru_t;


void 
fc_config(
    unsigned int maxcache_sz,
    unsigned int maxwrite_sz);

fc_t * 
fc_create(
    u_int64_t file_sz, 
    unsigned int bl_sz, 
    u_int64_t target,
    void *sess,
    rex_t *rex,
    void *xfer);

void 
fc_freshen(
    fc_t *fc, 
    u_int64_t file_sz,
    u_int64_t target);

void 
fc_set_start(
    fc_t *fc, 
    u_int32_t start_block);

void 
fc_destroy(
    fc_t *fc);

int 
fc_write(
    fc_t *fc, 
    unsigned int idx, 
    char *databuf, 
    int len);

int 
fc_flush(
    fc_t *fc);

extern void
fc_show_stats(void);

#endif
