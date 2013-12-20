/* mgmt_portfiles.h */

#ifndef FASP_DS_MGMT_PORTFILES_H
#define FASP_DS_MGMT_PORTFILES_H

#include <utils/src/asutils.h>
#include <ds/mgmtsocks.h>

typedef struct _mgmt_single_host_t {
    char* host;
    unsigned short port;
    int optional;
} mgmt_host_set_t[MGMT_SOCKS_MAX];


/* create_mgmt_context(): Create a mgmt_context from a list
   of addresses/ports.
 */
mgmt_context_t *
create_mgmt_context(mgmt_host_set_t *p_mgmt);

/* read_port_files
 * Reads files named *.port and *.optport in port_file_dir
 * returns the number of mgmt ports on success.
 *         0 on success.
 *         -1 on error opening the directory
 *         -2 on error with required port files
 */
int
read_port_files(
    const char* port_file_dir,
    struct _mgmt_single_host_t* mgmt,
    int* num_mgmt );


#endif
