/*
 * config_api.h
 *
 * Aspera, Inc.
 */

#ifndef _CONFIG_API_H
#define _CONFIG_API_H

#include <utils/src/asutils.h>
#include <frameworks/c/uac/parse_config_options.h>

#define MAX_CONF_EXCLUDE_PATTERN_COUNT (16)

/* Aspera configuration structure */
typedef struct {

    char        *local_ip_str;
    char        *create_policy_str;
    char        *file_manifest_str;
    char        *file_manifest_path;
    char        *overwrite_policy_str;
    u_int16_t   server_udp_port;
    u_int16_t   log_stats_int;
    u_int16_t   disable_pkt_batching;
    u_int16_t   sessini_opt;
    u_int32_t   filemode;
    u_int32_t   filegrantmask;
    u_int32_t   dirmode;
    u_int32_t   dirgrantmask;
    u_int32_t   read_block_size;
    u_int32_t   write_block_size;
    u_int32_t   max_sock_buf;
    u_int32_t   min_sock_buf;
    const char  *exclude_patterns[MAX_CONF_EXCLUDE_PATTERN_COUNT];
    u_int32_t   exclude_pattern_count;
    char       *resume_suffix;
    size_t      resume_suffix_len;
    char        use_filecache;
    u_int32_t   max_filecache_buf;
    u_int8_t    precalc;                /* pre calculate job size */
    u_int32_t   rtt_instru_type;
    u_int32_t   rate_instru_type; 

    /* disk rate control parameters */
    u_int8_t    ring_buf_rc;
    float       ring_buf_rc_min;
    float       ring_buf_rc_target;
    float       ring_buf_delta; 
    
    /* virtual link config */
    u_int16_t   vl_id;
    u_int16_t   vl_updown;
    u_int64_t   vl_local_Cin;
    u_int64_t   vl_local_Cout;
    char       *vl_if_addr;
    char       *vl_mcast_addr;
    u_int32_t   vl_qmax;
    u_int32_t   vl_qmin;
    u_int16_t   vl_mcast_port;
    float       vl_k_inner;
    float       vl_k_outer;
    float       vl_qb_over_qmax;
    
    /* FASP_AUTH related */
    u_int16_t   ext_auth_required;
    char        *ext_auth_url;
    u_int64_t   target_rate_cap;
    u_int64_t   min_rate_cap;
    int         allowed_cipher;
        
    /* New configuration file with user access control */
    int         _version;
    as_uac_user_option_set *_conf;

} aspera_conf_t;

extern aspera_conf_t    aspera_conf;
extern char             aspera_root_dir[AS_MAX_PATH + 1];
extern char             aspera_etc_dir[AS_MAX_PATH + 1];

int conf_init(char *conffile, char *licfile, char *user);
int conf_fini();

int as_getprepost(char **buf);

/* 
 * Return file or directory access mode based on the original
 * mode (argument) and the configured modes and grant masks.
 * If a mode is configured, it returns it.
 * If not, it returns the original mode ORed with the grant mask.
 */
as_file_mode_t as_get_filemode(int origmode);
as_file_mode_t as_get_dirmode(int origmode);
u_int32_t as_get_usefilecache(void);
#endif
