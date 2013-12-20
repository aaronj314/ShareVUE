#ifndef __CSV_4180_H__
#define __CSV_4180_H__

#include "utils/src/astypes.h"
#include "stdio.h"

#include "as_uac_memory_heap.h"

struct _csv_4180_table;
typedef struct _csv_4180_table *csv_4180_table;

struct _csv_4180_row;
typedef const struct _csv_4180_row *csv_4180_row;

const char *csv_4180_escape( memory_heap *heap, const char *input );
as_err_t csv_4180_escape_to_dest( const char *input, char *output, size_t output_size );
const char *csv_4180_unescape( memory_heap *heap, const char *input );
as_err_t csv_4180_unescape_to_dest( const char *input, char *output, size_t output_size );

as_err_t csv_4180_deserialize_stream_to_table( FILE *handle, csv_4180_table table );
as_err_t csv_4180_serialize_table_to_stream( FILE *handle, const csv_4180_table table );

as_err_t csv_4180_create_table( memory_heap *heap, csv_4180_table *table );
as_err_t csv_4180_release_table( csv_4180_table *table );

as_err_t csv_4180_stream_line_to_table( csv_4180_table table, const char *(*data_source)(void *param), void *param );
as_err_t csv_4180_add_line_to_table( csv_4180_table table, const char *line );
as_err_t csv_4180_print_line_to_table( csv_4180_table table, const char *template, ... );

as_err_t csv_4180_get_first_table_row( const csv_4180_table table, csv_4180_row *row );
as_err_t csv_4180_get_next_table_row( csv_4180_row *row );

const char *csv_4180_get_row_column( csv_4180_row row, int column );
int csv_4180_get_row_column_count( csv_4180_row row );

#endif
