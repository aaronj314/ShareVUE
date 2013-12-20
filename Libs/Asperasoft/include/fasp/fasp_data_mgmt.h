#ifndef _FASP_DATA_MGMT_H_
#define _FASP_DATA_MGMT_H_

struct fasp_datasess_t;

extern void
mgmt_update_no_transfer(
    void *vsess,
    struct fasp_datasess_t *ds
);

#endif /* _FASP_DATA_MGMT_H_ */
