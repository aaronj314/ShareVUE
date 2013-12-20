/*
 * security.h
 *
 * Cryptography routines for FASP
 *
 * Aspera Inc.
 */

#ifndef _SECURITY_H_
#define _SECURITY_H_

#include <frameworks/c/faspcrypto/faspcrypto.h>

// function prototypes

void init_security(void);
void create_security_keys( security_parms_t *sp );
void build_security_key_schedules( security_parms_t *sp );

void* aes_encrypt_cfbc(void  *in,
                       void  *out,
                       void  *init_vec,
                       void  *sum,
                       unsigned int len,
                       AES_KEY  *ks);

void
file_encrypt_block(
    AES_KEY* schedule,
    encryption_block_t *nonce_basis,
    u_int64_t block_number,
    void *block_in,  
    void *block_out,  
    unsigned size);  /* of block, multiple of 16 bytes */

#endif
