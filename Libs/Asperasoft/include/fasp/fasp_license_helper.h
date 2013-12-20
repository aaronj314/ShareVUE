/*
 * fasp_license_helper.h
 *   helper functions for license processing
 *  
 *  Aspera Inc.
 */

#ifndef _FASP_LICENSE_HELPER_H_
#define _FASP_LICENSE_HELPER_H_

#include "fasp/fasp.h"
#include "fasp/fasp_session.h"
#include "fasp/fasp_license.h"

struct fasp_t;
struct fasp_session_t;

void fasp_license_str(const fasp_t *fasp, int debuglevel, char* strbuf, size_t strbufsz);

fasp_lic_attr_err_t fasp_lic_maximum_bandwidth_str( fasp_license_t l, char* r, size_t r_sz );

int fasp_init_local_license(struct fasp_t *fasp);

int fasp_check_local_license(struct fasp_session_t *sess);

int fasp_init_peer_license(struct fasp_session_t *sess);

int fasp_check_peer_license(struct fasp_session_t *sess);

bool_t fasp_lic_is_server( fasp_license_t l );

#endif
