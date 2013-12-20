
#ifndef __AS_APP_INTERNAL_H__
#define __AS_APP_INTERNAL_H__

#include "asproduct.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

typedef struct as_product_info {
    xmlDocPtr _xml;

    char *_printable;
} as_product_info_t;

as_err_t as_product_info_file( const char* root_dir, char* buf, size_t bufsz );
as_err_t as_product_parse_xml( const xmlDocPtr* doc, as_product_info_t* info );

#endif


