
#ifndef __FASP_DS_TYPES_H__
#define __FASP_DS_TYPES_H__

#include <utils/src/asutils.h>
#include <fasp/fasp_limits.h>
#include <ds/fasp_ds_queue.h>
#include <ds/fasp_ds_api.h>
#include <meta/meta_api.h>
#include <fasp/fasp_data_read.h>
#include <fasp/security.h>
#include <frameworks/c/faspcrypto/faspcrypto.h>

#include <sys/types.h>
#include <stdio.h>

#define INLINE_XMITTER_EVENTS        1 // xmiter calls libfaspds directly
#define INLINE_XMITTER_EVENTS_NEXTDS 1 // same as above, plus retval is next_ds 

#ifdef INSTRUMENT_SINK
#define INSTRU_SINK_LATENCIES        1
#else
#define INSTRU_SINK_LATENCIES        0
#endif


#define PROTOCOL_DATASESS_PDU_BASE         0x10
#define PROTOCOL_DATASESS_REQ             (PROTOCOL_DATASESS_PDU_BASE + 0)
#define PROTOCOL_DATASESS_RSP             (PROTOCOL_DATASESS_PDU_BASE + 1)
#define PROTOCOL_DATASESS_DSERR_NOTFN     (PROTOCOL_DATASESS_PDU_BASE + 2)
#define PROTOCOL_DATASESS_SESSERR_NOTFN   (PROTOCOL_DATASESS_PDU_BASE + 3)
#define PROTOCOL_DATASESS_PDU_LAST        (PROTOCOL_DATASESS_SESSERR_NOTFN)

#define LATENCY_USEC_PER_TICK        10   /* 10 MICRO seconds per tick */
#define LATENCY_TICKS_PER_MSEC       100  /* 100 ticks per MILLI second */

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef WIN32
#define DSCONN_READ(fd, buf, len)  recv(fd, (buf), (len), 0)
#define DSCONN_WRITE(fd, buf, len) send(fd, (buf), (len), 0)
#else
#define DSCONN_READ(fd, buf, len)   read(fd, (buf), (len))
#define DSCONN_WRITE(fd, buf, len) write(fd, (buf), (len))
#endif
/*
 * Source queue constants.
 */
enum source_que_id_e {
    SOURCE_RETRY_Q = 0,
    SOURCE_ARG_Q,     
    SOURCE_DIR_Q,
    SOURCE_NEW_Q,
    SOURCE_ATTRPREP_Q,
    SOURCE_DSREQ_SENT_Q,
    /* SOURCE_DSRSP_RECD_Q,        Future - if want to read resp & search ds */
    /* SOURCE_CSUM_PREP_Q,         Future */
    /* SOURCE_CSUM_REQ_SENT_Q,     Future */
    /* SOURCE_CSUM_RSP_RECD_Q,     Future */
    SOURCE_READY_Q,
    SOURCE_RUNNING_Q,
    SOURCE_NOX_DISP_Q,
    SOURCE_DONE_Q,
};

#define SOURCE_RUNWAIT_Q_MAXSIZE     (2)
#define NUM_SOURCE_QUEUES            (SOURCE_DONE_Q + 1) 

#define SOURCE_NEW_Q_MAXSIZE         (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SOURCE_ATTRPREP_Q_MAXSIZE    (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SOURCE_DSREQ_SENT_Q_MAXSIZE  (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SOURCE_READY_Q_MAXSIZE       (0) // (2 * FASP_DATASESS_PIPELINE_DEPTH)
#define SOURCE_RUNNING_Q_MAXSIZE     (FASP_DATASESS_PIPELINE_DEPTH)


/*
 * Sink queue constants.
 */
enum sink_que_id_e {
    SINK_NEW_Q = 0,
    SINK_DSREQ_RECD_Q,           // TODO remove
    SINK_ATTRPREP_Q,
    /* SINK_CSUM_REQ_RECD_Q,     Future */
    SINK_READY_Q,
    SINK_RUNNING_Q,
    SINK_NOX_DISP_Q,
    SINK_DONE_Q,
};

#define NUM_SINK_QUEUES (SINK_DONE_Q + 1) 

#define SINK_NEW_Q_MAXSIZE         (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SINK_ATTRPREP_Q_MAXSIZE    (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SINK_DSREQ_RECD_Q_MAXSIZE  (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SINK_READY_Q_MAXSIZE       (4 * FASP_DATASESS_PIPELINE_DEPTH)
#define SINK_RUNNING_Q_MAXSIZE     (FASP_DATASESS_PIPELINE_DEPTH)


/*
 * DBF map.
 */
#define DBF_MAP_SIZE               (FASP_DATASESS_PIPELINE_DEPTH)

typedef struct _map_dbf_entry {
    /*
     * Bind data_session <-> block_range <-> file_fd
     */
    int             this_handle;
    int             ds_id;
    void           *ds;
    void           *xfer;
    as_filehandle_t file_fd;
    u_int64_t       fasp_start_block;
    u_int64_t       fasp_stop_block;
} map_dbf_entry_t;

typedef int dbfmap_handle_t;

typedef struct _map_ds_blkrange_fd {
    unsigned int map_size;
    unsigned int elem_count;
    map_dbf_entry_t map[DBF_MAP_SIZE];
} map_dbf_t;

typedef struct _map_iterator {
    int magic;
#define ITER_ALIVE 0x12345678
#define ITER_END   0x1eeeeeee
    map_dbf_t *p_dbfmap;    /* For future, if we need multiple map instances */
    unsigned int iter_index;
    unsigned int num_iterated;
} map_iterator_t;

typedef struct _map_fast_ctx {
    int hot_handle;
    int hh_hits;
    int hh_misses;
#define DBFMAP_FASTCTX_MODNAME_LEN 12
    char modname[DBFMAP_FASTCTX_MODNAME_LEN];
} dbfmap_fastlookup_ctx_t;

typedef void (* dbf_xfer_showfunc_t)(void *); /*Show func for each xfer in DBF*/


/*
 * Select constants.
 */
#define FASP_DATASESS_SEL_TMOUT_SEC        00  /* 00 secs */
#define FASP_DATASESS_SEL_TMOUT_USEC    10000  /* 10 millisecs */
#define FASP_DATASESS_PURGE_TMOUT_ITERS  1000  /* 1000 * 10 msecs = 10 sec */


/*
 * Data session roles.
 */
enum fasp_xfer_role_e {
    ROLE_SENDER,
    ROLE_RECEIVER
};

/*
 * Note: The on-disk format for .aspx file is described by the meta_aspx_t 
 * struct.
 */

/*
 * The following are encoded onto the wire to describe
 * the data transfer.
 */
typedef struct _fasp_data_attr {
    u_int8_t    ver;             /* .aspx file (meta-data) format version */
    u_int8_t    type;            /* object type */

    /* These object types should correspond to
     * the FASP_DS_FLAG_TYPE in fasp_datasess_t.
     */
    
    u_int16_t   unused2;         /* alignment */
    u_int32_t   unused3;         /* alignment */

    u_int64_t   attr_map;        /* bit mask of valid attrs in fasp_data_attr [NOT USED]*/

#define FASP_DATA_ATTR_FILESIZE (0x0000000000000001LL)
    u_int64_t   file_size;       /* reported file size in bytes */

#define FASP_DATA_ATTR_DISKSIZE (0x0000000000000002LL)
    u_int64_t   disk_size;       /* file size on disk - [REMOVE?] */

#define FASP_DATA_ATTR_LMTIME   (0x0000000000000004LL)
    u_int64_t   lmtime;          /* last modified time */

#define FASP_DATA_ATTR_FILEMODE (0x0000000000000008LL)
    u_int32_t   file_mode;       /* mode & permissions on file - [NEW] */
    u_int32_t   unused4;         /* alignment - [OPTIMIZE?] */

#define FASP_DATA_ATTR_CSUM     (0x0000000000000010LL)
    u_int8_t    csum_type;       /* type of checksum */
    u_int8_t    csum_level;      /* level of checksum {full, sparse} */
    u_int16_t   unused5;         /* alignment - [OPTIMIZE?] */
    u_int32_t   unused6;         /* alignment - [OPTIMIZE? or REMOVE?] */
    char        csum[CSUM_SZ];   /* checksum in hex text */

#define FASP_DATA_ATTR_SYMLINK  (0x0000000000000020LL)
    u_int32_t   symbolic_link_len;
    char        symbolic_link [FASP_FILENAME_MAXLEN + 1];
    
#define FASP_DATA_ATTR_CRYPTO   (0x0000000000000040LL)
    fasp_meta_crypto_t crypto; 
    /* blob in form suitable to append to a file, with size+type+magic: */
    u_int16_t   file_encrypted;  
    unsigned    num_locked_keys;
    unsigned    locked_key_offsets[
                    (file_crypto_max_blob_size - file_crypto_blobsize) /
                         file_crypto_blobsize_alt];
    u_int16_t   crypto_blob_size;
    u_int8_t    crypto_blob[file_crypto_max_blob_size];

} fasp_data_attr_t;


/*
 * The following is the variable length fields.
 */
typedef struct fasp_ds_vlf_comp_t {
    u_int16_t tag;
    u_int16_t len;
    char *sample_vlf;
    u_int64_t sinkQ_latency_usec;      /* Time spent sitting in sink ds Qs */
    u_int64_t sink_cmp_latency_usec;   /* Time spent in sink_compare() */
    
} fasp_ds_vlf_comp_t;

typedef struct _ds_pdu_header {
    unsigned char  type;
    unsigned char  unused;
    unsigned short length;
} ds_pdu_hdr_t;
#define DS_PDU_HDR_LEN  4


/*
 * Data Session Request PDU format.
 */

typedef struct fasp_datasess_req_pdu_t {
    ds_pdu_hdr_t     hdr;

    u_int32_t        ds_id;
    u_int32_t        file_id;

    u_int32_t        unused;

    fasp_data_attr_t attrs;

    u_int16_t        filename_len;
    char             filename[FASP_FILENAME_MAXLEN + 1];
    fasp_ds_vlf_comp_t vlfcomp;   

} fasp_datasess_req_pdu_t;


/*
 * Data Session Response PDU format.
 */
typedef struct fasp_datasess_rsp_pdu_t {
    ds_pdu_hdr_t hdr;

    u_int32_t ds_id;
    u_int32_t file_id;
    
    u_int32_t result;

    u_int32_t file_errno;
    u_int16_t file_errnostrlen;
    char      file_errnostr[FASP_ERRSTR_MAXLEN + 1];
    u_int32_t req2rsp_latency_ticks;/* 1 tick = 10 microseconds
                                     * latency @sink = req in->out time
                                     * this is equivalent to 
                                     * (1) time spent in sink-queues & enc/dec+ 
                                     * (2) time spent comparing meta data */

    u_int64_t datasess_start_block; /* Start block (data session context) */
    u_int64_t datasess_stop_block;  /* Stop  block (data session context) */
    u_int64_t faspsess_start_block; /* Start block (parent fasp session ctx) */
    u_int64_t faspsess_stop_block;  /* Stop  block (parent fasp session ctx) */

    fasp_data_attr_t attrs;
    
    fasp_ds_vlf_comp_t vlfcomp;

} fasp_datasess_rsp_pdu_t;


typedef struct fasp_ds_sesserr_pdu_t {
    ds_pdu_hdr_t hdr;
    int32_t      reason;

    u_int32_t    errstrlen;
    char         errstr[FASP_ERRSTR_MAXLEN + 1];

} fasp_ds_sesserr_pdu_t;


typedef struct fasp_ds_dserr_pdu_t {
    ds_pdu_hdr_t           hdr;
    u_int32_t              ds_id;
    u_int32_t              file_id;
    enum fasp_xfer_role_e  issuer_role;
    int32_t                errcode;
    int32_t                errnum;

    size_t                 errstrlen;
    char                   errstr[FASP_ERRSTR_MAXLEN + 1];

    size_t                 errpathlen;
    char                   errpath[FASP_ERRPATH_MAXLEN + 1];

} fasp_ds_dserr_pdu_t;

#define FASP_DATASESS_MAX_VLFSIZ 8192

#define FASP_DATASESS_MAX_PDU_SIZE \
    (max(sizeof(fasp_datasess_req_pdu_t), \
        max(sizeof(fasp_datasess_rsp_pdu_t),\
            max(sizeof(fasp_ds_sesserr_pdu_t),sizeof(fasp_ds_dserr_pdu_t)))) \
    + FASP_DATASESS_MAX_VLFSIZ)


struct pdu_scratchbuf {
    char          buf[FASP_DATASESS_MAX_PDU_SIZE + 128]; 
    /* although not required, allocate extra space for cross-platform 
     * sizeof differences, if any */
    unsigned int  siz;                /* size of buf */
    unsigned int  offset;             /* offset within buf */
    unsigned int  len;                /* length of buf used */

    int           hdr_decoded;        /* boolean flag */
    unsigned char version;            /* decoded version */
    unsigned char type;               /* decoded type */
    short         len_payload;        /* decoded len (of payload) */
    unsigned int  len_hdr;            /* length of header */
};



/*
 * Data Session Information.
 */
typedef struct fasp_datasess_receiver {
    fasp_datasess_req_pdu_t req_recd;
    fasp_datasess_rsp_pdu_t rsp_sent;

    as_file_t       sink_file;
    as_file_t       aspx_file;
    as_filehandle_t sink_fd;
    as_filehandle_t aspx_fd;

    u_int32_t  result;   /* ERROR, NO_XFER or NEED_XFER */
#define FASP_DATASESS_RESP_UNKNOWN             0
#define FASP_DATASESS_RESP_ERROR_OTHER         1
#define FASP_DATASESS_RESP_ERROR_EACCES        2
#define FASP_DATASESS_RESP_ERROR_EEXIST        3
#define FASP_DATASESS_RESP_ERROR_ASPX          4
#define FASP_DATASESS_RESP_NO_XFER             5
#define FASP_DATASESS_RESP_NEED_XFER           6
#define FASP_DATASESS_RESP_ERROR_FILEPASS      7

#define FASP_DATASESS_RESP_END                 8

    u_int64_t  start_byte;

    u_int64_t  datasess_start_block;
    u_int64_t  datasess_stop_block;
    u_int64_t  faspsess_start_block;
    u_int64_t  faspsess_stop_block;

    short      need_no_op;
    int        file_errno;
    int        file_error;

    struct timeval    tstamp_req_rcvd;
    struct timeval    tstamp_cmp_start;
    struct timeval    tstamp_cmp_stop;
    struct timeval    tstamp_rsp_sent;

} fasp_datasess_receiver_t;


typedef struct fasp_datasess_sender {
    fasp_datasess_req_pdu_t req_sent;
    fasp_datasess_rsp_pdu_t rsp_recd;

    as_file_t       source_file;
    as_filehandle_t source_fd;
    off_t           destname_offset;  /* offset indicating the starting point
                                         of the src filename that is sent
                                         to the sink. */
    u_int64_t  datasess_start_block;
    u_int64_t  datasess_stop_block;
    u_int64_t  faspsess_start_block;
    u_int64_t  faspsess_stop_block;

    u_int64_t  acked_blk_id;   /* ACK with block id of contiguous blocks */
    u_int64_t  next_blk_id;    /* Next block to send */ 

    struct timeval    tstamp_req_sent;
    struct timeval    tstamp_rsp_rcvd;

    u_int32_t         req2rsp_latency_ticks; 
                               /* req2rsp latency @ source 
                                *     = time req sent - time rsp rcvd,
                                *     = net latency (tcp) + sink req2rsp latency
                                */
    int32_t           src_dsconn_latency_ticks; 
                               /* latency due to network, as seen @ source
                                *   = src req2rsp latncy - sink req2rsp latncy
                                */
} fasp_datasess_sender_t;


typedef struct fasp_source_age_t {
    /*
     * Instrumentation: 
     * Used for tracking life of a data-session for debugging purposes.
     * For now, time_t will suffice (no need for struct timeval).
     */
    time_t since_alloc;
    time_t since_attrprep;
    time_t since_dsreq_sent;
    time_t since_ready;
    time_t since_running;
    time_t since_lastblock;
    time_t since_stopped;
    time_t since_done;
} fasp_source_age_t;

typedef struct fasp_sink_age_t {
    /*
     * Instrumentation: 
     * Used for tracking life of a data-session for debugging purposes.
     * For now, time_t will suffice (no need for struct timeval).
     */
    time_t since_alloc;
    time_t since_attrprep;
    time_t since_dsreq_rcvd;
    time_t since_ready;
    time_t since_running;
    time_t since_stopped;
    time_t since_done;
} fasp_sink_age_t;


/*
 * The fasp_datasess_t structure represents a file in the context of a file
 * transfer session.  It should be named better.
 */

typedef struct fasp_datasess_t {
    struct _queue_elem  elem;

    int magic;
#define DS_GOOD 0x6172756e
#define DS_BAD  0xbaddbadd

    char file_name[FASP_FILENAME_MAXLEN + 1]; /* XXX filename (large)
                                                 stored multiple times.
                                                 Notice fasp_datasess_sender_t
                                                 has another copy (inside
                                                 fasp_datasess_req_pdu_t).
                                              */

    union {
        fasp_datasess_receiver_t receiver;
        fasp_datasess_sender_t   sender;
    } U;
    enum fasp_xfer_role_e xfer_role;

    void            *faspsess;
    void            *xfer;
    u_int32_t        ds_id;
    u_int32_t        ds_flags;  /* This field was initially unused. 
                                 * Bob has defined a number of FLAGS.
                                 */

    /* 1 byte for type. Must be one byte. See fasp_data_attr.
     * this object type gets copied into the byte in fasp_data_attr.
     * See fasp_data_attr before modifying these.
     */
#define FASP_DS_FLAG_TYPE_MASK          0xff
#define FASP_DS_OBJECT_FILE             0x1
#define FASP_DS_OBJECT_DIRECTORY        0x2
#define FASP_DS_OBJECT_SYMBOLIC_LINK    0x4
#define FASP_DS_OBJECT_SPECIAL          0x8

    /* upper 16 bit for various other things */
#define FASP_DS_FLAG_STAT_CACHED        0x1000

    u_int32_t        file_id;
    int              file_fd;
    dbfmap_handle_t  dbfmap_handle;
    as_stat_t        astb;

    int              file_encrypted;
    int              encrypting_file;
    int              decrypting_file;
    encryption_block_t nonce_basis;
    encryption_block_t file_key;
    AES_KEY          file_key_schedule;

    /*
     * Error tracking.
     */
    u_int32_t        xfer_state;
    u_int32_t        xfer_errcode;

    /*
     * No transfer (NOX) state.
     */
    int              nox_errnoval;
    char             nox_errnostr[FASP_ERRSTR_MAXLEN];
    u_int64_t        nox_progcntr;

    /*
     * Instrumentation.
     */
    fasp_source_age_t src_age;
    fasp_sink_age_t   sink_age;
    time_t            ds_age;

    /*
     * Meta data.
     */
    meta_attr_t      src_mattrs;
    meta_data_t      md;

    /*
     * Read ahead.
     */
    int                maio_in_use;
    u_int32_t          maio_bl_issued;
    multaio_read_ctx_t multaio;

} fasp_datasess_t;


// TODO Keep reasons here till moving to an approp hdr file.
#define FASP_CLOSE_NORMAL      (0)
#define FASP_CLOSE_ABNORMAL    (1)
#define FASP_ABORT_UNKNOWN     (2)
#define FASP_ABORT_LOCAL       (3)
#define FASP_ABORT_BY_PEER     (4)
#define FASP_ABORT_BY_APP      (5)
#define FASP_ABORT_LAST        (FASP_ABORT_BY_APP)

typedef struct fasp_ds_sesserr_t {
    union {
        fasp_ds_sesserr_pdu_t sent;
        fasp_ds_sesserr_pdu_t recd;
    } U;

    int local_reason;
    int peer_reason;

} fasp_ds_sesserr_t;


typedef struct fasp_ds_activity_t {
    u_int32_t net_in;
    u_int32_t net_req_in;
    u_int32_t net_rsp_in;
    u_int32_t net_dserr_in;
    u_int32_t net_sesserr_in;
    u_int32_t net_msg_in;
    struct timeval tm_latest_net_req_in;
    struct timeval tm_latest_net_rsp_in;

    u_int32_t net_out;
    u_int32_t net_req_out;
    u_int32_t net_rsp_out;
    u_int32_t net_dserr_out;
    u_int32_t net_sesserr_out;
    u_int32_t net_msg_out;
    struct timeval tm_latest_net_req_out;
    struct timeval tm_latest_net_rsp_out;
    u_int32_t latest_src_req2rsp_latency_ticks;
    u_int32_t latest_src_dsconn_latency_ticks;

    u_int32_t latest_sink_req2rsp_latency_ticks;
    u_int64_t latest_sinkQ_latency_usec;
    u_int64_t latest_sink_cmp_latency_usec;

    u_int32_t local_new;
    u_int32_t local_metachk_inprog;
} fasp_ds_activity_t;

/*
 * These should correspond to FASP_DS_OBJECT types above
 */
typedef enum {
    AS_FILE_OBJECT,
    AS_DIRECTORY_OBJECT,
    AS_SYMLINK_OBJECT,
    AS_SPECIAL_OBJECT
} as_object_t;


#endif /* __FASP_DS_TYPES_H__ */


