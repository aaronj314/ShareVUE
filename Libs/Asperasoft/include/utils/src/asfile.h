/*
 * asfile.h
 *
 * TODO: consider changing as_fileopen() to return an as_filehandle_t.
 *
 * Aspera, Inc.
 *
 */

#ifndef _ASFILE_H_
#define _ASFILE_H_

#include "asplatform.h"
#include "astime.h"

#ifndef WIN32
#define AS_FILE_INVALID     (-1)
#ifdef LINUX
#define HAVE_PWRITE         (1)
#ifdef __USE_LARGEFILE64
#define HAVE_PWRITE64       (1)
#endif
#else
#define HAVE_PWRITE         (0)  /* FIXME for APPLE and other OS  */
#define HAVE_PWRITE64       (0)  /* FIXME for APPLE and other OS  */
#endif  /* LINUX */

#else
#define AS_FILE_INVALID     INVALID_HANDLE_VALUE

/* undefined stat mode flags */
#ifndef S_IFLNK
#define S_IFLNK     (0120000)
#endif
/* windows sockets are not regular files */
/*
#ifndef S_IFSOCK
#define S_IFSOCK    (0140000)
#endif
*/

/* File open modes for writing */
#ifndef NO_TEST_HOOKS
#define S_ISLNK(m)      (((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)      (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)      (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)      (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)      (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m)     (((m) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(m)     (((m) & S_IFMT) == S_IFSOCK)
#else
#define S_ISLNK(m)      as_islnk(m)
#define S_ISBLK(m)      as_isblk(m)
#define S_ISFIFO(m)     as_isfifo(m)
#define S_ISSOCK(m)     as_issock(m)
#define S_ISREG(m)      as_isreg(m)
#define S_ISDIR(m)      as_isdir(m)
#define S_ISCHR(m)      as_ischr(m)
#endif

#define S_ISUID  (0004000)
#define S_ISGID  (0002000)
#define S_ISVTX  (0001000)

#define S_IRWXU  (00700)
#define S_IRUSR  (00400)
#define S_IWUSR  (00200)
#define S_IXUSR  (00100)

#define S_IRWXG  (00070)
#define S_IRGRP  (00040)
#define S_IWGRP  (00020)
#define S_IXGRP  (00010)

#define S_IRWXO  (00007)
#define S_IROTH  (00004)
#define S_IWOTH  (00002)
#define S_IXOTH  (00001)

#define HAVE_PWRITE    0
#define HAVE_PWRITE64  0
#endif  /* WIN32 */

#define AS_SEEK_BEGIN   (SEEK_SET)
#define AS_SEEK_CURR    (SEEK_CUR)
#define AS_SEEK_END     (SEEK_END)

#define AS_FILE_ISREG(m)    (S_ISREG(m))
#define AS_FILE_ISDIR(m)    (S_ISDIR(m))
#define AS_FILE_ISCHR(m)    (S_ISCHR(m))
#define AS_FILE_ISLNK(m)    (S_ISLNK(m))
#define AS_FILE_ISBLK(m)    (S_ISBLK(m))
#define AS_FILE_ISFIFO(m)   (S_ISFIFO(m))
#define AS_FILE_ISSOCK(m)   (S_ISSOCK(m))

#define AS_FILE_UTIME_NOW   (-1)

typedef struct {
#ifdef WIN32
    HANDLE handle;
#else
    int handle;
#endif
} as_file_t;

typedef as_file_t* as_filehandle_t;

#ifdef WIN32
typedef u_int32_t as_file_mode_t;
#else
typedef mode_t as_file_mode_t;
#endif

/* File types */
typedef enum {
    AS_FILE_DIRECTORY = 0x0,
    AS_FILE_REGULAR   = 0x1,
    AS_FILE_CHAR      = 0x2,
    AS_FILE_BLOCK     = 0x3,
    AS_FILE_FIFO      = 0x4,
    AS_FILE_SOCK      = 0x5,
    AS_FILE_SYMLINK   = 0x6,
    AS_FILE_UNKNOWN   = 0xFFFF
} as_file_type_t;

/* File information (stat structure) */
typedef struct {
    u_int64_t size;         /* File size in bytes */
    u_int32_t blocks;       /* Blocks on disk */
    as_file_type_t type;    /* File type */
    as_file_mode_t mode;    /* File mode */
    u_int32_t uid;          /* User id of file */
    u_int32_t gid;          /* Group id of file */
    as_time_t ctime;        /* Creation time */
    as_time_t mtime;        /* Last modified time */
    as_time_t atime;        /* Last access time */
} as_stat_t;

/* File stat types */
typedef enum {
    AS_STAT_FILE        = 0x0,
    AS_STAT_SYMLINK     = 0x1
} as_stat_mode_t;

/* md5 data structure */
#define AS_MD5_SIZE         (16)
typedef struct {
    u_int8_t hash[AS_MD5_SIZE + 1];
    u_int8_t hashstr[(AS_MD5_SIZE << 1) + 1];
} as_md5_t;

/* File handle macros */
#define AS_FILE_INIT(f)     ((f).handle = AS_FILE_INVALID)
#define AS_FILE_VALID(f)    ((f).handle != AS_FILE_INVALID)

typedef FILE as_filestream_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * File open API
 * returns 0 on success or errno on error 
 * File writing modes are specified above
 */

/*
 * @brief   Initialize file handle
 * @param   fh          File handle
 * @return  O on success, errno on error
 */
ASUTILS_API as_err_t
as_file_init(
    as_file_t *fh);

/*
 * @brief   Open file for reading
 * @param   filename    File path
 * @param   fh          File handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_openread(       
    const char *filename,
    as_file_t *fh);

/*
 * @brief   Open file for writing 
 * @param   filename    File path
 * @param   fh          File handle
 * @param   mode        File open mode 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_openwrite(      
    const char *filename,
    as_file_t *fh,
    int mode);

/*
 * @brief   Open file for append
 * @param   filename    File path
 * @param   fh          File handle
 * @param   mode        File open mode
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_openappend(
    const char * filename,
    as_file_t *fh,
    int mode);

/*
 * @brief   Open file for read/write
 * @param   filename    File path
 * @param   fh          File handle
 * @param   mode        File open mode (0007 for no create)
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_openrw(
    const char * filename,
    as_file_t *fh,
    int mode);

/*
 * @brief   Close previously opened file 
 * Close file handle and reset handle
 * @param   file        File handle
 * @return  0 on successs, errno on error
 */
ASUTILS_API as_err_t 
as_file_close(
    as_file_t *file);

/*
 * @brief   Flush file changes to the disk
 * This will block untill file modifications are flushed to disk/tape
 * @param   file        File handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_file_flush(          
    as_file_t *file);

/*
 * @brief   Read from opened file 
 * @param   file        File handle
 * @param   buf         Data buffer
 * @param   bsize       Requested size to read
 * @param   rsize       Actiual size read 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_read(
    const as_file_t *file,
    char *buf,
    size_t bsize,
    size_t *rsize);

/*
 * @brief   Write to opened file
 * @param   file        File handle
 * @param   buf         Data buffer
 * @param   bsize       Requested size to write
 * @param   wsize       Actual size written
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_write(           
    const as_file_t *file,
    const char *buf,
    size_t bsize,
    size_t *wsize);

/*
 * @brief   Write to a file from a given offset
 * @param   file        File handle
 * @param   buf         Data buffer
 * @param   bsize       Requested size to write
 * @param   offset      File offset
 * @param   wsize       Actual number of size written
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_pwrite(          
    as_file_t *file,
    const char * buf,
    size_t bsize,
    int64_t offset,
    size_t *wsize);

/*
 * @brief   Reposition file offset
 * @param   file        File handle
 * @param   offset      File offset
 * @param   start       File start position
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_seek(
    as_file_t *file,
    int64_t offset,
    int start);

/*
 * @brief   Get stat info on a file
 * @param   filename    File path
 * @param   stb         Stat buffer
 * @param   flag        Stat type to dereference symlinks
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_stat(            
    const char *filename,
    as_stat_t *stb,
    as_stat_mode_t statmode);

/*
 * @brief  Get stat info of a file  
 * @param   file        File handle
 * @param   stb         Stat buffer
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_fstat(
    as_file_t *file,
    as_stat_t *stb);

/*
 * @brief   Get md5 sum of a file 
 * Either file handle or file name should be set
 * @param   file        File handle
 * @param   fname       File path
 * @param   md5         MD5 buffer
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_md5(
    as_file_t *file,
    const char *fname,
    as_md5_t *md5);

/*
 * @brief   Delete a file
 * @param   filename    File path
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_delete(
    const char *filename);

/*
 * @brief   Truncate a file to a given size 
 * @param   file        File handle
 * @param   size        Truncated file size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_truncate(
    as_file_t *file,
    int64_t size);

/*
 * @brief   Rename a file
 * @param   oldname     Previous file name(with full path) 
 * @param   newname     New file name(with full path) 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_rename(         
    const char * oldname,
    const char * newname);

/*
 * @brief   Copy a file
 * @param   srcpath     Full path to src file
 * @param   dstpath     Full path to dst file
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_copy(
    const char *srcpath,
    const char *dstpath,
    int mode);

/*
 * @brief   Convert file path to unix path
 * Convert argument to a Unix path by changing \ to /
 * @param   path        File path buffer
 */
ASUTILS_API void 
as_file_tounixpath(
    char *path);

/*
 * @brief   Create a file path
 * Append file name to the given directory path
 * Would insert "/" if the path does not have a trailing "/"
 * In case of empty path, would insert "/" before the file name
 * @param   path        File path
 * @param   fname       File name to append
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_append_path(
    const char *path,
    const char *fname,
    char *buf,
    size_t bsize);

/*
 * @brief   Get the basename of a file
 * @param   path        File path
 * @param   fname       File name
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_basename(
    const char *path,
    const char **fname);

/*
 * @brief  Get the absolute path of a file
 * @param  path        File path
 * @param  abspath     Absolute path
 * @param  abspathsz   Absolute path size
 * @return 0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_realpath(
    const char *path,
    char *abspath,
    size_t abspathsz);

/*
 * @brief   Read a symbolic link
 * Return the filename of a symbolic link
 * @param   path        File path of the symbolic link
 * @param   buf         Buffer to write symlink
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_readlink(
    const char *path,
    char *buf,
    size_t bsize);

/*
 * @brief   Create a symbolic link
 * Create a symlink to a given source file directory, 
 * with the given destination
 * @param   src         Symlink path
 * @param   path        Symlink dst path
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_symlink(
    const char *src,
    const char *path);

/* 
 * @brief   Create a hard link
 * @param   oldpath     Src path
 * @param   newpath     Dest path
 */
ASUTILS_API as_err_t
as_file_hardlink(
    const char *oldpath,
    const char *newpath);

/*
 * @brief   Output file mode as a string 
 * @param   sbuf        File stat buffer
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_permissions(
    const as_stat_t *sbuf,
    char *buf,
    size_t bsize);

/*
 * @brief   Compare file paths
 * Check for path1 in path2 
 * If path2 > path1, then should be separated by / 
 * @param   src         Src file path
 * @param   dst         Dst file path
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_path_compare(
    const char *src,
    const char *dst);

/*
 * @brief   Get the parent directory path
 * Modify fpath to show the parent directory
 * If fpath is not a directory path then set fpath to '.'
 * @param   fpath       File path
 * @param   buf         Buffer
 * @param   bsize       Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_dirname(
    char *fpath);

/*
 * @brief   Change file ownership
 * @param   fpath       File path
 * @param   owner       Name of new owner.  0 to leave unchanged.
 * @param   group       Name of new group.  0 to leave unchanged.
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_chown(
    const char *fpath,
    const char *owner,
    const char *group);

struct _as_chown_context_t;
typedef struct _as_chown_context_t *as_chown_context_t;

/*
 * @brief   Create file ownership context
 * This context can be used on further calls to as_file_chown_context to quickly change
 * several files to the same ownership values.  Windows has a lot of overhead for
 * establishing SIDS, etc.  Posix, not nearly as much.
 *
 * Examples:
 *
 * Set ownership of two files to user_foo and group_foo:
 * as_file_chown_create_context( "user_foo", "group_foo", &context );
 * as_file_chown_context( context, "/tmp/file_name_1" );
 * as_file_chown_context( context, "/tmp/file_name_2" );
 * as_file_chown_release_context( &context );
 *
 * Set ownership of one file to group_foo, leaving user alone:
 * as_file_chown_create_context( 0, "group_foo", &context );
 * as_file_chown_context( context, "/tmp/file_name_2" );
 * as_file_chown_release_context( &context );
 *
 * @param   owner       Name of new owner.  0 to leave unchanged.
 * @param   group       Name of new group.  0 to leave unchanged.
 * @param   context     Result
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_chown_create_context(
    const char *owner,
    const char *group,
    as_chown_context_t *context);

/*
 * @brief   Change file ownership based on context
 * @param   context     Context to use
 * @param   fpath       File name
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_chown_context(
    const as_chown_context_t context,
    const char *fpath);


/*
 * @brief   Release file ownership context
 * @param   context     Context to release
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_file_chown_release_context(
    as_chown_context_t *context);


/*
 * @brief   Open file for reading
 * @param   filename    File path
 * @param   f           File stream
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_filestream_openread(       
    const char *filename,
    as_filestream_t **f);


/* 
 * @brief   Update file access time
 * @param   fname       File name
 * @param   tstamp      Time stamp
 */
ASUTILS_API as_err_t
as_file_utime(
    const char *fname,
    int64_t tstamp);

ASUTILS_API bool_t
as_file_valid(
    as_file_t *f); 

ASUTILS_API int
as_file_desc(
    as_file_t *f);

#ifndef NO_TEST_HOOKS
ASUTILS_API bool_t as_islnk( as_file_mode_t m);
ASUTILS_API bool_t as_isblk( as_file_mode_t m);
ASUTILS_API bool_t as_isfifo(as_file_mode_t m);
ASUTILS_API bool_t as_issock(as_file_mode_t m);
ASUTILS_API bool_t as_isreg( as_file_mode_t m);
ASUTILS_API bool_t as_isdir( as_file_mode_t m);
ASUTILS_API bool_t as_ischr( as_file_mode_t m);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _AS_FILE_H_ */
