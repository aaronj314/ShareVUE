//  uac_forward_declares.h
//
//  I was having a lot of trouble with typedef's tripping over multiple
//  forward struct declares.  Hopefully this will straighten it out.


#ifndef __UAC_FORWARD_DECLARES_H__
#define __UAC_FORWARD_DECLARES_H__

    // This one shouldn't be const (user configurable).
struct _as_uac_parse_xml_node_filter_set;
typedef struct _as_uac_parse_xml_node_filter_set as_uac_parse_xml_node_filter_set;

struct _as_uac_conf_file_set;
typedef const struct _as_uac_conf_file_set as_uac_conf_file_set;
typedef struct _as_uac_conf_file_set as_uac_conf_file_set_NC;

    // Retains information about an active search.
    // This one shouldn't be const (it changes state as searches progress).
struct _as_uac_node_search_handle;
typedef struct _as_uac_node_search_handle as_uac_node_search_handle;

    // This one shouldn't be const (it gets filled out with tree info).
struct _as_uac_conf_level_tracker;
typedef struct _as_uac_conf_level_tracker as_uac_conf_level_tracker;

    // One node set within the conf file.  Could be a user node overlaying a group node, for instance.
    // What is it really internally?  An array of libXML2 xmlNodePtr's.
struct _as_uac_conf_node;
typedef const struct _as_uac_conf_node as_uac_conf_node;
typedef struct _as_uac_conf_node as_uac_conf_node_NC;

    // Structs to contain the full set of options for users, trunks and docroots respectively.
typedef const struct _as_uac_conf_node as_uac_user_node;
struct _as_uac_user_option_set;
typedef const struct _as_uac_user_option_set as_uac_user_option_set;
typedef struct _as_uac_user_option_set as_uac_user_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_trunk_node;
struct _as_uac_trunk_option_set;
typedef const struct _as_uac_trunk_option_set as_uac_trunk_option_set;
typedef struct _as_uac_trunk_option_set as_uac_trunk_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_docroot_node;
struct _as_uac_docroot_option_set;
typedef const struct _as_uac_docroot_option_set as_uac_docroot_option_set;
typedef struct _as_uac_docroot_option_set as_uac_docroot_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_database_node;
struct _as_uac_database_option_set;
typedef const struct _as_uac_database_option_set as_uac_database_option_set;
typedef struct _as_uac_database_option_set as_uac_database_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_central_server_node;
struct _as_uac_central_server_option_set;
typedef const struct _as_uac_central_server_option_set as_uac_central_server_option_set;
typedef struct _as_uac_central_server_option_set as_uac_central_server_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_http_server_node;
struct _as_uac_http_server_option_set;
typedef const struct _as_uac_http_server_option_set as_uac_http_server_option_set;
typedef struct _as_uac_http_server_option_set as_uac_http_server_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_conf_V1_node;
struct _as_uac_conf_V1_option_set;
typedef const struct _as_uac_conf_V1_option_set as_uac_conf_V1_option_set;
typedef struct _as_uac_conf_V1_option_set as_uac_conf_V1_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_vlink_V1_node;
struct _as_uac_vlink_V1_option_set;
typedef const struct _as_uac_vlink_V1_option_set as_uac_vlink_V1_option_set;
typedef struct _as_uac_vlink_V1_option_set as_uac_vlink_V1_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_http_session_start_node;
struct _as_uac_http_session_start_option_set;
typedef const struct _as_uac_http_session_start_option_set as_uac_http_session_start_option_set;
typedef struct _as_uac_http_session_start_option_set as_uac_http_session_start_option_set_NC;

typedef const struct _as_uac_conf_node as_uac_http_session_end_node;
struct _as_uac_http_session_end_option_set;
typedef const struct _as_uac_http_session_end_option_set as_uac_http_session_end_option_set;
typedef struct _as_uac_http_session_end_option_set as_uac_http_session_end_option_set_NC;

#endif // __UAC_FORWARD_DECLARES_H__
