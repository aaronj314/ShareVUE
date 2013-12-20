/* 
 * Special red-black tree module
 */

#include <utils/src/asutils.h>

#define RBT_ERROR_OK                0x00
#define RBT_ERROR_MEM_EXHAUSTED     0x11
#define RBT_ERROR_DUPLICATE_KEY     0x12
#define RBT_ERROR_KEY_NOT_FOUND     0x13
#define RBT_ERROR_INVALID_KEY       0x14

extern int rbt_size;

/* Initialize RBT specifying maximum size */
extern void rbt_init(u_int32_t sz);

/* Inserts a node with the key block_num */
extern int rbt_insert(u_int32_t block_num, 
                      u_int16_t block_idx,
                      u_int16_t tick);

/* Finds the minimum block_num and removes it from the tree */
extern int rbt_getmin(u_int32_t *block_num, 
                      u_int16_t *block_idx,
                      u_int16_t *tick);

extern void rbt_free();
