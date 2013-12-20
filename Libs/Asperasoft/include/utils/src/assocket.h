#ifndef _AS_SOCKET_H_
#define _AS_SOCKET_H_

#include "asplatform.h"
#include "asiovec.h"

/* Socket flags */
#ifdef WIN32
#define AS_MSG_NOSIGNAL     (0)
#elif defined APPLE
#define AS_MSG_NOSIGNAL     (0)
#elif defined(SOLARIS)
#define AS_MSG_NOSIGNAL     (0)
#else
#define AS_MSG_NOSIGNAL     (MSG_NOSIGNAL)
#endif  /* WIN32 */

typedef enum {
    AS_IO_READ = 0x01,
    AS_IO_WRITE = 0x02
} as_sockbuf_op_t;

#ifndef AF_LOCAL
#define AF_LOCAL AF_UNIX
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
typedef SOCKET as_socket_t;
#define AS_SOCKET_INVALID       (INVALID_SOCKET)
#else
typedef int as_socket_t;
#define AS_SOCKET_INVALID       (-1)
#endif /* WIN32 */

#if defined WIN32
#define as_sock_get_herrno()    (WSAGetLastError()) 
#define as_sock_set_errno(e)    (WSASetLastError(e))
typedef unsigned long in_addr_t;
#else
#define as_sock_get_herrno()    (h_errno)
#define as_sock_set_errno(e)    (errno = e)
#endif 

#ifdef WIN32
#define as_sock_get_errno()     (WSAGetLastError())
#else
#define as_sock_get_errno()     (errno)
#endif 

typedef struct sockaddr_in as_sockaddr_t; 

ASUTILS_API as_err_t 
as_sock_init(void);

ASUTILS_API void 
as_sock_fini(void); 

ASUTILS_API as_err_t
as_sock_shutdown(
    const as_socket_t *sock);

ASUTILS_API as_err_t
as_sock_close(
    as_socket_t *sock);

ASUTILS_API as_err_t
as_sock_ioctl(
    const as_socket_t *sock,
    int request,
    void *buf);

/*
 * @brief   Set socket option to blocking
 * @param   sock        Socket handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sock_set_blocking(
    const as_socket_t *sock);

/*
 * @brief   Set socket option to nonblocking
 * @param   sock        Socket handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sock_set_nonblocking(
    const as_socket_t *sock);

/*
 * @brief   Get nonblocking socket option
 * @param   fd          Socket handle
 * @param   opt         Socket option
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sock_get_nonblocking(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_rcvbuf(
    const as_socket_t *sock,
    const size_t *bufsz);

ASUTILS_API as_err_t
as_sock_get_rcvbuf(
    const as_socket_t *sock,
    size_t *bufsz);

ASUTILS_API as_err_t
as_sock_set_rcvlowat(
    const as_socket_t *sock,
    const size_t *bufsz);

ASUTILS_API as_err_t
as_sock_get_rcvlowat(
    const as_socket_t *sock,
    size_t *bufsz);

ASUTILS_API as_err_t
as_sock_set_sndbuf(
    const as_socket_t *sock,
    const size_t *bufsz);

ASUTILS_API as_err_t
as_sock_get_sndbuf(
    const as_socket_t *sock,
    size_t *bufsz);

ASUTILS_API as_err_t
as_sock_set_sndlowat(
    const as_socket_t *sock,
    const size_t *bufsz);

ASUTILS_API as_err_t
as_sock_get_sndlowat(
    const as_socket_t *sock,
    size_t *bufsz);

ASUTILS_API as_err_t
as_sock_set_linger(
    const as_socket_t *sock,
    const int *tmout);

ASUTILS_API as_err_t
as_sock_get_linger(
    const as_socket_t *sock,
    int *tmout);

ASUTILS_API as_err_t
as_sock_set_reuseaddr(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_reuseaddr(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_priority(
    const as_socket_t *sock,
    const int *priority);

ASUTILS_API as_err_t
as_sock_get_priority(
    const as_socket_t *sock,
    int *priority);

ASUTILS_API as_err_t
as_sock_get_errror(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_broadcast(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_broadcast(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_bindtodevice(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_bindtodevice(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_timestamp(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_timestamp(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_ip_options(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_ip_options(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_ip_pktinfo(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_ip_pktinfo(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_ip_tos(
    const as_socket_t *sock,
    const int *tos);

ASUTILS_API as_err_t
as_sock_get_ip_tos(
    const as_socket_t *sock,
    int *tos);

ASUTILS_API as_err_t
as_sock_set_ip_ttl(
    const as_socket_t *sock,
    const int *ttl);

ASUTILS_API as_err_t
as_sock_get_ip_ttl(
    const as_socket_t *sock,
    int *ttl);

ASUTILS_API as_err_t
as_sock_set_ip_rcverr(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_ip_rcverr(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_ip_mtudiscover(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_ip_mtudiscover(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_ip_mcast_loop(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_ip_mcast_loop(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_add_ip_mcast_membership(
    const as_socket_t *sock,
    const struct ip_mreq *group);

ASUTILS_API as_err_t
as_sock_drp_ip_mcast_membership(
    const as_socket_t *sock,
    const struct ip_mreq *group);

ASUTILS_API as_err_t
as_sock_set_ip_mcast_ttl(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_ip_mcast_ttl(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_ip_mcast_if(
    const as_socket_t *sock,
    const struct in_addr *iface);

ASUTILS_API as_err_t
as_sock_get_ip_mcast_if(
    const as_socket_t *sock,
    struct in_addr *iface);

ASUTILS_API as_err_t
as_sock_set_tcp_keepalive(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_tcp_keepalive(
    const as_socket_t *sock,
    int *flag);

ASUTILS_API as_err_t
as_sock_set_tcp_keepcnt(
    const as_socket_t *sock,
    const int *cnt);

ASUTILS_API as_err_t
as_sock_get_tcp_keepcnt(
    const as_socket_t *sock,
    int *cnt);

ASUTILS_API as_err_t
as_sock_set_tcp_keepidl(
    const as_socket_t *sock,
    const int *idletime);

ASUTILS_API as_err_t
as_sock_get_tcp_keepidl(
    const as_socket_t *sock,
    int *idletime);

ASUTILS_API as_err_t
as_sock_set_tcp_keepitvl(
    const as_socket_t *sock,
    const int *intvl);

ASUTILS_API as_err_t
as_sock_get_tcp_keepitvl(
    const as_socket_t *sock,
    int *intvl);

ASUTILS_API as_err_t
as_sock_set_tcp_linger(
    const as_socket_t *sock,
    const int *tmout);

ASUTILS_API as_err_t
as_sock_get_tcp_linger(
    const as_socket_t *sock,
    int *tmout);

ASUTILS_API as_err_t
as_sock_set_tcp_nodelay(
    const as_socket_t *sock,
    const int *flag);

ASUTILS_API as_err_t
as_sock_get_tcp_nodelay(
    const as_socket_t *sock,
    int *flag);

/* getsockopts */

ASUTILS_API as_err_t
as_sock_get_type(
    const as_socket_t *sock,
    int *type);

ASUTILS_API as_err_t
as_sock_get_tcp_inq_size(
    const as_socket_t *sock,
    int *inq);

ASUTILS_API as_err_t
as_sock_get_tcp_outq_size(
    const as_socket_t *sock,
    int *outq);

/*
 * @brief   Resolve remote address and port
 *
 * @param   host        Host name
 * @param   addr        IP address
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sock_resolve_addr(
    const char *host, 
    as_sockaddr_t *addr);

/*
 * @brief   Write to socket
 *
 * @param   fd          Socket handle
 * @param   buf         Buffer
 * @param   bsize       Requested size
 * @param   wsize       Actual written size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_buf_write(
    const as_socket_t *sock,
    const char *buf, 
    size_t bsize,
    size_t *wsize);

ASUTILS_API as_err_t 
as_buf_write_tmout(
    const as_socket_t *sock,
    const char *buf, 
    size_t bsize,
    size_t *wsize,
    int tmout_secs);

/*
 * @brief   Read from socket
 * @param   fd          Socket handle
 * @param   buf         Buffer
 * @param   bsize       Requested size
 * @param   rsize       Actual read size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_buf_read(
    const as_socket_t *sock, 
    char *buf, 
    size_t bsize,
    size_t *rsize);

ASUTILS_API as_err_t 
as_buf_read_tmout(
    const as_socket_t *sock, 
    char *buf, 
    size_t bsize,
    size_t *rsize,
    int tmout_secs);

/*
 * @brief   Create a socket pair
 * @param   socks       Socket handles
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_sock_pair(
    as_socket_t socks[2]);

ASUTILS_API as_err_t
as_sock_readv(
    const as_socket_t *sock,
    as_iovec_t *iovec,
    int iovec_count,
    size_t *nbytes);

ASUTILS_API as_err_t
as_sock_writev(
    const as_socket_t *sock,
    as_iovec_t *iovec,
    int iovec_count,
    size_t *nbytes);

#ifdef __cplusplus
}
#endif

#endif /* _AS_SOCKET_H_ */
