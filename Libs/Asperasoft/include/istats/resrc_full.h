#ifndef _RESRC_FULL_STATS_H_
#define _RESRC_FULL_STATS_H_

#include <utils/src/astime.h>
#include <utils/src/astypes.h>
#include <istats/resrc_util.h>
#include <stdio.h>

#define RESRC_FULL_STATS_DEFINE(typename, num_ents) \
    typedef struct typename {                  \
        char           mod_name[32];           \
        u_int32_t      full_count;             \
        u_int32_t      full_state;             \
        struct timeval full_tval;              \
        struct timeval avail_tval;             \
        u_int64_t      full2avail_latency;     \
        u_int32_t      adds;                   \
        u_int32_t      freqtab_num_ents;       \
        u_int32_t      peak_val;               \
        u_int32_t      mean_val;               \
        u_int32_t      freqtab[num_ents + 1];  \
        u_int32_t      full_exceptions;        \
    } typename;


typedef struct resrc_full_t {
    char           mod_name[32];
    u_int32_t      full_count;
    u_int32_t      full_state;
    struct timeval full_tval;
    struct timeval avail_tval;
    u_int64_t      full2avail_latency;
    u_int32_t      adds;
    u_int32_t      freqtab_num_ents;
    u_int32_t      peak_val;
    u_int32_t      mean_val;
    u_int32_t      freqtab[1];
    u_int32_t      full_exceptions;
} resrc_full_t;

#define RESRC_WAS_FULL(resrc)     (1 == (resrc)->full_state)
#define RESRC_WAS_NOT_FULL(resrc) (0 == (resrc)->full_state)
#define RESRC_IS_IT_FULL(resrc)   (RESRC_WAS_FULL(resrc))


/*
 * Resource statistics tracking API
 */
extern void
resrc_full_stats_init(
    resrc_full_t *resrc,
    char *modname,
    u_int32_t freqtab_num_ents
);

extern void
resrc_use(
    resrc_full_t *resrc,
    u_int32_t sample_val
);

extern void
resrc_became_full(
    resrc_full_t *resrc
);

extern void
resrc_became_nonfull(
    resrc_full_t *resrc
);

extern void
resrc_full_show_all_stats(
    resrc_full_t *resrc,
    char *str
);

#endif /* _RESRC_FULL_STATS_H_ */

