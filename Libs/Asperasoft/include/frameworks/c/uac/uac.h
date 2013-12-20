/*
 * uac.h
 *
 * Load user settings.
 *
 * Aspera, Inc.
 */

#ifndef __ASPERA_UAC_H__
#define __ASPERA_UAC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <utils/src/asplatform.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "parse_xml.h"

#define MAX_CONF_FILES_IN_SET   (10)

    // List of all groups present in a conf file set (so the external membership calls can choose from within them).
typedef struct as_uac_single_group
{
    char group[AS_MAX_USER_NAME];
    char realm[AS_MAX_USER_NAME];
    double precedence;

    xmlNodePtr group_node;

} as_uac_single_group;

typedef struct _as_uac_group_set
{
    int count;

        // This field will grow to accommodate the total number of groups, so it should always be last.
    as_uac_single_group members[1];

} as_uac_group_set;

    // Defines a callback interface for an external group membership manager.
typedef struct _as_uac_user_groups_object
{
    void (*declare_known_groups)( const as_uac_group_set *group_set, struct _as_uac_user_groups_object *group_object );
    int (*find_user_groups )( const char *realm, const char *user, u_int32_t *group_mask, struct _as_uac_user_groups_object *group_object );
    void (*release_group_object )( struct _as_uac_user_groups_object *group_object );

    struct _as_uac_user_groups_object *next_object;

} as_uac_user_groups_object;

/*

Each group object type shall implement a constructor of the form:

    void get_foo_group_object( as_uac_user_groups_object ***pp_link );

This will place zero or more objects in the list double pointed to by pp_link and set
pp_link to point to the next_object member of the last object added.  The next_object
member of the last object need not be initialized (we set it to 0 ourselves).

This call should then be added to as_uac_initialize().

*/

void
as_uac_get_external_group_objects(
    as_uac_user_groups_object ***ppp_link );

void
as_uac_initialize(
    void);

void
as_uac_deinitialize(
    void);

typedef void (*as_uac_conf_file_set_destructor)( as_uac_conf_file_set *file_set, void *extra_storage );

xmlNodePtr as_uac_conf_file_set_get_root_node( as_uac_conf_file_set *file_set );
xmlDocPtr as_uac_conf_file_set_get_root_doc( as_uac_conf_file_set *file_set );

void as_uac_conf_file_set_destructor_set( as_uac_conf_file_set *file_set, as_uac_conf_file_set_destructor destructor );
void as_uac_conf_file_set_storage_set( as_uac_conf_file_set *file_set, void *storage );
void *as_uac_conf_file_set_storage_get( as_uac_conf_file_set *file_set );

as_uac_conf_file_set *
as_uac_load_single_conf_file(
    const char *conffile,
    as_uac_parse_xml_node_filter_set *filter_set);

    // Given a null terminated list of file names, load the files in sequence (concatenated) into a conf object.
as_uac_conf_file_set *
as_uac_load_conf_file_set(
    const char **conffile,
    as_uac_parse_xml_node_filter_set *filter_set);

    // Combine two separately loaded conf objects.  The linked lists in the first object are connected up to the linked lists in the second.
    // Important:  Both objects still need to be freed in separate calls to as_uac_release_conf_file_set, even if they're still linked together.
as_err_t
as_uac_append_conf_file_set(
    as_uac_conf_file_set_NC *dest,
    as_uac_conf_file_set *src);

    // Given a previously loaded XML document, make a as_uac_conf_file_set out of it.  Note:  _private members of the xml nodes are taken.
as_uac_conf_file_set *
as_uac_process_loaded_XML_document(
    xmlDocPtr doc );

    // Release the conf file set, including the underlying xmllib2 document.
void
as_uac_release_conf_file_set(
    as_uac_conf_file_set *file_set);

    // Release the conf file set, not including the underlying xmllib2 document.
void
as_uac_release_conf_file_set_keep_docs(
    as_uac_conf_file_set *file_set);

    // Total existence failure?  Bad Permissions?  Bad XML?
    // Assumes that the file name is known bad already.
as_err_t
as_uac_diagnose_bad_conf_file(
    const char *file_name, char **description);

/* Inform the external group sources of the groups inside this file set so they know
   what they should choose from. */
as_err_t
as_uac_select_master_conf_file_set(
    as_uac_conf_file_set *set);

    // Get the version # (currently always 2).
int
as_uac_get_version(
    as_uac_conf_file_set *file_set);

    // Get the root node.  This is the starting point for all searches.
as_uac_conf_node *
as_uac_get_root_node(
    as_uac_conf_file_set *file_set,
    ... );

    // Find a user by name.  direction is ignored.
as_uac_user_node *
as_uac_get_user(
    as_uac_conf_file_set *file_set,
    const char *user,
    const char *realm,
    int direction);

    // Find a group by name.  direction is ignored.
as_uac_user_node *
as_uac_get_group(
    as_uac_conf_file_set *file_set,
    const char *group,
    const char *realm,
    int direction);

    // Release a node object returned by one of the above two functions.
void
as_uac_release_conf_node(
    as_uac_conf_node *node);

    // Finds the first subnode of a given node that matches a hard_config_search_terminator terminated query.
xmlNodePtr as_uac_get_first_matching_node( as_uac_conf_file_set *file_set, as_uac_node_search_handle **handle, ... );

bool_t as_uac_is_user_in_conf( as_uac_conf_file_set *file_set, const char *user_name );
bool_t as_uac_is_group_in_conf( as_uac_conf_file_set *file_set, const char *group_name );

    // Finds next match for above.
xmlNodePtr as_uac_get_next_matching_node( as_uac_node_search_handle *handle );


    // Generate a base64 token string based on the passed info.
int
as_uac_generate_token(
    const char *path,
    const char *user_name,
    as_uac_user_option_set *user_options,
    int upload,
    char *dst,
    size_t dstsize);

    // Approve a base64 token string based on the passed info.
int as_uac_approve_token(
    const char *token,
    const char *path,
    const char *user_name,
    as_uac_user_option_set *user_options,
    int upload);

    // Make sure a path has a leading slash and then canonicalize it.
int32_t uac_token_rooted_path(
    const char *path,
    char *buf,
    size_t bufsz);

#ifdef __cplusplus
}
#endif

#endif
