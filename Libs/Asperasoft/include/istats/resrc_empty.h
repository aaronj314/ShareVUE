#ifndef _RESRC_EMPTY_STATS_H_
#define _RESRC_EMPTY_STATS_H_

#include <utils/src/astime.h>
#include <utils/src/astypes.h>
#include <istats/resrc_util.h>
#include <stdio.h>

#define RESRC_EMPTY_STATS_DEFINE(typename, num_ents) \
    typedef struct typename {                  \
        char           mod_name[32];           \
        u_int32_t      empty_count;            \
        u_int32_t      empty_state;            \
        struct timeval empty_tval;             \
        struct timeval avail_tval;             \
        u_int64_t      empty2avail_latency;    \
        u_int32_t      adds;                   \
        u_int32_t      freqtab_num_ents;       \
        u_int32_t      peak_val;               \
        u_int32_t      mean_val;               \
        u_int32_t      freqtab[num_ents + 1];  \
        u_int32_t      empty_exceptions;       \
    } typename;


/*
 * TODO: Enhancement
 * Could add freqtab_ptr and make it point to either local or calloced mem.
 * Init routine could point the freqtab_ptr to the local memory, whereas
 * Create routine could porint the freqtab ptr to the calloced memory.
 * The rest of the routine could use the pointer (or switch based on a flag).
 */

typedef struct resrc_empty_t {
    char           mod_name[32];
    u_int32_t      empty_count;
    u_int32_t      empty_state;
    struct timeval empty_tval;
    struct timeval avail_tval;
    u_int64_t      empty2avail_latency;
    u_int32_t      adds;
    u_int32_t      freqtab_num_ents;
    u_int32_t      peak_val;
    u_int32_t      mean_val;
    u_int32_t      freqtab[1];
    u_int32_t      empty_exceptions;
} resrc_empty_t;

#define RESRC_WAS_EMPTY(resrc)     (1 == (resrc)->empty_state)
#define RESRC_WAS_NOT_EMPTY(resrc) (0 == (resrc)->empty_state)
#define RESRC_IS_IT_EMPTY(resrc)   (RESRC_WAS_EMPTY(resrc))


/*
 * Resource statistics tracking API
 */
extern void
resrc_empty_stats_init(
    resrc_empty_t *resrc,
    char *modname,
    u_int32_t freqtab_num_ents
);

extern void
resrc_created(
    resrc_empty_t *resrc,
    u_int32_t sample_val
);

extern void
resrc_became_empty(
    resrc_empty_t *resrc
);

extern void
resrc_became_nonempty(
    resrc_empty_t *resrc
);

extern void
resrc_empty_show_all_stats(
    resrc_empty_t *resrc,
    char *str
);

#endif /* _RESRC_EMPTY_STATS_H_ */

