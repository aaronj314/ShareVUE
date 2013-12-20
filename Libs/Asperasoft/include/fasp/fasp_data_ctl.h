#ifndef _FASP_DATA_CTL_H_
#define _FASP_DATA_CTL_H_

#include <utils/src/asutils.h>

struct fasp_session_t;

#define CTLMSG_NETTICKREQ_IMMED_COUNT   (01)
#define CTLMSG_ACKVEC_IMMED_COUNT       (03)
#define CTLMSG_RATE_IMMED_COUNT         (03)

#define CTLMSG_ACKVEC_PERIOD_USEC       (  10000)          /* 10 millisec */
#define CTLMSG_RATEPARAMS_PERIOD_USEC   (1000000)          /*  1 sec */
#define CTLMSG_RATEADAPT_PERIOD_USEC    (1000000)          /*  1 sec */
#define CTLMSG_NETTICK_PERIOD_USEC      (100000)           /* 100 msec */
#define CTLMSG_VLINK_PERIOD_USEC        (0)                /*  always disabled */
#define CTLMSG_JOBSIZE_PERIOD_USEC      (1000000UL)        /* 1 sec */

/**
 * Data structure to set the frequency of various control message 
 * components.
 *
 */
typedef struct control_pdu_freq_t {

    u_int32_t period_net_tick_req;
    struct timeval tm_prev_net_tick_req;
    u_int32_t immed_net_tick_req;

    u_int32_t period_net_tick_rsp;
    struct timeval tm_prev_net_tick_rsp;
    u_int32_t immed_net_tick_rsp;
    u_int32_t always_net_tick_rsp;

    u_int32_t period_dsid_ackvec;
    struct timeval tm_prev_dsid_ackvec;
    u_int32_t immed_dsid_ackvec;

    u_int32_t immed_dsid_ackvec_ack; /* Used by transmitter */

    u_int32_t period_rateparams_update;
    struct timeval tm_prev_rateparams_update;
    u_int32_t immed_rateparams_update;

    u_int32_t period_rateadapt_update;
    struct timeval tm_prev_rateadapt_update;
    u_int32_t immed_rateadapt_update;

    u_int32_t period_vlink_update;
    struct timeval tm_prev_vlink_update;
    u_int32_t immed_vlink_update;

    u_int32_t immed_rateparams_ack;  /* Could be used by xmitter & recvr */

    u_int32_t immed_keepalive;       /* Could be used by xmitter & recvr */

    u_int32_t period_jobsize;               /* time interval to post jobsize */
    struct timeval tm_prev_jobsize_update;  /* timestamp of last jobsize post */
    u_int32_t retry_jobsize;                /* number of retries to publish jobsize */
    u_int32_t immed_jobsize_ack;            /* ack jobsize */

    int immed_flag;                  /* One or more of above immed got set */
    int periodic_ctlpdu;             /* CTL pdu needs to be sent periodically */
    u_int32_t sampling_period;       /* Sampling period for periodic pdus */
    struct timeval tm_next_pdu;      /* Est time when next pdu is to be sent */

} control_pdu_freq_t;


/**
 * Data structure to store control information.  
 *
 * This information is used to construct control messages.  Information 
 * retrieved from incoming control messages are stored here as well.
 *
 */
typedef struct control_t {
    u_int32_t       pkt_id_sent;
    u_int32_t       pkt_id_rcvd;

    u_int32_t       num_pkts_rcvd;

    u_int32_t       comps_sent;
    u_int32_t       comps_rcvd;
#define FASP_CTLMSG_COMP_NET_TICK        0x00000001
#define FASP_CTLMSG_COMP_DSID_ACKVEC     0x00000002
#define FASP_CTLMSG_COMP_RATEPARAMS_CTL  0x00000004
#define FASP_CTLMSG_COMP_RATEADAPT_CTL   0x00000008
#define FASP_CTLMSG_COMP_DSID_ACKVEC_ACK 0x00000010
#define FASP_CTLMSG_COMP_RATEPARAMS_ACK  0x00000020
#define FASP_CTLMSG_COMP_KEEPALIVE       0x00000040
#define FASP_CTLMSG_COMP_VLINK_CTL       0x00000080
#define FASP_CTLMSG_COMP_JOBSIZE         0x00000100
#define FASP_CTLMSG_COMP_JOBSIZE_ACK     0x00000200

    u_int32_t       sec_seqno;

    struct timeval  tm_prev_ctlpdu_sent;
    struct timeval  tm_prev_ctlpdu_rcvd;

    /*
     * Receiver (tick request sender) values.
     */
    u_int16_t       net_tick_req_sent; 
    u_int16_t       net_tick_rsp_rcvd;
    struct timeval  tm_net_tick_rsp_rcvd;
    u_int16_t       net_tick_rtt;

    /*
     * Transmitter (tick response sender) values.
     */
    u_int16_t       net_tick_req_rcvd;
    struct timeval  tm_net_tick_req_rcvd;
    u_int16_t       net_tick_rsp_sent;

    u_int32_t       dsid_ackvec_seqno_rcvd;
    u_int32_t       dsid_ackvec[FASP_DATASESS_PIPELINE_DEPTH]; // received

    /*
     * The dsid ackvec is maintained in host as well as network order
     * in the fasp_session_t structure.  The network order ackvec eliminates
     * building it once per ctl message (instead simply copy).
     */

    /*
     * Keepalive values.  Track 'sent', 'rcvd' sequence numbers.  Also
     * track value of 'rcvd' seqno when it was previously sampled.
     * If the 'rcvd' and 'rcvd_sampled' values are the same, it implies
     * that no keepalives were received during the sampling interval.
     */
    u_int32_t      keepalive_seqno_sent;
    u_int32_t      keepalive_seqno_rcvd;
    u_int32_t      keepalive_seqno_rcvd_sampled;

} control_t;


/**
 * Data structure to store control related statistics/instrumentation.  
 *
 * This information is for record-keeping and efficiency evaluation only.
 */
typedef struct control_stats_t {

    /*
     * DSID Ackvec component.
     */
    u_int32_t    DV_comps_sent;        // dsid ackvec comps sent
    u_int32_t    DV_comps_rcvd;        // dsid ackvec comps rcvd
    u_int32_t    DV_comp_dups_rcvd;    // duplicate dsid ackvec comps rcvd

    /*
     * DSID Ackvec ack component.
     */
    u_int32_t    DVack_comps_sent;     // dsid ackvec ACK comps sent
    u_int32_t    DVack_comps_rcvd;     // dsid ackvec ACK comps rcvd

    /*
     * RateParam component.
     */
    u_int32_t    RP_comps_sent;        // rate param comps sent
    u_int32_t    RP_comps_rcvd;        // rate param comps rcvd

    /*
     * RateParamAck component.
     */
    u_int32_t    RPack_comps_sent;     // pure rate param ack comps sent
    u_int32_t    RPack_comps_rcvd;     // pure rate param ack comps rcvd

    /*
     * RateAdapt component.
     */
    u_int32_t   RA_comps_sent;         // rate adapt comps sent
    u_int32_t   RA_comps_rcvd;         // rate adapt comps rcvd

    /* 
     * Virtual link component.
     */
    u_int32_t    VLINK_comps_sent;    // vlink swarm size comps sent
    u_int32_t    VLINK_comps_rcvd;    // vlink swarm size comps rcvd

    /*
     * Keepalive component.
     */
    u_int32_t    KA_comps_sent;        // keepalive comps sent
    u_int32_t    KA_comps_rcvd;        // keepalive comps rcvd

#define CTLSTAT_INCR(s,counter)  (((s)->control_stats.counter)++)
#define CTLSTAT(s,counter)       ((s)->control_stats.counter)
} control_stats_t;


#define TEST_CTLPDUS 0

#if TEST_CTLPDUS

#define NUM_FASPCTL_HIST_ENTS  10240

struct fasp_tick_histent_t {
    u_int64_t tstamp_msec;
    u_int16_t tick_val;
    u_int8_t  tick_type;
    u_int8_t  valid;
    u_int16_t rtt;
    u_int16_t unused;
};

struct fasp_tick_hist_t {
#define FASP_TICK_HIST_TAB_SIZ 102400
#define FASP_TICK_HIST_TAB_NAMELEN 40

    char tabname[FASP_TICK_HIST_TAB_NAMELEN];
    struct fasp_tick_histent_t tab[FASP_TICK_HIST_TAB_SIZ];
    u_int32_t next_ent;
    u_int32_t first_ent;
    struct timeval start_time;
};

struct fasp_tick_hist_t fasp_tick_hist;


#define FASP_TICK_HIST_INIT(namestr)                                        \
{                                                                           \
    struct timeval now;                                                     \
    strncpy(fasp_tick_hist.tabname, namestr, FASP_TICK_HIST_TAB_NAMELEN);   \
    fasp_tick_hist.tabname[FASP_TICK_HIST_TAB_NAMELEN - 1] = 0;             \
    as_gettimeofday(&now, NULL);                                            \
    fasp_tick_hist.start_time = now;                                        \
    memset(&fasp_tick_hist.tab[0], 0, sizeof(fasp_tick_hist.tab));          \
    fasp_tick_hist.first_ent = 0;                                           \
    fasp_tick_hist.next_ent = 0;                                            \
}

#define FASP_TICK_HIST_ADD(tickval, ticktype, rttval)                       \
{                                                                           \
    register int next = fasp_tick_hist.next_ent;                            \
    fasp_tick_hist.tab[next].tstamp_msec =                                  \
            get_usec_since(&fasp_tick_hist.start_time)/1000;                \
    fasp_tick_hist.tab[next].tick_val = tickval;                            \
    fasp_tick_hist.tab[next].tick_type = ticktype;                          \
    fasp_tick_hist.tab[next].rtt = rttval;                                  \
    fasp_tick_hist.tab[next].valid = 1;                                     \
    fasp_tick_hist.next_ent = (next + 1) % FASP_TICK_HIST_TAB_SIZ;          \
    if (fasp_tick_hist.next_ent == fasp_tick_hist.first_ent) {              \
        fasp_tick_hist.first_ent = (fasp_tick_hist.first_ent + 1) %         \
                                    FASP_TICK_HIST_TAB_SIZ;                 \
    }                                                                       \
}

#define FASP_TICK_HIST_DUMP()                                               \
{                                                                           \
    register int i;                                                         \
    register int curr = fasp_tick_hist.first_ent;                           \
    as_log("======= FASP_TICK_HIST for %s (first index %d) =======",        \
            fasp_tick_hist.tabname, fasp_tick_hist.first_ent);              \
    for (i = 0; i < FASP_TICK_HIST_TAB_SIZ; i++) {                          \
        if (!fasp_tick_hist.tab[curr].valid) {                              \
            break;                                                          \
        }                                                                   \
        as_log("FASP_TICK_HIST[%d]: valid %d "                              \
               "{time_ms, tick_val, tick_type, rtt} = "                     \
               "%llu %u %s %d",                                             \
                curr, fasp_tick_hist.tab[curr].valid,                       \
                fasp_tick_hist.tab[curr].tstamp_msec,                       \
                fasp_tick_hist.tab[curr].tick_val,                          \
               (fasp_tick_hist.tab[curr].tick_type == DATA_TICK_NET) ?      \
                "TICK_NET" : "TICK_REX",                                    \
                fasp_tick_hist.tab[curr].rtt);                              \
        curr = (curr + 1) % FASP_TICK_HIST_TAB_SIZ;                         \
    }                                                                       \
    as_log("======= end =======");                                          \
}

#else 

#define FASP_TICK_HIST_INIT(namestr)
#define FASP_TICK_HIST_ADD(tick_val, tick_type, rtt)
#define FASP_TICK_HIST_DUMP()

#endif  /* TEST_CTLPDUS */


/*
 * Extern declarations for routines.
 */
extern void
faspctl_show_freqconf(
    control_pdu_freq_t *ctlfreq,
    const char *dbg_str
);

extern void
faspctl_transmitter_ctlpdu_freq_init(
    control_pdu_freq_t *ctlfreq
);

extern void
faspctl_receiver_ctlpdu_freq_init(
    control_pdu_freq_t *ctlfreq
);

extern inline void 
faspctl_net_tick_req_set_period(
    control_pdu_freq_t *ctlfreq,
    unsigned int period_usec
);

extern inline void
faspctl_net_tick_req_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_net_tick_rsp_set_period(
    control_pdu_freq_t *ctlfreq,
    unsigned int period_usec
);

extern inline void
faspctl_net_tick_rsp_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_net_tick_rsp_sched_always(
    control_pdu_freq_t *ctlfreq,
    unsigned int on_off
);

extern inline void
faspctl_dsid_ackvec_set_period(
    control_pdu_freq_t *ctlfreq,
    unsigned int period_usec
);

extern inline void
faspctl_dsid_ackvec_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_dsid_ackvec_ack_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_rateparams_update_set_period(
    control_pdu_freq_t *ctlfreq,
    unsigned int period_usec
);

extern inline void
faspctl_rateparams_update_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_rateadapt_update_set_period(
    control_pdu_freq_t *ctlfreq,
    unsigned int period_usec
);

extern inline void
faspctl_rateadapt_update_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_vlink_update_set_period(
    control_pdu_freq_t *ctlfreq,
    unsigned int period_usec
);

extern inline void
faspctl_vlink_update_sched_immed(
    control_pdu_freq_t *ctlfreq, 
    unsigned int count
);

extern inline void
faspctl_rateparams_ack_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern inline void
faspctl_keepalive_sched_immed(
    control_pdu_freq_t *ctlfreq,
    unsigned int count
);

extern u_int16_t
faspctl_net_tick_rsp_set_val(
    struct fasp_session_t *sess
);

extern inline void
faspctl_jobsize_set_period(
    control_pdu_freq_t *ctlfreq,
    u_int32_t period_usec,
    u_int32_t retries);

extern inline void
faspctl_jobsize_ack_sched_immed(
    control_pdu_freq_t *ctlfreq,
    u_int32_t count);

extern int
fasp_ctlpdu_send(
    struct fasp_session_t *sess,
    char *pdu,
    u_int16_t len
);

extern void
fasp_ctlpdu_dump(
    char *pdu,
    u_int16_t len
);

#endif /* _FASP_DATA_CTL_H_ */
