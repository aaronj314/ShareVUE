#ifndef _META_IMPL_H_
#define _META_IMPL_H_

#include <meta/meta_api.h>

/*
 * Extern declarations for routines.
 */

extern void
meta_md5_to_text(
    u_char *md5,
    char *csum
);

extern int
meta_calc_csum(
    as_filehandle_t fd,
    u_int64_t sz,
    int8_t resume_policy,
    char *csum,                 /* output arg (NO NULL TERMINATION) */
    int *errnoval               /* output arg */
);

extern int
meta_fcalc_csum(
    char *fname,
    u_int64_t sz,
    int8_t resume_policy,
    char *csum,                 /* output arg (NO NULL TERMINATION) */
    int *errnoval               /* output arg */
);

extern void
meta_calc_blocks(
    meta_data_t *md
);

extern int
meta_open_aspx(
    meta_data_t *md
);

extern enum meta_cmp_result
meta_cmp_attrs(
    meta_data_t *md,
    int *errnoval
);

extern enum meta_cmp_result
meta_cmp_attrs_csum(
    meta_data_t *md,
    u_int32_t usefilecache
);

extern int
meta_extract_crypto(
    as_filehandle_t fd,
    const char* file_name,
    u_int64_t file_size,
    u_int8_t *blob_buf,
    u_int16_t *blob_size);

#endif /* _META_IMPL_H_ */

