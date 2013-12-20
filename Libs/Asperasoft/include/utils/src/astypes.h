#ifndef _AS_TYPE_H_
#define _AS_TYPE_H_

#ifndef MAX_U64
#ifdef WIN32
#define MAX_U64     0xffffffffffffffffI64
#else
#define MAX_U64     0xffffffffffffffffLL
#endif  /* WIN32 */
#endif  /* MAX_U64 */

#include <sys/types.h>

#define AS_TRUE     (1)
#define AS_FALSE    (0)

/* Integral Types */

/* Signed 8-bit integral datatype */
/* typedef int8_t */

/* Signed 16-bit integral datatype */
/* typedef int16_t */

/* Signed 32-bit integral datatype */
/* typedef int32_t */

/* Signed 64-bit integral datatype */
/* typedef int64_t */

/* Unsigned 8-bit integral datatype */
/* typedef u_int8_t */

/* Unsigned 16-bit integral datatype */
/* typedef u_int16_t */

/* Unsigned 32-bit integral datatype */
/* typedef u_int32_t */

/* Unsigned 64-bit integral datatype */
/* typedef u_int64_t */

typedef int                 bool_t;
#ifdef WIN32
#ifdef VSTUDIO
typedef char                int8_t;
typedef short               int16_t;
typedef long                int32_t;
typedef __int64             int64_t;
typedef unsigned char       u_int8_t;
typedef unsigned short      u_int16_t;
typedef unsigned long       u_int32_t;
typedef unsigned __int64    u_int64_t;
#else
#ifndef _STDINT_H   /* Ming stdint.h defines the int bitdepth types */
typedef char                int8_t;
typedef short               int16_t;
typedef long                int32_t;
typedef long long           int64_t;
#endif
typedef unsigned char       u_int8_t;
typedef unsigned short      u_int16_t;
typedef unsigned long       u_int32_t;
typedef unsigned long long  u_int64_t;
#endif  /* VSTUDIO */
/* Remove if ssize_t shows up... */
typedef int64_t             ssize_t;
#endif  /* WIN32 */

#ifdef SOLARIS
typedef uint8_t             u_int8_t;
typedef uint16_t            u_int16_t;
typedef uint32_t            u_int32_t;
typedef uint64_t            u_int64_t;
#endif  /* SOLARIS */

typedef int                 as_err_t;

#endif  /* _AS_TYPES_H_ */
