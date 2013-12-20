/*
 * astime.h
 *
 * Aspera, Inc.
 */

#ifndef _AS_TIME_H_
#define _AS_TIME_H_

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct timeval as_time_val_t;
typedef struct tm as_time_tm_t;
#ifdef WIN32
typedef __time64_t as_time_t;
#else
typedef int64_t as_time_t;
#endif
typedef struct timezone as_time_zone_t;

#ifdef WIN32
/*
 * @brief   Get sys tick frequency 
 * @param   freq      sys tick frequency
 */
ASUTILS_API void as_time_sys_tick_frequency(
    u_int64_t *freq);
#endif
/*
 * @brief   Get time and timezone
 * @param   tvl        Time value
 * @param   tzone      Timezone
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_time_gettimeofday(
    as_time_val_t *tval, 
    as_time_zone_t *tzone);

/*
 * @brief   Transform epoch 
 * Converts the calendar time pointed to by timer to a broken-down 
 * time expressed as Coordinated Universal Time (UTC) and stores it in the 
 * structure pointed to by result.
 * @param   timer       Epoch
 * @param   result      Transformed time
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_time_gmtime(
    const as_time_t *timer, 
    as_time_tm_t *result);

/*
 * @brief   Time init
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_time_init(void);

/*
 * @brief   Print time
 *
 */
ASUTILS_API void 
as_time_print(void);

/*
 * @brief   Time since
 * Return the number of microseconds that have elapsed between the given time and 
 * the time of this call and store the new time in second argument.
 * This must only be used when the time difference is very small 
 * @param   old_time    t0
 * @param   new_time    t1
 * @return  time since t0,
 */
ASUTILS_API as_err_t 
as_time_getnstore_usec_since(
    as_time_val_t *old_time, 
    as_time_val_t *new_time,
    u_int64_t *timediff);

/*
 * @brief   Number of msecs since given time
 * Return the number of microseconds that have elapsed between 
 * the given time and the time of this call.
 * This must only be used when the time difference is very small 
 * @param   old_time        t0
 * @return  msecs since t0
 */
ASUTILS_API as_err_t  
as_time_get_usec_since_small(
    as_time_val_t *old_time,
    u_int64_t *timediff);

/*
 * @brief   Number of msecs since given time
 * Should be called when time difference is large
 * @param   old_time    t0
 * @return  msecs sine t0
 */
ASUTILS_API as_err_t  
as_time_get_usec_since(
    as_time_val_t *old_time,
    u_int64_t *timediff);

/*
 * @brief   Get usec time difference
 * @param   time_one    t0
 * @param   time_two    t1
 * @return  msecs since t0 to t1
 *   < 0 if time_one earlier than time_two
 *     0 if time_one equals time_two
 *   > 0 if time_one later than time_two
 */
ASUTILS_API int64_t 
as_time_get_usec_diff(
    as_time_val_t *time_one, 
    as_time_val_t *time_two);

/*
 * @brief   Decrement time val
 * n_usec must be less than 1,000,000.
 * @param   tv          Time value
 * @param   n_usec      Number of usecs to decrement
 */
ASUTILS_API void 
as_time_tv_dec(
    as_time_val_t *tv, 
    u_int32_t n_usec);

/*
 * @brief   Increment time val
 * @param   tv          Time value
 * @param   n_usec      Number of usecs to increment
 */
ASUTILS_API void 
as_time_tv_incr(
    as_time_val_t *tv, 
    u_int64_t n_usec);

/*
 * @brief   Convert time to a string
 * Converts given time into a string
 * @param   time        Time value
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_time_strftime(
    const as_time_t *tnow,
    char *buf,
    size_t bsize);

ASUTILS_API as_err_t
as_time_localtime(
    const as_time_val_t *tnow, 
    as_time_tm_t *tmnow);

ASUTILS_API as_err_t
as_time_mktime(
    as_time_tm_t *tmnow,
    as_time_t *tnow);

ASUTILS_API as_err_t
as_time_convert_epoch(
    as_time_t* as_time, 
    as_time_t native_time);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _AS_TIME_H_ */
