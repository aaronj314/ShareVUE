/*
 *  fasp_session_ops.h 
 *
 *    FASP session related operations
 *    Triggered by other modules, e.g., mgmt interface or scheduler
 *
 *  Aspera Inc.
 */

#ifndef __AS_FASP_SESSION_OP_H__
#define __AS_FASP_SESSION_OP_H__

/* Rate parameters bit flags */
#define FASP_RATE_PARAMS_NONE           0x00
#define FASP_RATE_PARAMS_POLICY         0x01
#define FASP_RATE_PARAMS_TARGET         0x02
#define FASP_RATE_PARAMS_MINIMUM        0x04

/* Vlink reconf parameters bit flags */
#define FASP_VLINK_RECONF_PARAMS_ON     0x01
#define FASP_VLINK_RECONF_PARAMS_CL     0x02     
        
struct fasp_session_t;
struct fasp_vlink_reconf_t;

void fasp_session_read_vlink_conf(fasp_session_t *s);

int fasp_session_vlink_init(fasp_session_t *s);

void fasp_session_schedule_bwevents(fasp_session_t *s);

/*! \brief
 * Change rate parameters of an ongoing FASP session. The which_params
 * flag is a bitmask representing the parameters to be changed:
 *
 * FASP_RATE_PARAMS_POLICY
 * FASP_RATE_PARAMS_TARGET
 * FASP_RATE_PARAMS_MINIMUM
 * FASP_RATE_PARAMS_BWCAP
 * FASP_RATE_PARAMS_ALL
 *
 * Return: 0 if successful, -1 otherwise
 */
int fasp_session_set_rate_params(
    fasp_session_t *sess,
    fasp_rate_params_t *rate_params, 
    unsigned int which_params);

/*
 * Function to change rate policy on the fly
 */
void fasp_session_change_rate_policy(
     fasp_session_t *sess, 
     u_int8_t old_policy, 
     u_int8_t new_policy);

/*
 * Trigger rate parameters negotiation defined 
 * inside fasp_ratparams_neg.c
 */
void fasp_session_rateparams_neg(
     fasp_session_t *sess, 
     fasp_rate_params_t *rp);

/* Session (flow) level admission control */
int fasp_session_cac_flow(fasp_session_t *sess);

/*
 * Reconfigure virtual link via mgmt/scheduler
 */

void fasp_session_vlink_reconf_local(
        fasp_session_t *sess, 
        struct fasp_vlink_reconf_t *vlink_conf,
        u_int32_t which_params);

/* 
 * Activate vlink communication channel 
 */
int fasp_session_start_local_vlink(fasp_session_t *sess);

/* 
 * Shutdown vlink communication channel and reset parameters 
 */
int fasp_session_shutdown_local_vlink(fasp_session_t *sess);

void fasp_session_convert_to_policy(
        u_int8_t policy, u_int32_t priority, 
        int *eff_policy);

void fasp_session_convert_policy(
        int eff_policy,
        u_int8_t *policy, u_int32_t *priority);

#endif
