/*
 * mgmt_err_mapper.h
 *
 * Defines the fasp to management protocol warning mapper.
 */

#ifndef MGMT_ERR_MAPPER_H
#define MGMT_ERR_MAPPER_H

#include <utils/src/asutils.h>

#ifdef FASP_CPP
extern "C" {
#endif

extern int mgmt_fasperr2mgmterr(int e);

#ifdef FASP_CPP
} // extern "C"
#endif

#endif
