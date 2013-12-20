#ifndef _RATE_H
#define _RATE_H

#include <utils/src/asutils.h>

/* Session rate priority levels*/
#define FASP_SESS_RATE_PRIORITY_UNSET        (0)
#define FASP_SESS_RATE_PRIORITY_HIGH         (1)
#define FASP_SESS_RATE_PRIORITY_REGULAR      (2)

/* Adaptive rate operation mode */
#define FASP_TCP     0
#define FASP_FAST    1
#define FASP_STARTUP 2 

#define RATE_UPDATE_NONE 0
#define RATE_UPDATE_PHY  1
#define RATE_UPDATE_VLQ  2

#define SIZE_DAMP_FACTOR                     (4.0)
#define ALPHA_PRIORITY_INFLATE_FACTOR        (2.0)

#define RATE_INFO_NET   0x00
#define RATE_INFO_VL    0x01
#define RATE_INFO_RING  0x02
#define RATE_INFO_DISK  0x03

/* Forward declarations */
struct rtt_info_t;

extern float q_target_eq;
extern u_int32_t rate_update_interval;  // update interval

typedef struct rate_info_t {
    u_int32_t       type; 
    u_int32_t       priority;       /* transfer rate priority            */
    u_int64_t       rate_current;   /* current rate             [bps]    */
    u_int64_t       rate_max;       /* target (maximum) rate    [bps]    */
    u_int64_t       rate_min;       /* minimum rate             [bps]    */
    u_int64_t       rate_est;       /* estimated bottleneck bw  [bps]    */
    u_int32_t       adaptive;       /* 0 - fixed
                                     * 1 - fair
                                     * 2 - trickle
                                     */
    struct rtt_info_t *rtt_info;      /* pointer to an rtt info struct     */
    float           alpha;            
    int             fasp;
    int             fast_const;     /* constant for fast in/out alog     */
    int             bl_sz;          /* block size                        */
    u_int32_t       target_qweight; /* weighing factor for alpha */
} rate_info_t;

/*------------------------------------------------------------------------
 * Function prototypes.
 *------------------------------------------------------------------------*/

/* initializes the rates, beta, and rtt values */
void rate_init(struct rate_info_t *ri, 
               struct rtt_info_t *rttinfo,
               u_int32_t type);

/* re-calculate rate parameters based on new target rate */
void rate_calc_params( struct rate_info_t *ri);

/* initializes the target rate */
void rate_init_target(struct rate_info_t *ri, u_int32_t priority,
                      u_int64_t target, u_int64_t min, u_int64_t est,
                      u_int32_t adaptive, u_int32_t bl_sz, u_int32_t qw);

/* returns the current rate */
int rate_get(struct rate_info_t *ri);

/* recalculates the rate based on the current rtt sample, and updates 
 * the rate info 
 */
void rate_update(struct rate_info_t *ri);

/* generic rate update function with normalizing factor */
void rate_update_generic(struct rate_info_t *ri, float q_extra, float f_norm, int size);

void rate_update_alpha(struct rate_info_t *ri, float alpha);

void rate_calc_update_alpha(struct rate_info_t *ri);

void rate_calc_update_inout(struct rate_info_t *ri);

void rate_dump_short(struct rate_info_t *ri);

void rate_dump(struct rate_info_t *ri);

#endif
