#ifndef _FASP_VERSION_H_
#define _FASP_VERSION_H_
/*
 * This documents the FASP modules version numbers and API.
 */

#include <utils/src/astypes.h>

#define BUILD_ID  0x19000000                /* Upper 2bytes = 1.9.00 */

#if 0   /* FOR HISTORICAL INTEREST */

/* 
 * In the initial beta, we just force version changes based on the beta
 * build id itself.  This can be improvised later.
 */
#define MOD_ID_OPEN_SESSION              ((int)'O' << 8)
#define VERS_OPEN_SESSION_SSH_V2         ((BUILD_ID | MOD_ID_OPEN_SESSION) + 23)
    /*
     * Change History:
     * 1) VERS_OPEN_SESSION_SSH_V1 was changed from +1 to +11 when 3 tlv tags
     *    were removed and various TLV tags were re-numbered.  This will ensure
     *    that compatible version are used during testing, and will also
     *    serve as an internal test case for testing version mismatch checking
     * 2) VERS_OPEN_SESSION_SSH_V2 changed from +2 to +21 for new tlv tags
     *    appropriate to CFB-MAC encryption.
     * 3) VERS_OPEN_SESSION_SSH_V2 changed to add remaining tags that were
     *    being passed to the remote invocation on the command line: udp port,
     *    max rex, verbosity, user string.
     * 4) VERS_OPEN_SESSION_SSH_V2 -> 23 to send/recv 64-bit rate values.
     */

#define MOD_ID_UDP_SESSION               ((int)'U' << 8)
#define VERS_UDP_SESSION_CLIENTSERVER_V2 ((BUILD_ID | MOD_ID_UDP_SESSION) + 4)
    /*
     * Change History:
     * 1) VERS_UDP_SESSION_CLIENTSERVER_V2 was changed from +3 to +4 when 
     *    the defines for PDU types were modified.
     */
     

#define MOD_ID_BWMEAS                    ((int)'B' << 8)
#define VERS_UDP_BWMEAS_V2               ((BUILD_ID | MOD_ID_BWMEAS) + 2)

#define MOD_ID_DATA_SESSION              ((int)'D' << 8)
#define VERS_DATA_SESSION_V2             ((BUILD_ID | MOD_ID_DATA_SESSION) + 41)
    /*
     * Change History:
     * 1) VERS_DATA_SESSION_V2 was changed from +2 to +21 when file_name_len
     *    was added to DS request.
     * 2) VERS_DATA_SESSION_V2 was changed from +21 to +22 when file_errnostrlen
     *    and file_errnostr were added to DS response.
     * 3) VERS_DATA_SESSION_V2 changed from +22 to +23 when the encryption 
     *    scheme ECB + MAC-MD5 was replaced with CFB-MAC.
     * 4) VERS_DATA_SESSION_V2 changed from +23 to +24 to indicate difference
     *    in control pdus (RATEPARAMS_CTL, RATEADAPT_CTL, RATEPARAMS_ACK,
     *    DSID_ACKVEC_ACK).
     * 5) VERS_DATA_SESSION_V2 changed from +24 to +25 when REX request pdu 
     *    format was changed.
     * 6) VERS_DATA_SESSION_V2 changed from +25 to +26 when fasp session 
     *    statistics pdu wire format was changed for forward compatibility
     *    by adding num_xfer_stats field.  In future, the statistics pdu
     *    might carry a variable number of xfer_stats (as opposed to
     *    pipeline depth, i.e. num_xfer_stats <= pipeline depth).
     * 7) VERS_DATA_SESSION_V2 changed from +26 to +27 when fasp session
     *    statistics pdu wire format was changed to eliminate the
     *    'unused', 'unused2', and 'target_rate' fields.
     * 8) VERS_DATA_SESSION_V2 changed from +27 to +28 when fasp control
     *    pdu (udp) wire format was changed to add tag & length fields to
     *    NetTickReq, DSID_AckVec, and DSID_AckVec components, such that 
     *    all comps are now in TLV format.
     *    Rename FASP_OPT_RATExxx tags to FASP_CTL_COMP_RATExxx, and 
     *    renumber these.
     *    Rename FASP_OPT_STATS_xxx tags to FASP_STATS_xxx, and renumber these.
     * 9) VERS_DATA_SESSION_V2 -> 29 when elapsed time (usec) became 64 bits.
     * 10)VERS_UDP_SESSION_CLIENTSERVER_V2 ->3, VERS_UDP_BWMEAS_V1 -> 2,
     *    VERS_DATA_SESSION_V2 -> 30 to send/recv 64-bit rate values.
     * 11)VERS_DATA_SESSION_V2 changed from +30 to +31 when fasp ds 
     *    Pipeline Depth was changed from 24 to 32.
     * 12)VERS_DATA_SESSION_V2 changed from +31 to +32 when fasp ds source
     *    statistics were added to close-session PDU and TAGs for 
     *    FASP_SESS_DATA_SRCLST and FASP_SESS_DATA_DST were changed.
     *    Also changed other tag values.
     * 13)VERS_DATA_SESSION_V2 was changed from +32 to +33 when fasp DS 
     *    request & response pdus were enhanced to carry a VLF component
     *    (variable length fields).  This can be used to exchange extended
     *    attributes (in future, whilst maintaining backward compat).
     * 14)VERS_DATA_SESSION_V2 was changed from +33 to +34 when 'unused1'
     *    field in DS response pdu was replaced by 'req2rsp_latency_usec',
     *    and two new optional vlf/tlv fields were added to the ds response
     *    pdu (sink latency instrumentation).
     * 15)VERS_DATA_SESSION_V2 was changed from +34 to +35 when format of
     *    RateParams control pdu was changed.
     * 16)VERS_DATA_SESSION_V2 was changed from +35 to +36 when format of
     *    Statistics pdu was changed to include session level 
     *    transfer_bytes_prog, file_bytes_prog, data_xfer_usec_elapsed.
     * 17)VERS_DATA_SESSION_V2 was changed from +36 to +37 when tags for
     *    open session request/responses were changed due to addition
     *    of FASP_SESS_DATA_DST_PREEXISTS tag for the 
     *    'ascp srcdir targetdoesnotexist' case.
     * 18)VERS_DATA_SESSION_V2 was changed from +37 to +38 when tags for
     *    source ds statistics were changed due to reformatting of source
     *    ds statistics.
     * 19)VERS_DATA_SESSION_V2 was changed from +38 to +39 when unneeded/unused
     *    fields (blocks_wrleft and time_since_start) were removed from the 
     *    statistics_pdu_xfer_t.  This reduces the per xfer entry in the
     *    statistics pdu from 24 down to 12 bytes.  For a full pipeline
     *    this results in savings of (32 * 12) = 384 bytes.
     * 20)VERS_DATA_SESSION_V2 was changed from +39 to +40 when the defines 
     *    for PDU types were modified.
     * 21)VERS_DATA_SESSION_V2 changed +40 -> 41 when rtt was added
     *    to the session statistics updates.
     */
#endif

/*
 * Protocol component version numbers.
 *
 * All module protocol version numbers are a composite of major and minor 
 * numbers.  The major version number is encoded in the high 16-bits, and the
 * minor version number in the low 16-bits.  Implementations with identical
 * major version numbers are expected to interoperate with each other.
 * Implementations with identical major version numbers, but differing
 * minor numbers are expected to negotiate to scale down to a common
 * denominator to interoperate.
 *
 * The minor version number could be implemented as an index into some
 * form of a features-bitmap table.
 */

/*
 *  protocol versions
 */
#define VERS_OPEN_SESSION_MAJOR                 (0x0002)
#define VERS_OPEN_SESSION_MINOR                 (0x0002)
#define VERS_OPEN_SESSION_V2                    \
      ((VERS_OPEN_SESSION_MAJOR << 16) +        \
        VERS_OPEN_SESSION_MINOR)

/* 
 * On next version:
 *   - increase size of license TLVs to 32 bits.
 *   - add transaction cycle to determine whether source should compute csum
 */

/* History:
 *
 * VERS_OPEN_SESSION_MINOR == 0x0001: 
 * - Add XOPT_FLAG_COPY_SYMBOLIC_LINKS support
 * - Use efficient sparse-checksum method if peer knows it
 * VERS_OPEN_SESSION_MINOR == 0x0002:
 * - Accept server-side rate params in open session rsp 
 */

/* TCP or out-of-band session initiation protocol versions (bitmap) 
 */
#define VERS_OPEN_SESSION_OOB                    0x10000000  // UNUSED

/*
 * UDP session initiation protocol versions
 */
#define VERS_UDP_SESSION_CLIENTSERVER_MAJOR      (0x0002)
#define VERS_UDP_SESSION_CLIENTSERVER_MINOR      (0x0000)
#define VERS_UDP_SESSION_CLIENTSERVER_V2         \
      ((VERS_UDP_SESSION_CLIENTSERVER_MAJOR << 16) + \
        VERS_UDP_SESSION_CLIENTSERVER_MINOR)

#define VERS_UDP_SESSION_PEERTOPEER_V2           0x00000020  // UNUSED

/*
 * Bandwidth Measurement protocol versions
 */
#define VERS_UDP_BWMEAS_MAJOR                    (0x0002)
#define VERS_UDP_BWMEAS_MINOR                    (0x0000)
#define VERS_UDP_BWMEAS_V2                       \
      ((VERS_UDP_BWMEAS_MAJOR << 16) +           \
        VERS_UDP_BWMEAS_MINOR)

/*
 * Data session/transfer protocol versions
 */
#define VERS_DATA_SESSION_MAJOR                  (0x0002)
#define VERS_DATA_SESSION_MINOR                  (0x0000)
#define VERS_DATA_SESSION_V2                     \
      ((VERS_DATA_SESSION_MAJOR << 16) +         \
        VERS_DATA_SESSION_MINOR)

#define PROTO_MAJOR_VER(proto_vers) (proto_vers >> 16)
#define PROTO_MINOR_VER(proto_vers) (proto_vers & 0xffff)


/*
 * Extern declarations.
 */
struct fasp_session_t;


extern void
proto_version_print(
    u_int32_t proto_vers,
    char *mod_name,
    char *role
);

extern void
proto_versions_print_all(
    struct fasp_session_t *s
);

extern int
proto_versions_compat(
    u_int32_t local_proto_ver,
    u_int32_t peer_proto_ver
);

extern int
proto_versions_compare(
    struct fasp_session_t *s
);

extern void
proto_versions_scaledown(
    struct fasp_session_t *s
);

#endif /* _FASP_VERSION_H_ */

