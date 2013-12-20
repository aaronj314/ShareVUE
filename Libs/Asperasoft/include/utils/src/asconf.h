/*
 * asconf.h
 *
 * Configuration file reader.
 * The configuration file is XML.
 *
 * 2005, Aspera Inc.
 */
#ifndef ASCONF_H
#define ASCONF_H

#include "asplatform.h"
#include "asfile.h"

#define MAX_XML_NODES   (1024)  /* Max number of nodes per parser */

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * XML parser
 * Contains the context of the XML file parsing
 */
typedef struct as_xml_parser {
    as_file_t fptr;
    const char *filename;
    char *buffer;
    char *pointer;
    size_t buffer_size;
} as_xml_parser_t;

/* 
 * XML attribute
 * Represents one attribute: name=value
 */
typedef struct as_xml_attr_t {
    char *name;
    char *val;
    struct as_xml_attr_t *next;
} as_xml_attr_t;

/* 
 * XML node
 * Contains node attributes
 */
typedef struct as_xml_node_t {
    char *tag;                /* Tag name, always available */
    as_xml_attr_t *attrs;     /* Not available if not parsed */
    int error;                /* 1 if error parsing */
} as_xml_node_t;

/*
 * @brief   Init XML parser
 * Initialize the configuration XML parser
 * @param   parser      Parser handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_conf_init(
    as_xml_parser_t *parser);

/*
 * @brief   Cleanup XML parser
 * Cleanup the configuration XML parser by closing the HANDLE.
 * Freeing up parser is left to the caller.
 * @param   parser      Parser handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_conf_cleanup(
    as_xml_parser_t *parser);

/*
 * @brief   Read XML attribute
 * Oversimplified XML attribute reader
 * Currently does not handle nested comments or comments inside the tag
 * The node's tag field is set to a copy of the argument tag;  
 * The node's attrs field is set to a list of as_xml_attr
 * @param   parser      Parser handle 
 * @param   tag         Attribute tag
 * @param   node        Attributes
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_conf_getnodeattr(
    as_xml_parser_t *parser, 
    const char *tag,
    as_xml_node_t **node);

/*
 * @brief   Free XML attributes
 * Free XML node
 * @param   node        Attributes node
 */
ASUTILS_API void 
as_conf_releasenode(
    as_xml_node_t *node);

#ifdef __cplusplus
} /* End extern "C" */
#endif

#endif
