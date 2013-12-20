#ifndef _LATENCY_TAB_H_ 
#define _LATENCY_TAB_H_ 

#include <utils/src/astypes.h>
#include <stdio.h>

typedef struct latency_tab_t {
    int            in_microsecs;
    int            in_millisecs;

#define LATTAB_ENTRIES (1 + 9 + 9 +  9 + 1 + 1)
                       /* < 1ms, 1..9ms, 10..90ms, 100..900ms, 1s, >1s*/
    u_int32_t      freqtab[LATTAB_ENTRIES];
    u_int32_t      mean_val;
    u_int32_t      peak_val;
} latency_tab_t;


extern void
latency_freqtab_add(
    latency_tab_t *lat,
    u_int64_t tdiff_usec
);

extern void
latency_microfreqtab_add(
    latency_tab_t *lat,
    u_int64_t tdiff_usec
);

extern void
latency_freqtab_show_distrib(
    latency_tab_t *lat,
    char *desc_str
);

#endif /* _LATENCY_TAB_H_ */

