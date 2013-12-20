#ifndef _RING_TEST_H_
#define _RING_TEST_H_

#define RING_TEST 0

#define SEQTAB_SIZE 200
#define SEQNAME_SIZE 40

struct order_seq_table {
    char tabname[SEQNAME_SIZE];
    int seqtab[SEQTAB_SIZE];
    int count;
    int next;
};

extern struct order_seq_table alloc_seq;
extern struct order_seq_table full_seq;
extern struct order_seq_table write_seq;

extern void
seqtab_init(
    struct order_seq_table *ost,
    char *name
);

extern void
seqtab_init_all(
    void
);

extern void
seqtab_add_entry(
    struct order_seq_table *ost,
    int buf_index
);

extern void
seqtab_display(
    struct order_seq_table *ost
);

extern void
seqtab_display_all(
    void
);

#endif /* _RING_TEST_H_ */

