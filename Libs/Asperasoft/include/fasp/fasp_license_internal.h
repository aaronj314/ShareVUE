// fasp_license_internal.h

#ifndef __FASP_LICENSE_INTERNAL__
#define __FASP_LICENSE_INTERNAL__

#include "libxml/parser.h"

/* Product types 
 * Before introducing product types the value of this byte was 5 (magic).
 */
enum lic_productlist_e {
    e_lic_old_product       = 0x5,
    e_lic_web_client        = 0x6,
    e_lic_scp_client        = 0x7,
    e_lic_scp               = 0x8,
    e_lic_ent_server        = 0x9,
    e_lic_ent_server_web    = 0xa
};

struct fasp_old_licinfo_t;

typedef struct _fasp_license_impl {
    char* terms;
    size_t termssz;
    xmlDocPtr xdp;
    lic_err_t* e;   
    char prepost_str[64]; // todo: move this to a prepost struct or something
} fasp_license_impl;

int fasp_lic_init_err( lic_err_t* e );
void fasp_lic_clear_err( lic_err_t* e );
void fasp_lic_init_xmldocptr( fasp_license_impl* l );

/*
 * fasp_lic_generate_peer_license: given an older license, create
 * an equivalent new license.
 */
// int fasp_lic_generate_peer_license(fasp_license_t p, licinfo_ptr peer);

fasp_lic_peer_attr_err_t
fasp_lic_check_attributes(fasp_license_t l, fasp_license_t p);

extern const char* g_fasp_lic_peer_attr_err_table[];
extern const char* g_fasp_lic_local_attr_err_table[];

extern const char* g_fasp_lic_gen_peer_license_err_table[];

#endif
