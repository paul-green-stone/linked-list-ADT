#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* ================================================================ */

#define INIT_SUCCESS EXIT_SUCCESS
#define PRINT_NULL (1 << 0) /* 1 */
#define MATCH_NULL (1 << 1) /* 2 */

/* ================================================================ */

struct Node {
    void* data;

    struct Node* next;
};

struct List {
    struct Node* head;
    struct Node* tail;

    size_t size;

    void (*destroy)(void*);
    void (*print)(const void*);
    int (*match)(const void*, const void*);
};

/* ================================================================ */

/*
    * Initializes the linked list specified by `list`. This operation must
    * be called for a linked list before the list can be used with any other operation.
    * The `destroy` argument provides a way to free dynamically allocated data when `List_destroy` 
    * is called.
*/
extern int List_init(struct List* list, void (*destroy)(void* data), void (*print)(const void* data), int (*match)(const void* data_1, const void* data_2));

/* 
    * Inserts an element at the beginning of the linked list.
*/
extern int List_insert_first(struct List* list, const void* data);

/*
    * Outputs content of the linked list. The `print` argument is a callback function 
    * that is called for every node in the list for this particular `List_display` invokation.
    * It does not overwrite the default `print` function (e.g., specified in the `List_init`). If
    * `print` is NULL, the default `print` is used.
*/
extern void List_display(const struct List* list, void (*print)(const void* data));

/*
    * Inserts an element at the end of the linked list.
*/
extern int List_insert_last(struct List* list, const void* data);

/*
    * Looks for a node with the given data.
    *
    * Returns a pointer to the list node with specified data. NULL inidcates the absence of a node with such data.
*/
extern struct Node* List_find(const struct List* list, const void* data, int (*match)(const void*, const void*));

/*
    * Removes the first element from the list.

    * Returns a pointer to data in a node.
*/
extern void* List_remove_first(struct List* list);

/*
    * Removes the last element from the list.

    * Returns a pointer to data in a node.
*/
extern void* List_remove_last(struct List* list);

/*
    * Removes the specified node from the given list.

    * Returns a pointer to data from removed element or NULL if there is no such node in the list.
*/
extern void* List_remove_node(struct List* list, struct Node* node);

/*
    * Insert a new node with specified data before another node
*/
extern int List_insert_before(struct List* list, const void* data, const struct Node* node);

/*
    * Insert a new node with specified data after another node.
*/
extern int List_insert_after(struct List* list, const void* data, const struct Node* node);

/*
    * Destroys a linked list.
*/
extern void List_destroy(struct List* list);

/*
    * Applies a callback function to every node data in a list.
*/
extern int List_each(const struct List* list, void (*callback)(void* data));

#endif