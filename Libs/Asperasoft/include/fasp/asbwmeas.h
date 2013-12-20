/*
 * asbwmeas.h
 *
 * Bandwidth discovery utilities
 *
 * Aspera Inc.
 */

#ifndef AS_BWMEAS_H
#define AS_BWMEAS_H


/* session probing operations */
#define SS_OP_PMTU_DISC  0x01
#define BW_OP_IC_DETECT  0x02
#define BW_OP_BW_DETECT  0x03

/* default skew removal algorithm */
#define SKEW_RLF         0x01
#define SKEW_RLF_DENOI   0x02
#define SKEW_CONV_HULL   0x03

/* Global variables */
#define DEFAULT_OBS_LEN  50
#define DEFAULT_PROBE_RATE 100
#define DEFAULT_PROBE_SIZE 772
#define DEFAULT_DEBUG    0

#define DEF_MIN_DISP     20   //Minimum possible disperson (empirical)
#define MAX_TRAIN_LEN    100
#define MIN_PROBE_SIZE   500
#define MIN_OBS_LEN      10
#define MAX_OBS_LEN      100
#define NO_INI_PKTS      50
#define UDPIP_HDR_SIZE   28
#define TCPIP_HDR_SIZE   40
#define SESS_PMTU_TOUT   2000000
#define SESS_INI_TOUT    10000000

#define as_sock_so_timestamp(sock, on) setsockopt(sock, SOL_SOCKET, SO_TIMESTAMP, (const char *)&on, sizeof(on))
typedef enum _DF_bit {
    DFbit_OFF = 0,
    DFbit_ON = 1 
} DFbit;
    
/* get (new_time-old_time) in the form of us */
u_int64_t get_usec_since_oldtime (struct timeval *old_time, struct timeval *new_time);

int as_ioctl(as_socket_t sock, struct timeval *t);

/* Cross-platform activation of "Don't fragment" socket option */
int as_setsock_DF(as_socket_t sock, DFbit bit);

int detect_timer_level(as_socket_t sock);

int as_sock_recv_dstaddr(as_socket_t sock);

int as_recvmsg_dstaddr(as_socket_t sock, void *buf, int size, int flags, 
                       struct sockaddr_in *from, char *dstaddr, int addrsize);

/* 
 * Cross-platform implementation of send()
 * that facilitates receiver timestamping
 */
int as_send_udp_pkt(as_socket_t sock, void *buf, int size, int flags, struct sockaddr_in *to, int tl);

/* 
 * Cross-platform implementation of recv()
 * that extracts precise arrival timestamp 
 */
int as_recv_udp_pkt(as_socket_t sock, void *buf, int size, int flags, struct sockaddr_in *from, int tl, struct timeval *t);

#endif









