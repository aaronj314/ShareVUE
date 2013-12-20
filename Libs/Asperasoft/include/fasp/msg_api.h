/*
 * msg_api.h
 *
 * Data structures and build/parse routines for FASP messages (TCP and UDP).
 *
 * The data structures contain generic header or specific message header info
 * but will not hold TLV or other variable length fields.
 *
 * Actual PDU formats and sizes in fasp_proto.h
 *
 * Aspera Inc.
 */

#ifndef _MSG_API_H_
#define _MSG_API_H_

#include <utils/src/asutils.h>

#include <fasp/fasp.h>
#include <fasp/fasp_session.h>
#include <fasp/fasp_proto.h>

// constant and mask for transfer id field carried in data messages
// 
#define TRANSFER_ID_SIZE                  256         // 8 bits 
#define TRANSFER_ID_MASK                  0xff000000  // mask for transfer id 
#define TRANSFER_ID_BIT_POSITION          24          // bit position where id is stored 


/*
 * Protocol specification: Open Session Request/Response
 *
 * The PDU contains the following TLV fields:
 *
 * A. Session components:
 *
 *     1. UDP initiation
 *         - type&ver (client/server, peer2peer)
 *         - IP version (4 or 6)
 *         - local IP address and UDP port (sockaddr storage)
 *         - peer IP address and UDP port (sockaddr storage)
 *
 *     2. B/W measurement
 *         - type&ver
 *         - operation (send, receive, none)
 *         - tl
 *         - obs_len
 *         - probe_size
 *         - probe_rate
 *
 *     3. Data transfer
 *         - type&ver
 *         - Size of block ID (default 16 bit if missing)
 *         - Suggested block size (may not be needed)
 *         - operation (send, receive, none)
 *         - source list
 *         - destination
 *         - target-must-be-dir flag
 *         - resume policy (-k)
 *         - file/dir create policy
 *         - security
 *             - to be defined for the file enveloping mechanism
 *
 *     4. External channels 
 *         - type&ver
 *
 * B. Session info:
 *     - Session UUID
 *     - Session ID
 *     - Session ID size (8bit, 16 bit, ...)
 *     - Local user name
 *     - Login user name (on remote node)
 *     - Datagram size
 *     - Backpath datagram size
 *
 * C. Rate info:
 *     - policy
 *     - target
 *     - min
 *
 * D. Host caps info:
 *     - policy
 *     - target
 *     - min
 *
 * E. Security:
 *     - mac algo
 *     - mac keys (2)
 *     - cipher (crypto algo)
 *     - crypto keys (2)
 *
 * F. License info:
 *     - product ID
 *     - seat id (license ID)
 *     - system id
 *
 * G. Application info:
 *     - Token
 *     - Cookie
 *     - user string (-u) (SS: not used/implemented right now)
 *
 * H. Error:
 *     - error code (RSP only)
 *     - error string (RSP only)
 *     - unknown TLV (RSP only)
 *
 *  Questions:
 *     - what info needed for PROXY (SOCKSv4, SOCKSv5)?
 *  
 *  Notes:
 *     - TLV convention: MSB of Type 0 - T [1 Byte], L [1 Byte]
 *                                   1 - T [2 Byte], L [2 Byte]
 *     - Unknown TLVs are reported back to the client in the
 *       "Unknown TLV"
 *
 */

/*
 * All fasp tags for TLV encodings are defined in tlv.h.
 */

/* Forward declarations */
struct transfer_t;

// ------------------------------------------------------------------------
// Data structures
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//   Message structures for control messages
// ------------------------------------------------------------------------

typedef struct _generic_stream_pdu_header {
    unsigned char     type;
    unsigned char     unused;
    unsigned short    length;      // 16 bit length in nbo
} stream_pdu_hdr_t;

typedef struct _udp_pdu_header {
    unsigned char     sess_id;
    unsigned char     type;
} udp_pdu_hdr_t;

/* Data structure for TCP PDU: Open Session */

typedef struct _open_session_pdu_t {

    stream_pdu_hdr_t    hdr;
} open_session_pdu_t;

/* Data structure for TCP PDU: Close Session */

typedef struct _close_session_pdu_t {

    stream_pdu_hdr_t    hdr;
} close_session_pdu_t;

/* Data structure for TCP PDU: Stop Request */

typedef struct _request_stop_pdu {

    stream_pdu_hdr_t    hdr;
    u_int64_t           bytes_written; // total number of bytes written to disk
} request_stop_pdu_t;

/* Data structure for TCP PDU: NOP */

typedef struct _nop_pdu {

    stream_pdu_hdr_t    hdr;

} nop_pdu_t;


/* Data structure for UDP PDU: Start Request */

typedef struct _request_start_pdu {

    udp_pdu_hdr_t       hdr;
    u_int8_t            xfer_id;
    u_int32_t           start_block;

} request_start_pdu_t;

/* Data structure for UDP PDU: Statistics */

typedef struct _statistics_pdu_xfer {
    u_int32_t           ds_id;
    u_int64_t           bytes_written;
#define STAT_PDU_XFER_ENTRY_LEN  (12)
} statistics_pdu_xfer_t;

typedef struct _statistics_pdu {
    udp_pdu_hdr_t       hdr;
    u_int32_t           ctl_seqno;    // sess-level ctl-pkt seqno
    u_int16_t           num_xfer_stats; // number of entries that follow
                                        // in the xfer_statvec (on-wire)
    statistics_pdu_xfer_t xfer_statvec[FASP_DATASESS_PIPELINE_DEPTH];

} statistics_pdu_t;

/* Data structure for UDP PDU: Retransmission */

typedef struct _request_retransmissions_pdu {

    udp_pdu_hdr_t       hdr;
    u_int16_t           tick;
    u_int16_t           num_blocks;
    u_int32_t           ctl_rex_seqno; // sess-level rex-ctl-pkt seqno

} request_retransmissions_pdu_t;

/* virtual link statistics PDU (12Bytes) */
typedef struct _vlink_stat_pdu {
    
    udp_pdu_hdr_t       hdr;
    u_int16_t           vlink_group_id;  // vlink group identifier
    u_int16_t           vlink_sess_id;   // vlink session identifier    
    u_int16_t           direc;           // direction (up/down)
    u_int32_t           bytes;           // number of bytes to report
} vlink_stat_pdu_t; 

#define MAX_MSG_PDU_SIZE (max(max(sizeof(nop_pdu_t),                      \
                                  sizeof(request_start_pdu_t)),           \
                              max(sizeof(request_retransmissions_pdu_t),  \
                                  sizeof(statistics_pdu_t))))

/* Data structure to temporarily hold information decoded from a 
 * 'UDP' control PDU.  The control pdu may carry a variable number 
 * of control components.
 */
typedef struct control_pdu_t {
    udp_pdu_hdr_t       hdr;
    u_int16_t           unused1;      // unused field #1
    u_int32_t           pkt_id;       // packet id
    u_int32_t           comps;        // components
    u_int32_t           sec_seqno;    // security (unused if no security)
    u_int16_t           net_tick;     // network tick
    u_int32_t           dsid_ackvec_seqno;
    u_int32_t           dsid_ackvec[FASP_DATASESS_PIPELINE_DEPTH]; // ds-id acks
    u_int32_t           rate_ctl_seqno;

} control_pdu_t;


/* Data structure for UDP PDU: data */

typedef struct dgram_hdr_ {

    udp_pdu_hdr_t   hdr;
    u_int16_t       tick;
    u_int32_t       block_index;
    u_int32_t       rex_index;
    u_int32_t       xfer_id;        // This field is not part of the PDU
                                    // It is the MSB of rex_index
} dgram_hdr_t;

// function prototypes
//

int build_open_session_req_msg (fasp_session_t *s,
                                char *pdu,
                                u_int16_t *len);

int build_open_session_rsp_msg (fasp_session_t *s,
                                char *pdu,
                                u_int16_t *len);

int build_close_session_msg(fasp_session_t *s,
                            char *pdu,
                            u_int16_t *len);

void build_sess_retransmit (fasp_session_t  *sess, 
                            char            *pdu,
                            u_int16_t       *len,
                            int             *rex_count,
                            int             rex_flag);

void build_sess_statistics( struct fasp_session_t *sess,
                            u_int8_t    *pdu,
                            u_int16_t *len);

void build_control_msg( struct fasp_session_t *sess, 
                        struct transfer_t *xfer, 
                        char *pdu,
                        u_int16_t *len);

void build_vlink_stat_msg (fasp_session_t *sess, char *pdu, 
                           u_int16_t id, int bytes);

int parse_vlink_stat_msg (fasp_session_t *sess, 
                           char *pdu, vlink_stat_pdu_t *pdu_rcvd);

int parse_open_session_req_msg (fasp_session_t *s,
                                char *pdu,
                                u_int16_t len);

int parse_open_session_rsp_msg (fasp_session_t *s,
                                char *pdu,
                                u_int16_t len);

int parse_close_session_msg (fasp_session_t *s,
                             char *pdu,
                             u_int16_t len);

int parse_sess_retransmission (fasp_session_t *sess,
                               char *pdu,
                               u_int16_t len);

int parse_sess_statistics( struct fasp_session_t *sess, 
                           char *pdu,
                           u_int16_t len);

int parse_udp_stop ( struct fasp_session_t *sess, 
                      struct transfer_t *xfer, 
                      char *pdu,
                      u_int16_t len);

void parse_stopped( struct transfer_t *xfer, 
                    char *pdu,
                    u_int16_t len);

int parse_request_start( struct fasp_session_t *sess, 
                         struct transfer_t *xfer, 
                         char *pdu,
                         u_int16_t len);

int parse_error_msg( struct fasp_session_t *sess,
                     char *pdu,
                     u_int16_t len);

extern int
build_sess_control(
    fasp_session_t *sess,
    char *pdu,
    u_int16_t pdu_len,
    u_int16_t *len_encoded,
    struct timeval *pnow
);

extern int
parse_sess_control_dbuf(
    fasp_session_t *sess, 
    dbuf_t *dbuf,
    u_int16_t len
);

extern int
parse_sess_control(
    fasp_session_t *sess, 
    char *pdu, 
    u_int16_t len
);

#endif

