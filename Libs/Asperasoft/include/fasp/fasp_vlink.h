/*
 * fasp_vlink.h
 *
 * FASP vlink data structures and related functions.
 *
 * Aspera, Inc.
 */

#ifndef __AS_FASP_VLINK_H__
#define __AS_FASP_VLINK_H__

#define FASP_VLINK_LOCAL            1
#define FASP_VLINK_REMOTE           2

#define USE_SMOOTHED_QL             1 
#define MIN_FP_THOUSAND             1        // minimum 1000*fp 
#define VLINK_UPDATE_PERMSG         0x01
#define VLINK_UPDATE_PERIOD         0x02

/*
 * Default virtual link configurations
 */
#define DEFAULT_VLINK_ID            1        // Default vlink id
#define DEFAULT_VLINK_SPEED         50000000 // 50Mbps
#define DEFAULT_UPDATE_PERIOD       1000     // 1ms
#define DEFAULT_MIN_QUEUE           0        // 0ms 
#define DEFAULT_MCAST_PORT          55001    // UDP multicast port 
#define DEFAULT_QB_OVER_QMAX        (1.2)      

// Parameter tuning across platforms
#ifdef ISILON
#define DEFAULT_TARGET_QUEUE        100      // 100ms 
#define TARGET_QWEIGHT_INI          2        // target queue adjustment factor for ISILON
#define DEFAULT_POWER_KIN           (1.0)    // k_inner = 1.0
#define DEFAULT_POWER_KOUT          (3.0)    // k_outer = 3.0    
#else
#define DEFAULT_TARGET_QUEUE        100      // 100ms
#define TARGET_QWEIGHT_INI          2        // target queue adjustment factor
#define DEFAULT_POWER_KIN           (0.5)    // k_inner = 0.5
#define DEFAULT_POWER_KOUT          (1.0)    // k_outer = 1.0    
#endif

#define VLINK_MCAST_BASE_ADDR       "239.255.0.0"
#define VLINK_MCAST_ADDR_RANGE      256      // default multicast address range
#define VLINK_SWARM_MAXSIZE         65536    // maximum number of sessions sharing 
                                             // a common virtual link 
#define VLINK_SESSION_EXPERIOD      1000     // 1000ms 

struct rate_info_t;

typedef struct fasp_vlink_core_t {

  u_int32_t          bytes_pending;    // bytes received since the last update
  u_int64_t          ql;               // instantaneous queue length (bytes)
  u_int64_t          s_ql;             // smoothed queue length (bytes)
} fasp_vlink_core_t; 

typedef struct fasp_vlink_sessdata_t{
  u_int16_t          tick;             // last time slot when an active session
                                       // was seen 
} fasp_vlink_sessdata_t;

typedef struct fasp_vlink_reconf_t {
  u_int16_t          valid;
  u_int16_t          prio;
  u_int16_t          id;
  u_int16_t          enabled;
  u_int64_t          cl;   
} fasp_vlink_reconf_t;

/* 
 * FASP virtual link data structure 
 */
typedef struct fasp_vlink_t {

  /* Queueing related */
  u_int8_t           enabled;
  u_int8_t           update_policy;    // update policy
  u_int16_t          id;               // virtual link id
  u_int16_t          type;             // virtual link type (local or remote) 
  u_int32_t          update_period;    // update period, usec
  u_int32_t          qmax;             // target queueing (ms) in equilibrium
  u_int32_t          qmin;             // minimum queueing (ms) 
  u_int64_t          Qmax;             // target queueing (bytes) in equilibrium
  u_int64_t          Qmin;             // minimum queueing (bytes)
  u_int64_t          QB;               // bound for virtual queue size 
  u_int64_t          cl;               // virtual link capacity 
  u_int16_t          mcast_port;       // virtual link multicast port
  float              k_inner;          // inside power k used for computing f(p)
  float              k_outer;          // outside power k used for computing f(p)
  fasp_vlink_core_t  queue;            // link queue status
  struct timeval     last_updated;     // time when vlink is last updated 
  struct rate_info_t *rateinfo;        // rate info maintained by the vlink object
  
  /* Multicasting related */
  as_socket_t        udp_sock;         // UDP socket associated with vlink
  struct sockaddr_in mcast_group_addr; // multicast group address to join/leave
  struct sockaddr_in mcast_if_addr;    // interface to bind/send multicast 
  
  /* swarm estimation related */ 
  u_int16_t          link_tick;          
  u_int16_t          link_swarm_size;   
  u_int16_t          cur_swarm_size; 
  fasp_vlink_reconf_t   vlink_reconf;  // hold useful info to reconfigure vlink
  fasp_vlink_sessdata_t *swarm_table;  // hash table that logs information of 
                                       // sessions sharing a common virtual link 
} fasp_vlink_t;

typedef struct fasp_vlink_init_t {
  u_int16_t          id; 
  u_int16_t          type; 
  u_int16_t          op;
  u_int16_t          enabled;
  u_int64_t          cl;
  int                policy;
  float              kin;
  float              kout;
  int                period; 
  int                qmax; 
  int                qmin;
  float              qb_over_qmax;
  u_int16_t          mcast_port;
  char               *mcast_addr;
  char               *if_addr;
} fasp_vlink_init_t;

/* Initialize virtual link*/
fasp_vlink_t  *fasp_vlink_init(fasp_vlink_init_t *vlink_init_params); 

/* Update bytes received between two consecutive ql updates */
void fasp_vlink_update_bytes(fasp_vlink_t *vlink, int bytes); 

/* Update virtual link queue length */
void fasp_vlink_update_Ql(fasp_vlink_t *vlink);

/* Retrieve current queue length */
u_int64_t fasp_vlink_get_Ql(fasp_vlink_t *vlink);

/* Retrieve current queue length */
u_int64_t fasp_vlink_get_sQl(fasp_vlink_t *vlink);

/* Retrieve current queueing delay (ms) */
float fasp_vlink_get_ql(fasp_vlink_t *vlink);
u_int16_t fasp_vlink_get_ql_u16(fasp_vlink_t *vlink);

/* Retrieve current smoothed queueing delay (ms) */
float fasp_vlink_get_sql(fasp_vlink_t *vlink);
u_int16_t fasp_vlink_get_sql_u16(fasp_vlink_t *vlink);

/* Compute pseudo-marking probability based on delay */
double fasp_vlink_calc_p(fasp_vlink_t *vlink);

/* Compute normalizing factor based on delay */
double fasp_vlink_calc_fp(fasp_vlink_t *vlink); 

/* Hardcode link speed into vlink structure */
void fasp_vlink_set_speed(fasp_vlink_t *vlink, u_int64_t cl);

void fasp_vlink_update_swarm_size(fasp_vlink_t *vlink);

/* Retrieve currently received bytes */
u_int32_t fasp_vlink_get_pending(fasp_vlink_t *vlink);

/* Reset vlink parameters to default values */
void fasp_vlink_reset(fasp_vlink_t *vlink);

/* Delete data structure */
void fasp_vlink_destroy(fasp_vlink_t *vlink); 

#endif
