#ifndef _FASP_DS_STATS_H_
#define _FASP_DS_STATS_H_
#include <utils/src/asutils.h>

/*
 * Header file for fasp data session statistics.  
 *
 * Keep this file free of DS dependencies so that it could be included
 * by upper layers to fetch statistics without having to include all
 * ds types.
 */

typedef struct fasp_ds_stats_src_export_t {
    /*
     * Source stats (exchanged in close-session pdu)
     */
    u_int32_t src_args_scan_attempted; /* ascp arguments scanned */
    u_int32_t src_args_scan_completed; /* ascp arguments scanned */

    u_int32_t src_paths_scan_attempted; /* attempted = total of following 5 */
    u_int32_t src_paths_scan_failed;    /* total number of path scans failed 
                                           (e.g. stat failed, and can't tell 
                                           if file or dir) */
    u_int32_t src_paths_scan_irreg_skipped;
    u_int32_t src_paths_scan_excluded;
    u_int32_t src_dirs_scan_completed;
    u_int32_t src_files_scan_completed;

    u_int32_t src_dirs_xfer_attempted;  /* attempted = total of following 2 */
    u_int32_t src_dirs_xfer_fail;       /* dirs failed */
    u_int32_t src_dirs_xfer_pass;       /* dirs passed */

    u_int32_t src_files_xfer_attempted; /* attempted = total of following 2 */
    u_int32_t src_files_xfer_fail;      /* files failed */
    u_int32_t src_files_xfer_pass;      /* files passed */
    u_int32_t src_files_xfer_noxfer;    /* files skipped */

    u_int64_t src_bytes_xfer_done;   /* actual number of bytes transferred */

} fasp_ds_stats_src_export_t;


typedef struct fasp_ds_local_stats_t {
    /* 
     * Common stats local to Source & Sink (not exported)
     */
    u_int32_t ds_started;            /* Cumu #DS added to RUNNING_Q */
    u_int32_t ds_done;               /* Cumu #DS currently in RUNNING_Q */

    u_int32_t dserr_sent;
    u_int32_t dserr_rcvd;
    u_int32_t sesserr_sent;
    u_int32_t sesserr_rcvd;


    /*
     * Stats local to Source
     */
    u_int32_t src_dirs_xfer_more;    /* dirs whose DS is yet to RUN */
    u_int32_t src_dirs_xfer_done;    /* dirs pass or failed */
    u_int32_t src_files_xfer_done;   /* files pass or failed */

    u_int32_t req_skipped;
    u_int32_t req_sent;
    u_int32_t rsp_rcvd;
    u_int32_t rsp_rcvd_xfernotneeded;
    u_int32_t rsp_rcvd_xferneeded;
    u_int32_t rsp_rcvd_error;


    /* 
     * Stats local to Sink
     */
    u_int32_t req_rcvd;
    u_int32_t rsp_sent;
    u_int32_t rsp_sent_xfernotneeded;
    u_int32_t rsp_sent_xferneeded;
    u_int32_t rsp_sent_error;

} fasp_ds_stats_local_t;


typedef struct fasp_ds_stats_t {
    fasp_ds_stats_src_export_t src_export;
    fasp_ds_stats_local_t      local;

#define DS_ESTAT_ADD(afield,cnt) ((g_fasp_ds_stats.src_export.afield) += cnt)
#define DS_ESTAT_INCR(afield)    ((g_fasp_ds_stats.src_export.afield)++)
#define DS_ESTAT_DECR(afield)    ((g_fasp_ds_stats.src_export.afield)--)
#define DS_ESTAT_VAL(afield)      (g_fasp_ds_stats.src_export.afield)

#define DS_LSTAT_ADD(afield,cnt) ((g_fasp_ds_stats.local.afield) += cnt)
#define DS_LSTAT_INCR(afield)    ((g_fasp_ds_stats.local.afield)++)
#define DS_LSTAT_DECR(afield)    ((g_fasp_ds_stats.local.afield)--)
#define DS_LSTAT_VAL(afield)      (g_fasp_ds_stats.local.afield)

} fasp_ds_stats_t;


/*
 * Extern declarations.
 */
extern fasp_ds_stats_t g_fasp_ds_stats;

extern void
show_fasp_ds_stats(
    int iam_source
);

extern void
fasp_ds_stats_src_export_get(
    fasp_ds_stats_src_export_t *src_exp_stats
);

extern void
fasp_ds_stats_src_export_set(
    fasp_ds_stats_src_export_t *src_exp_stats
);

#endif /* _FASP_DS_STATS_H_ */

