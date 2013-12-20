
#ifndef _TEST_STUBS_H_
#define _TEST_STUBS_H_

typedef struct _transfer_t {
    /*
     * Stub definition of transfer structure.
     */
    int         xfer_id;
} transfer_t;

typedef struct _fasp_session_t {
    /*
     * Stub definiation of fasp session.
     */
    int         sess_id;
    transfer_t *xfer;
    char       *docroot;

} fasp_session_t;

#endif /* _TEST_STUBS_H_ */



