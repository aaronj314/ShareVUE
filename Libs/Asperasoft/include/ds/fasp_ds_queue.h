
#ifndef _FASP_DS_QUEUE_H_
#define _FASP_DS_QUEUE_H_


struct _queue_elem {
    struct _queue_elem *next;
    struct _queue_elem *prev;
    void   *data;
    struct _queue *parent;
    int     life;
#define LIST_ELEM_ALLOCATED        1
#define LIST_ELEM_USER_SUPPLIED    2
};

typedef void (*queue_elem_data_destruct_func_t)(void *);

struct _queue {
    volatile unsigned int  elem_count;
    struct _queue_elem    *head;
    struct _queue_elem    *tail;
    queue_elem_data_destruct_func_t data_destruct_func;
};

/*
 * Extern function declarations.
 */
extern struct _queue *
queue_create(
    queue_elem_data_destruct_func_t data_destruct_func
);

extern void
queue_init(
    struct _queue *queue,
    queue_elem_data_destruct_func_t data_destruct_func
);

extern struct _queue *
queue_elem_parent_q(
    struct _queue_elem *elem
);

extern int
queue_add_data(
    struct _queue *queue,
    void *data,
    struct _queue_elem *user_elem
);

extern int
queue_insert_data(
    struct _queue *queue,
    void *data,
    struct _queue_elem *user_elem
);

extern void *
queue_deque_data(
    struct _queue *queue
);

extern void *
queue_rem_elem(
    struct _queue *queue,
    struct _queue_elem *elem
);

extern void *
queue_rem_data(
    struct _queue *queue,
    int (* cmp_func)(void *data, void *arg1, void *arg2),
    void *arg1,
    void *arg2
);

extern void *
queue_search_data(
    struct _queue *queue,
    int (* cmp_func)(void *data, void *arg1, void *arg2),
    void *arg1,
    void *arg2
);

extern int
queue_member(
    struct _queue *queue,
    struct _queue_elem *elem
);

extern unsigned int
queue_len(
    struct _queue *queue
);

extern void *
queue_head_data_ref(
    struct _queue *queue
);

extern void *
queue_tail_data_ref(
    struct _queue *queue
);

extern void *
queue_pos_data_ref(
    struct _queue *queue,
    unsigned int position
);

extern void
queue_foreach_data(
    struct _queue *queue,
    void (* func)(void *data, void *arg1, void *arg2),
    void *arg1,
    void *arg2
);

extern void
queue_destroy(
    struct _queue *queue
);


#endif /* _FASP_DS_QUEUE_H_ */
