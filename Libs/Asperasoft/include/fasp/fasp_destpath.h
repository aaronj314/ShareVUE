#ifndef _FASP_DESTPATH_H_
#define _FASP_DESTPATH_H_

#include <ds/fasp_ds_destpath.h>
#include <fasp/fasp_session.h>


extern int
fasp_path_set_targetdir(
    const fasp_t *fasp,
    struct fasp_session_t *sess
);

extern int
fasp_path_check_targetdir(
    struct fasp_session_t *sess
);

extern void
fasp_path_check_target_preexists(
    const fasp_t *fasp,
    struct fasp_session_t *sess
);

extern void
fasp_path_act_on_target_preexists(
    struct fasp_session_t *sess
);

extern int
fasp_path_skip_topdir(
    void *vsess
);

#endif

