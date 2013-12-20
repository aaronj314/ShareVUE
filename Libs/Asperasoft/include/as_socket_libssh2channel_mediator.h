/*
 *  as_socket_libssh2channel_mediator.h
 *  iphone_upload_app
 *
 *  Created by Amos Joshua on 10/15/09.
 *  Copyright 2009 Aspera. All rights reserved.
 *
 */

#include "as_cyclic_buffer.h"
#include <libssh2.h>
#include <libssh2_sftp.h>




typedef struct as_socket_libssh2channel_mediator_t{
	as_socket_t _sock1, _channelsock;
	as_cyclic_buffer_t _buffer;
	pthread_t _loop_thread;
	LIBSSH2_CHANNEL *_channel;
	LIBSSH2_SESSION *_session;
	void (*_error_callback)(int, char *);
} as_socket_libssh2channel_mediator_t;





as_socket_libssh2channel_mediator_t *as_socket_libssh2channel_mediator_alloc();
void as_socket_libssh2channel_mediator_init(as_socket_libssh2channel_mediator_t *mediator, as_socket_t sock1, as_socket_t channelsock, LIBSSH2_CHANNEL *channel, LIBSSH2_SESSION *session, void (*error_callback)(int, char *));
void as_socket_libssh2channel_mediator_dealloc(as_socket_libssh2channel_mediator_t *mediator);
void as_socket_libssh2channel_mediator_destroy(as_socket_libssh2channel_mediator_t *mediator);
void *as_socket_to_libssh2channel_mediator_loop(void *mediator_ptr);
void *as_libssh2channel_to_socket_mediator_loop(void *mediator_ptr);
void as_start_socket_libssh2channel_mediation(as_socket_t sock1, as_socket_t channelsock, LIBSSH2_CHANNEL *channel, LIBSSH2_SESSION *session, void (*error_callback)(int, char *), as_socket_libssh2channel_mediator_t **s1_to_csock_dptr, as_socket_libssh2channel_mediator_t **csock_to_s1_dptr);
void as_socket_libssh2channel_mediator_shutdown_loop(as_socket_libssh2channel_mediator_t *mediator);

