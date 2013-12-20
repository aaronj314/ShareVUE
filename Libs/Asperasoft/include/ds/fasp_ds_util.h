
#ifndef _FASP_DS_UTIL_H_
#define _FASP_DS_UTIL_H_
#include <fasp/fasp_errno.h>

extern char *
datasess_resp_result2str(
    int32_t result
);

extern fasp_errno_e
datasess_resp_result2fasperrno(
    int32_t result
);

extern char *
datasess_pdutype2str(
    char ds_pdu_type
);

extern char *
datasess_sesserr_reas2str(
    int reason
);

extern char *
datasess_errcode2str(
    int errcode
);

extern void
datasess_scratchpdu_reset(
    struct pdu_scratchbuf *psb
);

extern int
datasess_send_pdu(
    as_socket_t ctlout_fd,
    struct pdu_scratchbuf *psb
);

extern void
datasess_free(
    fasp_datasess_t *ds
);

extern void
datasess_cleanup(
    fasp_datasess_t *ds
);

extern int
compare_ds_id(
    void *ds,
    void *arg1,
    void *arg2
);

/*
 * Show PDU.
 */
extern void
show_pdu_dsreq(
    fasp_datasess_req_pdu_t *req
);
extern void
show_pdu_dsrsp(
    fasp_datasess_rsp_pdu_t *rsp
);
extern void
show_pdu_dserr(
    fasp_ds_dserr_pdu_t *dserr
);
extern void
show_pdu_sesserr(
    fasp_ds_sesserr_pdu_t *sesserr
);

/*
 * Instrumentation utility routines.
 */
extern u_int64_t
fasp_ds_timevaldiff(
    struct timeval *earlier,
    struct timeval *recent
);

#endif /* _FASP_DS_UTIL_H_ */


