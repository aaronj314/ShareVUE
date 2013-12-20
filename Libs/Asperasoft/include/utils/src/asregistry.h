#ifndef _AS_REGISTRY_H_
#define _AS_REGISTRY_H_

#include "asplatform.h"

#ifdef WIN32

#define AS_WINREG_FASP "SOFTWARE\\Aspera\\FASP" /* replace back slashes?? */
#define AS_WINREG_DIR  "InstallDir"
#define AS_WINREG_LOG  "LogDir"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief Get data from the registry.
 * To determine the size needed for databuf, call this method with databuf set
 * to NULL or buflen set to 0, and buflen will be set to the required buffer size.
 * @param hkey      Usually HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, or HKEY_USERS
 * @param subkey    Path to the key
 * @param value     Name of the key
 * @param databuf   Buffer to to store the key data in
 * @param bsize     Length of databuf. Will be set to the size/required size of the key's data
 * @return 0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_reg_get(
    HKEY hkey,
    const char *subkey,
    const char *value,
    char *buf,
    size_t *bsize);

/**
 * @brief Set string registery value
 * @param hkey      Usually HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, or HKEY_USERS
 * @param subkey    Path to the key
 * @param value     Name of the key
 * @param data      Buffer with key value to set (with null term)
 * @return 0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_reg_set(
    HKEY hkey,
    const char *subkey,
    const char *value,
    const char *data);

/**
 * @brief Delete registery value
 * @param hkey      Usually HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, or HKEY_USERS
 * @param subkey    Path to the key
 * @param value     Name of the key
 * @return 0 on success, errno on error
 */
ASUTILS_API as_err_t 
as_reg_del(
    HKEY hkey,
    const char *subkey,
    const char *value);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* WIN32 */

#endif /* _AS_REGISTRY_H_ */
