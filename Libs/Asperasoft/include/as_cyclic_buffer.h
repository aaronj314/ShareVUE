/*
 *  as_cyclic_buffer.h
 *
 *  Created by Amos Joshua on 10/16/09.
 *  Copyright 2009 Aspera. All rights reserved.
 *
 */

#include "assocket.h"
#include "astime.h"
#include "asselect.h"
#include "aslog.h"

typedef struct as_cyclic_buffer_t{
	char *_buffer;
	int _next_write_index;
	int _next_read_index;
	int _size;
} as_cyclic_buffer_t;


int as_cyclic_buffer_init(as_cyclic_buffer_t *cb, int size);
void as_cyclic_buffer_destroy(as_cyclic_buffer_t *cb);

int as_cyclic_buffer_is_full(as_cyclic_buffer_t *cb);
int as_cyclic_buffer_is_empty(as_cyclic_buffer_t *cb);

char *as_cyclic_buffer_write_ptr(as_cyclic_buffer_t *cb);
int as_cyclic_buffer_bytes_can_write(as_cyclic_buffer_t *cb);

char *as_cyclic_buffer_read_ptr(as_cyclic_buffer_t *cb);
int as_cyclic_buffer_bytes_can_read(as_cyclic_buffer_t *cb);

void as_cyclic_buffer_report_read_bytes(as_cyclic_buffer_t *cb, int bytes_read);
void as_cyclic_buffer_report_wrote_bytes(as_cyclic_buffer_t *cb, int bytes_written);

int as_cyclic_buffer_read_from_socket_to_buffer(as_cyclic_buffer_t *cb, as_socket_t sock);
int as_cyclic_buffer_write_from_buffer_to_socket(as_cyclic_buffer_t *cb, as_socket_t sock);