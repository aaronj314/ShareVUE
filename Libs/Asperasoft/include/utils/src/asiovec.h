/*
 * asiovec.h
 *
 * Aspera, Inc.
 *
 */

#ifndef _AS_IOVEC_H_
#define _AS_IOVEC_H_

#include "asplatform.h"

#ifdef WIN32
#define HAVE_IOVEC_H 1
#else
#define HAVE_IOVEC_H 1
#endif

#if HAVE_IOVEC_H
#ifndef WIN32
#include <sys/uio.h>
#endif
#endif

#ifdef WIN32
typedef char FAR *as_iovbase_t;
typedef u_long as_iovlen_t;
typedef WSABUF as_iovec_t;
#elif !HAVE_IOVEC_H
typedef char *as_iovbase_t;
typedef unsigned int as_iovlen_t;
typedef struct as_iovec {
    char *base;
    unsigned int len;
} as_iovec_t;
#else
typedef char *as_iovbase_t;
typedef unsigned int as_iovlen_t;
typedef struct iovec as_iovec_t;
#endif

#if HAVE_IOVEC_H
#ifdef WIN32
#define as_iovec_init(iovec, b, l)      \
    do {                                \
        as_assert(iovec != NULL);          \
        (iovec)->buf = b;               \
        (iovec)->len = l;               \
    } while (0)
#define as_iovec_base(iovec)    ((iovec)->buf)
#define as_iovec_len(iovec)     ((iovec)->len)
#else
#define as_iovec_init(iovec, base, len) \
    do {                                \
        as_assert(iovec != NULL);          \
        (iovec)->iov_base = base;       \
        (iovec)->iov_len = len;         \
    } while (0)
#define as_iovec_base(iovec)    ((iovec)->iov_base)
#define as_iovec_len(iovec)     ((iovec)->iov_len)
#endif
#else
#define as_iovec_init(iovec, b, l)      \
    do {                                \
        as_assert(iovec != NULL);          \
        (iovec)->base = b;              \
        (iovec)->len = l;               \
    } while (0)
#define as_iovec_base(iovec)    ((iovec)->base)
#define as_iovec_len(iovec)     ((iovec)->len)
#endif

#endif /* _AS_IOVEC_H_ */

