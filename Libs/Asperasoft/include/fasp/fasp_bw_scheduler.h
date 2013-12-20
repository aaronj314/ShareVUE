#ifndef __AS_FASP_BW_SCHEDULER_H__
#define __AS_FASP_BW_SCHEDULER_H__

/* Callback function used by bw scheduler */
typedef int32_t (*as_bw_scheduler_callback_t)(
    const void *arg,      /* argument passed to bw scheduler callback func */
    const char *cmd);     /* cmd passed to bw scheduler callback func */

int fasp_bw_scheduler_init(void);  

int fasp_bw_scheduler_term(void);

int fasp_bw_scheduler_issue_latest(as_bw_scheduler_callback_t cbk_func);

int fasp_bw_scheduler_eval(struct timeval *tnow);

int fasp_bw_scheduler_add_event(
        char *schedule,
        void *arg,
        as_bw_scheduler_callback_t cbk_func);

int fasp_bw_scheduler_del_event(
        char *schedule,
        void *arg,
        as_bw_scheduler_callback_t cbk_func);

#endif
