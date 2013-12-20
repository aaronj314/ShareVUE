#ifndef _FASP_DS_EVENT_Q_H
#define _FASP_DS_EVENT_Q_H

#include <ds/fasp_ds_queue.h>
#include <utils/src/asutils.h>

enum source_events_e {
    SOURCE_ITEM_XMIT = 1,                // evdata = ds
    SOURCE_ITEM_XMIT_ABORT = 2,          // evdata = ds
    SOURCE_ITEM_XMITED_LASTBLOCK = 3,    // evdata = ds
    SOURCE_ITEM_XMIT_STOPPED = 4,        // evdata = ds
    SOURCE_ITEM_NOXFER_DISP = 5,         // evdata = ds_noxfer
    SOURCE_ITEM_NOXFER_DISP_DONE = 6,    // evdata = ds_noxfer
    SOURCE_ITEM_LAST = 6,                // max delimiter
};

enum sink_events_e {
    SINK_ITEM_RECV = 1,                  // evdata = ds
    SINK_ITEM_RECV_ABORT = 2,            // evdata = ds
    SINK_ITEM_ALLBLOCKS_WRITTEN = 3,     // evdata = ds
    SINK_ITEM_RECV_STOPPED = 4,          // evdata = ds
    SINK_ITEM_NOXFER_DISP = 5,           // evdata = ds_noxfer
    SINK_ITEM_NOXFER_DISP_DONE = 6,      // evdata = ds_noxfer
    SINK_ITEM_LAST = 6,                  // max delimiter
};

typedef struct _event_q {
#ifndef DS_TESTER
    as_mutex_t mutex;
#endif
    int       next_evid;
    struct _queue req_q;
    struct _queue rsp_q;
} event_q_t;

typedef struct _event {
    struct _queue_elem elem;
    int   evtype;   
    int   evid;
    void *evdata;
} event_t;

#define EVENTQ_REQ_QLEN(evq) ((evq)->req_q.elem_count)
#define EVENTQ_RSP_QLEN(evq) ((evq)->rsp_q.elem_count)

/*
 * Extern declarations.
 */
extern int
eventq_init(
    event_q_t *evq
);

extern void
eventq_destroy(
    event_q_t *evq
);

extern const char *
eventq_source_evname(
    enum source_events_e ev
);

extern const char *
eventq_sink_evname(
    enum sink_events_e ev
);

extern unsigned int
eventq_tentative_req_qlen(
    event_q_t *evq
);

extern int
eventq_req_qlen(
    event_q_t *evq
);

extern int
eventq_req_post(
    event_q_t *evq,
    event_t *ev
);

extern event_t *
eventq_req_fetch(
    event_q_t *evq
);

extern event_t *
check_req_event(
    event_q_t *evq
);

extern unsigned int
eventq_tentative_rsp_qlen(
    event_q_t *evq
);

extern unsigned int
eventq_rsp_qlen(
    event_q_t *evq
);

extern int
eventq_rsp_post(
    event_q_t *evq,
    event_t *ev
);

extern event_t *
eventq_rsp_fetch(
    event_q_t *evq
);

extern event_t *
check_rsp_event(
    event_q_t *evq
);

#endif /* _FASP_DS_EVENT_Q_H */

