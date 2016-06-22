#ifndef _LIST_H_
#define _LIST_H_

struct list_head
{
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

void list_add     (struct list_head *newnode, struct list_head *head);
void list_add_tail(struct list_head *newnode, struct list_head *head);
void list_del     (struct list_head *entry);
void list_del_init(struct list_head *entry);
int  list_empty   (struct list_head *head );
void list_splice  (struct list_head *list, struct list_head *head);

struct list_head *list_get(struct list_head *head);

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)
	
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
			pos = pos->next)

#define list_for_each_entry(pos, head, member)                            \
	for (pos = list_entry((head)->next, typeof(*pos), member);        \
			&pos->member != (head);                                     \
			pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
			pos = n, n = pos->next)

#define list_for_each_entry_safe(pos, n, head, member)                           \
	for (pos = list_entry((head)->next, typeof(*pos), member),               \
			n = list_entry(pos->member.next, typeof(*pos), member);  \
			&pos->member != (head);                                    \
			pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define list_for_each_entry_safe_reverse(pos, n, head, member)		\
	for (pos = list_entry((head)->prev, typeof(*pos), member),	\
		n = list_entry(pos->member.prev, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.prev, typeof(*n), member))


#endif
