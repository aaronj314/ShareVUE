#ifndef _FASP_EVENTS_API_H_
#define _FASP_EVENTS_API_H_

/*
 * Event Handlers @ source between source-ds and transmitter.
 */
extern int
source_drain_req_events(
    void
);

extern int
data_transmission_add_xfer(
    fasp_session_t *sess,
    transfer_t *xfer
);

extern int
source_data_transmitted_lastblock(
    void *sess,
    transfer_t *xfer
);

extern int
source_data_transmission_stopped(
    fasp_session_t *sess,
    transfer_t *xfer
);

/*
 * Event Handlers @ sink between sink-ds and receiver.
 */
extern int
sink_check_one_req_event(
    void
);

extern int
data_reception_add_xfer(
    fasp_session_t *sess,
    transfer_t *xfer
);

extern int
sink_data_reception_stopped(
    fasp_session_t  *sess,
    transfer_t      *xfer
);

extern void
sink_flush_req_events(
    void
);

/*
 * API for submitting allblocks written event to the receiver-data thread.
 */
extern int
sink_data_allblocks_written(
    fasp_session_t  *sess,
    transfer_t      *xfer
);


/*
 * API for instrumentation.
 */
extern void
source_ds_events_instru_init(
    fasp_session_t *sess
);

#endif /* _FASP_EVENTS_API_H_ */

