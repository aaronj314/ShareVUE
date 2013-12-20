/*
 * asuuid.h
 *
 * Aspera, Inc.
 */

#ifndef _AS_UUID_H_
#define _AS_UUID_H_

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#include <Rpc.h>
#elif defined LINUX || defined SOLARIS || defined AIX
#define HAS_LIBUUID
#include <uuid/uuid.h>
#elif defined FREEBSD
#include <uuid.h>
#elif defined APPLE
#include <CoreFoundation/CoreFoundation.h>
#else
#error "Error: UUID support for this platform not implemented"
#endif  /* WIN32 */

#define AS_MAX_UUID_STR_SIZE  (36)

typedef struct {
#ifdef WIN32
    UUID muuid;
#elif defined HAS_LIBUUID
    uuid_t muuid;
#elif defined FREEBSD
    uuid_t muuid;
#elif defined APPLE
    CFUUIDRef muuid;
#endif
} as_uuid_t;

/*
 * @brief   Init UUID handle
 * @param   u       UUID handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_uuid_init(
    as_uuid_t *u);

/*
 * @brief   Get UUID string
 * @param   u       UUID handle
 * @param   out     UUID buffer
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_uuid_string(
    as_uuid_t *u, 
    char *out);

/*
 * @brief   Destroy UUID handle
 * @param   u       UUID handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_uuid_destroy(
    as_uuid_t *u);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _AS_UUID_H_ */
