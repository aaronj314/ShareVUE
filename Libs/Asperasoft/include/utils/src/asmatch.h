#ifndef ASMATCH_H
#define ASMATCH_H

#include "asplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

ASUTILS_API int as_match(const char * string, const char * pattern );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ASMATCH_H

