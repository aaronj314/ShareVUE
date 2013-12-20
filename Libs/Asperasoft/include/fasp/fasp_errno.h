/*
 * fasp_errno.h
 *
 * Aspera Inc.
 *
 */

#ifndef __AS_FASP_ERRNO_H__
#define __AS_FASP_ERRNO_H__

typedef enum _fasp_errno_e {

    e_err_success = 0,

    /* Open Session */
    e_err_bad_version = 1,
    e_err_bad_protocol = 2,
    e_err_targetdir_set_failed = 3,
    e_err_targetdir_check_failed = 4,
    e_err_incompat_mod_proto_vers = 5,
    e_err_incompat_pipeline_depth = 6,

    /* UDP Session INIT */
    e_err_sess_stopped = 7,
    e_err_connect_sock = 8,	
    e_err_send_stop = 9,
    e_err_recv_stop = 10,
    e_err_c_noresp = 11,
    e_err_s_noresp = 12,
    e_err_unconcluded_pmtu_brtt = 13,
    e_err_invalid_pmtu_brtt = 14,
    e_err_unmatched_tl = 15,
    e_err_unconcluded_bw = 16,
    e_err_invalid_bw = 17,

    /* Data session */
    e_err_ds_conn_lost = 18,
    e_err_peer_aborted_sess = 19,
    e_err_ds_proto_magic_mismatch = 20,
    e_err_ds_proto_pdutype_invalid = 21,
    e_err_ds_proto_msg_toosmall = 22,
    e_err_ds_proto_msg_toobig = 23,

    /* Internal errors */
    e_err_internal_disk_thread = 24,
    e_err_internal_ring = 25,
    e_err_internal_out_of_mem = 26,

    /* Session (sess) & Data Transfer (xfer) errors from FASP 1.3 */
                                    // old: FASP_SUCCESS
    e_err_sess_other = 27,          // old: FASP_TRANSFER_ERROR
    e_err_xfer_other = 28,          // old: FASP_SESSION_ERROR
                                    // old: FASP_TERMINAL_ERROR         (unused)
    e_err_sess_internal = 29,       // old: FASP_INTERNAL_ERROR
                                    // old: FASP_TRANSFER_SAME_LIC      (unused)
                                    // old: FASP_TRANSFER_BW_EXCEEDED   (unused)
                                    // old: FASP_TRANSFER_TIMEOUT       (unused)
    e_err_sess_conn_tmout = 30,     // see below: old: FASP_CONNECTION_TIMEOUT
                                    // NOTE:conn_tmout used in FASP 1.x only
                                    // old: FASP_CONNECTION_ERROR       (unused)
    e_err_sess_rex_send = 31,       // old: FASP_REX_SEND_ERROR
    e_err_sess_stats_send = 32,     // old: FASP_STATS_SEND_ERROR
    e_err_sess_reception = 33,      // old: FASP_RECEPTION_ERROR
                                    // old: FASP_SSHD_ERROR incompatsshd(unused)
    e_err_xfer_external_abort = 34, // old: FASP_TRANSFER_EXTERNAL_ABORT
    e_err_xfer_transfer_tmout = 35, // old: FASP_DATA_TRANSFER_TIMEOUT
    e_err_sess_transfer_tmout = 36, // new:
                                    // old: FASP_DATA_TRANSFER_ERROR    (unused)
    e_err_xfer_test_internal_abort_err = 37, // old: FASP_TEST_ERROR

    /* License errors from FASP 1.3 */
    e_err_lic_read = 38,            // old: LICENSE_READ_ERROR
    e_err_lic_expired = 39,         // old: LICENSE_EXPIRED
    e_err_lic_illegal = 40,         // old: LICENSE_ILLEGAL
    e_err_lic_bw_exceeded = 41,
    e_err_lic_duplicate = 42,

    /* Socket option errors from FASP 1.3 */
    e_err_sock_addrinfo = 43,       // old: SOCKET_ADDRINFO_ERROR
    e_err_sock_set_reuse = 44,      // old: SOCKET_SET_REUSE_ERROR
    e_err_sock_recvbuf = 45,        // old: SOCKET_RECVBUF_ERROR
    e_err_sock_sendbuf = 46,        // old: SOCKET_SENDBUF_ERROR
    e_err_sock_bind = 47,           // old: SOCKET_BIND_ERROR
    e_err_sock_create = 48,         // old: SOCKET_CREATE_ERROR

    /* Resource errors from FASP 1.3 */
                                    // old: RES_MEM_ALLOC_ERROR         (unused)
                                    // old: RES_THREAD_CREATE_ERROR     (unused)
    e_err_resrc_disk_buf = 49,      // old: RES_DISK_ERROR

    /* Error codes mapped to system errno */
    e_err_no_such_file = 50,             // ENOENT
    e_err_no_perms = 51,                 // EACCES or EPERM
    e_err_no_space_left = 52,            // ENOSPC
    e_err_not_dir = 53,                  // ENOTDIR
    e_err_is_dir = 54,                   // EISDIR
    e_err_file_table_overflow = 55,      // ENFILE
    e_err_too_many_files = 56,           // EMFILE
    e_err_file_too_big = 57,             // EFBIG
    e_err_read_only_fs = 58,             // EROFS

    /* IO errors */
    e_err_disk_read = 59,
    e_err_disk_write = 60,


    /* command line source/target errors */
    e_err_srclist_count_invalid = 61,
    e_err_srclist_not_specified = 62,
    e_err_srcpath_stat_failed = 63,

    e_err_dstpath_does_not_preexist = 64,
    e_err_dstpath_is_not_dir = 65,
    e_err_dstpath_dir_create_failed = 66,
    

    /* unknown/untranslated system errno */
    e_err_untranslated_syserrno = 67,

    /* more data session errnos */
    e_err_user_aborted_sess = 68,

    /* fasp_ds result errnos */
    e_err_ds_resp_unknown = 69,    // corres to FASP_DATASESS_RESP_UNKNOWN
    e_err_ds_resp_err_other = 70,  // corres to FASP_DATASESS_RESP_ERROR_OTHER
    /* use e_err_no_perms above */ // corres to FASP_DATASESS_RESP_ERROR_EACCES
    e_err_ds_resp_err_eexist = 71, // corres to FASP_DATASESS_RESP_ERROR_EEXIST
    e_err_ds_resp_err_aspx = 72,   // corres to FASP_DATASESS_RESP_ERROR_ASPX

    e_err_mgmt_auth_refused = 73,
    e_err_mgmt_conn_lost = 74,
    e_err_mgmt_auth_timeout = 75,

    e_err_had_file_errors = 76,
    e_err_disallowed_path = 77,
    e_err_filename_too_long = 78,
    e_err_not_regular_file = 79,
    e_err_lic_keyinvalid = 80,
    
    /* fasp virtual link related errnos */
    e_err_vlink_init_err = 81,
    e_err_vlink_start_err = 82, 

    e_err_file_encryption_err = 83,

    e_err_dstpath_invalid = 84,

    e_err_config_file_not_found = 85,
    e_err_config_file_invalid = 86,

    e_err_file_decryption_pass = 87,

    /* Docroot */
    e_err_docroot_invalid = 88,

    e_err_ssh_auth_failed = 89,
    
    e_err_max_num

} fasp_errno_e;

extern char *fasp_errno2str(fasp_errno_e e);

extern int syserrno2fasperr(int e);
extern int fasperrno2syserr(int e);

extern int fasp_error_may_fallback(int e);

struct fasp_session_t;

extern int fasp_error(struct fasp_session_t* sess, fasp_errno_e errcode,
    char const *format, ...);

#endif
