/*
 * faspmgmt.h
 *
 * Defines the FASP management protocol message formats
 * and provides basic parsing and formatting.
 */

#ifndef FASPMGMT_H
#define FASPMGMT_H

#ifdef WIN32
#ifndef FASPMGMT_DLLEXPORT
#define FASPMGMT_DLLEXPORT  __declspec(dllexport)
#endif
#else
#define FASPMGMT_DLLEXPORT
#endif

#include  <utils/src/asutils.h>

#define ARG_MAX_LEN         4096
#define MAX_MSG_SZ          10240  /* file name might appear twice. */

/* FASP management usage errors */
#define FASPMGMT_ERR_BAD_CMD    0x01
#define FASPMGMT_ERR_BAD_ARG    0x02
#define FASPMGMT_ERR_SOCK_ERR   0x03

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Commands
 */
typedef enum {

    CMD_NOP         = 0x00,
    CMD_START       = 0x01,
    CMD_QUERY       = 0x02,
    CMD_QUERYRSP    = 0x03,
    CMD_STATS       = 0x04,
    CMD_STOP        = 0x05,
    CMD_ERROR       = 0x06,
    CMD_CANCEL      = 0x07,
    CMD_DONE        = 0x08,
    CMD_RATE        = 0x09,
    CMD_FILEERROR   = 0x0a,
    CMD_SESSION     = 0x0b,
    CMD_NOTIF       = 0x0c,
    CMD_INIT        = 0x0d,
    CMD_VLINK       = 0x0e,

    CMD_MAX_NUM
} faspmgmt_cmd_t;

extern char const* const faspmgmt_cmd_name_str[];

/**
 * Arguments
 */
typedef enum {
    ARG_TYPE        = 0x00,
    ARG_FILE        = 0x01,
    ARG_SIZE        = 0x02,
    ARG_WRITTEN     = 0x03,
    ARG_BYTESCONT   = 0x04,
    ARG_RATE        = 0x05,
    ARG_LOSS        = 0x06,
    ARG_QUERY       = 0x07,
    ARG_CODE        = 0x08,
    ARG_PASSWORD    = 0x09,
    ARG_PROGRESS    = 0x0a,
    ARG_REMAINING   = 0x0b,
    ARG_ELAPSED     = 0x0c,
    ARG_REX_INFO    = 0x0d,
    ARG_BLOCK_INFO  = 0x0e,
    ARG_DISK_INFO   = 0x0f,
    ARG_RATE_INFO   = 0x10,
    ARG_MIN_RATE    = 0x11,
    ARG_DESCR       = 0x12,
    ARG_ELAPSEDUSEC = 0x13,
    ARG_SERVICELEVEL = 0x14,
    ARG_SESSIONID   = 0x15,
    ARG_USER        = 0x16,
    ARG_HOST        = 0x17,
    ARG_ENCRYPTION  = 0x18,
    ARG_ADAPTIVE    = 0x19,
    ARG_DIRECTION   = 0x1a,
    ARG_REMOTE      = 0x1b,
    ARG_PORT        = 0x1c,
    ARG_USERSTR     = 0x1d,
    ARG_COMMANDID   = 0x1e,
    ARG_STARTBYTE   = 0x1f,
    ARG_TOKEN       = 0x20,
    ARG_COOKIE      = 0x21,
    ARG_QUERYRSP    = 0x22,
    ARG_SOURCE      = 0x23,
    ARG_DEST        = 0x24,
    ARG_BWMEAS      = 0x25,
    ARG_BWMEAS_INFO = 0x26,
    ARG_PMTU        = 0x27,
    ARG_XFERBYTES   = 0x28,
    ARG_FILEBYTES   = 0x29,
    ARG_OPERATION   = 0x2a,
    ARG_DELAY       = 0x2b,
    ARG_PRECALC_FILES   = 0x2c,
    ARG_PRECALC_DIRS    = 0x2d,
    ARG_PRECALC_SPECIAL = 0x2e,
    ARG_PRECALC_FAILED  = 0x2f,
    ARG_PRECALC_BYTES   = 0x30,
    ARG_PRIORITY    = 0x31,
    ARG_TRANSPORT   = 0x32,
    ARG_VLINK_ID    = 0x33,
    ARG_VLINK_ON    = 0x34,
    ARG_VLINK_INBW  = 0x35,
    ARG_VLINK_OUTBW = 0x36,
    ARG_MANIFEST_FILE   = 0x37,
    /* src file/directory scan fields */ 
    ARG_SCANS_ATTEMPTED         = 0x38,
    ARG_SCANS_COMPLETED         = 0x39,
    ARG_PATH_SCANS_ATTEMPTED    = 0x3a,
    ARG_PATH_SCANS_FAILED       = 0x3b,
    ARG_PATH_SCANS_IRREG        = 0x3c,
    ARG_PATH_SCANS_EXCLUDED     = 0x3d,
    ARG_DIR_SCANS_COMPLETED     = 0x3e,
    ARG_FILE_SCANS_COMPLETED    = 0x3f,
    ARG_DIR_CREATES_ATTEMPTED   = 0x40,
    ARG_DIR_CREATES_FAILED      = 0x41,
    ARG_DIR_CREATES_PASSED      = 0x42,
    ARG_FILE_XFERS_ATTEMPTED    = 0x43,
    ARG_FILE_XFERS_FAILED       = 0x44,
    ARG_FILE_XFERS_PASSED       = 0x45,
    ARG_FILE_XFERS_NOXFER       = 0x46,
    ARG_FALLBACK_PROTOCOL       = 0x47,
    ARG_RETRY_TIMEOUT           = 0x48,

    ARG_MAX_NUM
} faspmgmt_arg_names_t;

extern char const* const faspmgmt_arg_name_str[];

/**
 * Error codes
 */
typedef enum {
    ERR_FASP_PROTO = 0x01,      //    Generic FASP protocol error
    ERR_ASCP,                   //    Generic SCP error
    ERR_AMBIGUOUS_TARGET,       //    Target incorrectly specified
    ERR_NO_SUCH_FILE,           //    No such file or directory
    ERR_NO_PERMS,               // 5  Insufficient permission to read or write
    ERR_NOT_DIR,                //    Target is not a directory
    ERR_IS_DIR,                 //    File is a directory - expected regular file
    ERR_USAGE,                  //    Incorrect usage of scp command
    ERR_LIC_DUP,                //    Duplicate license
    ERR_LIC_RATE_EXCEEDED,      // 10 Rate exceeds the cap imposed by license
    ERR_INTERNAL_ERROR,         //    Internal error (unexpected error)
    ERR_TRANSFER_ERROR,         //    Error establishing control connection
    ERR_TRANSFER_TIMEOUT,       //    Timeout establishing control connection
    ERR_CONNECTION_ERROR,       //    Error establishing data connection
    ERR_CONNECTION_TIMEOUT,     // 15 Timeout establishing data connection
    ERR_CONNECTION_LOST,        //    Connection lost
    ERR_RCVR_SEND_ERROR,        //    Receiver fails to send feedback
    ERR_RCVR_RECV_ERROR,        //    Receiver fails to receive data packets,
    ERR_AUTH,                   //    Authentication failure
    ERR_NOTHING,                // 20 Nothing to transfer
    ERR_NOT_REGULAR,            //    Not a regular file (special file)
    ERR_FILE_TABLE_OVR,         //    File table overflow
    ERR_TOO_MANY_FILES,         //    Too many files open
    ERR_FILE_TOO_BIG,           //    File too big for file system
    ERR_NO_SPACE_LEFT,          // 25 No space left on disk
    ERR_READ_ONLY_FS,           //    Read only file system
    ERR_SOME_FILE_ERRS,         //    Some individual files failed
    ERR_USER_CANCEL,            //    Cancelled by user
    ERR_LIC_NOLIC,              //    License not found or unable to access
    ERR_LIC_EXPIRED,            // 30 License expired
    ERR_SOCK_SETUP,             //    Unable to setup socket (create, bind, etc ...)
    ERR_OUT_OF_MEMORY,          //    Out of memory, unable to allocate
    ERR_THREAD_SPAWN,           //    Can't spawn thread
    ERR_UNAUTHORIZED,           //    Unauthorized by external auth server
    ERR_DISK_READ,              // 35 Error reading source file from disk
    ERR_DISK_WRITE,             //    Error writing to disk
    ERR_AUTHORIZATION,          //    External authorization failure
    ERR_LIC_ILLEGAL,		//    Operation not permitted by license
    ERR_PEER_ABORTED_SESSION,   //    Remote peer terminated session
    ERR_DATA_TRANSFER_TIMEOUT,  // 40 Transfer stalled, timed out 
    ERR_BAD_PATH,               //    Path violates docroot containment
    ERR_ALREADY_EXISTS,         //    File or directory already exists
    ERR_STAT_FAILS,             //    Cannot stat file
    ERR_PMTU_BRTT_ERROR,        //    UDP session initiation fatal error
    ERR_BWMEAS_ERROR,           // 45 Bandwidth measurement fatal error
    ERR_VLINK_ERROR,            //    Virtual link error
    ERR_CONNECTION_ERROR_HTTP,  //    Error establishing HTTP connection
    ERR_FILE_ENCRYPTION_ERROR,  //    File encryption error, e.g. corrupt file
    ERR_FILE_DECRYPTION_PASS,   //    File decryption bad passphrase

    ERR_UNDEFINED
} faspmgmt_error_code_t;

typedef enum {
    e_faspmgmt_ok = 0,
    e_faspmgmt_conn_error = -1,
    e_faspmgmt_conn_closed = -2,
    e_faspmgmt_parsing_error = -3
} faspmgmt_read_code_e;

/**
 * Structure representing a FASP message
 */
typedef struct {

    unsigned short  ver;
    faspmgmt_cmd_t  cmd;
    char            args[ARG_MAX_NUM][ARG_MAX_LEN];

} faspmgmt_args_t;

/**
 * Initialize a FASP message structure.
 */
FASPMGMT_DLLEXPORT int 
faspmgmt_init_args(faspmgmt_args_t *a);

/**
 * Read and parse a full FASP message from the socket. Store
 * the message in the faspmgmt_args_t structure.
 * Return codes: faspmgmt_read_code_e
 *      e_faspmgmt_conn_error      : Error reading char (from read_char())
 *      e_faspmgmt_conn_closed     : Connection closed (from read_char())
 *      e_faspmgmt_parsing_error   : Parsing error
 */
FASPMGMT_DLLEXPORT faspmgmt_read_code_e 
faspmgmt_read_msg(as_socket_t sock, faspmgmt_args_t *args);

FASPMGMT_DLLEXPORT faspmgmt_read_code_e 
faspmgmt_read_msg_buf(char* buffer, int length, faspmgmt_args_t *args);

faspmgmt_read_code_e faspmgmt_read_msg_helper(faspmgmt_args_t *args, as_socket_t sock, char* buffer);

/**
 * Write a full FASP message to the socket. The message
 * must be passed in the faspmgmt_args_t structure.
 * @return 0 on success
 *         FASPMGMT_ERR_BAD_CMD
 *         FASPMGMT_ERR_SOCK_ERR
 */
FASPMGMT_DLLEXPORT int
faspmgmt_send_msg(as_socket_t sock, faspmgmt_args_t *a);

FASPMGMT_DLLEXPORT int
faspmgmt_write_msg_buf(char* buffer, int* length, faspmgmt_args_t *a);

/**
 * Convert error codes to strings.
 */
FASPMGMT_DLLEXPORT const char *
faspmgmt_err2str(int errcode);

/**
 * Convert FASP managment command ID to string.
 */
FASPMGMT_DLLEXPORT const char *
faspmgmt_cmd2str(int cmd);

/**
 * Convert FASP management field ID to string.
 */
FASPMGMT_DLLEXPORT const char *
faspmgmt_field2str(int field);

/**
 * Return a printable string to display the contents of 
 * the faspmgmt_args_t structure.
 * Caller must free the string.
 */
FASPMGMT_DLLEXPORT char *
faspmgmt_args2str(const faspmgmt_args_t *a);

FASPMGMT_DLLEXPORT int
faspmgmt_err_is_resumable(int errcode);

FASPMGMT_DLLEXPORT int
faspmgmt_err_is_retryable(int errcode);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
