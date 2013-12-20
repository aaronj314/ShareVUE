#ifndef ASPATH_H
#define ASPATH_H

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char _prefix[AS_MAX_PATH];
    int  _current_directory;
    const char* _directories[AS_MAX_PATH];
    size_t  _directory_sizes[AS_MAX_PATH];
} as_path_t;

ASUTILS_API ssize_t as_path_parent_dir(const char * path, char *buf, size_t bufsz);
ASUTILS_API ssize_t as_path_remove_trailing_slashes(const char * path, char *buf, size_t bufsz);
ASUTILS_API ssize_t as_path_executable_path(char *buf, size_t bufsz, const char* arg);
ASUTILS_API ssize_t as_path_executable_path_from_arg(const char* arg, char* buf, size_t bufsz);
ASUTILS_API ssize_t as_path_executable_dir(char *buf, size_t bufsz, const char* arg);
ASUTILS_API int as_path_find_file_in_paths(const char* file_name, const char** paths, char* buf, size_t bufsz);
ASUTILS_API ssize_t as_path_root_dir(const char* exec_path, char* buf, size_t bufsz);
ASUTILS_API ssize_t as_path_etc_dir(const char* exec_path, char* buf, size_t bufsz);
ASUTILS_API ssize_t as_path_etc_file(const char* file_name, const char* exec_path, char* buf, size_t bufsz);
ASUTILS_API as_err_t as_path_user_home_dir(const char* user, char* buf, size_t bufsz);
ASUTILS_API ssize_t as_path_home_dir(char *buf, size_t bufsz);

ASUTILS_API bool_t as_path_exists(const char* filename);
ASUTILS_API bool_t as_path_is_dir(const char* filename);
ASUTILS_API int as_path_append(const char *path, const char *fname, char *dst, size_t len);

ASUTILS_API const char *as_path_getcwd(char *buf, size_t size);

ASUTILS_API int as_path_canonical_path(const char *path, char *buf, size_t bufsz);
ASUTILS_API void as_path_convert_path_to_forward_slashes(char *buf, size_t bufsz);
ASUTILS_API void as_path_remove_redundant_slashes(char *buf, size_t bufsz);
ASUTILS_API bool_t as_path_is_unc_path(const char* buf);
ASUTILS_API bool_t as_path_has_windows_drive_letter(const char* path);
ASUTILS_API bool_t as_path_is_relative(const char* path);

// Think of a better name for this function, win a prize! - rf
ASUTILS_API bool_t as_path_leaves_home_dir(const char* path);

ASUTILS_API as_err_t as_path_enforce_rootedness(char* filename, size_t bufsz);

ASUTILS_API int  as_path_extract_prefix(const char *path, as_path_t* path_t, const char** remainder);
ASUTILS_API bool_t  as_path_can_go_up_a_directory(as_path_t* path_t);
ASUTILS_API int  as_path_unc_parts(const char* path, char* prefix, const char** remainder);
ASUTILS_API void as_path_change_directory(as_path_t* path_t, const char* dir, size_t dirsz);
ASUTILS_API int  as_path_path_to_string(as_path_t* path_t, char* buf, size_t bufsz);
ASUTILS_API void as_path_string_to_path(as_path_t* path_t, const char* buf);
ASUTILS_API void as_path_init(as_path_t* path_t);
ASUTILS_API int  as_path_find_file_in_string_of_paths(const char* file_name, const char* paths, char* buf, size_t bufsz);

ASUTILS_API const char *as_path_product_info_file_name(void);

ASUTILS_API const char *
as_path_next_dirsep(
    const char *path);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ASPATH_H */
