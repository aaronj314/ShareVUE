//  parse_hard_config_list.h
//
//  Process contents of the list in parse_hard_config_names.h into an enum that can be used for token based string searches.
//
//  This is not a file that should change much...

#ifndef __PARSE_HARD_CONFIG_LIST_H__
#define __PARSE_HARD_CONFIG_LIST_H__

#define hard_config_name_use_attribute  (0x10000)

typedef enum
{
        // Do the cron evaluation stuff.
    hard_config_search_process_value = -10,
    hard_config_search_lowest_valid = hard_config_search_process_value,

        // Error state when a match is not found.
    unknown_hard_config_name = -9,

        // Prefixes to control string matching.
    hard_config_search_match_name = -8,         // Match user name depending on platform standards (Linux = case sensitive, windows = not)
    hard_config_search_match_trimmed = -7,      // Match ignoring leading and trailing whitespace
    hard_config_search_match_ignore_case = -6,  // Match ignoring case (stricmp)

    hard_config_search_match_numeric = -5,      // Match numerically (atoi(x) == atoi(y))
    hard_config_search_match_exact = -4,        // Match exactly (strcmp)
    hard_config_search_match_regexp_query = -3, // Treat the query value as a regular expression and try to match the tag to it
    hard_config_search_match_regexp_tag = -2,   // Treat the tag value as a regular expression and try to match the query to it

        // Terminates a varargs search query.
    hard_config_search_terminator = -1,

        // Indicates that we want to move into the parent instead of one of the children.
    hard_config_parent = 0,

#define hard_config_name(n) hcn_##n,
#include "parse_hard_config_names.h"

    total_hard_config_names,

    hard_config_start_attributes = hard_config_name_use_attribute,

#define hard_attribute_name(n) use_attribute_##n,
#include "parse_hard_attribute_names.h"

    total_hard_attribute_names

} e_parse_hard_config_names;

typedef enum
{
    hard_config_match_trimmed = 0x01,            // Trim leading and trailing 
    hard_config_match_caseless = 0x02            // Ignore case on match.

} e_parse_match_flags;

#define Prefix_Require_Numeric_Match_With( val )          hard_config_search_match_numeric, val
#define Prefix_Require_String_Match_With( val )           hard_config_search_match_exact, val
#define Prefix_Require_RegExp_In_Tag_To_Match( val )      hard_config_search_match_regexp_tag, val
#define Prefix_Require_Tag_To_Match_Regexp_In( val )      hard_config_search_match_regexp_query, val
#define Prefix_Allow_Trimmed_Match                        hard_config_search_match_trimmed
#define Prefix_Allow_CaselessString_Match                 hard_config_search_match_ignore_case
#define Prefix_Name_Match                                 hard_config_search_match_name

e_parse_hard_config_names phcn_find_index_from_name( const char *name );
const char *phcn_get_index_text( e_parse_hard_config_names index );

#endif // __PARSE_HARD_CONFIG_LIST_H__
