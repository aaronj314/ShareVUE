#ifndef _AS_THREAD_H_
#define _AS_THREAD_H_

#include "asplatform.h"

#ifdef WIN32
typedef LPTHREAD_START_ROUTINE as_thread_func_t;
#else
typedef void *(*as_thread_func_t)(void *);
#endif  /* WIN32 */

/* 
 * BSD's define pthread_t as void *
 * make sure that we don't do lower casts
 */
typedef unsigned long long as_thread_id_t;

typedef struct {
#ifdef WIN32
    HANDLE thandle;
    DWORD  tid;
#else
    pthread_t thandle;
#endif
} as_thread_t;

typedef struct {
    as_thread_t *thread;
    void *arg;
} as_thread_arg_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Creates a thread
 * @param   th          Thread handle
 * @param   func        Pointer to function to be executied
 * @param   parm        Painter to a variable to be passed to the thread
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_thread_spawn(
    as_thread_t *th, 
    as_thread_func_t func, 
    void* parm); 

/*
 * @brief   Wait for a thread to terminate
 * @param   th          Thread handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_thread_join(
    as_thread_t* th); 

/*
 * @brief   Thread sleep
 * @param   msec        Sleep time
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_thread_sleep(
    int msec);

/*
 * @brief   Get thread id
 * @return  thread id
 */
ASUTILS_API as_thread_id_t 
as_thread_self(void);

ASUTILS_API as_thread_id_t
as_thread_getid(
    as_thread_t *th);

ASUTILS_API void
as_thread_exit(
    int retval);

typedef struct as_thread_cache_t as_thread_cache_t;

#define AS_THREAD_CACHE (1)

#ifdef AS_THREAD_CACHE
ASUTILS_API as_err_t
as_thread_cache_init(
    as_thread_cache_t **cache);

ASUTILS_API as_err_t
as_thread_cache_submitjob(
    as_thread_cache_t *cache,
    as_thread_func_t jobfunc, 
    void *jobparam);

ASUTILS_API as_err_t
as_thread_cache_term(
    as_thread_cache_t **cache);
#else
    #define as_thread_spawn_cached(head, th, func, parm) head = head, as_thread_spawn(th, func, parm)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _AS_THREAD_H_ */
