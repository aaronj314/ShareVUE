/*
 * asdefs.h
 * 
 * Definitions used internally by the asutil project.
 */

#ifndef _AS_DEFS_H_
#define _AS_DEFS_H_

#ifdef WIN32
#ifndef ASUTILS_API
#define ASUTILS_API  __declspec(dllexport)
#endif
#else
#define ASUTILS_API  extern
#endif

#endif  /* _AS_DEFS_H_ */
