/*
 * parse_xml.h
 */

#ifndef __ASPERA_UAC_PARSE_XML_H__
#define __ASPERA_UAC_PARSE_XML_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/uri.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>

#include "parse_hard_config_list.h"
#include "uac_forward_declares.h"

    // Allocate a tracker object.  Passed to parse_xml_decorate_tree.  Same handle can be passed multiple times to concatenate XML files in memory.
as_uac_conf_level_tracker *parse_xml_allocate_tracker( void );

    // Tokenize and link up an XML file for easy searches.
void parse_xml_decorate_tree( xmlNodePtr cur, as_uac_conf_level_tracker *parent_tracker );

    // Free special search allocations.
void parse_xml_undecorate_tree( xmlNodePtr root );


    // Find the first node that matches a spec.  If handle is non-zero, return a value that can be used for calls to parse_xml_get_next_matching_node.
xmlNodePtr parse_xml_get_first_matching_node( const xmlNodePtr *root_list, as_uac_node_search_handle **handle, ... );
xmlNodePtr parse_xml_get_first_matching_node_args( const xmlNodePtr *root_list, as_uac_node_search_handle **handle, va_list *args );
xmlNodePtr parse_xml_get_first_matching_node_array( const xmlNodePtr *root_list, as_uac_node_search_handle **handle, e_parse_hard_config_names *query_list );

int parse_xml_get_int64_value( const xmlNodePtr *node, int64_t *result, ... );
const char *parse_xml_get_string_value( const xmlNodePtr *node, ... );

    // Continue the search just above.
xmlNodePtr parse_xml_get_next_matching_node( as_uac_node_search_handle *handle );

    // Free a search handle.
void parse_xml_free_node_search_handle( as_uac_node_search_handle *handle );

    // We get a link error if we call xmlFree directly, so do this instead.
#ifdef WIN32
void as_uac_call_xmlFree( void *data );
#define xmlFree(p) as_uac_call_xmlFree(p) 
#endif

xmlNodePtr parse_xml_get_first_child_of_type( as_uac_conf_level_tracker *tracker, e_parse_hard_config_names type );
xmlNodePtr parse_xml_get_next_sibling( as_uac_conf_level_tracker *tracker );


    // Get the content of a node.
const char *parse_xml_get_node_string( const xmlNodePtr node );

    // Get the parent of a node.
xmlNodePtr parse_xml_get_parent_node( const xmlNodePtr node );

typedef int t_parse_xml_node_filter_callback ( xmlTextReaderPtr reader_node, void *context );

as_uac_parse_xml_node_filter_set *parse_xml_allocate_node_filter_set( int default_keep );
void parse_xml_node_filter_set_members( as_uac_parse_xml_node_filter_set *filter_set, t_parse_xml_node_filter_callback *callback, void *context, ... );
xmlDocPtr parse_xml_load_filtered_xml_file( const char *file_name, as_uac_parse_xml_node_filter_set *filter_set, int *required_version );

int parse_xml_node_filter_callback_keep_all( xmlTextReaderPtr reader_node, void *context );

struct _as_uac_conf_level_tracker 
{
    xmlNodePtr firstOfType[ total_hard_config_names ];

    xmlNodePtr node;
    xmlNodePtr nextLikeMe;

    const xmlChar *content;
};


#ifdef __cplusplus
}
#endif

#endif
