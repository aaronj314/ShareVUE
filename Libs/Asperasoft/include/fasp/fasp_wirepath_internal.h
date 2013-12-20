/* 
 * fasp_wirepath_internal.h
 * These are the wirepath functions that are not part of the public interface
 */
#ifndef __FASP_WIREPATH_INTERNAL_H__
#define __FASP_WIREPATH_INTERNAL_H__

#include <fasp/fasp_errno.h>

/* Facts (describe the context of the file copy operation) */
#define wp_fact_create_dir                0x0001
#define wp_fact_source_is_dir             0x0002
#define wp_fact_destination_parent_exists 0x0004
#define wp_fact_destination_exists        0x0008
#define wp_fact_destination_is_dir        0x0010
#define wp_fact_multiple_sources          0x0020
#define FACT_COUNT  6

/* Macros used to "gather" facts */
#define WP_FACT_SET_CREATE_DIR(facts)                (*facts = *facts | wp_fact_create_dir)
#define WP_FACT_SET_SOURCE_IS_DIR(facts)             (*facts = *facts | wp_fact_source_is_dir)
#define WP_FACT_SET_MULTIPLE_SOURCES(facts)          (*facts = *facts | wp_fact_multiple_sources)
#define WP_FACT_SET_DESTINATION_PARENT_EXISTS(facts) (*facts = *facts | wp_fact_destination_parent_exists)
#define WP_FACT_SET_DESTINATION_EXISTS(facts)        (*facts = *facts | wp_fact_destination_exists)
#define WP_FACT_SET_DESTINATION_IS_DIR(facts)        (*facts = *facts | wp_fact_destination_is_dir)
/* Macros used to inspect facts */
#define WP_FACT_CREATE_DIR(facts)                    ((*facts & wp_fact_create_dir) ? AS_TRUE : AS_FALSE )
#define WP_FACT_SOURCE_IS_DIR(facts)                 ((*facts & wp_fact_source_is_dir) ? AS_TRUE : AS_FALSE )
#define WP_FACT_MULTIPLE_SOURCES(facts)              ((*facts & wp_fact_multiple_sources) ? AS_TRUE : AS_FALSE )
#define WP_FACT_DESTINATION_PARENT_EXISTS(facts)     ((*facts & wp_fact_destination_parent_exists) ? AS_TRUE : AS_FALSE )
#define WP_FACT_DESTINATION_EXISTS(facts)            ((*facts & wp_fact_destination_exists) ? AS_TRUE : AS_FALSE )
#define WP_FACT_DESTINATION_IS_DIR(facts)            ((*facts & wp_fact_destination_is_dir) ? AS_TRUE : AS_FALSE )

typedef fasp_errno_e (*fasp_wp_action_function_t)(const fasp_session_path_context_t *, char *, int);

/*  
 * Action functions 
 */

fasp_errno_e fasp_wp_action_fail_destination_does_not_exist(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_fail_destination_is_file(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_fail_invalid_facts(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_create_destination_dir(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_place_under_destination_dir(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_place_contents_under_destination_dir(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_replace_destination_file(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_create_destination_dir_and_place_under(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

fasp_errno_e fasp_wp_action_create_destination_dir_and_place_contents_under(
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz);

as_action_e fasp_wp_decide( as_fact_t facts );
fasp_wp_action_function_t fasp_wp_action_function( as_action_e action);

bool_t fasp_wp_effective_destination_is_parent( as_action_e action );
void fasp_wp_receiver_set_effective_destination( 
    const fasp_session_path_context_t* f,
    char* effective_destination, 
    int effective_destination_sz );

bool_t fasp_path_has_wildcard( const char * path);
bool_t fasp_more_than_one_source( const_char_const* const * source_paths);
int fasp_path_without_wildcard( const char * path, char * buf, int bufsz );

bool_t fasp_target_must_be_dir(
    const fasp_session_path_context_t* fpct,
    const_char_const* const * source_paths);

bool_t fasp_wp_destination_parent_exists( const char* parent_path );
bool_t fasp_wp_destination_exists( const char* path );
bool_t fasp_wp_destination_is_dir( const char* path );
as_fact_t fasp_wp_receiver_gather_facts( const fasp_session_path_context_t* fpct);
int   fasp_canonical_source_path( const char* source_path, char* buf, int bufsz);

fasp_errno_e fasp_receiver_initialize_session_path_context(
    fasp_session_path_context_t* fpct,
    bool_t create_target_dir,
    bool_t target_must_be_dir,
    as_uac_docroot_option_set* docroots,
    const_char_const* const * source_paths,
    const char* session_destination_path );

fasp_errno_e fasp_receiver_check_session_path_context( 
    const fasp_session_path_context_t* f, 
    char* error, 
    int errorsz );
    
#endif
