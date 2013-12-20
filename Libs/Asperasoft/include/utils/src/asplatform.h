/*
 * Platform specific definitions and code
 */

#ifndef _AS_PLATFORM_H_
#define _AS_PLATFORM_H_

/* Don't add any #includes before this */
#ifdef WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS     (1)
#endif
#ifndef WINVER
// _WIN32_WINNT_WINXP is not defined in the plain vanilla version of Visual Studio 2005,
// so we hard code instead.  This is OK since it is effectively impossible for this
// number to ever change.  Microsoft would have to retroactively change the version #
// of XP.  Good luck with that.
#define WINVER          (0x501)
#endif 
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT    (0x501)  // (_WIN32_WINNT_WINXP) 
#endif 
#ifndef NTDDI_VERSION 
#define NTDDI_VERSION   (NTDDI_WINXPSP2) 
#endif
/*
    If we want to be able to select more than 64 sockets in windows (say, 1024), we would put:

#define FD_SETSIZE 1024

    right here.  Do we?
*/
#include <winsock2.h>  /* Must be included before windows.h */
#include <winbase.h>
#include <windows.h>
#include <wincrypt.h>
#include <ws2tcpip.h>
#include <time.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <io.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <time.h>
#include <utime.h>
#include <dirent.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <pwd.h>
#if defined APPLE || defined FREEBSD
#include <sys/sysctl.h>
#elif defined SOLARIS
#include <alloca.h>
#include <stropts.h>
#elif defined AIX
#include <alloca.h>
#endif
#endif /* WIN32 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#include "astypes.h"
#include "asdefs.h"
#include "aserrno.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Maximum number of chars in user name */
#define AS_MAX_USER_NAME    (512)

#ifdef WIN32
/* Does this platform enforce case sensitivity in user names? */
#define AS_PLATFORM_IGNORE_USERNAME_CASE    (1)
#else
#define AS_PLATFORM_IGNORE_USERNAME_CASE    (0)
#endif

#ifdef WIN32
#ifdef MAX_PATH
#define AS_MAX_PATH     (MAX_PATH << 1)
#else
#error PATH_MAX not defined
#endif
#else
#ifdef PATH_MAX
#define AS_MAX_PATH     (PATH_MAX << 1)
#else
#error PATH_MAX not defined
#endif
#endif /* WIN32 */

#define AS_MAX_BUFFER   (4096)
#define AS_MAX_LOCALE   (128)

#ifndef AS_BIG_ENDIAN
#if defined(__sparc__) || defined(__ppc__) || defined(_POWER) || \
    defined(__sparc64__) || defined(__ppc64__)
#define AS_BIG_ENDIAN   (1)
#endif
#endif

/*
 * @brief   Get build version 
 * @param   strver      Buffer
 */
ASUTILS_API void 
as_platform_build_ver(
    char *strver);

/*
 * @brief   Get build os  
 * @param   strver      Buffer
 */
ASUTILS_API void 
as_platform_build_os(
    char *stros);

/*
 * @brief   Get OS information 
 * Type of Operating System
 * @param   buf         Buffer 
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_os(
    char *buf,
    size_t bsize);

/*
 * @brief   Get hostname
 * @param   buf         Buffer 
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_platform_hostname(
    char *buf,
    size_t bsize);

/*
 * @brief   Get Aspera root file path
 * Aspera file paths
 * @param   buf         Buffer 
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_root(
    char *buf,
    size_t bsize);

/*
 * @brief   Get error string for errno 
 * Set errstr to a descriptive error message for the given error number 
 * @param   err         Errno 
 * @param   errstr      Error string
 * @param   bsize       Size of errstr buffer
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_errstr(
    int err,
    char *errstr,
    size_t bsize);

/*
 * @brief   Get error string inline
 * @param   err         Errno 
 * @param   errstr      Error string
 * @param   bsize       Size of errstr buffer
 * @return  error message
 */
ASUTILS_API const char *
as_platform_errstr_inline(
    int err,
    char *errstr,
    size_t bsize);

/*
 * @brief Init threads 
 */
ASUTILS_API void 
as_platform_thread_init(
    void);

/*
 * @brief   Get user name for a uid
 * Return user name for the uid
 * @param   uid         User id 
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_uname(
    int uid,
    char *buf,
    size_t bsize);

/*
 * @brief   Get current user name from environment
 * @param   buf         User Name buffer
 * @param   bufsz       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_platform_usr(
    char *buf,
    size_t bufsz);

/*
 * @brief   Get group name for a gid 
 * Return group name of the gid
 * @param   gid         Group id 
 * @param   buf         Buffer
 * @param   bsize       Buffer size 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_gname(
    int gid,
    char *buf,
    size_t bsize);

/*
 * @brief   Get current user's uid
 * @param   uid         User Id
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_uid(
    int *uid);

typedef struct {
    char language[AS_MAX_LOCALE + 1];
    char territory[AS_MAX_LOCALE + 1];
    char codeset[AS_MAX_LOCALE + 1];
} as_platform_locale_t;

/*
 * @brief   Get locale
 * @param   loc         Locale buffer
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_platform_locale(
    as_platform_locale_t *loc);

typedef struct as_platform_dev_t {
    char devname[AS_MAX_PATH];      /* Drive name */
    struct as_platform_dev_t *next;
} as_platform_dev_t;

/*
 * @brief   Get platform drive list
 * Allocate memory for the drive list, should call as_platform_free_drives
 * to deallocate this memory.
 * @param   devlst      Device/drive list 
 */
ASUTILS_API as_err_t
as_platform_drives(
    as_platform_dev_t **devlst);

/*
 * @brief   Release previously created dev list
 * @param   devlst      Device/drive list
 */
ASUTILS_API as_err_t
as_platform_free_drives(
    as_platform_dev_t **devlst);


typedef struct as_platform_mnt_t {
    char mntfs[AS_MAX_PATH];        /* File system */
    char mntdir[AS_MAX_PATH];       /* Mount point */
    char mnttype[AS_MAX_PATH];      /* Mount type */
    u_int64_t mnttotal;             /* Total disk space */
    u_int64_t mntused;              /* Used space */
    u_int64_t mntfree;              /* Free space */
    u_int64_t mntfcount;            /* File count */
    int32_t mnterrno;               /* Mount error */
    u_int64_t mntdev;               /* Mount device in unix */
    struct as_platform_mnt_t *next;
} as_platform_mnt_t; 

/*
 * @brief   Get platform mount list
 * Allocate memory for the mount list, should call as_platform_free_mnt
 * to deallocate this memory.
 * @param   mntlst      Mount list
 * @param   path        File/Directory path for a specific device
 */
ASUTILS_API as_err_t
as_platform_mnt(
    as_platform_mnt_t **mntlst,
    const char *path);

/*
 * @brief   Release previously created mnt list
 * @param   mntlst      Mount list
 */
ASUTILS_API as_err_t
as_platform_free_mnt(
    as_platform_mnt_t **mntlst);

#ifdef WIN32
/*
 * @brief   Get windows file path 
 * Get Aspera path on windows
 * @param   buf         Buffer 
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_platform_winpath(
    char *buf,
    size_t bsize);
#endif

/*
 * Alignment and byte ordering
 */
typedef union { u_int16_t i; u_int8_t b[2]; } as_union16_t;
typedef union { u_int32_t i; u_int8_t b[4]; } as_union32_t;
typedef union { u_int64_t i; u_int8_t b[8]; } as_union64_t;

#ifdef AS_BIG_ENDIAN

#define cp16bit(d, s)                   \
    do {                                \
        memcpy(d, s, 2);                \
    } while (0)
#define cp32bit(d, s)                   \
    do {                                \
        memcpy(d, s, 4);                \
    } while (0)
#define cp64bit(d, s)                   \
    do {                                \
        memcpy(d, s, 8);                \
    } while (0)

#define enc08bits(buf, val)             \
    do {                                \
        *((u_int8_t *)(buf)) = val;     \
    } while (0)
#define enc16bits(buf, val)             \
    do {                                \
        as_union16_t vu;                \
        vu.i = htons(val);              \
        memcpy(buf, vu.b, 2);           \
    } while (0)
#define enc32bits(buf, val)             \
    do {                                \
        as_union32_t vu;                \
        vu.i = htonl(val);              \
        memcpy(buf, vu.b, 4);           \
    } while (0)
#define enc64bits(buf, val)             \
    do {                                \
        as_union64_t vu;                \
        vu.i = as_htonll(val);          \
        memcpy(buf, vu.b, 8);           \
    } while (0)

#define dec08bits(val, buf)             \
    do {                                \
        val = (*((u_int8_t *)(buf)));   \
    } while (0)
#define dec16bits(val, buf)             \
    do {                                \
        as_union16_t vu;                \
        memcpy(vu.b, buf, 2);           \
        val = ntohs(vu.i);              \
    } while (0)
#define dec32bits(val, buf)             \
    do {                                \
        as_union32_t vu;                \
        memcpy(vu.b, buf, 4);           \
        val = ntohl(vu.i);              \
    } while (0)
#define dec64bits(val, buf)             \
    do {                                \
        as_union64_t vu;                \
        memcpy(vu.b, buf, 8);           \
        val = as_ntohll(vu.i);          \
    } while (0)

#else /* x86 */

#define cp16bit(d, s)                   \
    do {                                \
        *(d) = *(s);                    \
    } while (0)
#define cp32bit(d, s)                   \
    do {                                \
        *(d) = *(s);                    \
    } while (0)
#define cp64bit(d, s)                   \
    do {                                \
        *(d) = *(s);                    \
    } while (0)

#define enc08bits(buf, val)                  \
    do {                                     \
        *((u_int8_t *)(buf)) = val;          \
    } while (0)
#define enc16bits(buf, val)                  \
    do {                                     \
        *((u_int16_t *)(buf)) = htons(val);  \
    } while (0)
#define enc32bits(buf, val)                  \
    do {                                     \
        *((u_int32_t *)(buf)) = htonl(val);  \
    } while (0)
#define enc64bits(buf, val)                  \
    do {                                     \
        *((u_int64_t *)(buf)) = as_htonll(val); \
    } while (0)

#define dec08bits(val, buf)                  \
    do {                                     \
        val = (*((u_int8_t *)(buf)));        \
    } while (0)
#define dec16bits(val, buf)                  \
    do {                                     \
        val = ntohs(*((u_int16_t *)(buf)));  \
    } while (0)
#define dec32bits(val, buf)                  \
    do {                                     \
        val = ntohl(*((u_int32_t *)(buf)));  \
    } while (0)
#define dec64bits(val, buf)                  \
    do {                                     \
        val = as_ntohll(*((u_int64_t *)(buf))); \
    } while (0)
#endif

/*
 * @brief   Convert 64-bit value to network byte order
 * @param   hostvalue   64-bit value in host byte order
 * @return  corresponding 64-bit value in network byte order
 */
ASUTILS_API u_int64_t 
as_htonll(
    u_int64_t hostvalue);

/*
 * @brief   Convert 64-bit value in network byte order to host byte order
 * @param   netvalue    64-bit value in network byte order
 * @return  corresponsing 64-bit value in host byte order
 */
ASUTILS_API u_int64_t
as_ntohll(
    u_int64_t netvalue);

extern int g_as_asserts_active;
extern int g_as_asserts_skipped;

#ifndef NDEBUG
#define as_assert(x)            {if (g_as_asserts_active) assert(x); else if (!(x)) g_as_asserts_skipped++;}
#else
#define as_assert(x)
#endif

#ifdef WIN32
#define as_set_errno(e)         (SetLastError(e))
#define as_get_quadint(high, low) \
                                (((u_int64_t)high) << 32 | (u_int64_t)low)
#define as_get_highdword(x)     ((DWORD)(x & 0x00000000FFFFFFFF))
#define as_get_lowdword(x)      ((DWORD)(x >> 32))
#define __func__ __FUNCTION__
#ifndef inline
#define inline __inline
#endif
#else
#define as_set_errno(e)         (errno = e)
#endif /* WIN32 */

/* 
 * WIN32 crt doesn't set GetLastErrno for posix api's
 * we need psychic powers to detect errors here
 */
#ifdef WIN32
#define as_get_errno()       ((GetLastError() ? GetLastError() : errno))
#else
#define as_get_errno()       (errno)
#endif

/*
 * Platform specifics
 */
#ifdef SOLARIS
struct option {
   char *name;
   int has_arg;
   int *flag;
   int val;
};

extern int getopt_long(int ___argc, char *const *___argv,
                       const char *__shortopts,
                       const struct option *__longopts, int *__longind);
#endif

#if 0
#ifdef SCP_SOLARIS
#define pselect(n, r, w, e, t, m) select(n, r, w, e, t)
#endif
#endif

#ifdef WIN32
int _as_snprintf( char *output, size_t count, const char *format, ...);

#define strcasecmp(x, y)            _stricmp(x, y)
#define strncasecmp(x, y, s)        _strnicmp(x, y, s)
#define wcsncasecmp(x, y, z)        _wcsnicmp(x, y, z)
#define strtoll(str, end, base)     _strtoi64(str, end, base)
#define strtoull(str, end, base)    _strtoui64(str, end, base)
#define snprintf                    _as_snprintf
#define vsnprintf                   _vsnprintf
#define strdup                      _strdup
#define as_get_process_id           GetCurrentProcessId
#define as_get_thread_id            GetCurrentThreadId
#elif defined APPLE || defined FREEBSD
#define as_get_process_id           (unsigned int)getpid
/* pthread_t is a pointer to struct pthread */
#define as_get_thread_id            (void *)pthread_self
#else
#define as_get_process_id           (unsigned int)getpid
#define as_get_thread_id            (unsigned int)pthread_self
#endif  /* WIN32 */

/*
 * Required alignment for multi-byte (word, dword, etc.) reads.
 * Intel allows any alignment, but non-aligned reads are very slow
 * (read dword 1, shift, read dword 2, shift, combine, return).
 */
#define AS_PROCESSOR_BYTE_ALIGNMENT (8)

#ifndef NDEBUG
#define AS_COMPILE_TIME_ASSERT(v)               {static int foo = 1 / ((int) (v)); (void) foo;}
#define AS_COMPILE_TIME_ELEMENTS_CHECK(a, s)    AS_COMPILE_TIME_ASSERT( (sizeof(a)/sizeof((a)[0])) == (s))
#else
#define AS_COMPILE_TIME_ASSERT(v) 
#define AS_COMPILE_TIME_ELEMENTS_CHECK(a, s)
#endif

#define AS_ELEMENT_COUNT(a) (sizeof(a) / sizeof(a[0]))

#ifdef WIN32
# define LLD "%I64d"
# define LLU "%I64u"
# define LLX "%I64x"
# define NLLD(n) "%" #n "I64d"
# define NLLU(n) "%" #n "I64u"
#else
#if LONG_MAX == (0x7fffffffffffffffL)
#  define LLD "%ld"
#  define LLU "%lu"
#  define LLX "%lx"
#  define NLLD(n) "%" #n "ld"
#  define NLLU(n) "%" #n "lu"
#else
#  define LLD "%lld"
#  define LLU "%llu"
#  define LLX "%llx"
#  define NLLD(n) "%" #n "lld"
#  define NLLU(n) "%" #n "llu"
#endif
#endif

/*
 *  @brief  Log a descriptive system error message
 *  Log message appends user string with errno and descriptive 
 *  system error.
 *  i.e.
 *      as_syserr("Couldn't read license file", AS_ENOENT) logs
 *      "Couldn't read license file, errno:2, err desc:No such file or directory"
 *      as_syserr("Couldn't read fasp block %u", AS_ENOMEM, 30) logs
 *      "Couldn't read file block 30, errno:12, err desc:Out of memory"
 *
 *  This is mainly for diagnostics and for users, 
 *  please don't use this to print debug messages.
 *  @param  msg     A descriptive error message to the user
 *  @param  errno   System error number
 */
#define as_syserr(msgformat, err, ...)                  \
    do {                                                \
        char errstr[AS_MAX_BUFFER];                     \
        as_err(msgformat ", errno:%d, err desc:%s",     \
               ##__VA_ARGS__, err,                      \
               as_platform_errstr_inline(               \
                   err, errstr, sizeof(errstr)));       \
    } while(0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _AS_PLATFORM_H_ */
