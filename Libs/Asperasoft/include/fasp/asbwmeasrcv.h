/*
 * asbwmeasrcv.h
 *
 * Receiver side utilities to discover bottleneck link capacity 
 *
 * Aspera Inc.
 */

#ifndef AS_BWMEASRCV_H
#define AS_BWMEASRCV_H

#define BWMEAS_SLACK 10
#define RCV_UDP_PORT 9922

#define LARGE_OFFSET 50000000

struct pkt_info {
  int snd_stamp;
  int rcv_stamp;
};

typedef struct {
  int seq;
  struct pkt_info pkt[2];  
} pp;

/* function to check min-delay sum rule */
int chk_min(pp *pp_info, int obs_len);

/* function to find packet pair with min-delay sum */     
int find_min_pp(pp *pp_info, int obs_len);

void log_delay_stat(char *logfile, pp *pp_info, int cur_pp, int obs_len);

int start_bwmeas_recv(fasp_session_t *xsess);

#endif



