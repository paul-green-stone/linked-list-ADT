#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* ================================================================ */

#include "data.h"
#include "guard/guard.h"

/* ================================ */

/* A pointer to a print function */
typedef void (*fptr_print)(const Data data);

/* A pointer to a destroy function */
typedef void (*fptr_destroy)(Data data);

/* A pointer to a match function */
typedef int (*fptr_match)(const Data data_1, const Data data_2);

/* ================================ */

/* A pointer to an incomplite type */
typedef struct _node* Node;

/* A pointer to an incomplite type */
typedef struct _linked_list* List_t;

/* ================================ */

/* Allocate a new instance of a List data type */
extern List_t List_create(fptr_destroy destroy_func, fptr_print print_func, fptr_match match_func);

/* Output the content of a linked list */
extern void List_print(const List_t list, fptr_print print_func);

/* Insert a new element with specified data at the beginning of the linked list */
extern int List_insert_first(List_t list, const Data data);

/* Insert a new element with specified data at the end of the linked list */
extern int List_insert_last(List_t list, const Data data);

/* Find a node in the list with specified data (the first occurrence) */
extern Node List_find(const List_t list, const Data data);

/* Remove the first element from the list */
extern int List_remove_first(List_t list);

/* Remove the last element from the list */
extern int List_remove_last(List_t list);

/* Get the list size */
extern size_t List_get_size(const List_t list);

/* Destroy the linked list */
extern void List_destroy(List_t* list);

/* Merge two lists into one */
extern int List_merge(List_t* dest, List_t* src);

/* Remove the specified node from the list */
extern int List_remove_node(List_t list, Node node);

/* Insert an element with the specified data after the node in the list */
extern int List_insert_after(List_t list, const Data data, const Node node);

/* Insert an element with the specified data before the node in the list */
extern int List_insert_before(List_t list, const Data data, const Node node);

/* ================================================================ */

#endif