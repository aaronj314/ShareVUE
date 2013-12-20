#ifndef _AS_SELECT_H_
#define _AS_SELECT_H_

#include "asplatform.h"
#include "astypes.h"
#include "astime.h"
#include "assocket.h"

typedef struct {
    /* 
     * fd index starts from 0
     * 0 is a valid value for maxfd and readymaxfd
     */
    int maxfd;          /* max fd in fd set, on windows max fd index in fd_set */
    int readymaxfd;     /* max fd in readyfd set, on windows max fd index in fd_set */
    fd_set fds;         /* fd set to poll on */
    fd_set readyfds;    /* fd set masked by select as ready */
} as_fd_set_t;

#ifdef __cplusplus
extern "C" {
#endif

ASUTILS_API as_err_t
as_select_setfdlimit(
    int fdlimit);

/*
 * @brief   Set select
 * @param   readfds     Read file descriptors
 * @param   writefds    Write file descriptors
 * @param   exceptfds   File descriptors to ignore
 * @oaran   timeout     Select timeout
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_select(
    as_fd_set_t *readfds, 
    as_fd_set_t *writefds, 
    as_fd_set_t *exceptfds, 
    const as_time_val_t *timeout,
    int *ready);

ASUTILS_API as_err_t
as_select_fd_zero(
    as_fd_set_t *fdset);

ASUTILS_API as_err_t
as_select_fd_set(
    as_socket_t fd,
    as_fd_set_t *fdset);

ASUTILS_API as_err_t
as_select_fd_clr(
    as_socket_t fd,
    as_fd_set_t *fdset);

ASUTILS_API int
as_select_fd_isset(
    as_socket_t fd,
    as_fd_set_t *fdset);

ASUTILS_API int
as_select_fd_atidx(
    int idx,
    as_fd_set_t *fdset);

#ifdef __cplusplus
} /* extern "C" */
#endif

#define AS_FD_ATIDX(idx, set)   as_select_fd_atidx(idx, set)
#define AS_FD_CLR(fd, set)      as_select_fd_clr(fd, set)
#define AS_FD_SET(fd, set)      as_select_fd_set(fd, set)
#define AS_FD_ZERO(set)         as_select_fd_zero(set)
#define AS_FD_ISSET(fd, set)    as_select_fd_isset(fd, set)

#endif /* _AS_SELECT_H_ */
