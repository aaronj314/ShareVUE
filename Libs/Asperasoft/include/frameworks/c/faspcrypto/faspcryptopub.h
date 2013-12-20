/*
 * faspcryptopub.h
 *
 */

#ifndef FASPCRYPTOPUB_H
#define FASPCRYPTOPUB_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct faspcrypto_state;
typedef struct faspcrypto_state faspcrypto_state_t;


/* faspcrypto_file_decrypt_error

  Yield description of last error.  Lifetime of pointer is until 
  next call to a faspcrypt_file_decrypt_* function.
*/
extern const char*
faspcrypto_file_decrypt_error(
    faspcrypto_state_t *state);


/* faspcrypto_file_decrypt_init:

   Create a decryption context.  
   Returns NULL on memory allocation failure.
*/
extern faspcrypto_state_t *
faspcrypto_file_decrypt_init();


/* faspcrypto_file_decrypt_open:

   Initialize a decryption.  
   Returns 
     0: success
     1: passphrase doesn't match
     2: trailer is corrupt
     3: file error, see errnoval

   On error, description may be extracted by calling
   faspcrypto_file_decrypt_error(state).
 */
extern int
faspcrypto_file_decrypt_open(
    char const* passphrase,
    char const* file_name,
    faspcrypto_state_t *state,
    int *errnoval);


/* faspcrypto_file_decrypt_block:

   Before calling, initialize state with faspcrypto_file_decrypt_init().
   Works a little faster if outbuf_size is 64K or more.
   Sets *outbuf_produced to number of bytes written to outbuf, 
   which may be less than outbuf_size. Sets *outbuf_produced 
   to zero when all input has been converted. 

   Returns 0 for success, 1 for error.
   On error, description may be extracted by calling
   faspcrypto_file_decrypt_error(state).
*/
extern int
faspcrypto_file_decrypt_some(
    faspcrypto_state_t *state, 
    char   *outbuf, 
    size_t  outbuf_size,
    size_t *outbuf_produced);


/* faspcrypto_file_decrypt_close:

   Close and release resources, NULL out *state.
 */
extern void
faspcrypto_file_decrypt_close(
    faspcrypto_state_t **state); 


/* faspcrypto_reprotect:

  (Interface not yet stable.)
 */
int
faspcrypto_reprotect(
    char const* passphrase,
    char const* passphrase2,
    char const* file_name,
    faspcrypto_state_t *state,
    int *errnoval);

/* faspcrypto_seed_random:

 Call this before faspcrypto_file_encrypt_init with truly-random data, 
 e.g. mouse event timing, or arbitrary data such as file name, process 
 ID, host address, etc.  If called with len==0, uses time of day; 
 e.g. call before and after opening a file or establishing a net 
 connection.  
 */
extern void
faspcrypto_seed_random(const void* bytes, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* FASPCRYPTOPUB_H */
