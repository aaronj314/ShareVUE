/*
 * asprocess.h
 *
 * Cross platform process handling routines.
 *
 * Aspera Inc.
 */

#ifndef _AS_PROCESS_H_
#define _AS_PROCESS_H_

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef WIN32
#include <grp.h>
#endif

typedef struct {
#ifdef WIN32
    PROCESS_INFORMATION p_info;
    HANDLE token;                   /* logged on token */
    WCHAR wlogin[AS_MAX_USER_NAME]; /* login user name */
    WCHAR wdomain[AS_MAX_USER_NAME];/* domain */
#else
    pid_t pid;
#endif
} as_process_t;

typedef enum {
    AS_PROCESS_WAIT_SIGNALLED,
    AS_PROCESS_WAIT_TIMEDOUT,
    AS_PROCESS_WAIT_ABANDONED,
    AS_PROCESS_WAIT_ERROR
} as_process_wait_t;

typedef enum {
    AS_PROCESS_ACTIVE,
    /* 
     * Normal child termination with exit or return from main,
     * exit code or return value is set 
     */
    AS_PROCESS_EXITED,
    /* 
     * Abnormal child termination, exit code is not set
     */
    AS_PROCESS_TERMINATED
} as_process_state_t;

/*
 *  Process flags
 */
typedef enum {
    /* 
     * Detach parent process from child, otherwise parent 
     * must wait on child process to avoid zombies.
     */
    AS_PROCESS_DETACH = 1 << 0,
    /*
     * Close all file descriptors except stdin, stdout and stderr,
     * otherwise child process inherits parents file descriptors.
     */
    AS_PROCESS_CLOSE_FDS = 1 << 1,
    AS_PROCESS_INHERIT_STDIN = 1 << 2,
    /*
     *  Redirect stdout and stderr to /dev/null
     */
    AS_PROCESS_REDIRECT_STDOUT = 1 << 3,
    AS_PROCESS_REDIRECT_STDERR = 1 << 4
} as_process_flags_t;

/* 
 *  Callback func to call just before spawning cmd 
 *  This could be used for switching user context etc.
 */
typedef as_err_t (*as_process_func_t)(as_process_t *p, void *);

/*
 * @brief   Spawn a process
 * @param   p       Process handle
 * @param   cmd     Command to run
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_process_create(
    as_process_t *p, 
    const char *cmd);

/*
 * @brief   Spawn a process
 * New process is detached from the parent process,
 * i.e. parent doesn't need to call as_process_wait() or 
 * as_process_waitany() to avoid zombie processes
 * New process doesn't inherit parent's open file descriptors
 * @param   cmd     Command to run including commandline arguments
 * @param   env     Environment variable array for the process in xx=yy format
 *                  each variable,value string must be NULL terminated and
 *                  last element of the array must be NULL
 * @param   envcount number of env variables in env array, such that env[envcount] = NULL
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_process_spawn(
    const char *cmd, 
    const char *env[],
    u_int32_t envcount);

/*
 * @brief   Default fork callback
 * @param   p       Process info struct
 * @param   data    Login name and credentials to change security context
 */
ASUTILS_API as_err_t
as_process_runas(
    as_process_t *p,
    void *data);

/*  
 * @brief   Fork child process
 * Callback function is primarily to setup security context of child process.
 * The caller shouldn't assume that they are called within the context of the parent process.
 * On windows parent process needs following tokens to create a child process in a 
 * different security context
 * SE_ASSIGNPRIMARYTOKEN_NAME : Replace a process level token
 * SE_INCREASE_QUOTA_NAME : Adjust memory quotas for a process
 * SE_RESTORE_NAME : Restore files and directories
 * SE_BACKUP_NAME : Backup files and directories
 * In addition, impersonated user must be a member of Administrators group.
 *
 * On unix platforms parent process needs root privileges 
 *
 * @param   p       Child process handle
 * @param   cmd     Command to execute in child process
 * @param   dir     Directory to execute command
 * @param   env     Environment for child process
 * @param   envsz   Environment array size such that env[envsz] == NULL
 * @param   flags   Flags to create child process
 * @param   func    Callback function to callback just before forking child process
 * @param   funcdata Data to callback function
 * @param   std_in  stdin to child process
 * @param   std_out stdout to child process
 * @param   std_err stderr to child process 
 */
ASUTILS_API as_err_t
as_process_fork(
    as_process_t *p,
    const char *cmd,
    const char *dir,
    const char *env[],
    size_t envsz,
    as_process_flags_t flags,
    as_process_func_t func,
    void *funcdata,
    int *std_in,
    int *std_out,
    int *std_err);

/*
 * @brief   Kill a process
 * Kill a process (It's better for the process to exit on its own because
 * the state of global data maintained by dynamic-link libraries (DLLs) may
 * be compromised by calling this method)
 * @param   p       Process handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_process_kill(
    as_process_t *p);

/*
 * @brief   Wait for process to finish
 * @param   p           Process handle
 * @param   t_ms        Wait time in milliseconds
 * @param   state       Wait state
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_process_wait(
    as_process_t *p, 
    u_int32_t t_ms,
    as_process_wait_t *state);

/*
 * @brief   Wait for any child process to finish
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_process_waitany(void);

/*
 * @brief   Check if process is alive
 * @param   p           Process handle
 * @param   state       Process state
 * @param   exitcode    Exit code of the process
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_process_exited(
    as_process_t *p,
    as_process_state_t *state,
    int32_t *exitcode);

/*
 * @brief   Set process env with value
 * @param   name        Env variable name
 * @param   value       Env variable value
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_process_setenv(
    const char *name, 
    const char *val);

/*
 * @brief   Get process env with name
 * @param   name        Env variable name
 * @param   buf         Env variable buffer
 * @param   bufsz       Env variable buffer size
 * @return  0 on success, errno on error
 *          AS_EINVAL if variable is not found
 */
ASUTILS_API as_err_t
as_process_getenv(
    const char *name,
    char *buf,
    size_t bufsz);


#ifndef WIN32
/*
 * @brief   Get password file entry for given username
 * @param   uname       Username
 * @param   pwbuf       Address of a 'struct passwd'
 * @param   buf         Buffer to hold data pointed to by above struct.
 * @param   bsize       Size of this buffer
 */
ASUTILS_API as_err_t
as_process_getpwnam(
    const char *uname,
    struct passwd *pwbuf,
    char *buf,
    size_t bsize);

/*
 * @brief   Get group file entry for given group name
 * @param   gname       Group name
 * @param   grbuf       Address of a 'struct group'
 * @param   buf         Buffer to hold data pointed to by above struct.
 * @param   bsize       Size of this buffer
 */
ASUTILS_API as_err_t
as_process_getgrnam(
    const char *gname,
    struct group *grbuf,
    char *buf,
    size_t bsize);
#endif

#ifdef __cplusplus
} /* End extern "C" */
#endif /* __cplusplus */

#endif /* _AS_PROCESS_H_ */
