// fasp_license.h
#ifndef __FASP_LICENSE__
#define __FASP_LICENSE__

#include <frameworks/c/license/src/aslicense.h>

#define AS_MAX_LIC_SIZE             4096
#define AS_MAX_LIC_ERRSTR_SIZE      1024

#define FASP_LIC_VERSION            1

#define FASP_UNLIMITED_ACCOUNTS     ((unsigned int)-1)

#define FASP_LIC_BWLIMIT_KBPS_SCALER    1ULL
#define FASP_LIC_BWLIMIT_MBPS_SCALER 1000ULL

/*
 * Expected usage {
 *   const char* terms;
 *   size_t termssz;
 *   // call as_license functions to populate terms and termssz
 *
 *   fasp_lic_t license_info;
 *   fasp_lic_init( &license_info, terms, termssz );
 *     // check for error
 *
 *   int id;
 *   fasp_lic_product_id( &license_info, &id );
 *
 *     // check for error
 *   fasp_lic_free( &license_info );
 * }
 */

/*
 * fasp_lic_t is initialized in fasp_lic_init and destroyed
 *     in fasp_lic_free.  It is the structure that holds the
 *     license terms and xml parsing information so that the
 *     accessor functions (fasp_lic_[accessor]) can quickly
 *     return the desired information.
 *
 *     There is debate over void* use, so this might change to
 *     fasp_lic_struct_t* or xmlDocPtr, but it will always
 *     be a pointer.
 */
struct _fasp_license_impl;
typedef struct _fasp_license_impl* fasp_license_t;

typedef struct fasp_old_licinfo_t {
    u_int16_t exp_day;
    u_int32_t license_id;
    u_int32_t product_id;
    u_int32_t customer_id;
    u_int64_t bw_limit;   /* Kbps */
} fasp_old_licinfo_t;

/*
 * initialize and free the fasp_lic_t
 * fasp_lic_init may return NULL if there is not enough memory
 * to create the error struct.  Otherwise, the error code is
 * in e->err, and an error string is in e->errstr.
 * {
 *   lic_err_t* e;
 *   e = fasp_lic_init(...);
 *   if( e && e->err != LIC_OK )
 * }
 */
lic_err_t* fasp_lic_init( fasp_license_t* l, char* locallicense, size_t llsz );
void fasp_lic_free( fasp_license_t* l );

/*
 * fasp_lic_t accessor functions.
 *     These functions fetch data from the license such as
 *     the product id, maximum bandwidth, etc.
 */
typedef enum fasp_lic_attr_err {
    FASP_LIC_OK,
    FASP_LIC_ATTR_INVALID
} fasp_lic_attr_err_t;

void fasp_lic_version( fasp_license_t l, int* r );
void fasp_lic_product_id( fasp_license_t l, int* r );

fasp_lic_attr_err_t fasp_lic_customer_id( fasp_license_t l, int* r );
fasp_lic_attr_err_t fasp_lic_license_id( fasp_license_t l, int* r );
fasp_lic_attr_err_t fasp_lic_accounts( fasp_license_t l, unsigned int* r );
fasp_lic_attr_err_t fasp_lic_unique_concurrent_logins( fasp_license_t l, int* r );
/*
 * fasp_lic_maximum_bandwidth: in Mbps
 */
fasp_lic_attr_err_t fasp_lic_maximum_bandwidth( fasp_license_t l, u_int64_t* r, u_int64_t scaler);
fasp_lic_attr_err_t fasp_lic_maximum_bandwidth_str( fasp_license_t l, char* r, size_t r_sz );

/*
 * fasp_lic_expiration_date: the number of days since 2004/1/1
 */
fasp_lic_attr_err_t fasp_lic_expiration_date( fasp_license_t l, u_int16_t* r );
fasp_lic_attr_err_t fasp_lic_connect_enabled( fasp_license_t l, int* r );

/*
 * fasp_lic_wire_terms:
 * Return the license terms that should be sent over the wire to the peer
 * (null terminated)
 */
int fasp_lic_wire_terms( fasp_license_t l, char* terms, size_t termssz );

int fasp_lic_terms( fasp_license_t l, char* terms, size_t termssz );

/*
 * fasp_lic_check_peer_attributes:
 * Checks that this license allows transfers with a peer given the peer license.
 */
typedef enum fasp_lic_peer_attr_err {
    FASP_LIC_CHECK_OK,
    // v1 license has bad product id or other bad information
    FASP_LIC_CHECK_INVALID,
    FASP_LIC_CHECK_DUPLICATE,
    FASP_LIC_CHECK_REQUIREMENTS_MALFORMED,
    FASP_LIC_CHECK_REQUIREMENT_UNKNOWN,
    // Example: requires connect_enabled=yes, 
    // no connect_enabled in peer license 
    FASP_LIC_CHECK_MISSING_REQUIREMENT, 
    // Local is connect, but peer is not connect_enabled
    FASP_LIC_CHECK_IS_NOT_CONNECT_SERVER,
    // Local requires Peer to have some customer_id, but Peer's
    // customer_id doesn't match
    FASP_LIC_CHECK_RESTRICTED_CUSTOMER_ID,
    // Unknown err must be last in this list
    FASP_LIC_CHECK_UNKNOWN_ERR
} fasp_lic_peer_attr_err_t;

fasp_lic_peer_attr_err_t 
fasp_lic_check_peer_attributes_match_local_requirements(
    fasp_license_t l, fasp_license_t p);

fasp_lic_peer_attr_err_t 
fasp_lic_check_local_attributes_match_peer_requirements(
    fasp_license_t l, fasp_license_t p);

/* 
 * fasp_lic_check_*_attributes_errstr
 * returns the error string for fasp_lic_check_*_attributes_match_*_requirements
 */
const char* fasp_lic_check_peer_attributes_errstr( fasp_lic_peer_attr_err_t e );
const char* fasp_lic_check_local_attributes_errstr( fasp_lic_peer_attr_err_t e );


typedef enum fasp_lic_gen_err {
    FASP_LIC_GEN_OK,
    FASP_LIC_GEN_NOMEM,
    FASP_LIC_GEN_DEPRECATED,
    FASP_LIC_GEN_UNKNOWN_LICENSE,
    FASP_LIC_GEN_OTHER_ERROR /* probably an error from snprintf */
} fasp_lic_gen_err_t;

fasp_lic_gen_err_t 
fasp_lic_generate_peer_license_str(struct fasp_old_licinfo_t* peer, char* peer_license_str, size_t* peer_license_strsz);

void fasp_license_prepost_str( fasp_license_t l, char* buf, size_t bufsz);
char* fasp_license_dbg_str( fasp_license_t l, fasp_license_t p, char* buf, size_t bufsz );

const char* fasp_lic_generate_peer_license_errstr( fasp_lic_gen_err_t e );

time_t fasp_lic_get_epoch_exp_time(u_int16_t exp_date);

as_err_t fasp_lic_get_exp_time_string(u_int16_t exp_date,
                                      char *expbuf,
                                      size_t expbufsz);

u_int64_t fasp_lic_get_bps_bw_limit(fasp_license_t l);

#endif
