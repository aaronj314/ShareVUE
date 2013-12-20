/* mgmtsocks.c */

#ifndef FASP_DS_MGMTSOCKS_H
#define FASP_DS_MGMTSOCKS_H

#include <utils/src/asutils.h>

#ifdef WIN32
#include <io.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

enum { MGMT_SOCKS_MAX = 32 };

struct mgmt_bufchain;
struct mgmt_socket;

typedef struct _mgmt_context_t {
    /* errors are reported here; err is a copy of errno. */
    int err;
    char errstr[256];

    /* these are testing aids. */
    int capacity;     /* set after calling mgmt_init() before i/o, e.g. 16 */
    int write_limit;  /* set before each call to mgmt_connect(), e.g. 7 */

    /* ignore these */
    int num_sockets;
    struct mgmt_socket* sockets;
    struct mgmt_bufchain* out;
} mgmt_context_t; 


/* mgmt_init(): Construct a mgmt_context_t object in place.
 * Returns -1 on failure, and sets err and errstr in *context.
 * May be called more than once, for different arguments.
 */
int mgmt_init(mgmt_context_t* context);

/* mgmt_connect(): Connect to one management message sink.
 * Returns AS_INVALID_SOCKET on failure, sets err and errstr 
 * in *context.  Otherwise returns the socket fd opened,
 * usable for select().  If argument <host> is NULL, connects
 * to 127.0.0.1.  If is_optional, write failures are ignored.
 */
as_socket_t  mgmt_connect(
    mgmt_context_t* context, char const* host, unsigned short port,
    int is_optional);

/* mgmt_write(); Write len bytes to all management sinks without blocking.
   Returns -1 on failure, sets err and errstr in *context.  Otherwise
   returns number of backlogged sockets.  Tries to send any backlog 
   again on subsequent calls.  
 */
int  mgmt_write(mgmt_context_t* context, char* buf, int len);

/* mgmt_writable(): Set flags in *set for backlogged sockets.
   Returns max writable socket fd, to pass to select (after +1),
   or zero if none.
*/
as_socket_t  mgmt_writable(mgmt_context_t* ctx, fd_set* set);

/* mgmt_do_backlog(): Try to flush backlogged sockets identified by *set.
   Returns -1 on error, sets err, errstr in *context.  Otherwise returns
   number of backlogged sockets.
 */
int  mgmt_do_backlog(mgmt_context_t* context, fd_set* set);

/* mgmt_read(): Read one or more complete messages from management sinks.
   Returns number of bytes stored in buf, or -1 on error (e.g.
   socket error or buffer too small), or 0 if no complete message
   is ready yet.
 */
int  mgmt_read(mgmt_context_t* context, char* buf, int maxlen);

/* mgmt_readable(): Set flags in *set for readable sockets.
   Returns max readable socket fd, to pass to select (after +1),
   or zero if none.
*/
as_socket_t  mgmt_readable(mgmt_context_t* ctx, fd_set* set);

/* mgmt_close(): Close open sockets, free storage.
 */
int mgmt_close(mgmt_context_t*);

#endif /* FASP_DS_MGMTSOCKS_H */
