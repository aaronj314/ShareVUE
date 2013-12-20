/*
 * struct_api.h
 *
 * Aspera, Inc.
 *
 */

#ifndef _STRUCT_API_H_
#define _STRUCT_API_H_

#include <utils/src/asutils.h>
#include <fasp/security.h>
#include <fasp/filecache.h>
#include <fasp/mgmt_proto.h>
#include <fasp/fasp_limits.h>
#include <fasp/fasp_dbuf.h>
#include <fasp/fasp_data_read.h>
#include <meta/meta_api.h>
#include <istats/latency_tab.h>

/* Forward declarations */
struct fasp_session_t;

#define BLOCKS_TABLE_SIZE    (4 * MAX_RETRANSMISSION_BUFFER)

/* statistical data */
typedef struct {

    struct timeval      start_time;         // when started timing the transfer
    struct timeval      stop_time;          // when stopped timing the transfer

    /* Common sender and receiver stats */
    u_int32_t           bl_first;           // num of first block sent
    u_int32_t           bl_total;           // total number of blocks sent
    u_int32_t           bl_orig;            // num of original blocks sent
    u_int32_t           bl_rex;             // num of retransmitted blocks
    u_int32_t           bl_last;            // num of "last block" sent
    u_int32_t           bl_highest;         // highest block received so far

    /* Receiver stats */
    u_int64_t           bytes_received;     // num bytes received this period
    u_int32_t           blocks_ooo;         // num blocks received out of order
    u_int32_t           blocks_badid;       // num blocks with bad transfer ID
    u_int32_t           rex_rem_failed;     // num of rex_remove failures
    u_int32_t           rex_add_failed;     // num of rex_add failures
    u_int32_t           rex_blocks_sent;    // num of block rex requested
    u_int32_t           rex_reqs_sent;      // num of rex requests sent
    u_int32_t           lost_blocks;        // num of non-rex blocks lost
    u_int32_t           dup_blocks;         // num of duplicates received
    u_int32_t           dup_last_block;     // num of last blocks received
    u_int32_t           drop_rexfull;       // blocks dropped when rex full

    u_int32_t           udp_stop_reqs_sent; // num of udp stop msgs sent @ EOF

    /* Sender stats */
    u_int32_t           rex_blocks_rcvd;    // num of block rex requests
    u_int32_t           rex_blocks_dup;     // num of block rex already in rbt
    u_int32_t           rex_reqs_rcvd;      // num of rex request messages

} statistics_t;

/* state of the retransmission table for a transfer */
typedef struct {
    u_int32_t          *table;          // table of retransmission blocks 
    u_int32_t           table_size;     // size of the retransmission table  
    u_int32_t           index_max;      // maximum table index in active use 
} retransmit_t;

typedef struct transfer_instrum_t {
    struct timeval      blocks_left_0;  // time when blocks_left == 0
    struct timeval      blocks_wrleft_0;// time when blocks_wrleft == 0
    struct timeval      add_ackvec;     // time when xfer was added to ackvec

    u_int32_t           num_filereads;  // num (blocking) read ops for this xfer
    u_int64_t           aio_rdorig_ok;  // Count aio rd orig ok, ok*blksiz=off

    struct timeval      tm_xfer_xmit_lblk; // time when xfer xmitted last blk
    struct timeval      tm_xfer_xmit_done; // time when xfer xmit was done/acked

} transfer_instrum_t;

typedef struct ci_rbuf_info_t {
    int                buf_id;
    u_int32_t          c8b_val;
} ci_rbuf_info_t;


typedef struct transfer_t {

    struct fasp_session_t *sess;

    // data transfer state
    //
    u_int32_t           state;       // state of the data tranfser
    u_int32_t           errcode;     // error code in case of failure
    int                 errnoval;    // errno val (currently used for NOX disp)
    char               *errnostr;    // errno str (currently used for NOX disp)

    unsigned char  xfer_abort_extnl;     // flag external abort of xfer
    unsigned char  xfer_abort_ring_done; // ring gracefully aborted this xfer
    unsigned char  xfer_abort_intnl;     // flag internal abort of xfer 

    // system resources
    //
    char                *filename;          // the path to the file
    as_filehandle_t     fileh;

    as_thread_t         data_tid;       // tid of the data processing thread
    as_file_t           aspx_file;      // aspx file
    as_filehandle_t     aspx_fh;        // aspx file descriptor

    // Progress meter context
    struct transfer_t  *progmtr_next; 
    struct transfer_t  *progmtr_prev; 
    int                 progmtr_magic;  // progress meter debug instrumentation 
    int                 progmtr_started;// fasp_callback(FASP_FILE_START) done

    // transfer parameters
    //
    u_int64_t           file_size;    // the total file size (in bytes)
    u_int32_t           block_count;  // the total number of blocks in the file

    u_int32_t           block;        // current block that we're up to  
    u_int32_t           start_block;  // start block for resumed xfers
    u_int32_t           stop_flag;    // indicate client has requested stop
    struct timeval      start_req_time; // when start request goes out

    // file-encryption details.
    int                 file_encrypted; // actually en/de-crypting this file
    u_int64_t           true_size;      // unencrypted size (in bytes)
    encryption_block_t  nonce_basis;    // hash of file path
    encryption_block_t  file_key;
    AES_KEY            *file_key_schedule;

    // transfer state
    //
    u_int32_t           next_block;     // index of the next block we expect   
    statistics_t        stats;          // statistical data for the transfer 
    u_char             *received;       // bitfield for received blocks 
    u_int32_t           cont8block_ci;  // num of continuous 8 block units @ci
    ci_rbuf_info_t      cont8block_ci_info[FASP_RING_NUM_BUFFERS_MAX];
                                        // cont8block info upon ci into ring buf
    u_int32_t           cont8block;     // num of continuous 8 block units
    u_int32_t           blocks_left;    // number of blocks left to receive
    volatile u_int32_t  blocks_wrleft;  // # blks yet to be written to store
    volatile u_int32_t  blocks_aborted; // # blks left when abort req arrived
    int                 event_rab;      // Receiver has received all blocks 
    int                 event_wab;      // Receiver has written all blocks 
    u_int32_t           count;          // number of consecutive transfers 
    u_int32_t           id;             // id of current transfer
  
    u_int64_t           start_counter;
    u_int64_t           progress_counter;// Cont bytes ACKed to sender
    u_int64_t           last_progress;  // time the progress

    u_int32_t           ds_id;          // data sess id of current transfer
    void               *ds;             // parent data session
    meta_data_t        *sink_md_ref;    // reference to meta info
    int                 dbf_handle;     // DBF map handle
    u_int64_t           fasp_start_block;// Session level mapping of start block
    u_int64_t           fasp_stop_block;// Session level mapping of stop block
    int                 event_xlb;      //Have posted xmit_last_block event

    // receiver stats
    int             stats_after_zerobl; // num stat reqs sent to sender
                                        // by recvr after xfer->blocks_left = 0
    //
    // 'padding' contains the amount added to each message 
    // (of size 'block_size') s.t. it consist of an 
    // integral number of cipher blocks
    //
    fc_t                *file_cache;

    dbuf_hdr_t         *head_dbhdr;
    u_int32_t           head_dbhdr_bufid;

    multaio_read_ctx_t  *multaio;

    transfer_instrum_t  instru;  // instrumentation

    u_int32_t           xfer_flags;
#define XFER_FLAG_FILE_DELETED               0x1            /* file deleted */

#ifdef SUM_ALL_BLOCKS
    MD5_CTX            running_md5sum;
    u_int8_t           *block_sums;  
#endif

} transfer_t;

#endif



