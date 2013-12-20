#ifndef _FASP_TLV_H_
#define _FASP_TLV_H_


#define FASP_OPT_MAX_SZ 65000   // Max size of FASP options

/*
 * FASP protocol option TLV types (T)
 */
#define FASP_OPT_UNUSED                 0x00

#define FASP_SESS_OPENSESS_VER          0x01
#define FASP_SESS_UUID                  0x02
#define FASP_SESS_ID                    0x03
#define FASP_SESS_SIZE_ID               0x04
#define FASP_SESS_ERROR_UNKNOWN_TYPE    0x05
#define FASP_SESS_LOCAL_USER            0x06
#define FASP_SESS_LOGIN_USER            0x07
#define FASP_SESS_TOKEN                 0x08
#define FASP_SESS_COOKIE                0x09
#define FASP_SESS_CIPHER                0x0a
#define FASP_SESS_DGRAM_SIZE            0x0b
/* #define FASP_SESS_DGRAM_BACK_SIZE       0x0c */
#define FASP_SESS_USER_STR              0x0d
#define FASP_SESS_VERBOSE               0x0e
#define FASP_SESS_FILE_PASS_STRENGTH    0x0f

#define FASP_SESS_RATE_POLICY           0x10
#define FASP_SESS_RATE_TARGET           0x11
#define FASP_SESS_RATE_MIN              0x12
#define FASP_SESS_RATECAP_POLICY        0x13
#define FASP_SESS_RATECAP_TARGET        0x14
#define FASP_SESS_RATECAP_MIN           0x15
#define FASP_SESS_RATE_TPERC            0x16
#define FASP_SESS_RATE_MPERC            0x17
#define FASP_SESS_RATE_QWEIGHT          0x18
#define FASP_SESS_PRIORITY              0x19
#define FASP_SESS_RATE_POLICY_LOCK      0x1a
#define FASP_SESS_RATE_PRIORITY_LOCK    0x1b
#define FASP_SESS_RATE_MIN_LOCK         0x1c
#define FASP_SESS_RATE_TARGET_LOCK      0x1d

#define FASP_SESS_SEC_CIPHER            0x21
#define FASP_SESS_SEC_HEADER_KEY        0x23 
#define FASP_SESS_SEC_KEY               0x24 
#define FASP_SESS_SEQ_NUM_SEND          0x25
#define FASP_SESS_SEQ_NUM_RECV          0x26
#define FASP_SESS_CTRL_HMAC_ALG         0x27
#define FASP_SESS_MAC_KEY               0x28

#define FASP_SESS_LIC_VER               0x29
#define FASP_SESS_LIC_PRODUCT           0x2a
#define FASP_SESS_LIC_ID                0x2b
#define FASP_SESS_LIC_SYS_ID            0x2c
#define FASP_SESS_AS_OS                 0x2d
#define FASP_SESS_AS_VERSION            0x2e
#define FASP_SESS_LIC_TERMS             0x2f

#define FASP_SESS_UDPINI_VER            0x30
#define FASP_SESS_IPVER                 0x31
#define FASP_SESS_LOCAL_IP              0x32
#define FASP_SESS_PEER_IP               0x33
#define FASP_SESS_UDP_PORT              0x34
#define FASP_SESS_RETRY_TIMEOUT         0x35

#define FASP_SESS_BWMEAS_VER            0x36
#define FASP_SESS_BWMEAS_OP             0x37
#define FASP_SESS_BWMEAS_PEER_OP        0x38 //SS: do we need peer op?
#define FASP_SESS_BWMEAS_TL             0x39
#define FASP_SESS_BWMEAS_OBS_LEN        0x3a
#define FASP_SESS_BWMEAS_PROBE_SIZE     0x3b
#define FASP_SESS_BWMEAS_PROBE_RATE     0x3c
#define FASP_SESS_BWMEAS_PRESETBW       0x3d

#define FASP_SESS_DATA_VER              0x40
#define FASP_SESS_DATA_OP               0x41
#define FASP_SESS_DATA_SRCLIST          0x42
#define FASP_SESS_DATA_DST              0x43
#define FASP_SESS_DATA_DST_MUSTBEDIR    0x44
#define FASP_SESS_DATA_DST_PREEXISTS    0x45
#define FASP_SESS_DATA_CIPHER           0x46
#define FASP_SESS_DATA_RESUME           0x47
#define FASP_SESS_DATA_CREATEPOLICY     0x48
#define FASP_SESS_DATA_PIPELINE_DEPTH   0x49
#define FASP_SESS_DATA_MAX_REX          0x4a

#define FASP_SESS_EXCLUDE_PATTERN       0x4b
#define FASP_SESS_CLUSTER_NUM_NODES     0x4c
#define FASP_SESS_CLUSTER_NODE_ID       0x4d
#define FASP_SESS_DATA_OVERWRPOLICY     0x4e
#define FASP_SESS_FALLBACK_PROTOCOL     0x4f

#define FASP_SESS_RESULT_ERRCODE        0x50
#define FASP_SESS_RESULT_ERRSTR         0x51
#define FASP_SESS_RESULT_RTT            0x52
#define FASP_SESS_RESULT_REXRTT         0x53
#define FASP_SESS_RESULT_REXBLKS        0x54
#define FASP_SESS_RESULT_TOTBLKS        0x55
#define FASP_SESS_RESULT_CTLMSGS_SENT   0x56
#define FASP_SESS_RESULT_CTLMSGS_RCVD   0x57
#define FASP_SESS_RESULT_REXREQS_SENT   0x58
#define FASP_SESS_RESULT_REXREQS_RCVD   0x59

#define FASP_CTL_COMP_NET_TICK          0x60
#define FASP_CTL_COMP_DSID_ACKVEC       0x61
#define FASP_CTL_COMP_DSID_ACKVEC_ACK   0x62
#define FASP_CTL_COMP_RATEPARAMS        0x63
#define FASP_CTL_COMP_RATEPARAMS_ACK    0x64
#define FASP_CTL_COMP_RATEADAPT         0x65
#define FASP_CTL_COMP_KEEPALIVE         0x66
#define FASP_CTL_COMP_VLINK             0x67
#define FASP_CTL_COMP_JOBSIZE           0x68
#define FASP_CTL_COMP_JOBSIZE_ACK       0x69

#if 0
#define FASP_STATS_REXINFO              0x6a
#define FASP_STATS_RATEINFO             0x6b
#define FASP_STATS_BLOCKINFO            0x6c
#define FASP_STATS_XFER                 0x6d
#endif

#define FASP_TRANSFER_BYTES_PROG        0x70
#define FASP_FILE_BYTES_PROG            0x71
#define FASP_DATAXFER_USEC_ELAPSED      0x72

#define FASP_DS_STATS_SRC_ARGS_SCANS_ATTEMPTED     0x80
#define FASP_DS_STATS_SRC_ARGS_SCANS_COMPLETED     0x81
#define FASP_DS_STATS_SRC_PATH_SCANS_ATTEMPTED     0x82
#define FASP_DS_STATS_SRC_PATH_SCANS_FAILED        0x83
#define FASP_DS_STATS_SRC_PATH_SCANS_IRREG_SKIPPED 0x84
#define FASP_DS_STATS_SRC_PATH_EXCLUDED            0x85
#define FASP_DS_STATS_SRC_DIR_SCANS_COMPLETED      0x86
#define FASP_DS_STATS_SRC_FILE_SCANS_COMPLETED     0x87
#define FASP_DS_STATS_DIR_CREATES_ATTEMPTED        0x88
#define FASP_DS_STATS_DIR_CREATES_FAILED           0x89
#define FASP_DS_STATS_DIR_CREATES_PASSED_EXISTED   0x8a
#define FASP_DS_STATS_FILE_TRANSFERS_ATTEMPTED     0x8b
#define FASP_DS_STATS_FILE_TRANSFERS_FAILED        0x8c
#define FASP_DS_STATS_FILE_TRANSFERS_PASSED        0x8d
#define FASP_DS_STATS_SRC_BYTES_XFER_DONE          0x8e
#define FASP_DS_STATS_FILE_TRANSFERS_NOXFER        0x8f

#define FASP_SESS_VLINK_ENABLED         0x90
#define FASP_SESS_VLINK_ID              0x91
#define FASP_SESS_VLINK_SPEED           0x92
#define FASP_SESS_VLINK_QMAX            0x93
#define FASP_SESS_VLINK_QMIN            0x94
#define FASP_SESS_VLINK_K_IN            0x95
#define FASP_SESS_VLINK_K_OUT           0x96

#define FASP_SESS_XOPT_FLAGS            0x97
#define FASP_SESS_CALC_JOBSIZE          0x98

#endif /* _FASP_TLV_H_ */

