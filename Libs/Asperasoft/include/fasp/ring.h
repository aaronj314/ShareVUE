/*
 * ring.h
 *
 * Disk buffers and write routines.
 */

#ifndef __AS_RING_H__
#define __AS_RING_H__

#include <utils/src/asutils.h>
#include <fasp/fasp_dbuf.h>
#include <fasp/fasp_limits.h>
#include <istats/resrc_full.h>
#include <istats/latency_tab.h>

#define MAX_BUFFER_SIZE        FASP_RING_BUFFER_SIZE     // number blocks in one buffer
#define NUM_BLOCK_BUFFERS_MAX  FASP_RING_NUM_BUFFERS_MAX // maximum number of buffers

#define BUF_FULL        0x01
#define BUF_PROCESS     0x02
#define BUF_EMPTY       0x03

#define RING_ERROR_FATAL        -1
#define RING_ERROR_TEMPFULL     -2

#define USE_SMOOTHED_RING_OP    1 

/* Forward declarations */
struct transfer_t;
struct fasp_session_t;


typedef struct ring_instrum_t {
    struct timeval buf_co_tval[NUM_BLOCK_BUFFERS_MAX];
    struct timeval buf_ci_tval[NUM_BLOCK_BUFFERS_MAX];
    struct timeval buf_wrstart_tval[NUM_BLOCK_BUFFERS_MAX];
    struct timeval buf_wrdone_tval[NUM_BLOCK_BUFFERS_MAX];

    latency_tab_t  buf_co_to_ci;
    latency_tab_t  buf_ci_to_wrstart;
    latency_tab_t  buf_wrstart_to_wrdone;
    latency_tab_t  buf_ci_to_wrdone;
    latency_tab_t  xfer_left0_to_wrleft0;
    latency_tab_t  xfer_wrleft0_to_ackvec;

    u_int64_t      op_write_timespent;
    u_int64_t      op_writes;
    u_int64_t      num_blks_written;
} ring_instrum_t;

RESRC_FULL_STATS_DEFINE(ring_resrc_t, NUM_BLOCK_BUFFERS_MAX);


/* 
 * Buffer structure for queuing blocks to be written to disk.
 * Contains a small ring of data buffers. Each data buffer contains slots.
 * The application checks out an empty slot to store block data,
 * writes to it and then it checks it back in.
 * Checking in the last slot in a buffer automatically checks in the buffer
 * and it tries to check out a new buffer if it doesn't have to wait.
 * Each data buffer has a block number array associated with it.
 * The buffer checkin and checkout is synchronized with a mutex. Operations
 * inside a checked out buffer (slot check out and check in) are not 
 * synchronized.
 *
 * 'buf_co_ix2id_map' is a mapping of buffer_index to buffer_id at the 
 * moment of buffer checkout.  The buf_ix is the index into the
 * ring_buffer array.  The buf_id is a monotonically increasing unique 
 * identifier of a buffer.
 */
typedef struct ring_buffer_t {

    u_char          **bldata_buf; 
    u_int32_t       **blnum_buf;
    struct dbuf_hdr_t **buf_hdrs;
    u_char          buf_state[NUM_BLOCK_BUFFERS_MAX];
    u_int32_t       buf_slots_used[NUM_BLOCK_BUFFERS_MAX];
    u_int32_t       buf_co_ix2id_map[NUM_BLOCK_BUFFERS_MAX];

#define RING_BLOCK_HDR_BUFSIZE  (16)
    u_int64_t       blhdr_force_alignment_dummy;  /* FIXME: put hdr in ring */
    u_char          blhdr_buf[RING_BLOCK_HDR_BUFSIZE];

    int             num_block_buffers;  // num of ring block buffers 
    int             buf_hdr_off;
    int             buf_dat_off;

    int             block_size;         // the size of a FASP block
    int             header_size;        // the size of FASP header
    int             datagram_size;      // the size of a single datagram 
    int             trailer_size;       // the size of security trailer

    int             buffer_size;        // the size of a disk buffer

    int             buf_co;             // buffer currently checked out
    int             buf_co_id;          // Monotonically increasing id of buf_co
    int             buf_wr;             // buffer currently writing out
    int             buf_wr_id;          // id of buffer currently writing out
    volatile int    buf_wrote;          // buffer recently written out
    volatile int    buf_wrote_id;       // id of buffer recently written out
    int             buf_co_blocks;      // blocks checked into the buffer

    as_mutex_t      mutex;              // a mutex to guard the ring buffer  
    as_cond_t       data_ready_cond;    // cond variable to indicate data ready
    as_cond_t       space_ready_cond;   // cond variable indicate space ready

    int             count_full;         // number of full data buffers
    int             count_inuse;        // number of data buffers in use

    void           *dbflookup_ctx;      // ptr to dbf fast lookup ctx (in sess)

    int             shutdown;

    ring_resrc_t    ring_resrc;
    ring_instrum_t  instru;
    u_int8_t        cipher;

    /* Disk rate control related */
#define DEFAULT_RING_SLOTS_MIN_THRES    2.0
#define DEFAULT_RING_SLOTS_TARGET_OCCU  4.0
#define DEFAULT_RING_BUF_DELTA          0.5
    u_int8_t        ring_buf_rc;        /* disk rate control on/off */
    u_int8_t        ring_buf_rc_active; /* disk rate control currently active */
    u_int32_t       ring_buf_wr_tval;   /* average time to write a ring buf (ms) */
    u_int32_t       ring_buf_rc_updated;/* number of times ring buf rc has been performed */
    float           ring_slots_rc_min;  /* minimum ring buf occupancy, 0 - 36 */
    float           ring_buf_target_op; /* target ring buf occupancy, 0 - 36 */
    float           ring_ql;     
    float           ring_buf_delta;                                  
#if !USE_SMOOTHED_RING_OP
    float           ring_buf_occu;      /* average ring buffer occupancy */
#endif
    struct rate_info_t  *rateinfo;
    struct rtt_info_t   *rtt_info_ring;
} ring_buffer_t;


/*
 * Check out a ring buffer for storing block data.
 * Returns the index of the buffer to use. The call blocks to
 * wait for an available buffer if none available.
 */
extern int
ring_buf_co(
    ring_buffer_t *ring
);

/*
 * Check in a completed ring buffer.
 * Returns the index of an empty buffer to be used next or -1 if
 * no empty buffers are available.
 */
extern int
ring_buf_ci(
    ring_buffer_t *ring
);

/*
 * Unconditionally check in a ring buffer, so as to submit it to the
 * ring thread for writing.
 */
int
ring_force_buf_ci(
    ring_buffer_t *ring
);

/*
 * Check out a slot for one datagram. It takes care of checking out a new 
 * buffer if the old one was full.
 * If called multiple times without checkin, it returns the same slot.
 */
extern u_char *
ring_slot_co(
    ring_buffer_t *ring
);

extern int
ring_slot_dbuf_co(
    ring_buffer_t *ring,
    dbuf_t *dbuf
);

/*
 * Check in a slot for one datagram. It takes care of checking in the
 * buffer if full.
 */
extern int 
ring_slot_ci(
    ring_buffer_t *ring,
    u_int32_t bl
);

extern int
ring_slot_dbuf_ci(
    ring_buffer_t *ring,
    u_int32_t fasp_bl,
    u_int32_t bl,
    struct transfer_t *xfer,
    dbuf_t *dbuf
);

extern int
ring_write_buf(
    ring_buffer_t *ring,
    int buf_idx
);

extern int
ring_wrbuf_info(
    ring_buffer_t *ring,
    int *buf_wrote_ix,
    int *buf_wrote_id
);

extern int
ring_dump(
    ring_buffer_t *ring
);

extern u_int32_t 
ring_num_slots_used(
    ring_buffer_t *ring
);

#ifdef WIN32
extern DWORD WINAPI disk_thread(LPVOID arg);
#else
extern void * disk_thread(void *arg);
#endif

/*
 * Create ring buffer
 */ 
extern ring_buffer_t *
ring_create(
    struct fasp_session_t *sess
);

/*
 * Clean up and free ring buffer
 */
extern int
ring_destroy(
    ring_buffer_t *ring
);

extern void
rcvr_and_ring_show_latencies(
    ring_buffer_t *ring
);

#endif
