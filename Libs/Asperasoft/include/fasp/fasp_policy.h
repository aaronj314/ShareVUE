/*! \file
 * fasp_policy.h
 *
 * FASP policy related flags.
 *
 * Aspera, Inc.
 */

#ifndef _FASP_POLICY_H_
#define _FASP_POLICY_H_

/* Bandwidth measurement policy */
#define BWMEAS_NONE                     0x00
#define BWMEAS_SEND                     0x01
#define BWMEAS_RECV                     0x02

/* Security/Encryption policy */
#define CIPHER_NONE                     0x00
#define CIPHER_AES128                   0x01
#define CIPHER_AES192                   0x02
#define CIPHER_AES256                   0x03

/* Transfer Rate policy */
#define RATE_POLICY_FIXED               0x00
#define RATE_POLICY_FAIR                0x01
#define RATE_POLICY_TRICKLE             0x02

/* File Transfer Resume policy */
#define RESUME_POLICY_NONE              0x00
#define RESUME_POLICY_ATTRS             0x01
#define RESUME_POLICY_SPARSE_CSUM_OLD   0x02
#define RESUME_POLICY_FULL_CSUM         0x03
#define RESUME_POLICY_SPARSE_CSUM       0x04

/* File Creation policy */
#define CREATE_PRESERVE_TIME            0x01
#define CREATE_BACKUP                   0x02
#define CREATE_SKIP_EXISTING            0x04
#define CREATE_DIR_PATH                 0x08

/* File Manifest policy */
#define FILE_MANIFEST_NONE              0x00
#define FILE_MANIFEST_TEXT              0x01
#define FILE_MANIFEST_XML               0x02

/* Overwrite policy cap */
#define OVERWRITE_ALLOW                 0x00
#define OVERWRITE_DENY                  0x01

/* Overwrite policy */
#define OVERWRITE_NONE                  0x00
#define OVERWRITE_DIFF                  0x01
#define OVERWRITE_OLDER                 0x02
#define OVERWRITE_PROMPT                0x04
/* Last 2 bits reserved for exclusive policy */
#define OVERWRITE_NEVER                 0x3f
#define OVERWRITE_ALWAYS                0xff

#endif /* _FASP_POLICY_H_ */

