/*
 * aspmtu.h
 *
 * pMTU discovery utilities
 *
 * Aspera Inc.
 */

#ifndef AS_PMTU_H
#define AS_PMTU_H

#define MTU_TABLE_SIZE   4
#define MTU_BATCH_SIZE   3

#define MAX_BRTT 10000000
#define TICK_EXPR_DURA   1000000   // in microseconds

extern unsigned MTU_TABLE[MTU_TABLE_SIZE];

extern int find_idx_by_MTU (unsigned mtusize);

/* Procedures for starting pmtu prober */
int start_pmtu_brtt_probing (fasp_session_t *xsess);

/* Procedures for starting pmtu receiver */
int start_pmtu_brtt_recv(fasp_session_t *xsess);

#endif
