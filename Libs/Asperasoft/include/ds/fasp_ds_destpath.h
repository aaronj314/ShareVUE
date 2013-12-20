#ifndef _FASP_DS_DESTPATH_H_
#define _FASP_DS_DESTPATH_H_

enum file_type {
    FT_UNKNOWN = 0,
    FT_FILE,
    FT_DIR,
    FT_OTHER,
};

typedef struct fasp_destpath {
    const char *dest_ref;

    int  must_preexist;
    enum file_type must_ftype;

    int  exists;
    enum file_type exists_ftype;

    int  mk_hierarchy;

    int  create_target_dir;
} fasp_destpath_t;



extern off_t
locate_destname_offset(
    char *srcpath
);

extern void
make_destname(
    char *destname,
    char *srcpath,
    off_t srcpath_offset
);

extern void
make_destpath(
    char *destpath,
    const char *recd_fname,
    fasp_destpath_t *destinfo
);

#endif /* _FASP_DS_DESTPATH_H_ */

