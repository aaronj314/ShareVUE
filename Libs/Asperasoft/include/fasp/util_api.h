#ifndef _UTIL_API_H_
#define _UTIL_API_H_
/*------------------------------------------------------------------------
 * util_api.h - miscellanous utility functions
 *
 *------------------------------------------------------------------------*/

#include <utils/src/asutils.h>

#define MIN_SLEEP_USEC     (1000)
#define INTER_BATCH_USEC   (5000)

// See http://msdn.microsoft.com/en-us/library/ms682425.aspx.
// "The maximum length of this string is 32,768 characters, including the Unicode terminating null character."
#define MAX_COMMAND_LINE    (32767) // Move somewhere in utils when convenient.

/* Forward declarations */
struct transfer_t;
#ifndef __AS_FASP_SESSION_H__
struct fasp_session_def_t;
struct fasp_session_t;
#endif 

typedef struct sourcelistinfo_t_ {
    u_int64_t   _num_files;     /* Number of regular files */
    u_int64_t   _num_dirs;      
    u_int64_t   _num_special;   
    u_int64_t   _num_failed;
    u_int64_t   _total_bytes;
    int         sourcelist_ready;  /* 0: not ready; 1: send; 2: sent */
} sourcelistinfo_t;

/*------------------------------------------------------------------------
 * constants
 *------------------------------------------------------------------------*/
#if 0  /* consider deleting this */
#define IPD_RATE_INTERVAL    (5 * 1000000LL)  // rate calculation interval (usec)
#endif

#ifdef ACP
void freeaddrinfo(struct addrinfo *ai);
int getaddrinfo(const char *hostname, const char *servname, 
                const struct addrinfo *hints, struct addrinfo **res);
#endif

/*------------------------------------------------------------------------
 * function prototypes
 *------------------------------------------------------------------------*/

int        init_transfer(struct fasp_session_t *sess,
                         struct transfer_t *xfer);

int        init_data_transmission_parms(struct fasp_session_t *sess,
                                        struct transfer_t *xfer,
                                        as_filehandle_t fh,
                                        u_int64_t fsize,
                                        char *errstr);
int        free_data_transmission_parms();
int        init_data_reception_parms(struct fasp_session_t *sess,
                                     struct transfer_t *xfer, 
                                     as_filehandle_t fh,
                                     u_int64_t fsize);
int        start_data_transmission(struct fasp_session_t *sess, 
                                   struct transfer_t *xfer );
int        stop_data_transmission(struct fasp_session_t *sess,
                                  struct transfer_t *xfer );
int        start_data_reception(struct fasp_session_t *sess,
                                struct transfer_t *xfer );
int        stop_data_reception(struct fasp_session_t *sess,
                               struct transfer_t *xfer );
void       reinit_transfer(struct fasp_session_t *sess,
                           struct transfer_t *xfer );
void       freshen_up_transfer(struct fasp_session_t *sess,
                               struct transfer_t *xfer );
void       cleanup_transfer(struct fasp_session_t *sess,
                            struct transfer_t *xfer);

int        send_nop(struct fasp_session_t *sess);

int        calculate_ipd(struct fasp_session_t *sess);

void       calc_rex_poll_int(struct fasp_session_t *sess);

int as_build_client_sourcelist(char ***sourcelist, char **srcs, int num);
int as_build_server_sourcelist(char ***srclist);
sourcelistinfo_t sourcelist_info(char **sourcelist);

char *as_get_host(char *remotepath);
char *as_get_user(char *remotepath);

/* dsid ackvec utility */
extern int dsid_ackvec_sprintf(char *buf, int buflen, u_int32_t *ackvec);

/* Vlink utilities*/
int vlink_check_and_broadcast(struct fasp_session_t *sess); 
int vlink_check_and_update(struct fasp_session_t *sess);

/* File manifest generation */
extern char manifest_fname[AS_MAX_PATH];
int file_manifest_init(struct fasp_session_t *sess);
int file_manifest_act_file(struct fasp_session_t *sess, transfer_t *xfer);
int file_manifest_fini(struct fasp_session_t *sess);

void fasp_getver(char* strver, size_t);
void fasp_getos(char* strver, size_t);

#endif
