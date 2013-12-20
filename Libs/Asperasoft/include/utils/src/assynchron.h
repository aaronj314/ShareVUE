#ifndef _AS_SYNCHRON_H_
#define _AS_SYNCHRON_H_

#include "asplatform.h"
#ifdef WIN32
#define AS_SEM_VALUE_MAX    (32767)     /* 2^15 - 1 */
#else
#include <pthread.h>
#if defined ISILON || defined FREEBSD || defined APPLE || defined LINUX || defined SOLARIS
#include <sys/sem.h>
#include <sys/ipc.h>
#include <semaphore.h>
#else
#include <semaphore.h>
#endif
#endif

/* Data Structures */

typedef struct {
#ifdef WIN32
    HANDLE mutex;
    volatile DWORD ownerthread;
#else
    pthread_mutex_t mutex;
#endif
} as_mutex_t;

typedef struct {
#ifdef WIN32
    HANDLE sem;
#elif defined ISILON || defined FREEBSD || defined APPLE || defined LINUX || defined SOLARIS
    int sem;
#else
    sem_t *sem;
#endif
} as_named_mutex_t;

typedef struct {
    as_mutex_t *mutex;
#ifdef WIN32
    HANDLE event;
#else
    pthread_cond_t condvar;
#endif
} as_cond_t;

typedef struct {
#ifdef WIN32
    HANDLE sem;
#elif defined APPLE
    sem_t *sem;
#else
    sem_t sem;
#endif
} as_sem_t;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Initialize mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_named_mutex_init(
    as_named_mutex_t* m,
    const char *name);

/*
 * @brief   Destroy mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_named_mutex_destroy(
    as_named_mutex_t* m);

/*
 * @brief   Acquire mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_named_mutex_acquire(
    as_named_mutex_t* m);

/*
 * @brief   Acquire mutex non-blocking
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_named_mutex_acquire_nb(
    as_named_mutex_t* m);
 
/*
 * @brief   Release mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_named_mutex_release(
    as_named_mutex_t* m);


/*
 * @brief   Initialize mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_mutex_init(
    as_mutex_t* m);

/*
 * @brief   Init recursive mutex
 * I.e.  a mutex that uses a lock count.
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_mutex_init_recursive(
    as_mutex_t* m);

/*
 * @brief   Destroy mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_mutex_destroy(
    as_mutex_t* m);

/*
 * @brief   Acquire mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_mutex_acquire(
    as_mutex_t* m);

/*
 * @brief   Acquire mutex non-blocking
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_mutex_acquire_nb(
    as_mutex_t* m);
 
/*
 * @brief   Release mutex
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_mutex_release(
    as_mutex_t* m);

/*
 * @brief   Init condition variable
 * @param   cv          Condition handle
 * @param   m           Mutex handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_cond_init(
    as_cond_t* cv, 
    as_mutex_t* m);
    
/*
 * @brief   Destroy condition variable
 * @param   cv          Condition handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_cond_destroy(
    as_cond_t* cv);
    
/*
 * @brief   Condition wait
 * @param   cv          Condition handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_cond_wait(
    as_cond_t* cv);
 
/*
 * @brief   Signal condition variable
 * @param   cv          Condition handle 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_cond_signal(
    as_cond_t* cv);

/*
 * @brief   Init semaphore
 * @param   s           Sem handle
 * @param   value       Init value
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sem_init(
    as_sem_t* s, 
    u_int32_t value);

/*
 * @brief   Destroy semaphore
 * @param   s           Sem handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sem_destroy(
    as_sem_t* s);

/*
 * @brief   Post semaphore
 * @param   s           Sem handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sem_post(
    as_sem_t* s);

/*
 * @brief   Wait semaphore
 * @param   s           Sem handle 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sem_wait(
    as_sem_t* s);

/*
 * @brief   Wait sem non-blocking
 * @param   s           Sem handle
 * @param   tout_millisec   Timeout in millisecs
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sem_trywait(
    as_sem_t* s,
    u_int32_t tout_millisec);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
