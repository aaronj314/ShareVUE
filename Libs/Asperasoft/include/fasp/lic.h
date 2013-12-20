/*
 * lic.h
 *
 * License handling routines
 */

#ifndef LIC_H
#define LIC_H

/* Error codes */
#define LIC_FILE_OPEN           0x01
#define LIC_FILE_READ           0x02
#define LIC_WRONG_MD5           0x03
#define LIC_WRONG_MAGIC         0x04

typedef struct licinfo_t {

    u_int16_t  exp_day;     /* day since 2004-01-01 */
    // TODO: uplift bw_limit to 32-bit unsigned
    u_int16_t  bw_limit;    /* Mbps */
    u_int32_t  sys_id;      /* 16 bits on wire, at present */
    u_int32_t  lic_id;      /* 16 bits on wire, at present */
    u_int32_t  product_id;  /* 16 bits on wire, at present */
    int        errcode;

} licinfo_t;

/*
 * Creates a license key string (42 ASCII characters) based on the
 * information in licinfo_t.
 */
int create_lic_key(licinfo_t *lic, char *lickey);

/*
 * Reads a license key string (28 or 42 ASCII characters) into a licinfo_t 
 * structure.
 */
int read_lic_info(licinfo_t *lic, char *lickey);

/*
 * Read the license key from the license file into a licinfo_t structure.
 */
int read_lic_file(char *licfile, licinfo_t *li);

const char *get_product_name(licinfo_t *li);

time_t get_epoch_exp_time(u_int16_t exp_date);

as_err_t
lic_get_exp_time_string(
    u_int16_t exp_date,
    char *expbuf,
    size_t expbufsz);

u_int64_t get_bps_bw_limit(licinfo_t *li);

#endif
