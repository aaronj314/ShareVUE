#ifndef _FASP_DS_API_H_
#define _FASP_DS_API_H_

#include <utils/src/asutils.h>

extern int g_standalone_test;

#define FASP_DATASESS_PIPELINE_DEPTH  32

struct fasp_datasess_t;
struct fasp_session_t;

extern void
source_work(
    struct fasp_session_t *faspsess,
    as_socket_t ctlin_fd,
    as_socket_t ctlout_fd,
    char **srclist
);

extern void
source_work_abort(
    void *faspsess,
    int reason
);

extern void
source_foreach_running(
    void (* func)(void *data, void *arg1, void *arg2),
    void *arg1,
    void *arg2
);

extern void *
source_ds_data_transmitted_lastblock(
    void *ds
);

extern void
source_ds_data_transmission_stopped(
    void *ds
);

extern int
source_readyq_maio_rd_issue(
    unsigned int bl_count
);

extern int
source_net_progress(
    void
);

extern int
source_local_progress(
    void
);

extern void
source_sess_stats_log(
    void
);

extern void
sink_work(
    struct fasp_session_t *faspsess,
    as_socket_t ctlin_fd,
    as_socket_t ctlout_fd,
    void *destinfo
);

extern void
sink_work_abort(
    void *faspsess,
    int reason
);

extern void
sink_foreach_running(
    void (* func)(void *data, void *arg1, void *arg2),
    void *arg1,
    void *arg2
);

extern int
sink_net_progress(
    void
);

extern int
sink_local_progress(
    void
);

extern void
sink_preserve_timestamp(
    struct fasp_datasess_t *ds
);

extern void
sink_sess_stats_log(
    void
);


/*
 * Instrumentation API.
 */
extern int
fasp_ds_age(
    void *ds
);

extern int
source_work_age(
    void
);

extern int
sink_work_age(
    void
);

extern int
source_running_age(
    void *ds
);

extern int
source_lastblock_age(
    void *ds
);

extern int
sink_running_age(
    void *ds
);

extern void
fasp_ds_enable_qdumps(
    void
);

extern void
fasp_ds_disable_qdumps(
    void
);

extern void
source_dump_queues(
    void
);

extern void
sink_dump_queues(
    void
);

#endif /* _FASP_DS_API_H_ */

