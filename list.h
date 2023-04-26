#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* ================================================================ */

#include "data.h"
#include "guard/guard.h"

typedef struct _node* Node;             /* A pointer to an incomplite type */

typedef struct _linked_list* List;      /* A pointer to an incomplite type */

/* ================================ */

/*
    * Create a linked list and return a handle to it
*/
extern List List_new(void (*fptr_destroy)(void*), void (*fptr_print)(const Data));

/*
    * Display a linked list
*/
extern void List_print(const List list, void (*fptr_print)(const Data));

/*
    * Insert a new element with specified data at the beginning of the linked list
*/
extern int8_t List_insert_first(List list, const Data data);

/*
    * Insert a new element with specified data at the end of the linked list
*/
extern int8_t List_insert_last(List list, const Data data);

/*
    * Find a node in the list with specified data (the first occurrence)
*/
extern Node List_find(const List list, const Data data, int (*fptr_match)(const Data data_1, const Data data_2));

/*
    * Remove the first element from the list
*/
extern Data List_remove_first(List list);

/*
    * Remove the last element from the list
*/
extern Data List_remove_last(List list);

/*
    * Return the list size
*/
extern size_t List_get_size(const List list);

/*
    * Destroy the linked list
*/
extern void List_destroy(List* list);

/*
    * Merge two lists into one
*/
extern int8_t List_merge(List* dest, List* src);

/*
    * Remove the specified node from the list
*/
extern Data List_remove_node(List list, Node node);

/*
    * Insert an element with the specified data after the node in the list
*/
extern int8_t List_insert_after(List list, const Data data, const Node node);

/*
    * Insert an element with the specified data before the node in the list
*/
extern int8_t List_insert_before(List list, const Data data, const Node node);

/* ================================================================ */

#endif