/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"


node_t *new_node(char *text, char *key) {
    assert( text != NULL);
    assert( key != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    strncpy(temp->text, text, LIST_MAXLEN_TEXT);
    strncpy(temp->key, key, LIST_MAXLEN_TEXT);
    temp->next = NULL;

    return temp;
}


node_t *new_node_one(char *text) {
    assert( text != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));
    strncpy(temp->text, text, LIST_MAXLEN_TEXT);
    temp->next = NULL;

    return temp;
}


node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


/* applys a function to each node in the list */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}


node_t *add_inorder(node_t *list, node_t *new){
    node_t * cur = NULL;
    node_t * prev = NULL;

    if(list == NULL) return new;

    for(cur = list; cur != NULL; cur = cur->next){
        if(strcmp(new->key, cur->key) >= 0){
                prev = cur;
                continue;
        }
        if(strcmp(new->key, cur->key) < 0){
                break;
        }
    }
    new->next = cur;

    if(prev == NULL){
        return new;
    }
    else{
        prev->next = new;
        return list;
    }
}

