/*
 * asaio.h
 *
 * Aspera, Inc.
 *
 */

#ifndef _AS_AIO_H_
#define _AS_AIO_H_

#include "asplatform.h"
#include "asfile.h"

#ifdef APPLE
#if defined PPC || defined APPLEARM
#define HAVE_AIO_H 0
#else
#include <aio.h>
#define HAVE_AIO_H 1
#endif
#elif defined WIN32 || defined ISILON
#define HAVE_AIO_H 0
#else
#include <aio.h>
#define HAVE_AIO_H 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if HAVE_AIO_H
typedef struct aiocb as_aiocb_t;
#else
typedef struct {
    int io_opcode;          /* operation */
    volatile void *io_buf;  /* buffer */
    size_t io_nbytes;       /* number of bytes to write */
    int64_t io_offset;      /* file offset */
} as_aiocb_t;
#endif  /* HAVE_AIO_H */

typedef struct {
    as_file_t fildes;       /* file descriptor */
    as_aiocb_t aiocb;
    size_t size;            /* Actual read size  */
    int err;                /* Error code */
} as_aio_t;

/*
 * @brief   Create AIO handle
 * @param   aiocbp      AIO handle
 * @param   filedes     File handle for AIO
 * @param   off         File offset
 * @param   buf         Buffer for reading/writing
 * @param   nbytes      Buffer size
 * @return  0 on success, errno on error
 */
ASUTILS_API void
as_aio_init(
    as_aio_t *aiocbp,       /* AIO handle */
    as_file_t filedes,      /* File handle */
    int64_t off,            /* File offset */
    void  *buf,             /* Read/write buffer */
    size_t nbytes           /* Number of bytes requested */
);

/*
 * @brief   AIO read
 * @param   aiocbp      Initialized AIO handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_aio_read(
    as_aio_t *aiocbp
);

/*
 * @brief   AIO error
 * @param   aiocbp      AIO handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_aio_error(
    as_aio_t *aiocbp
);

/*
 * @brief   AIO return value
 * @param   aiocbp      AIO handle
 * @param   retsz       Returned size on successful aio operation
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_aio_return(
    as_aio_t *aiocbp,
    size_t *retsz
);

/*
 * @brief   AIO cancel
 * @param   filedes     File handle
 * @param   aiocbp      AIO handle
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t
as_aio_cancel(
    as_aio_t *aiocbp
);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* _AS_AIO_H_ */

