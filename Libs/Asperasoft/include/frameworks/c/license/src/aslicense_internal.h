#ifndef __AS_LICENSE_INTERNAL_H__
#define __AS_LICENSE_INTERNAL_H__

#include <utils/src/asplatform.h>
#include <utils/src/aserrno.h>
#include <utils/src/asfile.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/sha.h>
#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Open the file, read the file, close the file.
 * Return the file contents in buf.
 */
void
as_license_read_file( const char* license_path, 
                      char* buf, size_t bufsz, 
                      size_t* readsz, lic_err_t* e );

/*
 * Split the license file into two parts: the license 
 * terms and license signature.
 *
 * buf       [in]  the license
 * bufsz     [in]  
 * terms     [out] points to the portion of the license within buf
 *                 that represents the license terms.
 * termssz   [out] the size of the terms
 * signature [out] points to the portion of the license within buf
 *                 that represents the signature.
 * signaturesz [out]
 */
void
as_license_split( char* buf, size_t bufsz, 
                  char** terms, size_t* termssz, 
                  char** signature, size_t* signaturesz, lic_err_t* e );

void
as_license_verify_signature( char* terms, size_t termssz, 
                             char* signature, size_t signaturesz, lic_err_t* e );


void
as_license_sha1( char* terms, size_t termssz, unsigned char* digest, lic_err_t* e );

void
as_license_verify_with_key( unsigned char* digest, size_t digestsz, 
                            unsigned char* signature, size_t signaturesz,
                            RSA* rsa, lic_err_t* e );
void
as_license_create_public_key_rsa( RSA** rsa, lic_err_t* e );

void
as_license_destroy_public_key_rsa( RSA** rsa, lic_err_t* e );

void
as_license_create_public_key_rsa_from_file( RSA** rsa, as_filestream_t* f, lic_err_t* e );

void
as_license_open_public_key_file(const char* path, as_filestream_t **f, lic_err_t* e);

void
as_license_public_key( char* key, size_t keysz );

void 
as_license_public_key_path( const char** path );

void 
as_license_canonicalize_terms( char* terms, size_t termssz, 
                               char* buf, size_t* bufsz, lic_err_t* e );

void 
as_license_read_entire_file( const char* path, char* buf, 
                             size_t bufsz, size_t* readsz, lic_err_t* e );

void
lic_set_err( lic_err_t* e, int lic_err );

void
lic_set_as_err( lic_err_t* e, as_err_t aserr );

void
lic_get_errno( lic_err_t* e );

#ifdef __cplusplus 
}
#endif

#endif
