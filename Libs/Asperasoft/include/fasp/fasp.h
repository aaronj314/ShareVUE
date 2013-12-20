/*
 * fasp.h
 *
 * Main header file for the FASP library
 *
 * Aspera Inc.
 */

#ifndef __AS_FASP_H__
#define __AS_FASP_H__

#include <sys/types.h>  /* for u_char, u_int16_t, etc. */
#include <fasp/fasp_limits.h>
#include <fasp/config_api.h>
#include <fasp/fasp_errno.h>
#include <fasp/fasp_license.h>

/*------------------------------------------------------------------------
 * Macro definitions.
 *------------------------------------------------------------------------*/
#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

/*------------------------------------------------------------------------
 * Global constants.
 *------------------------------------------------------------------------*/
#define MAX_ERROR_MESSAGE  512           /* maximum length of an error message */
#define MAX_DGRAM_SIZE     65535         /* maximum size of a data block       */
#define DEF_DGRAM_SIZE     1492          /* default datagram size */

#ifdef ISILON
#define DEFAULT_UDP_BUFFER  (20000000)       /* size of UDP rcv buffer */
#else
/* The Mac OS X scheduler blocks the process if socket buffer is too large. */
#define DEFAULT_UDP_BUFFER  (10 * (1<<20))  /* size of UDP rcv buffer */
#endif

#define DEFAULT_IPV6_YN     0

/* Both of these must be multiples of 16 */
#define MIN_BLOCK_SIZE     ( 256 )
#define MAX_BLOCK_SIZE     ( 48 * 1024 )

#define PROTOCOL_SUCCESS                  0x01
#define PROTOCOL_FAIL                     0x02
#define PROTOCOL_SERVER_ERROR             0x03
#define PROTOCOL_INVALID_FILE             0x04

#define MAX_FILENAME_LENGTH        1024  /* max length of a requested filename */
/*
 * max # of sources 32K pdu / 5B TLV,
 * assuming 2B + NULL source paths, TLV: T-1B L-1B V-3B
 */
#define MAX_SRCLIST_LENGTH         6550
#define MAX_OPEN_XFER_TLV_LENGTH  32768  /* max length of open transfer TLV */
#define MAX_AUTH_DATA_LENGTH         64
#define MAX_DIGEST_LENGTH            16

#define MAX_RETRANSMISSION_NUMBER    240  /* maximum number of retransmission
                                           * requests to send in one PDU,
                                           * sized such that the rex request
                                           * fits MTU
                                           */
#define MAX_RETRANSMISSION_BUFFER    (MAX_RETRANSMISSION_NUMBER * 6)
                                           /* maximum retransmission buffer
                                            * size, in bytes, which contains 
                                            * one 32 bit block number and one 
                                            * 16 bit retransmission index for
                                            * each reqested block.
                                            */
#define REXELEM_SIZE                 6     /* size of one rex entry in rex 
                                            * request 
                                            */ 
#define TRANSFER_TIMEOUT             60
#define CONNECTION_TIMEOUT           (10 * 1000 * 1000)   /* usec */

/* FASP action types */
#define ACT_START                   0x01
#define ACT_STOP                    0x02
#define ACT_SESSION                 0x01
#define ACT_TRANSFER                0x02

/* FASP operations */
#define FASP_NONE                   0x00
#define FASP_SEND                   0x01
#define FASP_RECV                   0x02
#define FASP_CTRL                   0x03

/* FASP peers */
#define FASP_RECEIVER               0x01    /* Receiver */
#define FASP_SENDER                 0x02    /* Sender */                

// session protocol states
//
#define SESSION_RESET               0x00  
#define SESSION_READY_AUTH          0x10
#define SESSION_WAIT_FOR_AUTH       0x20
#define SESSION_AUTHORIZED          0x30
#define SESSION_CONNECTED           0x40
#define SESSION_TRANSFERRING        0x50
#define SESSION_SUCCESS             0x60
#define SESSION_TIMEOUT             0x70
#define SESSION_ERROR               0x80

// session administrative states
#define SESSION_IDLE                0x0000
#define SESSION_START               0x0101
#define SESSION_STOP                0x0102

// session bwmeas state
#define SESSION_PMTU_PROBING        0x0201
#define SESSION_BW_PROBING          0x0202

// transfer states
//
#define XFER_STARTED                0x00
#define XFER_SUCCESS                0x01
#define XFER_ERROR                  0x02


// Should probably go in utils somewhere.
#ifdef WIN32
#define SELECT_SOCKET_COUNT(c)  0
#else
#define SELECT_SOCKET_COUNT(c)  (c)
#endif

#define LICENSE_OLD_VER         0
#define LICENSE_NEW_VER         1

/* Forward declarations */
struct fasp_lic; 
struct licinfo_t;
struct fasp_session_t;
struct fasp_t;

/* Globals */

/* These two globals are used throughout the fasp code. 
 * TODO: use the equivalent variables from the fasp_t context instead 
 */

/*! \brief
 * Store all FASP context
 *
 */

/* XXX we do not store "all" FASP context here contrary to the comment above */

typedef struct fasp_t {
    /* List of sessions (currently just one) */
    const struct fasp_session_t   *sess;

    char *_bin_dir;
    char *_root_dir;
    char *_etc_dir;
    char *_var_dir;
    char *_var_port_dir;
    char *_log_dir;

    char                    *_conf_file;
    aspera_conf_t           *conf;

    char                    *_license_file;
    char const              *_license_string;  
    fasp_license_t          _license;
    u_int8_t                _license_ver;
    
    const char *docroot;

    /* Error information */
    int32_t                 errcode;
    char                    errstr[FASP_ERRSTR_MAXLEN];

} fasp_t;

extern const fasp_t *g_fasp;

/*! \brief
 * Initializes FASP library
 * Stores context in the fasp_t structure.
 */
extern fasp_errno_e fasp_init(
    char *argv0,
    int iamremote,
    char *aspera_conf_file,
    char const *license_string,
    char *log_dir,
    char *user);

/*! \brief
 * Cleans up FASP library
 *
 */
extern int fasp_fini(void);

/* External error reporting routines */
extern void as_run_err(char desctype, char* descr, int sys_err, int mgmt_err);
extern void as_fatal_err(char desctype, char *descr, int sys_err, int mgmt_err);

int 
fasp_set_session(
    const struct fasp_session_t *sess);

int fasp_print_license_str(const char* lic_str, const char* argv0, int debuglevel);

#endif
