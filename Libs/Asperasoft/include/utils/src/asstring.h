/*
 * asstring.h
 *
 * Aspera, Inc.
 */

#ifndef _AS_STRING_H_
#define _AS_STRING_H_

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Create duplicate string
 * Caller should free returned string
 * @param   s           String
 * @param   size        String length
 * @return  Duplicate string on success, NULL on error
 */
ASUTILS_API char *
as_str_ndup(
    const char *s, 
    size_t size);

/*
 * @brief   Convert string to int32
 * @param   s           String
 * @return  int32 on success
 */
ASUTILS_API int32_t 
as_str_atoi(
    const char *s);

/*
 * @brief   Convert string to long
 * @param   s           String
 * @return  int32 on success
 */
ASUTILS_API int32_t 
as_str_atol(
    const char *s);

/*
 * @brief   Convert string to int64
 * @param   s           String
 * @return  int64 on success
 */
ASUTILS_API int64_t 
as_str_atoll(
    const char *s);

/*
 * @brief   Convert string to double
 * @param   s           String
 * @return  double on success
 */
ASUTILS_API double  
as_str_atof(
    const char *s);

/*
 * @brief   Convert int32 to string
 * @param   n           int32 value
 * @param   s           Buffer
 * @return  s on success
 */
ASUTILS_API char *
as_str_itoa(
    int32_t n,
    char *s);

/*
 * @brief   Convert u_int32 to string
 * @param   n           u_int32 value
 * @param   s           Buffer
 * @return  s on success
 */
ASUTILS_API char *
as_str_uitoa(
    u_int32_t n, 
    char *s);

/*
 * @brief   Convert int64 to string
 * @param   n           int64 value
 * @param   s           Buffer
 * @return  s on success
 */
ASUTILS_API char *
as_str_lltoa(
    int64_t n, 
    char *s);

/*
 * @brief   Convert u_int64 to string 
 * @param   n           u_int64 value
 * @param   s           Buffer
 * @return  s on success
 */
ASUTILS_API char *
as_str_ulltoa(
    u_int64_t n, 
    char *s);

/*
 * @brief   Convert double to string 
 * @param   f           Double value
 * @param   s           Buffer
 * @return  s on success
 */
ASUTILS_API char *
as_str_ftoa(
    double f, 
    char *s);

/*
 *  @brief  Similar to atoli
 *  But allowing for bases: 32 = %100000 = 0x20 = 0X20 = 040
 *  @param  s           Value as a string
 */
ASUTILS_API int32_t
as_str_ahtoi(
    const char *s);

/*
 *  @brief  Similar to atoll
 *  But allowing for bases: 32 = %100000 = 0x20 = 0X20 = 040
 *  @param  s           Value as a string
 */
ASUTILS_API int64_t
as_str_ahtoll(
    const char *s);

/*
 *  @brief  Similar to atoi
 *  But allowing for bases: 32 = %100000 = 0x20 = 0X20 = 040
 *  @param  s           Value as a string
 *  @result result      Result
 *  @param  e           (if not 0) Set to first unused char in s
 */
ASUTILS_API as_err_t
as_str_ahtoi_err(
    const char *s,
    int32_t *result,
    const char **e);

/*
 *  @brief  Similar to atoi (but unsigned)
 *  But allowing for bases: 32 = %100000 = 0x20 = 0X20 = 040
 *  @param  s           Value as a string
 *  @result result      Result
 *  @param  e           (if not 0) Set to first unused char in s
 */
ASUTILS_API as_err_t
as_str_ahtou_err(
    const char *s,
    u_int32_t *result,
    const char **e);

/*
 *  @brief  Similar to atoll
 *  But allowing for bases: 32 = %100000 = 0x20 = 0X20 = 040
 *  @param  s           Value as a string
 *  @result result      Result
 *  @param  e           (if not 0) Set to first unused char in s
 */
ASUTILS_API as_err_t
as_str_ahtoll_err(
    const char *s,
    int64_t *result,
    const char **e);

/*
 * @brief   Regular expression matching '*', '?' and '\'
 * @param   template    Template to match
 * @param   string      Input string
 * @return  0 or 1
 */
ASUTILS_API int 
as_str_regexp_strcmp(
    const char *tmplate, 
    const char *string);

/*
 * @brief   Does the supplied template contain wildcards?
 * @param   template    Template to check
 * @return  AS_FALSE or AS_TRUE
 */
ASUTILS_API bool_t
as_str_regexp_wildcards_present(
    const char *tmplate);

/*
 * @brief   Is the passed char whitespace?
 * @param   c    char to check
 * @return  AS_FALSE or AS_TRUE
 */
extern const bool_t as_str_whitespace_lut_bool[];
#define as_str_is_whitespace(c) (as_str_whitespace_lut_bool[(unsigned char)(c)])

/*
 * @brief   Tokenize string
 * Create a token array from a given string, Take [ ],["] and ['] as delimiters
 * Returned array should be freed by calling as_free_tokens
 * @param   str         String
 * @param   tokarray    Token array
 * @param   tokcount    Token count
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_str_tokenize(
    const char *str,
    char ***tokarray,
    u_int32_t *tokcount);

/*
 * @brief   Free token array
 * Free token array returned by a previous as_str_tokenize call
 * @param   tokarry     Token array
 * @param   tokcount    Token count 
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_str_tokcleanup(
    char **tokarray,
    u_int32_t tokcount);

/*
 * @brief   Tokenize based on a delimiter
 * Return tokens delimited by a given character
 * To get tokens of a string first call as_str_tok with 
 * str set, subsequent calls with the savedptr and NULL 
 * as str will return successive tokens from the initial string
 * This method modifies the initial string.
 * @param   str         String
 * @param   delimit     Token delimiter
 * @param   savedptr    Pointer for traversing str
 * @return  next token on success, NULL on error
 */
ASUTILS_API char *
as_str_tok(
    char *str,
    const char *delimit,
    char **savedptr);

/*
 * @brief   Replace a given character in string with another
 * @param   s           String 
 * @param   c1          Char to replace
 * @param   c2          Char to replace with
 */
ASUTILS_API void 
as_str_repchr(
    char *str,
    char c1,
    char c2);

/*
 * @brief
 * Copies up to dstsize-*end-1 characters from src to (dst + *end), 
 * stopping at NUL. Adds the number of characters copied (not 
 * including the NUL) into *end, and assigns dst[*end] = '\0'.  
 * dstsize must be greater than *end.  Treats NULL end as pointing at 0.
 * @param   dst         Destination buffer
 * @param   src         NULL terminated src string
 * @param   dstsize     Destination buffer size
 * @param   end         [in/out] Destination string length 
 * @return  0 if source string was copied fully, or EBUFFER or EINVAL
 *
 * Example:
 *   end = 0;
 *   if (as_str_to(dst, path, bufsize, &end) || 
 *           as_str_to(dst, "/", bufsize, &end) || 
 *           as_str_to(dst, filename, bufsize, &end)) {
 *       as_err("path too long");
 *       return -1;
 *   }
 *
 * Where truncation is OK, caller can ignore results:
 *
 *   end = 0;
 *   as_str_to(dst, "failed, ", bufsize, &end);
 *   as_str_to(dst, path, bufsize, &end);
 *   as_str_to(dst, " : ", bufsize, &end);
 *   as_str_to(dst, errmsg, bufsize, &end);
 *
 * In the extremum, it may be used like a safe strncpy:
 *
 *   as_str_to(dst, msg, bufsize, NULL);
 */
ASUTILS_API as_err_t 
as_str_to(
    char *dst,
    const char *src,
    size_t dstsize,
    size_t *end);


/*
 * @brief
 * Performs an as_str_to, but removes leading and trailing whitespace
 * during the copy.  src and dst can be the same to trim in place.
 * @param   dst         Destination buffer
 * @param   src         Src string
 * @param   dstsize     Destination buffer size
 * @param   end         [in/out] Destination string length 
 * @return  0 if source string was copied fully, or EBUFFER or EINVAL
 */
ASUTILS_API as_err_t 
as_trimmed_str_to(
    char *dst,
    const char *src,
    size_t dstsize,
    size_t *end);

/*
 * @brief   strncpy with gurenteed NULL terminator in destination string
 * @param   dst         Buffer
 * @param   src         Src string
 * @param   len         Buffer size
 * @return  0 if source string was copied fully, or EBUFFER or EINVAL
 */
ASUTILS_API as_err_t 
as_str_ncpy(
    char *dst,
    const char *src,
    size_t len);

/*
 * @brief   strncat with gurenteed NULL terminator in destination string
 * @param   dst         Buffer
 * @param   src         Src string
 * @param   len         Buffer size
 * @return  0 if source string was copied fully, or EBUFFER or EINVAL
 */
ASUTILS_API as_err_t 
as_str_ncat(
    char *dst,
    const char *src,
    size_t dstsize);

/*
 * @brief   Encode src string in base64
 * @param   src         Buffer to encode
 * @param   srcsize     Number of bytes to encode
 * @param   dst         Buffer for encoded string
 * @param   dstsize     Size of the destination buffer
 */
ASUTILS_API as_err_t
as_str_buf_to_base64(
    const u_int8_t *src,
    size_t srcsize,
    char *dst,
    size_t dstsize);

/*
 * @brief   Decode base64 encoded string
 * @param   src         Base64 encoded string
 * @param   srcsize     Number of bytes to decode, must be divisible by 4
 * @param   dst         Buffer for decoded string
 * @param   dstsize     Size of the destination buffer
 */
ASUTILS_API as_err_t 
as_str_base64_to_buf(
    const char *src,
    size_t srcsize,
    u_int8_t *dst,
    size_t dstsize,
    size_t *output_bytes);

/* 
 * @brief   Decode base64 encoded string according to MIME rules
 *          Warning: this is incomplete.  Non-base64 characters
 *          are only allowed at specific positions in the source string.
 * @param   src         Base64 encoded string
 * @param   srcsize     Number of bytes to decode, must be divisible by 4
 * @param   dst         Buffer for decoded string
 * @param   dstsize     Size of the destination buffer
*/
ASUTILS_API as_err_t 
as_str_mime_base64_to_buf(
    const char *_src,
    size_t srcsize,
    u_int8_t *dst,
    size_t dstsize,
    size_t *output_bytes);


/*
 * @brief   Encode src string in base64 URL
 * @param   src         Buffer to encode
 * @param   srcsize     Number of bytes to encode
 * @param   dst         Buffer for encoded string
 * @param   dstsize     Size of the destination buffer
 *
 */
ASUTILS_API as_err_t
as_str_buf_to_base64url(
    const u_int8_t *src,
    size_t srcsize,
    char *dst,
    size_t dstsize);

/*
 * @brief   Decode base64 encoded url string
 * @param   src         Base64 encoded url string
 * @param   srcsize     Number of bytes to decode
 * @param   dst         Buffer for decoded string
 * @param   dstsize     Size of the destination buffer
 */
ASUTILS_API as_err_t 
as_str_base64url_to_buf(
    const char *src,
    size_t srcsize,
    u_int8_t *dst,
    size_t dstsize,
    size_t *output_bytes);

    // Copy a source into a dest of known size.  Throw a compile time divide by zero error if sizeof( dest ) <= sizeof(void *).
#define AS_STR_SAFISH_STRCPY( dest, source ) as_str_to( dest, source, ( 1 / (( sizeof(dest) > sizeof(void *) )?1:0) ) * ( sizeof( dest ) ), NULL )
#define AS_STR_SAFISH_STRCAT( dest, source ) as_str_ncat( dest, source, ( 1 / (( sizeof(dest) > sizeof(void *) )?1:0) ) * ( sizeof( dest ) ) )
#define AS_STR_SAFISH_SNPRINTF( dest, ... ) snprintf( dest, ( 1 / (( sizeof(dest) > sizeof(void *) )?1:0) ) * ( sizeof( dest ) ), __VA_ARGS__ )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*_AS_STRING_H_ */
