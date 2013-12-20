/* Instrumentation for RTT and rate control */

#ifndef _RCINSTR_H_
#define _RCINSTR_H_

#define RC_INSTRU_TABLE_SIZE 1000000

/* Receiver side: RTT update */
typedef struct _rate_rtt_history_t
{
   struct timeval stamp;
   u_int32_t rtt;
   u_int32_t srtt;
   u_int32_t brtt;
   u_int32_t rto; 
   u_int64_t last_loop_period;
   u_int64_t last_loop_select_period;
} rate_rtt_history_t;

/*
 * Receiver side: rate update
 */
typedef struct _rate_update_history_t
{
   struct timeval stamp;
   u_int32_t rtt;
   u_int32_t srtt;
   u_int32_t brtt;
   u_int32_t drtt;
   u_int32_t fast;
   u_int32_t alpha;
   u_int32_t gamma;
   u_int32_t size;
   u_int64_t rate;
} rate_update_history_t;

/*
 * Sender side: RTT measurement ticks
 */
typedef struct _rtt_meas_t
{
  struct timeval stamp;
  /* tick received 'R' 
     or tick sent 'S' */
  char what;  
  u_int32_t adjustment;
  u_int16_t tick;
  //struct timeval mtime; 
} rtt_meas_t;

void dump_recv_history_to_file(char *filename);
void dump_send_history_to_file(char *filename);

extern char * g_recv_history_header;
extern char * g_send_history_header;

extern rate_rtt_history_t g_rate_rtt_history[RC_INSTRU_TABLE_SIZE];
extern u_int32_t g_rate_rtt_idx;

extern rtt_meas_t g_rtt_meas[RC_INSTRU_TABLE_SIZE];
extern u_int32_t g_rtt_meas_idx;

extern rate_update_history_t g_rate_update_history[RC_INSTRU_TABLE_SIZE];
extern u_int32_t g_rate_update_idx;

#endif

