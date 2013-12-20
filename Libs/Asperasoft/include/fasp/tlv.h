/*
 * tlv.h
 *
 * TLV manipulation routines
 *
 * A TLV is a char[] with the format: 
 *  ------------------------------------------------------------------------
 * |  Type [8/16 bits]  |  Length [8/16 bits]  |  Value [Length-2/4 bytes]  |
 *  ------------------------------------------------------------------------
 *
 * Convention:
 *     If MSB of Type is 1: Type   - 16 bits
 *                          Length - 16 bits
 *     If MSB of Type is 0: Type   - 8 bits
 *                          Length - 8 bits
 *
 * TLV are part of a FASP protocol option. A protocol option is a 
 * piece of data appended to any FASP PDU. The length of options is
 * included in the FASP PDU length field.
 *
 */

#ifndef TLV_H
#define TLV_H

#include <utils/src/astypes.h>

/* Forward declarations */
struct transfer_t;
struct fasp_session_t;

#define TLV_HDR_SZ      2       // Size of TLV header. Also min size of TLV

typedef union { u_int16_t i; u_int8_t b[2]; } union16;
typedef union { u_int32_t i; u_int8_t b[4]; } union32;
typedef union { u_int64_t i; u_int8_t b[8]; } union64;

#define EXTRACT16(v, p) do { \
        union16 vu; vu.b[0] = p[0]; vu.b[1] = p[1]; v = ntohs(vu.i); p+=2; \
    } while (0)
#define EXTRACT32(v, p) do { \
        union32 vu; memcpy(vu.b,p,4); v = ntohl(vu.i); p+=4; \
    } while (0)
#define EXTRACT64(v, p) do { \
        union64 vu; memcpy(vu.b,p,8); v = as_ntohll(vu.i); p+=8; \
    } while (0)

#define GETVAL8(v) \
    do { u_int8_t uv; offset = tlv_getval(offset, &uv); v = uv; } while (0)
#define GETVAL16(v) \
  do { union16 uv; offset=tlv_getval(offset, uv.b); v=ntohs(uv.i); } while (0)
#define GETVAL32(v) \
  do { union32 uv; offset=tlv_getval(offset, uv.b); v=ntohl(uv.i); } while (0)
#define GETVAL64(v) \
  do { union64 uv; offset=tlv_getval(offset, uv.b); v=as_ntohll(uv.i); } while (0)
#define GETVALSTR(v) \
    do { v = malloc(l); offset = tlv_getval(offset, (u_int8_t*) v); } while (0)

#define APPEND16(p, v) \
    do { union16 vu; vu.i = htons(v); memcpy(p,vu.b,2); p+=2; } while (0)
#define APPEND32(p, v) \
    do { union32 vu; vu.i = htonl(v); memcpy(p,vu.b,4); p+=4; } while (0)
#define APPEND64(p, v) \
    do { union64 vu; vu.i = as_htonll(v); memcpy(p,vu.b,8); p+=8; } while (0)


/*
 * TLV routines
 */
extern u_int8_t *
tlv_append(
    u_int8_t *tlv_buf,
    u_int32_t tlv_buf_len,
    u_int16_t T,
    u_int16_t L,
    u_int8_t *V
);
extern u_int8_t *
tl_append(
    u_int8_t *tlv_buf,
    u_int32_t tlv_buf_len,
    u_int16_t T,
    u_int16_t L
);
extern void 
tlv_peek(
    u_int8_t *tlv_buf,
    u_int16_t *T,
    u_int16_t *L
);
extern u_int8_t *
tlv_getval(
    u_int8_t *tlv_buf,
    u_int8_t *V
);
extern
u_int8_t *
tlv_getnval(
    u_int8_t *tlv_buf,
    u_int8_t *V,
    u_int32_t N
);

/*
 * FASP option construction
 */
extern void
extract_raw_uuid(char const* uuid, unsigned char* raw_uuid);

extern void 
build_tlv_xferstats(
    u_int8_t *tlv_buf,
    struct transfer_t *xfer
);
extern void
build_tlv_rexinfo(
    u_int8_t *tlv_buf
);
extern void 
build_tlv_rateinfo(
    u_int8_t *tlv_buf
);
extern void
build_tlv_blockinfo(
    u_int8_t *tlv_buf
);
extern int
build_tlv_rateparams(
    u_int8_t *tlv_buf,
    struct fasp_session_t *sess
);
extern int
build_tlv_rateadapt(
    u_int8_t *tlv_buf,
    struct fasp_session_t *sess
);
extern int
build_tlv_rateparams_ack(
    u_int8_t *tlv_buf, 
    struct fasp_session_t *sess
);
extern int
build_tlv_keepalive(
    u_int8_t *tlv_buf, 
    struct fasp_session_t *sess
);

int
build_tlv_jobsize(
    u_int8_t *tlv_buf,
    struct fasp_session_t *sess);

int
build_tlv_jobsize_ack(
    u_int8_t *tlv_buf,
    struct fasp_session_t *sess);

extern int
build_tlv_sess(
    u_int8_t *tlv_buf,
    struct fasp_session_t *sess
);
extern int
build_tlv_sess_close(
    u_int8_t *tlv_buf,
    struct fasp_session_t *sess
);

/*
 * FASP option parsing
 */
extern void
process_fasp_opt(
    struct fasp_session_t *sess, 
    u_int8_t *buf, 
    u_int16_t opt_len
);
extern void
process_fasp_opt_sess(
    struct fasp_session_t *sess,
    u_int8_t *buf,
    u_int16_t opt_len
);

#endif
