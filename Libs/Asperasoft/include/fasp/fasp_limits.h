/*
 * Definitions for FASP limits.
 */
#ifndef _FASP_LIMITS_H_

#include <utils/src/asutils.h>

#define FASP_FILENAME_MAXLEN        AS_MAX_PATH

#define FASP_ERRSTR_MAXLEN          128
#define FASP_ERRPATH_MAXLEN         128

#define FASP_RING_NUM_BUFFERS_DFT   12
#define FASP_RING_NUM_BUFFERS_MAX   60
#define FASP_RING_BUFFER_SIZE      2048

/* Unlimited rate is (u_int64_t)-1 */
#define FASP_UNLIMITED_RATE         0xffffffffffffffffULL

/* expiration date = 'nono' is 0 */
#define FASP_NO_EXPIRATION_DATE    0x0

#endif /* _FASP_LIMITS_H_ */

