#ifndef _AS_LIBRARY_H_
#define _AS_LIBRARY_H_

#include "asplatform.h"
#ifdef APPLE
/* on MacPPC, compiler warns we should use dylib, not dlopen */
#define DLOPEN_NO_WARN 1 
#include <dlfcn.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
#ifdef WIN32
    HMODULE handle;
#else 
    void* handle;
#endif
} as_library_t;


/*
 * @brief   Load dynamic library
 * @param   lib         Lib handle
 * @param   name        Library name
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_library_open(
    as_library_t *lib,
    const char *name);

/*
 * @brief   Remove dynamic library
 * @param   lib         Lib handle  
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_library_close(
    as_library_t *lib);

/*
 * @brief   Load dynamic library symbol
 * @param   lib         Lib handle
 * @param   sym         Symbol name
 * @param   addr        Symbol address
 * @return  0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_library_symbol(
    as_library_t *lib,
    const char *sym,
    void **addr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _AS_LIBRARY_H_ */
