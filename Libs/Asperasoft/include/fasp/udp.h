/* 
 * udp.h
 *
 * UDP related routines
 */

#include <utils/src/asutils.h>

#include <fasp/msg_api.h>

#define UDP_PORT_RANGE  10000 // FASP tries to bind to a range of ports
                              // in case the indicated port is in use

/* Forward declarations */
struct fasp_session_t;
struct transfer_t;

/*------------------------------------------------------------------------
 * create_udp_socket
 *
 * Establishes a new UDP socket for data transfer, returning the file
 * descriptor of the socket on success and -1 on error. The size_rcv_buffer
 * and size_snd_buffer parameters are used for setting the size of the UDP 
 * receive and send buffers, respectively.  This creates an IPv6 socket if 
 * ipv6 is true and an IPv4 socket otherwise. If out_port is non-NULL, is
 * is set to the port of the created socket.
 *------------------------------------------------------------------------*/
as_socket_t create_udp_socket ( 
                        const char* ip_address,
                        int         service_port,
                        int         ipv6,
                        int         reusable,
                        int         iamremote,
                        int         size_rcv_buffer,
                        int         size_snd_buffer,
                        struct sockaddr_in *out_addr,
                        int        *errcode);

int connect_snd_sock(struct fasp_session_t *sess);

int connect_rcv_sock(struct fasp_session_t *sess);

int send_request_start_udp(struct fasp_session_t *sess, 
                           struct transfer_t *xfer);

int send_control_msg(struct fasp_session_t *sess, 
                     struct transfer_t *xfer, 
                     control_pdu_t *control_pdu_buf );

/*------------------------------------------------------------------------
 *
 * TODO: update packet format (fasp_proto.h)
 *
 * Constructs to hold the given block of data, with the given type
 * stored in it.  The format of the datagram is:
 *
 *     32                    0
 *     +---------------------+
 *     |     block_number    |
 *     +----------+----------+
 *     |         idx         |
 *     +---------------------+
 *     |   type   |   tick   |
 *     +----------+----------|
 *     :     :          :    :
 *     +---------------------+
 *
 * The datagram is stored in the given buffer, which must be at least
 * ten bytes longer than the block size for the transfer.  Returns 0 on
 * success and non-zero on failure.
 *------------------------------------------------------------------------*/

extern int
build_datagram_vec(
    fasp_session_t *sess, 
    transfer_t     *xfer,
    u_int32_t       fasp_block_index,
    u_int32_t       block_index,
    u_int32_t       rex_idx,
    u_int8_t        block_type,
    u_int16_t       tickstamp,
    dbuf_t         *dbuf
);

extern int
build_datagram_secure(
    fasp_session_t *sess, 
    transfer_t     *xfer,
    u_int32_t       fasp_block_index,
    u_int32_t       block_index,
    u_int32_t       rex_idx,
    u_int8_t        block_type,
    u_int16_t       tickstamp,
    dbuf_t         *dbuf
);

/*------------------------------------------------------------------------
 *
 * TODO: update packet format (fasp_proto.h)
 *
 * Builds a datagram within an encapsulating header and 
 * trailer containing a sequence number to guard against 
 * replay attacks and an authentication tag used to ensure 
 * message authenticity, respectively. 
 *
 * The format of a secure datagram is:
 *
 *     32                    0
 *     +---------------------+     
 *     |     block_number    |
 *     +----------+----------+
 *     |        idx          |
 *     +---------------------+
 *     |   type   |   tick   |
 *     +----------+----------+
 *     |       seqno         |
 *     +---------------------+
 *     :     :          :    :
 *     :     :          :    :
 *     +---------------------+
 *     |                     |
 *     +                     +
 *     |                     |
 *     +      MD5 MAC        +
 *     |                     |
 *     +                     +
 *     |                     |
 *     +---------------------+
 *
 *
 * The datagram is stored in the given buffer, the size of which 
 * is block size + sizeof(seqno) + sizeof(block number) 
 * + sizeof( type ) + sizeof(MD5 MAC)for the transfer.  
 *
 * If successful returns 0, otherwise returns a non-zero return code
 *
 *------------------------------------------------------------------------*/

extern int parse_datagram_dbuf(dbuf_t *dbuf,
                               dgram_hdr_t *dgram_hdr);

/*
 * Inspects errno and returns 1 if the errno is fatal.
 */
int is_fatal(int e);
