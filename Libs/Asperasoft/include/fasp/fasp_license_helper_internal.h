/*
 * fasp_license_helper_internal.h
 *   helper functions for license processing
 *  
 *  Aspera Inc.
 */

#ifndef _FASP_LICENSE_HELPER_INTERNAL_H_
#define _FASP_LICENSE_HELPER_INTERNAL_H_

#include "fasp/fasp_license.h"
#include "fasp/fasp_session.h"

int fasp_lic_populate_licinfo( fasp_license_t license, const char** errstr );

int fasp_check_local_license_exp_time(fasp_session_t *sess);

int fasp_check_local_license_bw_cap(fasp_session_t *sess);

bool_t fasp_check_peer_duplicate_license(fasp_license_t l, fasp_license_t p);

bool_t fasp_check_is_server( fasp_session_t *sess );

bool_t fasp_check_peer_is_localhost(struct sockaddr_in local_ip, struct sockaddr_in peer_ip);


#endif
