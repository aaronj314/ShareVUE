/*
 * mgmt_proto.h
 *
 * Defines the management protocol message formats.
 */

#ifndef MGMT_PROTO_H
#define MGMT_PROTO_H

#include <utils/src/asutils.h>
#include <faspmgmt/faspmgmt.h>

#include "mgmt_err_mapper.h"

/* Forward declarations */
struct fasp_session_t;
struct fasp_session_def_t;
struct transfer_t;

#ifdef FASP_CPP
extern "C" {
#endif

/* Management message handling functions */

typedef int (*p_mgmt_process_read_msg)(void *sess, faspmgmt_args_t *a);

int mgmt_format_msg(faspmgmt_args_t *a, char *buf, unsigned maxlen);
int mgmt_parse_msg(struct fasp_session_t *s, char const* start, char const* end);
void mgmt_set_read_msg_hook( p_mgmt_process_read_msg hook );
int process_read_msg(struct fasp_session_t *s, faspmgmt_args_t *a);

int prep_init_cmd(faspmgmt_args_t *a, struct fasp_session_def_t *s,
    char const* uuid_string, char* buf, unsigned bufsiz);
int prep_session_cmd(faspmgmt_args_t *a, struct fasp_session_t *s, char* buf, unsigned bufsiz);
int prep_stats(faspmgmt_cmd_t cmd,
    faspmgmt_args_t *a, struct fasp_session_t *sess,
    char const* filename, u_int64_t filesize,
    u_int64_t count, u_int64_t bytescont, u_int64_t startbyte, 
    int errcode, char const* errstr,
    char* buf, unsigned bufsiz);
int prep_notif_cmd(
    faspmgmt_args_t *a, struct fasp_session_t *s, char* buf, unsigned bufsiz);
int prep_error_cmd(faspmgmt_args_t *a, int errcode, char *filename, 
    char *descr, char* buf, unsigned bufsiz);
int prep_fileerror_cmd(faspmgmt_args_t *a, int errcode, char *filename,
    char *descr, char* buf, unsigned bufsiz);
int prep_done_cmd(faspmgmt_cmd_t cmd,
    faspmgmt_args_t *a, struct fasp_session_t *s, char* buf, unsigned bufsiz);
int prep_notif_cmd(faspmgmt_args_t *a, struct fasp_session_t *s,
    char* buf, unsigned bufsiz);
int prep_notif_precalc_cmd(faspmgmt_args_t *a, struct fasp_session_t *s,
    char* buf, unsigned bufsiz);


extern int mgmt_fasperr2mgmterr(int e);

#ifdef FASP_CPP
} // extern "C"
#endif

#endif
