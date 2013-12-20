#ifndef _AS_DIR_H_
#define _AS_DIR_H_

#include "asplatform.h"
#include "asfile.h"

#ifndef WIN32
#include <dirent.h>
#elif defined APPLE
#include <sys/dirent.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AS_DIR_CREATE_PARENT    (1)

typedef struct {
#ifdef WIN32
    HANDLE handle;
    BOOL next_data;
    WIN32_FIND_DATA find_data;
#define AS_DIR_INVALID          (INVALID_HANDLE_VALUE)
#else
    DIR *handle;
#define AS_DIR_INVALID          (NULL)
#endif  /* WIN32 */
} as_dir_t;

typedef struct {
    char name[AS_MAX_PATH];
} as_dir_entry_t;

typedef enum {
    AS_DIRWALK_FILE      = 0x01,
    AS_DIRWALK_DIR       = 0x02,
    AS_DIRWALK_FALLBACK  = 0x03,
    AS_DIRWALK_DIREMPTY  = 0x04,
    AS_DIRWALK_ERR       = 0x05,
    AS_DIRWALK_NOTREG    = 0x06
} as_dir_walk_type_t;

typedef struct {
    int files;
    int dirs;
    int notregs;
    int errs;
} as_dir_walk_stat_t; 

/*
 * @brief   Initialize directory handle
 * @param   dir         Directory handle
 * @return  O on success, errno on error
 */
ASUTILS_API as_err_t
as_dir_init(
    as_dir_t *dir);

/*
 * @brief   Open directory 
 * @param   name        Canonical directory path with unix slashes
 * @param   dir         Directory handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_dir_open(
    const char *name,
    as_dir_t *dir);

/*
 * @brief   Close directory 
 * @param   dir         Directory handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_dir_close(
    as_dir_t *dir);

/*
 * @brief   Check for valid directory handle 
 * @param   dir         Directory handle
 * @return  O on invalid handle, != 0 otherwise
 */
ASUTILS_API int
as_dir_valid(
    const as_dir_t *dir);

/*
 * @brief   Browse opened directory
 * @param   dir         Directory handle 
 * @param   entry       Directory entry
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_dir_next(
    as_dir_t *dir,
    as_dir_entry_t *entry);

/*
 * @brief   Create a directory 
 * @param   name        Absolute directory path with unix slashes
 * @param   mode        Directory mode
 * @param   create_parentdir Create parent directory
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_dir_create(
    const char *name,
    int mode,
    bool_t create_parentdir);

/*
 * @brief   Delete directory 
 * @param   name        Absolute directory path with unix slashes
 * @param   delete_dircontent Delete directory content
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_dir_delete(
    const char *name,
    bool_t delete_dircontent);

/*
 * @brief   Get installation root dir
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
#if 0 /* obsolete */
ASUTILS_API as_err_t
as_dir_get_root(
    char *buf,
    size_t bsize);
#endif

/*
 * @brief   Get docroot for the current user 
 * Get document root by user ID from /etc/docroot. 
 * This is used on the server side (remote).
 * The format of the docroot file is one user entry per line:
 * <user-id>:<document-root-path>
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
#if 0 /* obsolete */
ASUTILS_API as_err_t 
as_dir_get_docroot(
    char *buf,
    size_t bsize);
#endif

/*
 * @brief   Get installation etc dir
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
#if 0 /* obsolete */
ASUTILS_API as_err_t
as_dir_get_etc(
    char *buf,
    size_t bsize);
#endif

/* Forward declarations, opaque to caller */
/* One of the builds throws a warning unless you define the struct ahead of time.  BSD I think... */
struct as_dir_walk_handle_t;
struct as_dir_walk_t;
typedef struct as_dir_walk_handle_t as_dir_walk_handle_t;
typedef struct as_dir_walk_t as_dir_walk_t;

/* 
 * @brief   Init directory walker for iterative walk
 * Initialize directory walker for iterative directory traversal.
 * On success, successive as_dir_walk_iterate calls return each 
 * directory entry.
 * @param   walker      Walker instance
 * @param   root        Root directory 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_dir_walk_init(
    as_dir_walk_t **walker,
    const char *root);

ASUTILS_API as_err_t
as_dir_walk_pop(
    as_dir_walk_t *walker);

/* 
 * @brief   Iterate directory traversal with directory walker
 * Iterate directory stucture.
 * @param   walker      Walker instance
 * @param   path        Path from root directory
 * @param   pathsz      Path buffer size
 * @param   type        File/Directory type
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_dir_walk_iterate(
    as_dir_walk_t *walker,
    char *fname,
    size_t fnamesz,
    as_dir_walk_type_t *type);

/* 
 * @brief   Release directory walker 
 * Release resources allocated in as_dir_walker_init.
 * @param   walker      Walker instance
 * @return  0 on success, errno om error
 */
ASUTILS_API as_err_t
as_dir_walk_release(
    as_dir_walk_t **walker);

/* Directory walk callback, returning != 0 aborts directory tree walking */
typedef as_err_t (*as_dir_walk_callback_t)(as_dir_walk_type_t type, /* Directory entry type */
                                           const char *name,        /* Directory entry path */
                                           void *context,           /* Callback token */
                                           as_err_t err);           /* Path err */

/* 
 * @brief   Walke directory with callback
 * Traverse directory with callbacks for each file/directory.
 * Ignores "." and ".." files.
 * On encountering an error, errno and path are returned to callback function.
 * Retruning != 0 in callback function aborts traversing. 
 * Aborting traversal always returns an error.
 * @param   root        Root directory
 * @param   callback    Callback function
 * @param   walkstats   Traversal stats
 * @param   context     Callback token
 * @return  0 on success, errno on error
 */
/* Currently unused.  Will need tests written if it comes back. */
#if 0
ASUTILS_API as_err_t
as_dir_walk_tree(
    const char *root,
    as_dir_walk_callback_t callback,
    as_dir_walk_stat_t *walkstats,
    void *context);
#endif 

#ifdef __cplusplus
} /* extern "C" */
#endif 

#endif /* _AS_DIR_H_ */
