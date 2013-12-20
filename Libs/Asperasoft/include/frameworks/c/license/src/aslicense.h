#ifndef __AS_LICENSE_H__
#define __AS_LICENSE_H__

#include <utils/src/asplatform.h>

#ifdef WIN32
#ifndef ASLICENSE_API
#ifndef _USRDLL
#define ASLICENSE_API 
#else
#define ASLICENSE_API  __declspec(dllimport)
#endif
#endif
#else
#ifndef ASLICENSE_API
#define ASLICENSE_API
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AS_MAX_LIC_LEN                (4096)
    
extern const char AS_LICENSE_SEPARATOR[16]; 

enum lic_errno {
    LIC_OK = 0,
    LIC_EUNKNOWN,
    LIC_ENOMEM,
    LIC_EBUFFER,
    LIC_EVERIFY,
    LIC_EINVAL,
    LIC_LAST_ERR
};

typedef struct lic_err {
    long err;
    char* errstr;
    size_t errstrsz;
} lic_err_t;


/*
 * Given a license file:
 *   1) read the signed string and the signature
 *   2) verify that the signature is valid
 *   3) return the signed string
 *
 * Expected License Key format: line endings are CRLF, the signed
 * string is first in the file and separated from the signature by
 * a line containing only "==SIGNATURE==\n\r".
 *
 * args
 *   license_path [in]     full path to the file containing the license
 *   buf          [out]    the license terms
 *   bufsz        [in]     the size of the license_string buffer
 *   newbufsz     [out]    the length of the contents of buf
 */ 
ASLICENSE_API void
as_license_read( const char* license_path, 
                 char* buf, size_t bufsz, 
                 size_t* newbufsz, lic_err_t* e );

ASLICENSE_API void
as_license_read_from_str( const char* str, size_t strsz,
                          char* buf, size_t bufsz, size_t* newbufsz, 
                          lic_err_t* e) ;

ASLICENSE_API void
as_license_parse( char* buf, size_t bufsz, 
                  char** terms, size_t* termssz, 
                  char** signature, size_t* signaturesz, lic_err_t* e );

ASLICENSE_API void
as_license_verify(char* terms, size_t termssz, 
                  char* signature_b64, size_t signature_b64sz, lic_err_t* e );


ASLICENSE_API as_err_t
as_license_errstr( int err, char* buf, size_t bufsz );

#ifdef __cplusplus 
}
#endif

#endif
