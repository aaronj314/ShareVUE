/*
 * action.h
 *
 * Routines for pre/post processing and other customized features.
 *
 * Aspera Inc.
 */

#ifndef __AS_ACTION_H__
#define __AS_ACTION_H__

/* Forward declarations */
struct fasp_session_t;
struct transfer_t;

/* Routine implementing all per-session actions */
void as_act_session(int stratstop, struct fasp_session_t *session);

/* Routine implementing all per-transfer actions */
void as_act_transfer(int startstop, struct fasp_session_t *session, struct transfer_t *xfer);

#endif

