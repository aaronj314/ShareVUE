/*
 * vlink instrumentation header file
 */

#ifndef _VLINK_INSTRU_H_
#define _VLINK_INSTRU_H_

#define VLINK_INSTRU_TABLE_SIZE 1000000

/* structure for recording */
typedef struct _vlink_sent_history_t 
{
   struct timeval stamp;
   u_int16_t      vlink_sess_id; 
   u_int32_t      direc; 
   u_int32_t      bytes;
   u_int64_t      elapsed;
} vlink_sent_history_t;

typedef struct _vlink_recvd_history_t 
{
   struct timeval stamp;
   u_int16_t      vlink_sess_id; 
   u_int32_t      recvd_direc;
   u_int32_t      recvd_bytes;
   u_int64_t      cur_Ql; 
   u_int64_t      cur_s_Ql;
} vlink_recvd_history_t;

void dump_vlink_history_to_file(char *filename);

extern u_int32_t g_sent_hist_idx;
extern u_int32_t g_recvd_hist_idx;

extern vlink_sent_history_t g_vlink_sent_history[VLINK_INSTRU_TABLE_SIZE];
extern vlink_recvd_history_t g_vlink_recvd_history[VLINK_INSTRU_TABLE_SIZE];

#endif
