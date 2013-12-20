#ifndef _FASP_DATA_READ_H_
#define _FASP_DATA_READ_H_

#ifndef WIN32
#include <errno.h>
#endif
#include <fasp/fasp_dbuf.h>

#include <utils/src/asutils.h>

struct fasp_session_t;
struct transfer_t;
struct fasp_datasess_t;

#define FASP_TRANSMITTER_READ_CONTIG_BYTES   (524288)
#define FASP_TRANSMITTER_READ_CONTIG_BLOCKS  (364)
#define MAX_READYQ_READAHEAD_BLOCKS  (2 * FASP_TRANSMITTER_READ_CONTIG_BLOCKS)

#define IO_PAGE_SIZ       4096
#define NUM_PAGES_NO_AIO    16

typedef struct fasp_data_read_cfg {
    u_int32_t max_batch_siz;
    u_int32_t max_rdbuf_len;
} fasp_data_read_cfg_t;


typedef struct aio_read_ctx {
    /*
     * AIO control block.
     */
    as_aio_t aiocb;

    /*
     * Flags.
     */
    int issued;
    int pending;
    int failed;
    int ready;
    int errnum;
    int have_lastblock;

    /*
     * Dynamically allocated read buffer for aio reads.
     */
    unsigned char *async_buf;
    u_int32_t async_buflen;

    /*
     * Block info pertaining to this context.
     */
    u_int32_t first_block_num;  /* [Configured] First block num in this ctx */
    u_int32_t last_block_num;   /* [Configured] Last block num in this ctx */
    u_int32_t block_count;      /* [Configured] Num blocks read in 1 aio oper */

    /*
     * Instrumentation.
     */
    struct timeval issued_tval;
    struct timeval done_tval;
    u_int32_t pending_count;
    u_int32_t read_buf_count;
} aio_read_ctx_t;


typedef struct multaio_read_ctx {
    /*
     * Flags.
     */
    int valid;
#define MAIO_CTX_VALID 0x6172756e
    int cfg_read_siz;

    /*
     * Flag for blocking mode only.
     */
    int blocking_only;

    /*
     * Multiple AIO contexts to reduce IO latency.
     */
    aio_read_ctx_t *curr;
    aio_read_ctx_t *next;
    aio_read_ctx_t *nextnext;

    /*
     * Buffer info pertaining to each read context.
     */
    u_int32_t  async_bufsiz;

    /*
     * Block info pertaining to the "FILE".
     */
    u_int32_t  block_size;        /* [Configured] block size */
    u_int32_t  blocks_rdcontig;   /* [Configured] max blocks to read per aio */

    u_int32_t  blocks_rdoff;      /* [Computed] block offset within file */
    u_int32_t  blocks_rdleft;     /* [Computed] blocks left to be read */
    u_int32_t  blocks_rdinprog;   /* [Computed] Num blocks read in progress */

    /*
     * File descriptor/handle.
     */
    as_filehandle_t fh;

    /* 
     * Dynamically allocated buf for blocking reads
     */
    unsigned char *blocking_buf;     

    /*
     * Instrumentation.
     */
    u_int32_t op_reads_issued;
    u_int32_t op_reads_done;

} multaio_read_ctx_t;


/*
 * API routine declarations.
 */
extern void
fasp_data_read_config(
    struct fasp_session_t *sess
);

extern int
multaio_xfer_read_ctx_init(
    struct fasp_session_t *sess,
    struct transfer_t *xfer
);

extern int
multaio_ds_read_ctx_init(
    struct fasp_session_t *sess,
    struct fasp_datasess_t *ds
);

extern void
multaio_read_ctx_destroy(
    multaio_read_ctx_t *mctx
);

extern int
multaio_read_issue_all(
    multaio_read_ctx_t *multaio,
    u_int32_t batch_siz
);

extern void
multaio_read_cancel_all(
    multaio_read_ctx_t *multaio
);

extern int
multaio_readahead(
    struct fasp_session_t *sess,
    multaio_read_ctx_t *multaio,
    u_int32_t batch_siz,
    int32_t *err
);

extern int
multaio_readv(
    struct fasp_session_t *sess,
    struct transfer_t *xfer,
    u_int32_t xfer_block_num,
    multaio_read_ctx_t *multaio,
    dbuf_t *dbuf,
    u_int32_t batch_siz,
    int *call_readahead,
    int *err
);

/*
 * Internal routine declarations.
 */
extern void
aio_read_ctx_clear(
    aio_read_ctx_t *ctx
);

extern int
multaio_read_issue(
    multaio_read_ctx_t *multctx,
    aio_read_ctx_t *ctx,
    u_int32_t batch_siz,
    int32_t *err
);

extern int
multaio_blocking_readv(
    struct fasp_session_t *sess,
    struct transfer_t *xfer,
    u_int32_t xfer_block_num,
    multaio_read_ctx_t *multaio,
    dbuf_t *dbuf,
    int *err
);

#endif /* _FASP_DATA_READ_H_ */

