/*
 * asstring.h
 *
 * Aspera, Inc.
 */

#ifndef _AS_STRING_IMPL_H_
#define _AS_STRING_IMPL_H_

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif


ASUTILS_API as_err_t
as_str_base64_to_buf_impl(
    const char *_src,
    size_t srcsize,
    u_int8_t *dst,
    size_t dstsize,
    size_t *output_bytes,
    int mime);

ASUTILS_API as_err_t 
as_str_base64_chars_to_buf( 
    unsigned char *c, 
    u_int8_t** dst,
    u_int8_t* dstend);

ASUTILS_API void 
as_str_base64_next_chars( char* c, const char** src, const char* end, int mime );

ASUTILS_API void 
as_str_base64_next_char( char* c, const char** src, const char* end, int mime );

ASUTILS_API int 
as_str_base64_valid_char( int c );


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*_AS_STRING_IMPL_H_ */
