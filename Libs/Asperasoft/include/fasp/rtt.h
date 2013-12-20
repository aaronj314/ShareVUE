#ifndef _RTT_H
#define _RTT_H

#include <utils/src/asutils.h>

#include <time.h>

#define RTT_RXTMIN      1      /* min retransmit timeout value, in tick units */
#define RTT_RXTMAX      20000  /* max retransmit timeout value, in tick units */
#define RTT_RXTRATEMAX  8000   /* max RTO for rate RTT */
#define TICK_INTERVAL   1      /* number of milliseconds per tick count */

/* RTT types */
#define RTT_TYPE_REX    0x01
#define RTT_TYPE_RATE   0x02
#define RTT_TYPE_RING   0x03

typedef struct rtt_info_t {
    float rtt_rtt;          /* most recent measured RTT, milliseconds    */
    float rtt_srtt;         /* smoothed RTT estimator, milliseconds      */
    float rtt_srtt_old;     /* previous smoothed RTT estimator           */
    float rtt_brtt;         /* smallest RTT observed, milliseconds       */
    float rtt_rttvar;       /* smoothed mean deviation, milliseconds     */
    float rtt_rto;          /* current RTO to use, milliseconds          */
    int rtt_nrexmt;         /* #times retransmitted: 0, 1, 2, ...   */
    u_int32_t rtt_base;     /* #sec since 1/1/1970 at start         */
    u_int32_t rtt_type;     /* type (ex: rex, rate)                 */
} rtt_info_t;

/*------------------------------------------------------------------------
 * Function prototypes.
 *------------------------------------------------------------------------*/
/* initializes the rtt base time and calculates an initial rto */
void rtt_init(struct rtt_info_t * ri, u_int32_t rtt_type);
/* returns the current rto */
int rtt_get(struct rtt_info_t *);
/* updates brtt based on start request calculated rtt */
void rtt_update_brtt(struct rtt_info_t *ptr, u_int32_t ms);
/* recalculates the rto given the measured rtt */
void rtt_update(struct rtt_info_t *ptr, u_int32_t ms);
int ticker_init(void);
int ticker_get(void);
u_int64_t ticker_msec( u_int64_t ticks );

#endif
