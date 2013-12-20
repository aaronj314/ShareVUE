#ifndef _RESRC_UTIL_H_
#define _RESRC_UTIL_H_

#include <utils/src/astypes.h>
#include <utils/src/astime.h>

/*
 * Resource statistics utility routines
 */
extern u_int32_t
resrc_freqtab_mean(
    u_int32_t *freqtab,
    u_int32_t  freqtab_num_ents
);

extern void
resrc_freqtab_show_distrib(
    char *modname,
    u_int32_t *freqtab,
    u_int32_t  freqtab_num_ents
);

extern u_int64_t
resrc_timevaldiff(
    struct timeval *earlier,
    struct timeval *recent
);

#endif /* _RESRC_UTIL_H_ */

