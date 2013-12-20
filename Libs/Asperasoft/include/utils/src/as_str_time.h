/*
 * as_str_time.h
 *
 * Aspera Inc.
 * 
 * Conversion between string and time format
 */

#ifndef _AS_STR_TIME_H
#define _AS_STR_TIME_H

#include "asplatform.h"
#include "astime.h"

#ifdef __cplusplus
extern "C" {
#endif

ASUTILS_API as_err_t
as_time_strptime(const char *s, 
                 const char *fmt,
                 const char *endp,
                 as_time_tm_t *tm);

#ifdef __cplusplus
}
#endif

#endif 
