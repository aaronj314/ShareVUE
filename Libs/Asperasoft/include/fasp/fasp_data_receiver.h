#ifndef _FASP_DATA_RECEIVER_H_
#define _FASP_DATA_RECEIVER_H_ 

extern int
data_reception_add_xfer(
    fasp_session_t *sess,
    transfer_t *xfer
);

extern int
__start_data_receiver(
    fasp_session_t *sess
);

extern int
__stop_data_receiver(
    fasp_session_t *sess
);

extern int
check_xfer_recv_done(
    fasp_session_t *sess,
    transfer_t *xfer
);

extern void
data_rcvr_xfer_abort_extnl(
    fasp_session_t *sess,
    transfer_t *xfer
);

extern void
data_rcvr_xfer_abort_allblkswritten(
    fasp_session_t *sess,
    transfer_t *xfer
);

#endif /* _FASP_DATA_RECEIVER_H_ */

