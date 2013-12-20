#ifndef _FASP_DBUF_H_
#define _FASP_DBUF_H_

#include <utils/src/asutils.h>

struct transfer_t;

/*
 * Data structure to hold the data block buffer io-vector and the associated
 * count.
 */
typedef struct dbuf_t {
    as_iovec_t vec[3];
    int vec_count;
} dbuf_t;

/*
 * Data structure maintained for each 'received' data-block-buffer that is
 * placed in the ring buffer to construct/maintain information about
 * contiguous data blocks (for a given xfer) within a ring buffer.
 */
typedef struct dbuf_hdr_t {
    struct transfer_t *xfer;
    u_int32_t   fblk_num;
    u_int16_t   contig;
    u_int16_t   spare;
} dbuf_hdr_t;


/*
 * Extern routine declarations.
 */
extern int
dbuf_read(
    const as_socket_t *sock,
    dbuf_t *dbuf,
    size_t *rsize);

extern int
dbuf_write(
    const as_socket_t *sock,
    dbuf_t *dbuf,
    size_t *wsize);

#endif /* _FASP_DBUF_H_ */

