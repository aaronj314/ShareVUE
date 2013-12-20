/*
 * Copyright 2001-2004 Unicode, Inc.
 * 
 * Disclaimer
 * 
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 * 
 * Limitations on Rights to Redistribute This Code
 * 
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------

    Conversions between UTF32, UTF-16, and UTF-8.  Header file.

    Several funtions are included here, forming a complete set of
    conversions between the three formats.  UTF-7 is not included
    here, but is handled in a separate source file.

    Each of these routines takes pointers to input buffers and output
    buffers.  The input buffers are const.

    Each routine converts the text between *sourceStart and sourceEnd,
    putting the result into the buffer between *targetStart and
    targetEnd. Note: the end pointers are *after* the last item: e.g. 
    *(sourceEnd - 1) is the last item.

    The return result indicates whether the conversion was successful,
    and if not, whether the problem was in the source or target buffers.
    (Only the first encountered problem is indicated.)

    After the conversion, *sourceStart and *targetStart are both
    updated to point to the end of last text successfully converted in
    the respective buffers.

    Input parameters:
    sourceStart - pointer to a pointer to the source buffer.
        The contents of this are modified on return so that
        it points at the next thing to be converted.
    targetStart - similarly, pointer to pointer to the target buffer.
    sourceEnd, targetEnd - respectively pointers to the ends of the
        two buffers, for overflow checking only.

    These conversion functions take a ConversionFlags argument. When this
    flag is set to strict, both irregular sequences and isolated surrogates
    will cause an error.  When the flag is set to lenient, both irregular
    sequences and isolated surrogates are converted.

    Whether the flag is strict or lenient, all illegal sequences will cause
    an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
    or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
    must check for illegal sequences.

    When the flag is set to lenient, characters over 0x10FFFF are converted
    to the replacement character; otherwise (when the flag is set to strict)
    they constitute an error.

    Output parameters:
    The value "sourceIllegal" is returned from some routines if the input
    sequence is malformed.  When "sourceIllegal" is returned, the source
    value will point to the illegal value that caused the problem. E.g.,
    in UTF-8 when a sequence is malformed, it points to the start of the
    malformed sequence.  

    Author: Mark E. Davis, 1994.
    Rev History: Rick McGowan, fixes & updates May 2001.
         Fixes & updates, Sept 2001.

------------------------------------------------------------------------ */

#ifndef _AS_UTF8_H_
#define _AS_UTF8_H_

#include "asdefs.h"
#include "astypes.h"

#ifdef WIN32

#include "asplatform.h"

#endif

/* This is for C++ and does no harm in C */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Get NULL terminated utf16 string length
 * sizeof(wchar_t) is not gurenteed to be 2 bytes!
 * Don't use wcslen on utf16 string length
 * @param   utf16       UTF16 string
 * @return  0 on success, errno on error
 */
ASUTILS_API size_t 
as_utf16_len(
    const u_int16_t *utf16);

/*
 * @brief   Get NULL terminated utf8 string length
 * If UNICODE is set in VC strlen will actually call
 * wcslen, so use following to get actual utf8 string
 * length
 * @param   utf8        UTF8 string
 * @return  0 on success, errno on error
 */
ASUTILS_API size_t 
as_utf8_len(
    const u_int8_t *utf8); 

/*
 * @brief   Convert NULL terminated UTF8 string to UTF16 string
 * Conversion flags - 0 strict, 1 lenient
 * If utf16 buffer doesn't have sufficient space, AS_ERANGE is 
 * returned and utf16sz is set to minimum number of bytes required 
 * for the conversion.
 * Note that sizeof(u_int16_t) != sizeof(u_int8_t)
 * @param   utf8        UTF8 string
 * @param   flags       Conversion flags
 * @param   utf16       UTF16 buffer
 * @param   utf16       UTF16 buffersz in bytes
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_utf8_to_utf16(
    const char *utf8,
    int flags,
    u_int16_t *utf16,
    size_t *utf16sz);

/*
 * @brief   Convert NULL terminated UTF16 string to UTF8 string
 * Conversion flags - 0 strict, 1 lenient 
 * Unless strict conversion is done, it may not be possible to
 * convert returned utf8 string backto utf16
 * If utf8 buffer doesn't have sufficient space, AS_ERANGE is 
 * returned and utf8sz is set to minimum number of bytes required 
 * for the conversion.
 * @param   utf16       UTF16 string
 * @param   flags       Conversion flags
 * @param   utf8        UTF8 buffer
 * @param   utf8sz      UTF8 buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_utf16_to_utf8(
    const u_int16_t *utf16,
    int flags,
    char *utf8, 
    size_t *utf8sz);

#ifdef WIN32
typedef WCHAR as_wchar_t;
#else
typedef u_int16_t as_wchar_t;
#endif

/*
 * @brief   Convert NULL terminated UTF8 to wchar
 * If wchar buffer doesn't have enough space for the conversion,
 * then AS_ERANGE is returned and wcharsz is set to the minimum number 
 * of bytes required.
 * @param   utf         UTF8 string
 * @param   wchar       wchar converted string
 * @param   wcharsz     wchar buffer size in bytes
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_utf8_to_wchar(
    const char *utf8,
    as_wchar_t *wchar,
    size_t *wcharsz);

/*
 * @brief   Convert NULL terminated wchar string to UTF8
 * If utf8 buffer doesn't have enough space for the conversion,
 * then AS_ERANGE is returned and utf8sz is set to the minimum number 
 * of bytes required.
 * @param   wchar       wchar string
 * @param   utf8        UTF8 converted string
 * @param   utf8sz      utf8 buffer size in bytes
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_wchar_to_utf8(
    const as_wchar_t *wchar,
    char *utf8,
    size_t *utf8sz);

#ifdef __cplusplus
}
#endif

#endif /*_AS_UTF8_H_ */
