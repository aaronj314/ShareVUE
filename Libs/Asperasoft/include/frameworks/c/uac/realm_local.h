/*
 * realm_local.h
 */

typedef struct _uac_realm_local
{

    char *_name;

} uac_realm_local;

int
is_member(
    uac_realm_local *realm,
    char *user, 
    char *group);
