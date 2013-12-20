/*
 * faspcrypto.h
 *
 */

#ifndef FASPCRYPTO_H
#define FASPCRYPTO_H

#include <stddef.h>

#include <openssl/e_os2.h>
#include <openssl/aes.h>

#include <openssl/rand.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>

#include "faspcryptopub.h"

#ifdef __cplusplus
extern "C" {
#endif

/* extracted from fasp/security.h */
typedef union encryption_block {
    u_int8_t bytes[16];
    u_int64_t words[2];
} encryption_block_t;

#define ENC_KEY_64           8
#define ENC_KEY_128          16
#define ENC_KEY_192          24
#define ENC_KEY_256          32

#define ENC_MAX_KEY_SIZE     ENC_KEY_256

#define ENC_BLOCK_SIZE       AES_BLOCK_SIZE

// constants defining security algorithms

#define SECURITY_ENC_AES128  0xa128      // AES128
#define SECURITY_ENC_AES192  0xa192      // AES192
#define SECURITY_ENC_AES256  0xa256      // AES256

// md5 parameters exchanged over a secure SSL connection
//
// note: md5 is more than strong enough for everything we need of it.
//     For a broken md5 to be useful, it would have to be broken during
//     a session, *and* to hash a forged sequence of the same length as
//     a valid block.  Known exploits depend on appending uninterpreted
//     garbage to the end of a block.

typedef struct _md5_parms {
    unsigned char  key[8];
} md5_parms_t;

// AES parameters

typedef struct _aes_parms {

  unsigned char    key[ ENC_MAX_KEY_SIZE ]; 
  unsigned char    hdr_key[ ENC_MAX_KEY_SIZE ]; 
  unsigned char    file_key[16];  /* for "at-rest" encryption */

  // 'AES_KEY' is the format in which keys are supplied
  // to the AES encryption algorithm through its OpenSSL api.
 
  AES_KEY          schedule; 
  AES_KEY          hdr_schedule; 
  AES_KEY          file_schedule;  /* for "at-rest" encryption */

} aes_parms_t;

typedef struct _security_parms {
  ENGINE          *openssl_engine;  // hardware crypto acclerator

  /* cipher applied to data blocks & (separately) their headers */
  int              enc_alg; // encryption algorithm 
  int              enc_key_size; // size of encryption/decryption keys 
  int              enc_block_size; 

  /* HMACs are appended to control messages */
  u_int32_t        mac_algorithm;  /* 0: none; 1: md5 */
  u_int32_t        mac_key_size;
  u_int32_t        mac_result_size;

  /* message sequence numbers used for both crypto nonce and msg auth */
  u_int32_t        seq_num_send;
  u_int32_t        previous_block_index;
  u_int32_t        seq_num_recv;

  encryption_block_t  file_key_hash;  
  encryption_block_t  file_key_locked;  
  encryption_block_t  file_key_salt;  

  union { 
      md5_parms_t  md5;
  } mac;

  // Crypto algorithm parameters
  union {
      aes_parms_t  aes;   // 128, 192 and 256 aes
  } crypto;

} security_parms_t;


/* extracted from meta/meta_api.h */
#define CSUM_SZ                 32  /* Checksum length, no null termination */

typedef struct fasp_meta_crypto_t {
    u_int64_t   true_size;        /* size of plaintext, before padding */
    u_int8_t    nonce_basis[16];  /* hash of file path */
    u_int8_t    sess_key_locked[16];  /* encrypted copy of session key */
    u_int8_t    sess_key_hash[16];    /* checksum of session key */
    u_int8_t    salt[16];         /* original uuid used as salt to hash key */
    u_int8_t    file_hash[CSUM_SZ];  /* checksum of plaintext file, if done */
    u_int16_t   file_hash_type;   /* 0:md5sum */
    u_int16_t   file_hash_level;  /* 0:none, 2:complete, 3:sparse */ 
    u_int16_t   key_mode;         /* how sess_key locked, 0:no key, 1:pw */
    u_int16_t   version;          /* 1 */
} fasp_meta_crypto_t;

typedef struct fasp_meta_crypto_alt_t {
    u_int8_t    sess_key_locked[16];  /* encrypted copy of session key */
    u_int16_t   version;          /* 1 */
} fasp_meta_crypto_alt_t;


enum {
    file_crypto_blobsize = 8+16+16+16+16+CSUM_SZ+2+2+2+2,
    file_crypto_blobsize_alt = 16+2,
    file_crypto_lgchunksize = 7,  /* 128 bytes */ 
    file_crypto_chunksize = (1 << file_crypto_lgchunksize),

    file_crypto_max_blob_size = 8192
};

/* the following are used internally */

void aes_decrypt_cfbc(
    void  *in,
    void  *out,
    void  *init_vec,
    void  *sum,
    unsigned int len,
    AES_KEY  *ks);

void
file_decrypt_block(
    AES_KEY* schedule,
    encryption_block_t *nonce_basis,
    u_int64_t file_offset,
    void *block_in,
    void *block_out,
    unsigned size);

void
file_encryption_init(
    char const* passphrase,
    u_int8_t const* raw_uuid,
    security_parms_t *sp);

int
file_extract_key(
    char const* passphrase,
    u_int8_t* salt,
    u_int8_t* sess_key_locked,
    u_int8_t* sess_key_hashed,
    u_int8_t* key);



#ifdef __cplusplus
}
#endif

#endif /* FASPCRYPTO_H */
