#ifndef _FASP_DATA_TRANSMITTER_H_
#define _FASP_DATA_TRANSMITTER_H_ 

extern int
data_transmission_add_xfer(
    fasp_session_t *sess,
    transfer_t *xfer
);

extern int
__start_data_transmitter(
    fasp_session_t *sess
);

extern int
__stop_data_transmitter(
    fasp_session_t *sess
);

extern void
data_xmtr_xfer_abort_extnl(
    fasp_session_t *sess,
    transfer_t *xfer
);

#endif /* _FASP_DATA_TRANSMITTER_H_ */

