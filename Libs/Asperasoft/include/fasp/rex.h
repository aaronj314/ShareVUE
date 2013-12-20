/*
 * Retransmission module.
 * 
 */

#ifndef __AS_REX_H__
#define __AS_REX_H__

#include <utils/src/asutils.h>
#include <fasp/rtt.h>

#define REX_FULL            1
#define REX_NO_SUCH         2
#define REX_TIMER_FULL      3
#define REX_TIMER_PASSED    4
#define REX_WRONG_BLOCK     5
#define REX_WRONG_IDX       6

#define REX_NO_DELAY        0x0001

#define REX_TABLE_SZ    1024 * 1024
#define REX_TIMER_REZ   10              /* millisec */
#define REX_TIMER_PER   100000          /* millisec */
#define REX_TIMER_SZ    (REX_TIMER_PER / REX_TIMER_REZ)

typedef struct rex_elem_struct {
    unsigned int                rexbl;
    struct rex_elem_struct      *next;
    struct rex_elem_struct      *prev;
} rex_elem_t;

/*
 * Data structure containing all rex context for a FASP session
 */
typedef struct rex_t {

    rex_elem_t          rex_table[REX_TABLE_SZ];
    rex_elem_t          *rex_free_list;
    unsigned int        rex_table_elems;
    unsigned int        rex_table_free_elems;
    rex_elem_t          rex_timer[REX_TIMER_SZ];
    unsigned int        rex_timer_elems;
    unsigned int        rex_timer_crt_idx;
    unsigned int        rex_timer_crt_ticks;
    unsigned int        rex_timer_crt_ticks_off;
    rtt_info_t          rttinfo;

} rex_t;

/*
 * Gets the number of elements in the retransmission table
 */
extern void rex_elems(rex_t *rex, int * elems);

/*
 * Initializes the retransmission module 
 */
extern int rex_init(rex_t *rex);

/*
 * Adds a block to the retransmission list
 * Flag values:
 *   REX_NO_DELAY - add the block in the list with no delay (normally RTO)
 * Returns: 0 if successful
 *          REX_FULL if no more space to store retransmissions
 */
extern int rex_add(rex_t *rex, unsigned int blockno, unsigned short flag);

/*
 * Removes a block from the retransmission list
 *
 * Returns: 0 if successful
 *          REX_NO_SUCH if the blockno or rexidx are not in the list
 */
extern int rex_remove(rex_t *rex,
                      unsigned int blockno,
                      unsigned int rexidx);

/*
 * Removes a blocks belonging to a block range.  Used in case of abort
 * of a given xfer.
 *
 * Returns: void.
 */
extern int rex_remove_range(rex_t *rex,
                            unsigned int lo_blockno,
                            unsigned int hi_blockno);

/*
 * Recalculates RTO based on the input RTT 
 */
extern int rex_update_rtt(rex_t *rex,
                          unsigned int rtt);

/*
 * Reads the value of the current RTO
 */
extern int rex_get_rtt(rex_t* rex);

/*
 * Called periocally by the main thread to check for timed out retransmissions.
 * It fills in the output buffers with the expired blocks (block number and 
 * index) and it adds back the block to the timer list for retransmission.
 *
 * Returns: number of blocks returned in the list (0 if none)
 *
 */
extern int rex_tick(rex_t *rex,
                    u_int32_t *req_rex_buf,
                    u_int32_t *req_rex_ctrl,
                    unsigned int maxlen,
                    int rex_flag);

#endif
