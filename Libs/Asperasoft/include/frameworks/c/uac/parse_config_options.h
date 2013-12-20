//  parse_config_options.h
//
//  Process contents of the list in parse_hard_config_names.h into an enum that can be used for token based string searches.


#ifndef __PARSE_CONFIG_OPTIONS_H__
#define __PARSE_CONFIG_OPTIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "uac_forward_declares.h"
#include "uac.h"

#include <utils/src/asfile.h>
#include <utils/src/ascontainers.h>
#include <utils/src/asdir.h>

#define MAX_STRINGIZE_SIZE          (8192)
#define SCHEDULE_CHANGE_POINTS_MAX  (256)
#define MAX_DOCROOTS_PER_USER       (32)

extern const char as_uac_boolean_true_values[];

#define AS_ALLOW_UNROOTED_DOCROOTS

extern const char AS_UAC_NULL_STRING[];

extern const char as_uac_string_list_terminator[];

/* Data carried by the protocol options section */
typedef struct _as_uac_schedule_change_point_t
{
    char _epoch[128];
    char _value[64];

} as_uac_schedule_change_point_t;

typedef struct _as_uac_schedule_t
{
    const char *_source_string;

    as_uac_schedule_change_point_t _change_points[SCHEDULE_CHANGE_POINTS_MAX];
    int _num_change_points;

} as_uac_schedule_t;

    // Canonical list of types that can be in the option classes.
typedef int                         as_uac_conf_lookup;
typedef int                         as_uac_conf_boolean;
typedef int64_t                     as_uac_conf_int64_t;
typedef u_int64_t                   as_uac_conf_u_int64_t;
typedef int32_t                     as_uac_conf_int32_t;
typedef u_int32_t                   as_uac_conf_u_int32_t;
typedef u_int32_t                   as_uac_conf_octal_32;
typedef double                      as_uac_conf_double;
typedef const char*                 as_uac_conf_char_ptr;
typedef const char*                 as_uac_conf_trimmed_char_ptr;
typedef const as_uac_schedule_t*    as_uac_conf_cron;
typedef const char*                 as_uac_conf_string_list;

void as_uac_free_cron ( as_uac_conf_cron cron_ptr, as_uac_conf_cron default_cron_ptr );

as_uac_conf_string_list as_uac_next_string_list_item( as_uac_conf_string_list item );

    // Stringize functions (for output)
const char *as_uac_xml_stringize_boolean( as_uac_conf_boolean val, char *output, char *param );
const char *as_uac_xml_stringize_u_int32_t( as_uac_conf_u_int32_t val, char *output, void *param );
const char *as_uac_xml_stringize_octal_32( as_uac_conf_octal_32 val, char *output, void *param );
const char *as_uac_xml_stringize_int32_t( as_uac_conf_int32_t val, char *output, void *param );
const char *as_uac_xml_stringize_lookup( as_uac_conf_lookup val, char *output, void *param );
const char *as_uac_xml_stringize_u_int64_t( as_uac_conf_u_int64_t val, char *output, void *param );
const char *as_uac_xml_stringize_int64_t( as_uac_conf_int64_t val, char *output, void *param );
const char *as_uac_xml_stringize_double( as_uac_conf_double val, char *output, void *param );
const char *as_uac_xml_stringize_char_ptr( as_uac_conf_char_ptr val, char *output, void *param );
const char *as_uac_xml_stringize_trimmed_char_ptr( as_uac_conf_char_ptr val, char *output, void *param );
const char *as_uac_xml_stringize_string_list( as_uac_conf_string_list val, char *output, e_parse_hard_config_names param );
const char *as_uac_xml_stringize_cron( as_uac_conf_cron c, char *output, void *param );

const char *as_uac_csv_stringize_boolean( as_uac_conf_boolean val, char *output, char *param );
const char *as_uac_csv_stringize_u_int32_t( as_uac_conf_u_int32_t val, char *output, void *param );
const char *as_uac_csv_stringize_octal_32( as_uac_conf_octal_32 val, char *output, void *param );
const char *as_uac_csv_stringize_int32_t( as_uac_conf_int32_t val, char *output, void *param );
const char *as_uac_csv_stringize_lookup( as_uac_conf_lookup val, char *output, void *param );
const char *as_uac_csv_stringize_u_int64_t( as_uac_conf_u_int64_t val, char *output, void *param );
const char *as_uac_csv_stringize_int64_t( as_uac_conf_int64_t val, char *output, void *param );
const char *as_uac_csv_stringize_double( as_uac_conf_double val, char *output, void *param );
const char *as_uac_csv_stringize_char_ptr( as_uac_conf_char_ptr val, char *output, void *param );
const char *as_uac_csv_stringize_trimmed_char_ptr( as_uac_conf_char_ptr val, char *output, void *param );
const char *as_uac_csv_stringize_string_list( as_uac_conf_string_list val, char *output, e_parse_hard_config_names param );
const char *as_uac_csv_stringize_cron( as_uac_conf_cron c, char *output, void *param );

const char *as_uac_csv_to_xml_do_nothing( const char **input, char *output, char *param );

// Only define the ones that perform a conversion.  Non-compound types (int, bool, lookup, etc) are the same for both.
#define as_uac_csv_to_xml_boolean            as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_u_int32_t          as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_octal_32           as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_int32_t            as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_lookup             as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_u_int64_t          as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_int64_t            as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_double             as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_char_ptr           as_uac_csv_to_xml_do_nothing
#define as_uac_csv_to_xml_trimmed_char_ptr   as_uac_csv_to_xml_do_nothing

const char *as_uac_csv_to_xml_string_list( const char **input, char *output, char *param );
const char *as_uac_csv_to_xml_cron( const char **input, char *output, char *param );

as_err_t as_uac_xml_check_boolean( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_u_int32_t( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_octal_32( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_int32_t( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_lookup( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_u_int64_t( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_int64_t( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_double( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_char_ptr( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_trimmed_char_ptr( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_string_list( const char *string, void *param, const char **complaint );
as_err_t as_uac_xml_check_cron( const char *string, void *param, const char **complaint );

as_err_t as_uac_xml_check_incoming_user_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_docroot_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_trunk_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_central_server_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_database_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_http_server_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_http_session_start_value( const char *name, const char *value, const char **complaint );
as_err_t as_uac_xml_check_incoming_http_session_end_value( const char *name, const char *value, const char **complaint );

const char *as_uac_csv_convert_incoming_user_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_docroot_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_trunk_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_central_server_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_database_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_http_server_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_http_session_start_value( const char *name, const char **value, char *dest );
const char *as_uac_csv_convert_incoming_http_session_end_value( const char *name, const char **value, char *dest );

typedef struct _as_uac_single_warning
{
    as_err_t    _error_code;

    struct _as_uac_single_warning *_next_warning;

        // Variable size array.  Must remain at end.
    char _error_description[1];

} as_uac_single_warning;

void as_uac_insert_warning( as_uac_single_warning **link, as_err_t code, const char *tmplate, ... );
void as_uac_release_warning( as_uac_single_warning **link );


as_err_t as_uac_verify_conf_file( as_uac_conf_file_set *file_set );
as_err_t as_uac_verify_conf_file_kw( as_uac_conf_file_set *file_set, as_uac_single_warning **_warning );
as_err_t as_uac_verify_conf_file_by_name( const char *file_name, as_uac_single_warning **_warning );

////////////////////
//                //
//  User options  //
//                //
////////////////////

    // build function headers.
#define as_uac_user_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_user_default_get_##name( as_uac_conf_node *user, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"

    // Option set definition.  This is everything listed in parse_config_option_set.h, plus some extras.
struct _as_uac_user_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_user_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

        // The name value in the conf file may be something like "*", so make the final name available.
    char _full_name[256];

        // The encryption key is declared as a string in the conf and then hashed into a binary.  This is where the binary lives.
    u_int8_t *_token_encryption_key_binary;

        // Pointers to the trunks.  Might point to default version if there are none.
    as_uac_trunk_option_set *_in_trunk;
    as_uac_trunk_option_set *_out_trunk;

        // Variables available for replacement into strings via as_parse_variables_into_string if so desired.
    as_binary_tree_t _variables;

        // First docroot.  Further docroots are in _first_doc_root->_next_set.
    as_uac_docroot_option_set *_first_doc_root;

    struct _as_uac_user_option_set *_cache_link;

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_user_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

as_err_t as_uac_user_option_set_override( as_uac_user_option_set *_option_set, const char *option_name, const char *option_value, as_uac_single_warning **warning_link );

    // Get a user option set from a node.
as_uac_user_option_set *as_uac_user_get_option_set( as_uac_conf_file_set *file_set, as_uac_conf_node *user, const char *name_override );

    // Recalculate the derived variables from possibly changed master variables.
as_uac_user_option_set_NC *as_uac_user_option_set_finalize( as_uac_conf_file_set *file_set, as_uac_user_node *user, const char *name_override, as_uac_user_option_set_NC *option_set );

const char *as_uac_user_serialize_xml( as_uac_user_option_set *option_set );

    // Get a user option set by name given a parsed file set.
as_uac_user_option_set *as_uac_user_get_option_set_by_name( as_uac_conf_file_set *file_set, const char *user_name, const char *realm );

    // Delete option set.
void as_uac_user_free_option_set( as_uac_user_option_set *option_set );

    // Given a name of a option set member, return the xml path where it lives (used in asconfigurator).
const e_parse_hard_config_names *as_uac_get_user_query_by_name( const char *name );
void construct_default_as_uac_user_option_set( as_uac_user_option_set_NC *option_set );

    // as_uac_user_node, as_uac_trunk_node, etc. are all the same, they're just defined to make sure that a node that came from somewhere alien doesn't get passed to the wrong function.
void as_uac_release_user_node( as_uac_user_node *node);


/////////////////////
//                 //
//  Trunk options  //
//                 //
/////////////////////

#define as_uac_trunk_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_trunk_default_get_##name( as_uac_trunk_node *trunk, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_trunk_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_trunk_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_trunk in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_trunk_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get trunk option set from a node.
as_uac_trunk_option_set *as_uac_trunk_get_option_set( as_uac_conf_node *trunk );

const char *as_uac_trunk_serialize_xml( as_uac_trunk_option_set *option_set );

    // Get trunk option set by name given a file set.
as_uac_trunk_option_set *as_uac_trunk_get_option_set_by_name( as_uac_conf_file_set *file_set, const char *trunk_name );

    // Get trunk option set by id given a file set.
as_uac_trunk_option_set *as_uac_trunk_get_option_set_by_id( as_uac_conf_file_set *file_set, int id );

    // Release trunk option set.
void as_uac_trunk_free_option_set( as_uac_trunk_option_set *option_set );

const e_parse_hard_config_names *as_uac_get_trunk_query_by_name( const char *name );
void construct_default_as_uac_trunk_option_set( as_uac_trunk_option_set_NC *option_set );
void as_uac_release_trunk_node( as_uac_trunk_node *node);


////////////////////////
//                    //
//  Doc Root options  //
//                    //
////////////////////////

#define as_uac_docroot_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_docroot_default_get_##name( as_uac_docroot_node *docroot, xmlNodePtr* source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_docroot_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_docroot_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you change any of the following forced members, you must update
    // the definition of _global_default_docroot in parse_config_options.c.

        // The _absolute and _show_as members in the base object have not had variable replacement done on them.  These ones do.
        // For instance, _absolute might be "/usr/$(name)" when _canonical_absolute is "/usr/luke".
    char _canonical_absolute[AS_MAX_PATH];
    char _canonical_show_as[AS_MAX_PATH];

        // Internal use only.
    char _forced_docroot_separator[16];

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_docroot_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;

        // Pointer to next docroot.
    as_uac_docroot_option_set *_next_set;
};

    // Get an option set given a node and a string replacement tree.
as_uac_docroot_option_set *as_uac_docroot_get_option_set( as_uac_conf_node *docroot, const as_binary_tree_t var_tree );

const char *as_uac_docroot_serialize_xml( as_uac_docroot_option_set *option_set );

    // Get a list of all docroots for a user.
as_uac_docroot_option_set *as_uac_docroot_get_option_set_list( as_uac_conf_node *user_node, const as_binary_tree_t var_tree );

void as_uac_docroot_free_option_set( as_uac_docroot_option_set *option_set );

    // For the docroot walker functions, describes one file in the list.
typedef struct _as_uac_one_tree_entry
{
    char *absolute;
    char *show_as;

    as_dir_walk_type_t type;

    bool_t readable, writable, dirable;
} as_uac_one_tree_entry;

    // Forward declared iterator for the docroot walker functions.
struct _as_uac_docroot_walker;
typedef struct _as_uac_docroot_walker *as_uac_docroot_walker;

    // Given a file or directory name ("*.bin" or "/image_files/ready_to_ship", for instance), establish an iterator that will return all matches in sequence.
as_uac_docroot_walker as_uac_docroot_walker_open( const char *file_name, as_uac_docroot_option_set *option_set );

    // Allow wildcards in path.
as_uac_docroot_walker as_uac_docroot_walker_open_wildcardable( const char *file_name, as_uac_docroot_option_set *option_set, bool_t recurse );

    // Get next match in walk.
int as_uac_docroot_walker_get( as_uac_docroot_walker walker, as_uac_one_tree_entry *file );

    // Release iterator.
void as_uac_docroot_walker_close( as_uac_docroot_walker walker );

    // Given a show_as file name, a docroot set, and an operation (read or write), decide if the operation is allowed and, if so, what the absolute file name for the final file is.
int as_uac_docroot_approve_file_access( const char *file_name, as_uac_docroot_option_set *option_set, int write, char *absolute_file_name, size_t absolute_file_name_length, as_uac_docroot_option_set **option_set_used );

    // Given a file name of one type (show_as or absolute) and a docroot, convert it to the other type and return the docroot that was used to do it.  NULL return value means no sale.
as_uac_docroot_option_set *as_uac_docroot_show_as_to_absolute( const char *_file_name, as_uac_docroot_option_set *option_set, char *absolute_file_name, size_t absolute_file_name_length );
as_uac_docroot_option_set *as_uac_docroot_absolute_to_show_as( const char *_file_name, as_uac_docroot_option_set *option_set, char *show_as_file_name, size_t show_as_file_name_length );

const e_parse_hard_config_names *as_uac_get_docroot_query_by_name( const char *name );
void construct_default_as_uac_docroot_option_set( as_uac_docroot_option_set_NC *option_set );
void as_uac_release_docroot_node( as_uac_docroot_node *node);


//////////////////////////////
//                          //
//  Central Server options  //
//                          //
//////////////////////////////

#define as_uac_central_server_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_central_server_default_get_##name( as_uac_central_server_node *central_server, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_central_server_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_central_server_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_central_server in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_central_server_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get central_server option set from a node.
as_uac_central_server_option_set *as_uac_central_server_get_option_set( as_uac_conf_file_set *cfs );

const char *as_uac_central_server_serialize_xml( as_uac_central_server_option_set *option_set );

    // Release central_server option set.
void as_uac_central_server_free_option_set( as_uac_central_server_option_set *option_set );

const e_parse_hard_config_names *as_uac_get_central_server_query_by_name( const char *name );
void construct_default_as_uac_central_server_option_set( as_uac_central_server_option_set_NC *option_set );
void as_uac_release_central_server_node( as_uac_central_server_node *node);


////////////////////////
//                    //
//  Database options  //
//                    //
////////////////////////

#define as_uac_database_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_database_default_get_##name( as_uac_database_node *database, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_database_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_database_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_database in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_database_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get database option set from a node.
as_uac_database_option_set *as_uac_database_get_option_set( as_uac_conf_file_set *cfs );

const char *as_uac_database_serialize_xml( as_uac_database_option_set *option_set );

    // Release database option set.
void as_uac_database_free_option_set( as_uac_database_option_set *option_set );

const e_parse_hard_config_names *as_uac_get_database_query_by_name( const char *name );
void construct_default_as_uac_database_option_set( as_uac_database_option_set_NC *option_set );
void as_uac_release_database_node( as_uac_database_node *node);


///////////////////////////
//                       //
//  HTTP Server options  //
//                       //
///////////////////////////

#define as_uac_http_server_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_http_server_default_get_##name( as_uac_http_server_node *http_server, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_http_server_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_http_server_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_http_server in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_http_server_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get http_server option set from a node.
as_uac_http_server_option_set *as_uac_http_server_get_option_set( as_uac_conf_file_set *cfs );

const char *as_uac_http_server_serialize_xml( as_uac_http_server_option_set *option_set );

    // Release http_server option set.
void as_uac_http_server_free_option_set( as_uac_http_server_option_set *option_set );

const e_parse_hard_config_names *as_uac_get_http_server_query_by_name( const char *name );
void construct_default_as_uac_http_server_option_set( as_uac_http_server_option_set_NC *option_set );
void as_uac_release_http_server_node( as_uac_http_server_node *node);


////////////////////////
//                    //
//  VLink V1 options  //
//                    //
////////////////////////

#define as_uac_vlink_V1_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_vlink_V1_default_get_##name( as_uac_vlink_V1_node *vlink_V1, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_vlink_V1_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_vlink_V1_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_vlink_V1 in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_vlink_V1_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;

    struct _as_uac_vlink_V1_option_set *_next_vlink;
};

    // Get vlink_V1 option set from a node.
as_uac_vlink_V1_option_set *as_uac_vlink_V1_get_option_set( as_uac_conf_file_set *cfs );

    // Release vlink_V1 option set.
void as_uac_vlink_V1_free_option_set( as_uac_vlink_V1_option_set *option_set );

void construct_default_as_uac_vlink_V1_option_set( as_uac_vlink_V1_option_set_NC *option_set );


///////////////////////
//                   //
//  Conf V1 options  //
//                   //
///////////////////////

#define as_uac_conf_V1_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_conf_V1_default_get_##name( as_uac_conf_V1_node *conf_V1, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_conf_V1_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_conf_V1_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    as_uac_vlink_V1_option_set *_first_vlink;

    // If you add any forced members, you must update the
    // definition of _global_default_conf_V1 in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_conf_V1_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get conf_V1 option set from a node.
as_uac_conf_V1_option_set *as_uac_conf_V1_get_option_set( as_uac_conf_file_set *cfs );

    // Release conf_V1 option set.
void as_uac_conf_V1_free_option_set( as_uac_conf_V1_option_set *option_set );

void construct_default_as_uac_conf_V1_option_set( as_uac_conf_V1_option_set_NC *option_set );


//////////////////////////////////
//                              //
//  HTTP Session Start options  //
//                              //
//////////////////////////////////

#define as_uac_http_session_start_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_http_session_start_default_get_##name( as_uac_http_session_start_node *http_session_start, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_http_session_start_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_http_session_start_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_http_session_start in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_http_session_start_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get http_session_start option set from a node.
as_uac_http_session_start_option_set *as_uac_http_session_start_get_option_set( as_uac_conf_node *node );

const char *as_uac_http_session_start_serialize_xml( as_uac_http_session_start_option_set *option_set );
as_uac_http_session_start_option_set *as_uac_http_session_start_deserialize_xml( const char *xml );

    // Release http_session_start option set.
void as_uac_http_session_start_free_option_set( as_uac_http_session_start_option_set *option_set );

const e_parse_hard_config_names *as_uac_get_http_session_start_query_by_name( const char *name );
void construct_default_as_uac_http_session_start_option_set( as_uac_http_session_start_option_set_NC *option_set );
void as_uac_release_http_session_start_node( as_uac_http_session_start_node *node);


////////////////////////////////
//                            //
//  HTTP Session End options  //
//                            //
////////////////////////////////

#define as_uac_http_session_end_option(name, type, default_value, param) \
    as_uac_conf_##type as_uac_http_session_end_default_get_##name( as_uac_http_session_end_node *http_session_end, xmlNodePtr *source_node, as_uac_single_warning **warning_link );
#include "parse_config_option_set.h"


struct _as_uac_http_session_end_option_set
{
    as_uac_single_warning *_warning_list;

#   define as_uac_http_session_end_option(name, type, default_value, param) as_uac_conf_##type _##name;
#   include "parse_config_option_set.h"

    // If you add any forced members, you must update the
    // definition of _global_default_http_session_end in parse_config_options.c.

        // Internal use only:  Where did each option come from in the xml tree?
    struct {
        xmlNodePtr _top_level;

#       define as_uac_http_session_end_option(name, type, default_value, param) xmlNodePtr _##name;
#       include "parse_config_option_set.h"
    } _data_sources;
};

    // Get http_session_end option set from a node.
as_uac_http_session_end_option_set *as_uac_http_session_end_get_option_set( as_uac_conf_node *node );

const char *as_uac_http_session_end_serialize_xml( as_uac_http_session_end_option_set *option_set );
as_uac_http_session_end_option_set *as_uac_http_session_end_deserialize_xml( const char *xml );

    // Release http_session_end option set.
void as_uac_http_session_end_free_option_set( as_uac_http_session_end_option_set *option_set );

const e_parse_hard_config_names *as_uac_get_http_session_end_query_by_name( const char *name );
void construct_default_as_uac_http_session_end_option_set( as_uac_http_session_end_option_set_NC *option_set );
void as_uac_release_http_session_end_node( as_uac_http_session_end_node *node);

    // To allow changing from "* * * * *" to/from "" or whatever.
void uac_set_default_cron_string( const char *new_string );

const char *as_uac_absolute_file_name( const char *file_name, as_uac_docroot_option_set *docroot );

#ifdef __cplusplus
}
#endif

#endif // __PARSE_CONFIG_OPTIONS_H__
