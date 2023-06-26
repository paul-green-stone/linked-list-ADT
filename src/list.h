#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "data/data.h"
#include "../guard/guard.h"

#define List_size(list) ((list != NULL) ? list->size : -1)

/* ================================================================ */
/* ======================= TYPES DEFINITIONS ====================== */
/* ================================================================ */

/**
 * A structure that represents an individual node of a linked list
*/
typedef struct _node* Node_t;

/* ================================ */

/**
 * A data type that represents a set of logical arrangement of nodes
*/
typedef struct _linked_list* List_t;

/* ================================ */

/* ================================================================ */
/* ====================== TYPES IMPLEMENTAION ===================== */
/* ================================================================ */

struct _node {
    /* Pointer to a data container */
    Data data;

    /* The next node in the sequence */
    struct _node* next;
};

struct _linked_list {
    /* Number of elements in the list */
    size_t size;

    /* First element of the list */
    struct _node* head;

    /* Last element of the list */
    struct _node* tail;

    /* ================================================================ */
    /* ==== Members not used by linked lists but by datatypes that ==== */
    /* =========== will derive them later from linked lists =========== */
    /* ================================================================ */

    /* The encapsulated destroy function passed to List_create */
    destroy_fptr destroy;

    /* The encapsulated print function passed to List_create */
    print_fptr print;

    /* The encapsulated match function passed to List_create */
    match_fptr match;
};

/* ================================================================ */
/* ========================== List_t API ========================== */
/* ================================================================ */

/**
 * Create a new node.
 * 
 * @param data data to be inserted into a new node
 * @param caller_name name of the function that calls a Node_create function
 * 
 * @return A new instance of a node on success, NULL on failure.
*/
extern Node_t Node_create(const Data data);

/**
 * Allocate a new instance of a linked list data type.
 * 
 * @param destroy pointer to a function that handles the deletion of a linked list node
 * @param print pointer to a function that prints data residing in a linked list node
 * @param match a pointer to a function that compares data in a linked list node
 * 
 * @return a new instance of a linked list on success, NULL on failure.
*/
extern List_t List_create(destroy_fptr destroy, print_fptr print, match_fptr match);

/* ================================================================ */

/**
 * Output the content of a linked list.
 * 
 * @param list list to be printed out
 * @param print alternative print function used to handle data in a linked list node
 * 
 * @return none.
*/
extern void List_print(const List_t list, print_fptr print);

/* ================================================================ */

/**
 * Insert a new element with specified data at the beginning of the linked list
 * 
 * @param list list to insert into
 * @param data data to be inserted
 * 
 * @return 0 on success, negative value on error.
*/
extern int List_insert_first(List_t list, const Data data);

/* ================================================================ */

/**
 * Insert a new element with specified data at the end of the linked list
 * 
 * @param list list to insert into
 * @param data data to be inserted
 * 
 * @return 0 on success, negative value on error.
*/
extern int List_insert_last(List_t list, const Data data);

/* ================================================================ */

/**
 * Find a node in the list with specified data (the first occurrence).
 * 
 * @param list list to search in
 * @param data data to be searched
 * @param match alternative match function used to compare data in a linked list node
 * 
 * @return node with the specified data on success, NULL on failure.
*/
extern Node_t List_find(const List_t list, const Data data, match_fptr match);

/* ================================================================ */

/**
 * Remove the first element from the list
 * 
 * @param list list to remove from
 * 
 * @return 0 on success, negative value on failure.
*/
extern int List_remove_first(List_t list);

/* ================================================================ */

/**
 * Remove the last element from the list
 * 
 * @param list list to remove from
 * 
 * @return 0 on success, negative value on failure.
*/
extern int List_remove_last(List_t list);

/* ================================================================ */

/**
 * Destroy the linked list.
 * 
 * @param list list to be destroyed
 * 
 * @return 0 on success, negative value on failure.
*/
extern int List_destroy(List_t* list);

/* ================================================================ */

/**
 * Merge two lists into one.
 * 
 * @param dest the destination list
 * @param src the source list, the one to be merged into dest list
 * 
 * @return 0 on success, negative value on failure.
*/
extern int List_merge(const List_t* dest, List_t* src);

/* ================================================================ */

/**
 * Remove the specified node from the list
 * 
 * @param list list to remove from
 * @param node node to be removed
 * 
 * @return 0 on success, negative value on failure.
 */
extern int List_remove_node(const List_t list, Node_t node);

/* ================================================================ */

/**
 * Insert a new node with specified data after the node.
 * 
 * @param list list to insert into
 * @param data data to be inserted
 * @param node node that precedes the new node
 * 
 * @return 0 on success, negative value on failure.
*/
extern int List_insert_after(List_t list, const Data data, const Node_t node);

/* ================================================================ */

/**
 * Insert a new node with specified data before the node.
 * 
 * @param list list to insert into
 * @param data data to be inserted
 * @param node node that follows the new node
 * 
 * @return 0 on success, negative value on failure.
*/
extern int List_insert_before(List_t list, const Data data, const Node_t node);

/* ================================================================ */

#ifdef __cplusplus
    }
#endif

#endif