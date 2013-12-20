/*
 * fasp_wirepath.h
 *
 * Logic for determining where to copy the files on the destination, largely
 * respecting the semantics of the copy command (cp src dst).
 *
 * Converts from 
 *    1) source to wire paths and 
 *    2) wire to destination paths
 * 
 * Terminology used for path names:
 *   If fasp transfers a path "path/to/some/folder" to "/tmp"
 *   and the current file is  "path/to/some/folder/named/myfile"
 *   then the
 *     source_path               = "path/to/some/folder"
 *     source_item_path          = "path/to/some/folder/named/myfile"
 *     wire_path                 =              "folder/named/myfile" 
 *     session_destination_path  =         "/tmp"
 *     absolute_destination_path =         "/tmp/folder/named/myfile" 
 *
 * Note: in the notations below we use \* instead of * because the compiler
 *       interprets it as a start of a nested comment.
 *
 * Behavior: (letters are directories, numbers are files)
 *   SOURCE      DEST           RESULT
 *               doesn't exist
 *   a        -> /z/y        => a/\* in /z/y/\* (a renamed to y)
 *   a, b     -> /z/y        => a, b in /z/y/\* (z/y/a, z/y/b)
 *   a/1      -> /z/y        => 1 renamed to y
 *   a/1, a/2 -> /z/y        => 1, 2 in /z/y/\*
 *   "a/\*"   -> /z/y        => a/\* in /z/y/\*
 *   a/\*     -> /z/y        => if a/\* expands to a/1, then 1 is renamed to y.
 *                                if a/\* expands to a/1 and a/2, then 1 and 2 go in /z/y/\*
 *               does exist
 *   a        -> /z/y        => a goes to /z/y/a
 *   a/1      -> /z/y        => 1 goes to /z/y/1
 *   a/1, a/2 -> /z/y        => 1, 2 in z/y/\*
 *   a/\*     -> /z/y        => a/\* in /z/y/\*
 *
 * Aspera, Inc.
 *
 */

#ifndef __FASP_WIREPATH_H__
#define __FASP_WIREPATH_H__

#include <uac/parse_config_options.h>
#include <utils/src/asutils.h>
#include <fasp/fasp_errno.h>

/* todo: move these to utils/src/astypes.h */
#ifdef WIN32
#pragma warning(push)
#pragma warning( disable:4114 ) // warning C4114: same type qualifier used more than once
#endif
typedef const char const_char;
typedef char const char_const;
typedef const_char const const_char_const;
#ifdef WIN32
#pragma warning(pop)
#endif


typedef unsigned as_fact_t;

typedef enum _as_action_e {
    e_wp_place_under_destination_dir = 0,
    e_wp_replace_destination_file,
    e_wp_create_destination_dir_and_place_under,
    e_wp_create_destination_dir_and_place_contents_under,
    e_wp_fail_destination_is_file,
    e_wp_fail_destination_does_not_exist,
    e_wp_fail_invalid_facts,
    e_wp_number_of_actions /* not an action, but keep this at the end of the list */
} as_action_e;

/*
 * fasp_session_path_context_t
 *
 *   Used by both the sender and receiver to hold the info that
 *   the receiver needs to make file-location decisions.
 */
typedef struct _fasp_session_path_context_t {

    /* 
     * Both the sending and receiving sides use these
     */

    /* For instance: if multiple files are being sent, then the target must be
     * a directory.
     */
     bool_t _target_must_be_dir;

    /* If the receiver needs to create the target dir and/or its parent dirs
     */
     bool_t _create_target_dir;

    /* The destination for the file/directory
     */
     char _session_destination_path[AS_MAX_PATH];

    /* 
     * Only the receiver side uses these
     */
    
    bool_t _multiple_sources;
    /* If /tmp/a is being transfered to non-existing directory /tmp/b, then
     * don't place 'a' in 'b', but instead place the contents of 'a' into 'b' (rename).
     */
    as_action_e _action;

    /* Docroot information from the conf files.
     * as_uac_docroot_option_set is innately const.
     */
    as_uac_docroot_option_set* _docroots;

    /* The destination's parent
     */
    char _session_destination_parent_path[AS_MAX_PATH];
    char _effective_destination_path[AS_MAX_PATH];

} fasp_session_path_context_t;


/*
 * Used by the sender to fill the session_path_context with
 * the info that the receiver will need.   
 *
 * Conventions for input values:
 *   - source_paths are relative to docroot "show_as" (not resolved to absolute paths)
 *   - docroots is never NULL (the caller will create a stand-in docroot if needed)
 *
 * Conventions for output values:
 *   - if one, non-wildcarded source, and it cannot be resolved to an absolute path, target_must_be_dir is false
 *     (this statement is no longer needed if we decide to always require show_as "/")
 */
fasp_errno_e
fasp_sender_prepare_session_path_context(
    fasp_session_path_context_t* fpct,
    bool_t create_target_dir,
    as_uac_docroot_option_set* docroots,
    const_char * const * source_paths,
    const char* session_destination_path
);

/* 
 * Used by the receiver to fill the session_path_context with
 * the info that was sent.  This context will be used in 
 * fasp_wire_to_absolute_path to convert wire paths to 
 * receiver-specific paths.
 *
 * side-effects: directories will be created on the file-system
 * if create_target_dir is true.
 *
 * Conventions for input values:
 *   - session_destination_path is relative to docroot "show_as" (not resolved to absolute paths)
 *   - docroots is never NULL (the caller will create a stand-in docroot if needed)
 *
 */

fasp_errno_e
fasp_receiver_prepare_session_path_context(
    fasp_session_path_context_t* fpct,
    bool_t create_target_dir,
    bool_t target_must_be_dir,
    as_uac_docroot_option_set* docroots,
    const_char_const * const * source_paths,
    const char* session_destination_path,
    char* error, 
    int errorsz
);

/*
 * Convert from sender-specific paths to paths that will
 * be sent to the receiver.
 *
 * If the   source_path is      b/c/d
 * and the  source_item_path is b/c/d/e/f
 * then the wire_path will be       d/e/f
 */
size_t
fasp_source_to_wire_path(         // /a/(b/c/[d)/e/f]
    const char* source_path,      // (.*) = b/c/d
    const char* source_item_path, // (.*] = b/c/d/e/f
    char* wire_path,              // [.*] = d/e/f
    size_t wire_path_sz,
    char *error,
    size_t errorsz
);

/*
 * Convert to receiver-specific paths from the relative path 
 * that was sent to the receiver.
 */
int
fasp_wire_to_destination_path(
    const fasp_session_path_context_t* fpct,
    const char* wire_path,
    char* absolute_path,
    size_t absolute_path_sz,
    char *error,
    size_t errorsz
);

#endif /* __FASP_WIREPATH_H__ */
