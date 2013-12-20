#ifndef _AS_ERRNO_H_
#define _AS_ERRNO_H_

#include <errno.h>
#ifdef WIN32
#include <WinError.h>
#endif
#include "astypes.h"

/* ----- Aspera error offset ------- */
/* set error range from 0x7000-0x7FFF */
#define AS_ERR_OFFSET   (0x7000)    
#define AS_ERR(x)       (AS_ERR_OFFSET + x)
/* ----- Aspera error offset ------- */

enum e_aserrno {
    AS_OK,
#ifdef WIN32
    AS_ENOENT       = ERROR_FILE_NOT_FOUND,
    AS_ESRCH        = ERROR_PATH_NOT_FOUND,
    AS_EACCES       = ERROR_ACCESS_DENIED,
    AS_EMFILE       = ERROR_TOO_MANY_OPEN_FILES,
    AS_ENFILE       = ERROR_TOO_MANY_OPEN_FILES,
    AS_EADDRINUSE   = WSAEADDRINUSE,
    AS_EAGAIN       = WSAEWOULDBLOCK,
    AS_EWOULDBLOCK  = WSAEWOULDBLOCK,
    AS_EINTR        = EINTR,
    AS_EINVAL       = EINVAL,
    AS_ECONNREFUSED = WSAECONNREFUSED,
    AS_EISCONN      = WSAEISCONN,
    AS_ECONNRESET   = WSAECONNRESET,
    AS_EINPROGRESS  = WSAEINPROGRESS,
    AS_EMSGSIZE     = WSAEMSGSIZE,
    AS_ENOTCONN     = WSAENOTCONN,
    AS_EPATHMAX     = ERROR_FILENAME_EXCED_RANGE,
    AS_ENOTDIR      = ERROR_DIRECTORY,
    AS_ENOBUFS      = WSAENOBUFS,
    AS_ENOTREADY    = ERROR_NOT_READY,
    AS_ENOMEM       = ERROR_NOT_ENOUGH_MEMORY,
    AS_EBADF        = ERROR_INVALID_HANDLE,
    AS_ENOSPC       = ERROR_OUTOFMEMORY,
    AS_ERANGE       = ERROR_INSUFFICIENT_BUFFER,
    AS_EPERM        = ERROR_INVALID_FUNCTION,
    AS_ENOTEMPTY    = ENOTEMPTY,
#else /* Non Windows platforms */
    AS_ENOENT       = ENOENT,
    AS_ESRCH        = ESRCH,
    AS_EACCES       = EACCES,
    AS_EMFILE       = EMFILE,
    AS_ENFILE       = ENFILE,
    AS_EADDRINUSE   = EADDRINUSE,
    AS_EAGAIN       = EAGAIN,
#ifndef EWOULDBLOCK
    AS_EWOULDBLOCK  = EAGAIN,
#else
    AS_EWOULDBLOCK  = EWOULDBLOCK,
#endif
    AS_EINTR        = EINTR,
    AS_EINVAL       = EINVAL,
    AS_ECONNREFUSED = ECONNREFUSED,
    AS_EISCONN      = EISCONN,
    AS_ECONNRESET   = ECONNRESET,
    AS_EINPROGRESS  = EINPROGRESS,
    AS_EMSGSIZE     = EMSGSIZE,
    AS_ENOTCONN     = ENOTCONN,
    AS_EPATHMAX     = ENAMETOOLONG,
    AS_ENOTDIR      = ENOTDIR,
    AS_ENOBUFS      = ENOBUFS,
    AS_ENOTREADY    = EBUSY,
    AS_ENOMEM       = ENOMEM,
    AS_EBADF        = EBADF,
    AS_ENOSPC       = ENOSPC,
    AS_ERANGE       = ERANGE,
    AS_EPERM        = EPERM,
    AS_ENOTEMPTY    = ENOTEMPTY,
#endif
    /* -------- Aspera errors ---------- */
    AS_EDOCROOT     = (AS_ERR(0)),
    AS_ETOKENIZER   = (AS_ERR(1)),
    AS_EBASENAME    = (AS_ERR(2)),
    AS_EPATHMATCH   = (AS_ERR(3)),
    AS_EILLUTFSTR   = (AS_ERR(4)),
    AS_EBUFFER      = (AS_ERR(5)),
    AS_EDIREND      = (AS_ERR(6)),
    AS_ELIBERR      = (AS_ERR(7)),
    AS_ELIBMODERR   = (AS_ERR(8)),
    AS_EUUID        = (AS_ERR(9)),
    AS_EXMLPARSER   = (AS_ERR(10)),
    AS_ELOCALE      = (AS_ERR(11)),
    AS_EMD5SUM      = (AS_ERR(12)),
    AS_ELOG         = (AS_ERR(13)),
    AS_EUNAME       = (AS_ERR(14)),
    AS_EUACPARSE    = (AS_ERR(15))
/* -------- Aspera errors ---------- */
}; 

/*
 * ------ Aspera error table ------ 
 * To get errstr, should - AS_ERR_OFFSET
 * from the errno, or call as_get_errstr()
 */
extern const char *g_as_err_table[];
extern const u_int16_t g_as_err_count;
/* ------ Aspera error table ------ */
 
#endif /* _AS_ERRNO_H_ */
