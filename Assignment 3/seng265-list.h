#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define LIST_MAXLEN_TEXT 5100

typedef struct node_t {
    char text[LIST_MAXLEN_TEXT];
    char key[LIST_MAXLEN_TEXT];
    struct node_t  *next;
} node_t;

node_t *new_node(char *, char *);
node_t *new_node_one(char *text);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void    apply(node_t *, void(*fn)(node_t *, void *), void *arg);
node_t *add_inorder(node_t *list, node_t *new);

#endif