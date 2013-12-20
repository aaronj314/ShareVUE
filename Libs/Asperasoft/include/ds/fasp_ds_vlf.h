#ifndef _FASP_DS_VLF_H_
#define _FASP_DS_VLF_H_

extern int
enc_fasp_ds_vlf_comp(
    unsigned char pdu_type,
    unsigned char *pdu,
    u_int16_t pdulen,
    fasp_ds_vlf_comp_t *vlfcomp,
    fasp_data_attr_t *attrs,
    u_int16_t *len_used
);

extern int
dec_fasp_ds_vlf_comp(
    unsigned char pdu_type,
    unsigned char *pdu,
    u_int16_t pdulen,
    fasp_ds_vlf_comp_t *vlfcomp,
    fasp_data_attr_t *attrs,
    u_int16_t *len_decoded
);

#endif /* _FASP_DS_VLF_H_ */
