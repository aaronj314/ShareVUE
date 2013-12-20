#ifndef _AS_DOCROOT_H_
#define _AS_DOCROOT_H_

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Flags for docroot checks
 * path : string comparison of docroot and given path
 * link : stat for symbolic links
 * file : stat for file 
 */
typedef enum {
    AS_DOCROOT_PATH     = 0x0,
    AS_DOCROOT_SYMLINK  = 0x1,
    AS_DOCROOT_FILE     = 0x2,
} as_docroot_type_t;

/*
 * @brief   Check if docroot exists
 * @param   docroot     Docroot
 * @return  0 if exists, -1 if not
 */
ASUTILS_API as_err_t 
as_docroot_isvalid(     
   const char *docroot,
   as_docroot_type_t flag);

/*
 * @brief   Check for docroot in given path 
 * @param   docroot     Docroot 
 * @param   path        Canonicalized path
 * @param   flag        File stat flag 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_docroot_check(
    const char *docroot,
    const char *path,
    as_docroot_type_t flag);

/*
 * @brief   Check directory path to be in docroot
 * @param   docroot     Docroot 
 * @param   path        Canonicalized directory path
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_docroot_dirpath_check(
    const char *docroot,
    const char *path);

/*
 * @brief   Get Canonicalized file path
 * Return the canonicalized path without ".." and "."
 * Returned path is baded on docroot
 * @param   docroot     Docroot
 * @param   str         Uncanonicalized path
 * @param   path        Canonicalized path
 * @param   pathsz      Path buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_canonicalized_path(
    const char *docroot,
    const char *str,
    char *path,
    size_t pathsz);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _AS_DOCROOT_H_ */
