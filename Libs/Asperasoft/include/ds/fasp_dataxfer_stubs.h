
#ifndef _FASP_DATAXFER_STUBS_H_
#define _FASP_DATAXFER_STUBS_H_

/*
 * Transmitter Start/Stop routines.
 */
extern int
start_data_transmitter(
    void *sess
);

extern int
stop_data_transmitter(
    void *sess
);

/*
 * Receiver Start/Stop routines.
 */
extern int
start_data_receiver(
    void *sess
);

extern int
stop_data_receiver(
    void *sess
);

#endif /* _FASP_DATAXFER_STUBS_H_ */

