/*! \file
 * fasp_session.h
 *
 * FASP session data structures and related functions.
 *
 * Aspera, Inc.
 */

#ifndef __AS_FASP_SESSION_H__
#define __AS_FASP_SESSION_H__

#include <utils/src/asutils.h>

#include <fasp/fasp.h>
#include <fasp/fasp_errno.h>
#include <fasp/fasp_version.h>
#include <fasp/struct_api.h>
#include <fasp/rtt.h>
#include <fasp/rate.h>
#include <fasp/rex.h>
#include <fasp/ring.h>
#include <fasp/security.h>
#include <fasp/mgmt_proto.h>
#include <fasp/fasp_license.h>
#include <ds/fasp_ds_api.h>
#include <ds/fasp_ds_types.h>
#include <ds/fasp_ds_stats.h>
#include <fasp/fasp_destpath.h>
#include <fasp/fasp_data_ctl.h>
#include <fasp/fasp_policy.h>
#include <fasp/util_api.h>
#include <istats/latency_tab.h>

/*! \mainpage Aspera FASP
 *
 * This documents the FASP session API.
 *
 */

/*
 * The maximum number of exclude patterns that may be specified
 * at the command line
 */
#define MAX_EXCLUDE_PATTERN_COUNT 16

/* Default session values */
#define DEFAULT_TCP_PORT                22
#define DEFAULT_UDP_PORT                33001
#define DEFAULT_TARGET_RATE             10000000ULL
#define DEFAULT_MIN_RATE                0ULL
#define DEFAULT_SERVICE_CAP             1000000000000ULL

#define DEFAULT_ENCRYPT_ALG             SECURITY_ENC_AES128;

/* FASP events */
#define FASP_SESSION_START              0x01 /* SESSION mgmt msg */
#define FASP_SESSION_STOP               0x02 /* DONE or ERROR */
#define FASP_FILE_START                 0x11 /* STATS */
#define FASP_FILE_STATS                 0x12 /* STATS mgmt msg */
#define FASP_FILE_STOP                  0x13 /* STOP or FILEERROR mgmt msg */
#define FASP_NOTIFY_RATE                0x21 /* NOTIFICATION mgmt msg */
#define FASP_WAIT_AUTH                  0x22 /* sent QUERY/AUTHORIZATION */
#define FASP_NOTIFY_PRETRANSFER         0x23 /* NOTIFICATION of pretransfer numbers */

/* Pre-calculate job totals */
#define FASP_PRECALC_ANY                0x00
#define FASP_PRECALC_NO                 0x01
#define FASP_PRECALC_YES                0x02

/*! \brief
 * Rate parameters
 */
typedef struct fasp_rate_params_t {

    u_int8_t            policy;
    u_int8_t            policy_lock;
    u_int8_t            priority_lock;
    u_int8_t            min_rate_lock;
    u_int8_t            target_rate_lock;
    u_int64_t           target_rate;    // target rate (if absolute value)
    u_int64_t           min_rate;       // min rate (if absolute value)
    u_int32_t           target_perc;    // target rate as percentage of link
    u_int32_t           min_perc;       // min rate as percentage of link
    u_int32_t           seqno;          // change id
    u_int32_t           ackno;          // change id ack to send to peer
    u_int32_t           phaseno;        // phase id of RP negotiation
    u_int16_t           target_qweight; // target queue weighted adjustment (local)
    u_int16_t           peer_target_qweight; 
                                        // target queue weighted adjustment (remote)
    u_int32_t           priority;       // transfer rate priority

    /*
     * Housekeeping variables.
     */
    u_int32_t           seqno_in;       // seqno just received from peer
    u_int32_t           ackno_in;       // ackno just received from peer
    u_int16_t           rcvd_new_seqno; // flag
    u_int16_t           una_cnt;        // count indicating 'need to send ack'

    u_int32_t           neg_state;      // current state of negotiation

    /*
     * Statistics.
     */
    u_int32_t           app_reqno;      // number of changes made by local app
    u_int32_t           app_notfns_done;// number of application notifications
                                        // done (regardless of change initiated
                                        // by local or peer).

} fasp_rate_params_t;

typedef struct fasp_rate_request_t {

    u_int32_t           which_params;   // rate params flags
    fasp_rate_params_t  rate_params;    // requested rate parameters
    void                *next_request;  // pointer to next saved request

} fasp_rate_request_t;

typedef struct fasp_dsid_ackvec_t {
    /*
     * Local (sender & receiver) dsid ack-vector seqno and vector.
     */
    u_int32_t           dsid_ackvec_seqno;
    u_int32_t           dsid_ackvec[FASP_DATASESS_PIPELINE_DEPTH];

    /*
     * Receiver keeps dsid ack-vector seqno & vector in netorder.
     */
    u_int32_t           netorder_dsid_ackvec_seqno;
    u_int32_t           netorder_dsid_ackvec[FASP_DATASESS_PIPELINE_DEPTH];

    /*
     * Receiver tracks next_slot to be filled/overwritten in vector.
     */
    u_int32_t           ackvec_next_slot;

    /*
     * Sender-side housekeeping flag that gets set when a new (greater seqno)
     * dsid ackvec is received (at sender).
     */
    u_int16_t           ackvec_rcvd_new;
    u_int16_t           una_cnt;        // count indicating 'could send ack'

    /*
     * Sender sends ACK to receiver for given dsid_ackvec seqno.
     */
    u_int32_t           dsid_ackvec_ackno;

} fasp_dsid_ackvec_t;

    
/* flags used in xopt_flags field, indicative of user provided parameters */
enum {
    XOPT_FLAG_USE_PSEUDO_SNAP_FOLDER = (1<<1),

    XOPT_FLAG_SKIP_SYMBOLIC_LINKS    = (1<<2),
    XOPT_FLAG_COPY_SYMBOLIC_LINKS    = (1<<3),
    XOPT_FLAG_FOLLOW_SYMBOLIC_LINKS  = (1<<4),

    /* skip device, fifo, socket, etc. files
     * XXX should this be default behavior?
     */
    XOPT_FLAG_SKIP_SPECIAL_FILES     = (1<<5),

    XOPT_FLAG_MAY_FILE_ENCRYPT       = (1<<6),
    XOPT_FLAG_MAY_FILE_DECRYPT       = (1<<7),
    /* a special version check */
    XOPT_FLAG_NO_FILE_ENCRYPT        = (1<<8),

    /* These flags are "post-processing" flags and therefore located at 
     * high word, so that we can mask the high word to see if
     * any post processing needs to be done.
     */
    XOPT_FLAG_POST_PROCESS_MASK      =   (-(1<<16)), /* 0xffff0000 */

    XOPT_FLAG_REMOVE_AFTER_TRANSFER  =   (1<<16),
    XOPT_FLAG_REMOVE_EMPTY_DIRECTORIES = (1<<17)
};

/*! \brief
 * FASP Session Definition
 * Contains all information on what needs to be transferred.
 *
 * XXX
 * the definition of fasp_session_def_t is closely tied to the
 * code in tlv.c : build_tlv_sess(), which takes fields from
 * fasp_session_def_t and encodes in open session PDU.
 *
 * XXX
 * That means whenever you add new parameters to applications,
 * you first have to add them to fasp_session_def_t and then
 * accordingly code build_tlv_sess() to convey the new parameter
 * as part of session being opened.
 * 
 */

typedef struct fasp_session_def_t {

    u_int8_t            transfer_op;    // transfer operation (none, send, receive)
    char                **sourcelist;
    char                *dest;
    char                *remotehost;
    char                *remoteuser;
    char                *remotepassword;
    u_int32_t           remoteaddr;    /* IP address putty is talking to */

    u_int16_t           tcp_port;       //! SSH port
    u_int16_t           udp_port;       //! FASP port

    u_int8_t            verbose;        
    u_int8_t            cipher;         // encryption cipher
    u_int8_t            resume_policy;
    u_int8_t            create_policy;  // flags for file creation
    u_int8_t            manifest_policy;// flags for file manifestion
    u_int8_t            precalc;        // pre-calculate job totals
    u_int8_t            overwrite_policy; 
                                        // flags for overwriting existing file
    /* FIXME retry timeout is only used for reporting purposes */
    u_int16_t           retry_timeout;  /* retry timeout */

    char                *manifest_path; // directory to create manifest file

    fasp_rate_params_t  rate_params;

    char const          *token;
    char const          *cookie;
    char const          *user_str;
    char const          *file_pass;
    u_int8_t            file_pass_details[5];
    u_int8_t            got_file_pass_details;

    const char          *fallback_protocol; /* alternate fallback protocol */

    int                 files_encrypt;   /* encrypt when sending */
    int                 files_decrypt;   /* decrypt when receiving */

    u_int32_t           max_rex_number; // max num of rex per request
    u_int32_t           dgramsz;        // datagram size

    char                *prepostcmd;    // path to pre/post processing script

    /* extended parameter options */

    char                *xopt_aspera_conf_file_name; /* alternate aspera conf file */
    u_int32_t           xopt_flags; /* user specified options, XOPT_FLAGS bits */

    char                *xopt_pseudo_snap_folder_name; /* optional */

    /* Bandwidth measurement parameters */ 
    u_int8_t            bwmeas_op;      // bandwidth measurement operation
    u_int8_t            peer_bwmeas_op; // peer bandwidth measurement operation
    u_int32_t           obs_len;
    u_int32_t           probe_size;
    u_int32_t           probe_rate;
    u_int64_t           presetbw;       // bottleneck bw preset by others

    /* virtual link related parameters */
    u_int8_t            vl_local_enabled;
    u_int16_t           vl_local_id;    
    u_int64_t           vl_local_cl;    // local virtual link capacity
    u_int32_t           vl_local_qmax; 
    u_int32_t           vl_local_qmin; 
    u_int32_t           vl_local_k_inner;
    u_int32_t           vl_local_k_outer;
    u_int8_t            vl_remote_enabled;
    u_int16_t           vl_remote_id;    
    u_int64_t           vl_remote_cl;   // remote virtual link capacity
    u_int32_t           vl_remote_qmax; 
    u_int32_t           vl_remote_qmin; 
    u_int32_t           vl_remote_k_inner;
    u_int32_t           vl_remote_k_outer;

    /* Data session parameters */
    u_int32_t           ds_pipeline_depth;
    u_int32_t           peer_ds_pipeline_depth;
    char               *local_ip_str;

    /* IO size parameters */
    u_int32_t           read_block_size;
    u_int32_t           write_block_size;

    /* Command line exclude patterns */
    const char          *exclude_patterns[MAX_EXCLUDE_PATTERN_COUNT];
    u_int32_t           exclude_pattern_count;

    u_int32_t           cluster_num_nodes;  /* N (default 1) */
    u_int32_t           cluster_node_id;    /* M < N (default 0) */
                        /* Note: user should only see (cluster_node_id+1) */

    int                 move_range;  // 0: no, 1: yes
    u_int64_t           move_range_low;
    u_int64_t           move_range_high;

} fasp_session_def_t;


/*! \brief
 * Bandwidth measurement internal data
 */
typedef struct fasp_bw_t {
    // measurement states
    
    // used in both pMTU (brtt) discovery and bw discovery
    u_int32_t           curops;       // current operation
    u_int32_t           curseq;       // current probe seq number (sent/recvd)
    u_int32_t           cur_ts;       // current timestamp;  

    // used only in pMTU (brtt) discovery
    u_int32_t           cur_prb_size; // current udp packet size 
    u_int32_t           cur_MTU_size; // current MTU size (sent/recvd)

    // used only in bw discovery
    u_int32_t           curpos;       // current probe position in a pair
    u_int32_t           nextseq;      // next (expected) probe sequence number
    u_int32_t           nextpos;      // next (expected) probe position
    u_int32_t           total_pairs;  // total packet pairs sent or received
    
} fasp_bw_t;

/*! \brief
 * Session level statistics
 */
typedef struct fasp_sess_stats_t {

    /* Common sender and receiver stats */
    u_int32_t           bl_first;           // num of first block sent
    u_int64_t           bl_total;           // total number of blocks sent
    u_int64_t           bl_orig;            // num of original blocks sent
    u_int64_t           bl_rex;             // num of retransmitted blocks
    u_int32_t           bl_last;            // num of "last block" could send
    u_int32_t           bl_highest;         // highest block received so far

    /* Receiver stats */

                        /* API fields for prog counters */
    u_int64_t           transfer_bytes_prog;// running total of non-duplicate 
                                            // bytes rcvd @rcvr for entire sess
    u_int64_t           file_bytes_prog;    // running total of file bytes at
                                            // receiver for entire sess
    u_int64_t           data_xfer_usec_elapsed; // periodic/statpdu snapshot of
                                            // usec elapsed since reception
                                            // of first data packet
    u_int32_t           rtt_rto;

                        /* Receiver side temp prog vars */
    u_int64_t           transfer_bytes_prog_snapshot;//when data packet arrived
    u_int64_t           file_bytes_prog_snapshot;    //when data packet arrived
                        /* Sender side temp prog vars */
    u_int64_t           transfer_bytes_prog_statin;   // copied from stat pdu
    u_int64_t           file_bytes_prog_statin;       // copied from stat pdu
    u_int64_t           data_xfer_usec_elapsed_statin;// copied from stat pdu
    u_int32_t           rtt_rto_statin;               //

                        /* Internal counter */
    u_int64_t           bytes_prog_update_cnt;// num of bytes prog updates done

    u_int64_t           good_bytes_rcvd;    // num good bytes received in sess
    struct timeval      data_xfer_start;    // time first data xfer started
    struct timeval      data_xfer_stop;     // time last  data xfer stopped
    u_int64_t           data_xfer_dur;      // time duration of total data xfer 
    u_int32_t           blocks_ooo;         // num blocks received out of order
    u_int32_t           blocks_badid;       // num blocks with bad transfer ID
    u_int32_t           blocks_badmac;      // num blocks with bad MAC
    u_int32_t           blocks_badseqnum;   // num blocks with bad sequence num
    u_int32_t           ctlpdu_badseqnum;   // num ctlpdus with bad sequence num
    u_int32_t           rex_rem_failed;     // num of rex_remove failures
    u_int32_t           rex_add_failed;     // num of rex_add failures
    u_int32_t           rex_blocks_sent;    // num of block rex requested
    u_int32_t           rex_reqs_sent;      // num of rex requests sent
    u_int64_t           block_count;        // num of blocks in sess
    u_int64_t           lost_blocks;        // num of non-rex blks lost in sess
    u_int64_t           dup_blocks;         // num of duplicates rcvd in sess
    u_int64_t           dup_last_block;     // num of dup last blocks sent/rcvd
    u_int32_t           drop_rexfull;       // blocks dropped when rex full
    u_int32_t           drop_ringfull;      // blocks dropped when ring buffer is full
    u_int64_t           drop_blocks_xfer_notfound;// num of blocks dropped !xfer
    u_int32_t           udp_stop_reqs_sent; // num of udp stop msgs sent @ EOF

    /* Sender stats */
    u_int32_t           rex_blocks_rcvd;    // num of block rex requests
    u_int32_t           rex_blocks_dup;     // num of block rex already in rbt
    u_int32_t           rex_reqs_rcvd;      // num of rex request messages

    /* Error stats */
    u_int32_t           xmtr_ds_abrt_intnl; // Internal DS aborts @ xmitter
    u_int32_t           xmtr_ds_abrt_extnl; // External DS aborts rcvd @ xmitter
    u_int32_t           rcvr_ds_abrt_intnl; // Internal DS aborts @ receiver
    u_int32_t           rcvr_ds_abrt_extnl; // External DS aborts rcvd @ rcvr

} fasp_sess_stats_t;


typedef struct fasp_instrumentation_t {
    u_int32_t  ipd_pkn_sent;      // num of pkts actually sent in this batch
    time_t     tm_prev_pkts_sent; // prev time when sent atleast 1 pkt 
    time_t     tm_snoring;        // duration of no pkt sent (tm_pkts_not_sent)

    u_int32_t  ipd_pkn_miss;    // num of pkts send-miss in this batch
    u_int32_t  ipd_pkn_miss_einprog; // num of pkts send-miss due to EINPROG
                                     // in this batch
    u_int32_t  ipd_pkn_miss_noxmtr;  // num of pkts send-miss due to 
                                     // !g_xmitting_xfer

    /*
     * Transmitter debug instrumentation for use FOREACH send_batch() loop.
     */
    u_int16_t  send_batch_debug;  // Flag to enable IPD debug instrumentation
    u_int32_t  num_no_xmitter;    // num of times !g_xmitting_xfer in LOOP iter
    u_int32_t  num_send_rex_fail; // num of times rex send failed in LOOP iter
    u_int32_t  num_send_orig_fail;// num of times orig send failed in LOOP iter
    u_int32_t  num_rex_xfer_not_found;// num of times !rex_xfer in LOOP iter
    u_int32_t  num_xfer_last_block;   // num of times no xmit due to last block
    u_int32_t  num_rex_abrtxfer_not_found;// # of (abrtd) !rex_xfer in LOOP iter

    /* Abort handling housekeeping */
    u_int32_t  xmtr_latest_xfrabrt_fstrtblk;
    u_int32_t  xmtr_latest_xfrabrt_fstopblk;

    /* Rate */
    u_int64_t  pkts_sent_persec;
    u_int64_t  pkts_miss_einprog_persec;
    u_int64_t  pkts_miss_noxmtr_persec;

    /*
     * Transmitter debug instrumentation for on the mark ds.
     */
    u_int32_t  num_onthemark;      // num of times in sess found g_onthemark_ds
    u_int32_t  num_none_onthemark; // num of times in sess !g_onthemark_ds

    u_int32_t  num_stat_calls_periodic; // num of calls to periodic stat check
    u_int32_t  num_stat_calls;    // total num of calls to send stat pdu

      /* tstamp of prev last block event */
    struct timeval tm_xmit_lblk_event; 
      /* tstamp of nxt xmit xfer added to runQ */
    struct timeval tm_xmit_next_add_run;
    latency_tab_t  xmit_lblk_to_done;
    latency_tab_t  xmit_lblk_to_nextadd;

    latency_tab_t first_fileread_tab;
    latency_tab_t other_fileread_tab;

    u_int64_t  op_reads_blocking;
    u_int64_t  op_reads_blocking_timespent;
    u_int64_t  op_reads_rex;

    u_int64_t  op_reads_aio;
    u_int64_t  op_reads_aio_timespent;
    u_int64_t  op_reads_aio_blocks;
    u_int64_t  op_reads_aio_pending;
    u_int64_t  op_reads_aio_no_pending;
    u_int64_t  op_reads_did_blocking_readv;

    u_int64_t  op_reads_aio_inprog_yield_useful;
    u_int64_t  op_reads_aio_inprog_yield_waste;
    u_int64_t  op_reads_aio_inprog_yield_tot;
    u_int64_t  op_reads_aio_inprog_sleep_one;
    u_int64_t  op_reads_aio_inprog_sleep_many;
    u_int64_t  op_reads_aio_inprog_sleep_tot;

    u_int64_t  send_one_einprog;
    u_int64_t  send_one_noxmtr;


    /*
     * Receiver debug instrumentation.
     */
    struct timeval tm_rcvr_done_event; // tstamp of recv done event
    struct timeval tm_rcvr_next_add_run; // tstamp of nxt rcvr xfer add to runQ
    latency_tab_t  rcvr_done_to_nextadd;

} fasp_instrumentation_t;


typedef struct fasp_sess_result_t {
    int32_t errcode;
    size_t  errstrlen;
    char    errstr[FASP_ERRSTR_MAXLEN];
    int32_t rtt;
    int32_t rex_rtt;
    int64_t rex_xmit_blks;
    float   rex_xmit_pct;
    int64_t tot_blks;
    int64_t ctlmsgs_sent;
    int64_t ctlmsgs_rcvd;
    int64_t rexreqs_sent;
    int64_t rexreqs_rcvd;
    fasp_ds_stats_src_export_t ds_src_stats;
} fasp_sess_result_t;

struct transfer_t;
struct fasp_session_t;
struct fasp_vlink_t;

typedef enum {
    FASP_LAST_ERROR_START,  FASP_LAST_ERROR_SAME,  FASP_LAST_ERROR_DIFF
} fasp_last_error_e;

/*
 * FASP callback function
 */
typedef void (*fasp_cbk_t)(
    int event, struct fasp_session_t *sess, struct transfer_t *xfer);

/*! \brief
 * FASP session internal data
 */
typedef struct fasp_session_t {

    /* Session parameters */
    char                *uuid;
    u_int8_t            raw_uuid[ENC_BLOCK_SIZE];
    u_int8_t            id;             // Actual size: 8 or 16 bytes
    u_int8_t            iamremote;
    u_int8_t            encrypt_files;
    u_int8_t            decrypt_files;  
    u_int8_t            flow_cac_rateparams_capped;

#define MAX_AS_OS_LEN  40
    char                as_os[MAX_AS_OS_LEN + 1];
    char                *peer_as_os;
#define MAX_AS_VER_LEN 40
    char                as_version[MAX_AS_OS_LEN + 1];
    char                *peer_as_version;

    /* Session definition (all parameters user can set) */
    fasp_session_def_t  *sess_def;

    /* Session parameters */
    security_parms_t    security_parms;
    fasp_rate_params_t  rate_params;
    fasp_rate_params_t  rate_caps;
    fasp_rate_params_t  peer_rate_caps;
    u_int64_t           license_bandwidth_limit; // this can be changed to a rate_params for more control

    fasp_rate_request_t rate_request_saved; 
    u_int64_t           calc_rate;

    char                *prepostcmd;    // path to pre/post processing script    
    u_int32_t           source_num;     // number of source items
    sourcelistinfo_t    sourcelistinfo; // total size and num files in sources
    u_int8_t            target_must_be_dir;
    u_int8_t            target_path_preexists;// rcvr informs sndr in OS req/rsp
    u_int8_t            target_skip_topdir;   // derived parameter
    u_int8_t            overwrite_policy_cap; // overwrite allow/deny
    
    /* Session results */
    fasp_sess_result_t  sess_result_sndr;  // result sent by sender
    fasp_sess_result_t  sess_result_rcvr;  // result sent by receiver
    fasp_sess_result_t  *local_res;
    fasp_sess_result_t  *peer_res;
    char                *local_role;
    char                *peer_role;

    /* Session state */
    u_int16_t           admin_state;
    u_int16_t           state;
    u_int16_t           event_state;       // Remember past event
    int32_t             errcode;
    char                errstr[FASP_ERRSTR_MAXLEN];
    u_int32_t           last_file_error; 
    fasp_last_error_e   last_file_error_state;

    u_int32_t           stopped;      // if the measurement has been stopped
                                      // TODO: we can use admin_stat for this
    u_int32_t           udp_connected;// true if the udp_socket is connected
    struct timeval      start_time;   // time when session started
    struct timeval      rcv_start_time;// time when session data receive started
    fasp_bw_t           meas_state;   // session measurement state
    u_int16_t           tout_age;     // session timeout count
    u_int8_t            tout_fired;   // session timeout occured
    u_int8_t            xfer_no_progress;// instantaneous # xfers w/no progress
    u_int8_t            nowork;       // "running" queue empty, don't time out
    u_int8_t            got_transit_key; // peer sent transfer encryption key

    /* Protocol versions and settings */
    u_int32_t           proto_open_sess;    // In the future these can be used as bitmaps
    u_int32_t           proto_udp_sess;
    u_int32_t           proto_bwmeas;
    u_int32_t           proto_data;
    u_int32_t           peer_proto_open_sess;
    u_int32_t           peer_proto_bwmeas;
    u_int32_t           peer_proto_udp_sess;
    u_int32_t           peer_proto_data;
    u_int8_t            size_sess_id;   // Size of session ID (bytes)
    u_int8_t            size_block_id;  // Size of FASP block ID (bytes)

    /* License information */
    u_int8_t            license_ver;
    u_int8_t            peer_license_ver;
    fasp_license_t      fasp_license;
    fasp_license_t      peer_fasp_license;
    char               *peerterms;
    size_t              peertermsz;
    fasp_old_licinfo_t  peerlicense_info;
    
    /* Session resources */
    as_socket_t         udp_sock; 
    as_socket_t         udp_sock_ephemeral; 
                                        // ephemeral UDP socket for initial UDP bootstrap
    as_socket_t         tcp_fd_in;      // SSH channel (pipe)
    as_socket_t         tcp_fd_out;     // SSH channel (pipe)

    u_int8_t            remote_port_ephemeral;
                                        // if the first server udp sock is ephemeral 
    char                *localuser;
    char                *localuserid;

    /* Session end-point data */
    u_int8_t            ipv6_yn;
    struct sockaddr_in  ip_address;         // our address
    socklen_t           ip_length;          // length of our address
    u_int16_t           udp_port;           // local port
    int                 udp_tl;             // timer precision level
    struct sockaddr_in  peer_ip_address;    // address of peer
    socklen_t           peer_ip_length;     // length of address of peer
    u_int16_t           peer_udp_port;      // peer port
    int                 peer_udp_tl;        // timer precision level of peer

    /* Session measurement results */
    u_int16_t           sessini_opt;  // sessini optimization  
    u_int32_t           pMTU;         // transfer direction path MTU
    int                 start_brtt;   // measured base RTT at start-up
    int                 coal_flag;    // flag to indicate interrupt coalescing
    u_int64_t           bw;           // bottleneck bandwidth (bps)

    /* Virtual link related parameters */
    u_int16_t           vlink_sess_id;// virtual link session identifier
    u_int8_t            vl_local_enabled;
    u_int8_t            vl_remote_enabled;
    struct fasp_vlink_t *vlink_local; // pointer to local vlink data structure
    struct fasp_vlink_t *vlink_remote;// pointer to remote vlink data structure

    // local vlink internal variables
    u_int8_t            vl_report_local;  
                                      // send current local (s)ql in next packet
    u_int32_t           vl_tB;        // send update message every tB bytes
    u_int32_t           vl_tT;        // send update message every tT msec
    struct timeval      vl_last_broadcast;  
                                      // last moment when vlink broadcasted
    u_int32_t           vl_cur_recvd; // currently received bytes
 
    /* Session private data */
    u_int32_t           udp_buffer;     // size of the UDP send buffer in bytes
    u_int32_t           block_size;
    u_int32_t           user_id;
    struct sockaddr_in  tmp_ip_address;
    struct sockaddr_in  tmp_peer_ip_address;

    u_int32_t           rex_poll_int; // the polling interval for rex requests
    u_int32_t           rex_num_int;  // num of rex reqs allowed per interval
    
    u_int32_t           ipd_target;   // target inter-packet delay in usec
    struct timeval      ipd_intstart; // start of rate calculation interval
    u_int32_t           ipd_intbytes; // number of bytes received in interval
    u_int32_t           ipd_pkn;      // number of packets to send in a batch

    rtt_info_t          rttinfo_rate;
    rate_info_t         rateinfo;

    ring_buffer_t       *ring;
    int                  prev_ringbuf_wrote_id; // track ring buf for cont8bytes
    int                  curr_ringbuf_wrote_id; // track ring buf for cont8bytes

    /* Session transfer data */
    u_int32_t           sess_start_block;
    u_int32_t           sess_block;
    u_int32_t           sess_next_block;
    u_int32_t           ctl_seqno_out;  // sess-level seqno on outgoing ctl pkt
    u_int32_t           ctl_seqno_in;   // sess-level seqno on incoming ctl pkt
    u_int32_t           ctl_rex_seqno_out;//sess-level seqno on outgoing ctl pkt
    u_int32_t           ctl_rex_seqno_in; //sess-level seqno on incoming ctl pkt
    u_int32_t           ctl_rex_rcvd;   //sess-level seqno on incoming ctl pkt
    fasp_dsid_ackvec_t  dsid_av;
    u_int32_t           sess_blk_prevhimark;
    u_int32_t           sess_blk_himark;
    u_int16_t           rex_flag;
    u_int16_t           last_sessblk_rcvd;

    /* Disk thread private data */
    as_thread_t         disk_tid;       // thread writing recvd data to disk 

    /* fasp destination path context */
    fasp_destpath_t     destinfo;

    /* DBF lookup contexts */
    dbfmap_fastlookup_ctx_t data_xmtr_dbflookup_ctx;
    dbfmap_fastlookup_ctx_t data_rcvr_dbflookup_ctx;
    dbfmap_fastlookup_ctx_t data_ring_dbflookup_ctx;

    /* Data transfer using classing scp */
    struct transfer_t   *xfer;
    

    as_thread_t         xmit_data_tid;  // data transmitter thread
    as_thread_t         recv_data_tid;  // data receiver arun
    /* Callback function */
    fasp_cbk_t          cbk;

    /* Session level statistics */
    fasp_sess_stats_t   sess_stats;     // Reuse statistics_t for now

    /* Session level instrumentation */
    fasp_instrumentation_t instru;      // instrumentation for tracking/debug

    control_t          control;
    control_pdu_freq_t ctlpdu_freq;
    control_stats_t    control_stats;

    /* Current outstanding aio reads on DS that are still in ReadyQ */
    int                readyq_readahead_bl_cnt;

    u_int16_t           pdu_len;

    /* big things */
    u_int64_t           force_pdu_buf_alignment;  /* this is an awful hack */
    char                pdu_buf[MAX_DGRAM_SIZE];

    rex_t               rex;
    
    /* File manifest */
    char                *manifest_fname;
    as_file_t           manifest_fh;

} fasp_session_t;

/*! \brief
 * Init a FASP session structure before the connection is opened.
 *    - verify Aspera license
 *    - initialize some session-level structure elements
 */
fasp_session_t *fasp_session_init(
    fasp_session_def_t *sess_def,
    char const* uuid_string);

/*! \brief
 * Open a FASP session to initiate a transfer
 *    - create UDP socket
 *    - create security keys (all of them)
 *    - initialize session-level structure elements
 */
void fasp_session_open(
    fasp_session_t *sess,
    as_socket_t read_fd,
    as_socket_t write_fd,
    fasp_cbk_t cbk);

/*! \brief
 * Accepts an incoming client connection and opens the server side
 * FASP session.
 *
 * This will initialize the server side FASP session.
 */
fasp_session_t *fasp_session_accept(as_socket_t read_fd, 
                                    as_socket_t write_fd, 
                                    fasp_cbk_t cbk);


/*! \brief
 * Starts a FASP session, after the Open Session exchange has completed.
 *
 * Called by both sender and receiver, after the session has been opened,
 * to start the UDP session and transfer.
 */
int fasp_session_start(fasp_session_t *sess);

/*! \brief
 * Close a FASP session.
 *
 * Clean up FASP session  (sockets, allocated memory)
 */
void fasp_session_close(fasp_session_t *sess);

/*! \brief
 * Cancel a FASP session.
 */
void fasp_session_cancel(fasp_session_t *sess, char *reason_str);

/*
 * Create a default session definition
 */
fasp_session_def_t *fasp_session_def_create(void);

/*
 * Utility routines.
 */

/* FIXME: replace calls to this with calls to fasp_error */

extern int
fasp_sess_err_set(
    fasp_session_t *s,
    int errcode,
    char *errstr
);

/*
 * Return client/server role as a printable string.
 */
char *fasp_session_role_str(fasp_session_t *sess);

/*
 * Return client/server role of peer as a printable string.
 */
char *fasp_session_peer_role_str(fasp_session_t *sess);

#endif
