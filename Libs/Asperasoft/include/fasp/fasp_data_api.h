#ifndef _FASP_DATA_API_H_
#define _FASP_DATA_API_H_

extern int
start_data_transmitter(
    void *sess
);

extern int
stop_data_transmitter(
    void *sess
);

extern int
start_data_receiver(
    void *sess
);

extern int
stop_data_receiver(
    void *sess
);

extern int
fasp_xfer_abort_errcode(
    int errcode
);

extern void
fasp_sess_errset(
    void *sess,
    int errcode,
    const char *errstr
);

#endif /* _FASP_DATA_API_H_ */

