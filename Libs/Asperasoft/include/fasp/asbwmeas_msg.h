#ifndef ASBWMEAS_MSG_H_
#define ASBWMEAS_MSG_H_

/*========================================================================
 * asbwmeas_msg.h 
 *
 *========================================================================*/

#include <utils/src/asuuid.h>


typedef struct {
        u_int32_t         tl;              // timer_precision level
} udp_port_info_t;

// 8B + UUID + 4B padding + 16B sum
// only sent when client is receiver 
typedef struct _udp_prtopen_pdu {
        udp_pdu_hdr_t     hdr;
        u_int16_t         padding;        // padding to maintain compatibility
        u_int32_t         seq;            // sequence number
        char              uuid[AS_MAX_UUID_STR_SIZE + 4];
        u_int8_t          mac[MD5_DIGEST_LENGTH];
} udp_prtopen_pdu_t;

// 20B + UUID + 4B padding + 16B sum
typedef struct _pmtu_brtt_probe_pdu {
        udp_pdu_hdr_t	  hdr;
        u_int16_t         padding;        // padding to maintain compatibility;
        u_int32_t         seq;            // sequence number
        u_int32_t         tsize;          // size of the MTU or ACK pkt
        u_int32_t         mmtick;         // sender side tick value
        u_int32_t         pMTU;           // concluded pMTU (0 if not avail)
        char              uuid[AS_MAX_UUID_STR_SIZE + 4];
        u_int8_t          mac[MD5_DIGEST_LENGTH];
} pmtu_brtt_probe_pdu_t;

// 20B + 16B sum, total size determined by probe_size
typedef struct _bw_probe_pdu {
        udp_pdu_hdr_t     hdr;
        u_int16_t         padding;        // padding to maintain compatibility; 
        u_int32_t         seq;            // sequence number
        u_int32_t         pos;            // position: 0 or 1
        u_int32_t         timestamp;      // local timestamp
        u_int32_t         ops;            // specific operation
        u_int8_t          mac[MD5_DIGEST_LENGTH];
} bw_probe_pdu_t;

#define SESS_DATA_STRU_SIZE               (24)
#define SESS_STOP_PDU_SIZE                (32)

typedef struct sess_data {
        u_int32_t         pMTU;           // pMTU
        u_int32_t         brtt;           // start brtt (ms)
        u_int32_t         coal_flag;      // coalescing flag
        u_int64_t         bw;             // bottleneck bw
        u_int32_t         total_pairs;    // total valid pairs received     
} sess_data_t;

// 32B: Carrying measurement results
typedef struct _sess_stop_pdu {
        stream_pdu_hdr_t  hdr;          
        sess_data_t       meas_results;   // (could be expanded)
        u_int32_t         ops;            // specific operation
} sess_stop_pdu_t;

void build_udp_prtopen_msg(fasp_session_t *xsess, unsigned char *pdu, int *len);

void build_pmtu_brtt_probe_msg(fasp_session_t *xsess, unsigned char *pdu, int tick, int *len);

void build_bw_probe_msg(fasp_session_t *xsess, unsigned char *pdu);

void build_sess_stop_msg(fasp_session_t *xsess, unsigned char *pdu, int *len);

int parse_udp_prtopen_msg(fasp_session_t *xsess, unsigned char *pdu);

int parse_pmtu_brtt_probe_msg(fasp_session_t *xsess, unsigned char *pdu, unsigned *pmtu, unsigned *t);

int parse_and_proc_bw_probe_msg(fasp_session_t *xsess, unsigned char *pdu);

int parse_sess_stop_msg(fasp_session_t *xsess, unsigned char *pdu);

#endif

