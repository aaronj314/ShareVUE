
#ifndef _FASP_DS_ENCDEC_H_
#define _FASP_DS_ENCDEC_H_

#include <ds/fasp_ds_types.h>


/*
 * Extern declarations for PDU routines.
 */

extern int
enc_generic_pdu_hdr(
    void *faspsess,
    char *pdu_buf, 
    unsigned int pdu_buflen,
    char  type,
    short len,
    unsigned int *pdubuf_consumed                          /* output */
);
extern int
dec_generic_pdu_hdr(
    void *faspsess,
    char *pdu_buf, 
    unsigned int pdu_buflen,
    char *type,                                            /* output */
    short *len_of_pdu,                                     /* output */
    unsigned int *pdulen_consumed                          /* output */
);
extern int
enc_datasess_req_pdu(
    char  *pdu_buf,
    unsigned int pdu_buflen,
    fasp_datasess_req_pdu_t *req_pdu,
    unsigned int *len_encoded                              /* output */
);
extern int
dec_datasess_req_pdu(
    char *pdu_buf,
    unsigned int pdu_buflen,
    fasp_datasess_req_pdu_t *req_pdu,
    unsigned int *len_decoded                              /* output */
);
extern int
enc_datasess_rsp_pdu(
    char  *pdu_buf,
    unsigned int pdu_buflen,
    fasp_datasess_rsp_pdu_t *rsp_pdu,
    unsigned int *len_encoded                              /* output */
);
extern int
dec_datasess_rsp_pdu(
    char *pdu_buf,
    unsigned int pdu_len,
    fasp_datasess_rsp_pdu_t *rsp_pdu,
    unsigned int *len_decoded                              /* output */
);
extern int
enc_ds_sesserr_notfn_pdu(
    char  *pdu_buf,
    unsigned int pdu_buflen,
    fasp_ds_sesserr_pdu_t *sesserr_pdu,
    unsigned int *len_encoded                              /* output */
);
extern int
dec_ds_sesserr_notfn_pdu(
    char *pdu_buf,
    unsigned int pdu_len,
    fasp_ds_sesserr_pdu_t *sesserr_pdu,
    unsigned int *len_decoded                              /* output */
);
extern int
enc_ds_dserr_notfn_pdu(
    char  *pdu_buf,
    unsigned int  pdu_buflen,
    fasp_ds_dserr_pdu_t *error_pdu,
    unsigned int *len_decoded                              /* output */
);
extern int
dec_ds_dserr_notfn_pdu(
    char *pdu_buf,
    unsigned int pdu_len,
    fasp_ds_dserr_pdu_t *error_pdu,
    unsigned int *len_decoded                              /* output */
);
extern int
enc_datasess_pdu(
    void *faspsess,
    char type,
    char *pdu_buf,
    unsigned int pdu_buflen,
    void *pdu_struct,
    unsigned int *len_decoded                              /* output */
);
extern int
dec_datasess_pdu(
    void *faspsess,
    char *pdu_buf,
    unsigned int len_recvd,
    unsigned int *len_decoded,                             /* output */
    fasp_datasess_t *ds
);

#endif /* _FASP_DS_ENCDEC_H_ */

