#include "list.h"

struct _node {
    Data data;

    struct _node* next;
};

struct _linked_list {
    size_t size;                        /* Number of elements in the list */

    struct _node* head;                 /* First element of the list */
    struct _node* tail;                 /* Last element of the list */

    void (*fptr_destroy)(void*);        /* Destroys every element of the list */
    void (*fptr_print)(const Data);     /* Displays the list */
};

/* ================================================================ */

static Node Node_new(const Data data) {
    Node node = NULL;

    if (data == NULL) {
        warn_with_user_msg(__func__, "data can't be NULL");

        return node;
    }

    if ((node = (Node) malloc(sizeof(struct _node))) != NULL) {
        node->data = (Data) data;
        node->next = NULL;
    }
    else {
        warn_with_sys_msg("Memory allocation failure");
    }

    return node;
}

/* ================================ */

List List_new(void (*fptr_destroy)(void*), void (*fptr_print)(const Data)) {
    List list = NULL;

    if ((list = (List) malloc(sizeof(struct _linked_list))) != NULL) {
        list->size = 0;
        list->head = list->tail = NULL;

        list->fptr_destroy = fptr_destroy;
        list->fptr_print = fptr_print;
    }
    else {
        warn_with_sys_msg("List_new() error");
    }

    return list;
}

/* ================================ */

void List_print(const List list, void (*fptr_print)(const Data)) {
    void (*alt_fptr_print)(const Data) = NULL;

    if (list != NULL) {
        if ((list->fptr_print == NULL) && (fptr_print == NULL)) {
            warn_with_user_msg(__func__, "there is no associated `print` function with the list");

            return ;
        }

        printf("[");

        if (list->size > 0) {
            alt_fptr_print = (list->fptr_print == NULL) ? fptr_print : list->fptr_print;

            for (Node node = list->head; node != NULL; node = node->next) {
                alt_fptr_print(node->data);

                if (node->next != NULL) {
                    printf(", ");
                }
            }
        }

        printf("]\n");
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return ;
}

/* ================================ */

int8_t List_insert_first(List list, const Data data) {
    int8_t result = 0;
    Node node = NULL;

    if (list != NULL) {
        if ((node = Node_new(data)) != NULL) {
            switch (list->size) {
                case 0:
                    list->head = list->tail = node;

                    break ;

                default:
                    node->next = list->head;
                    list->head = node;

                    break ;
            }

            list->size++;
            result = 1;
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return result;
}

/* ================================ */

int8_t List_insert_last(List list, const Data data) {
    int8_t result = 0;
    Node node = NULL;

    if (list != NULL) {
        if ((node = Node_new(data)) != NULL) {
            switch (list->size) {
                case 0:
                    list->tail = list->head = node;

                    break ;

                default:
                    list->tail->next = node;
                    list->tail = node;

                    break ;
            }

            list->size++;
            result = 0;
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return result;
}

/* ================================ */

 Node List_find(const List list, const Data data, int (*fptr_match)(const Data data_1, const Data data_2)) {
    Node node = NULL;

    if (list != NULL) {
        if (data != NULL) {
            if (fptr_match != NULL) {
                for (node = list->head; node != NULL; node = node->next) {
                    if (fptr_match(node->data, data) == 0) {
                        return node;
                    }
                }
            }
            else {
                warn_with_user_msg(__func__, "match argument can't be NULL");
            }
        }
        else {
            warn_with_user_msg(__func__, "data argument can't be NULL");
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return node;
 }

 /* ================================ */

Data List_remove_first(List list) {
    Node node = NULL;
    Data data = NULL;

    if (list != NULL) {
        if (list->size > 0) {
            node = list->head;
            data = node->data;

            list->head = node->next;

            if (list->size == 1) {
                list->tail = list->head;
            }

            list->size--;

            memset(node, 0, sizeof(struct _node));
            free(node);
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return data;
}

/* ================================ */

size_t List_get_size(const List list) {
    return (list != NULL) ? list->size : -1;
}

/* ================================ */

Data List_remove_last(List list) {
    Node node = NULL;                   /* A node to be freed */
    Data data = NULL;                   /* A pointer to the returned data */

    if (list != NULL) {
        if (list->size > 0) {
            node = list->tail;
            data = node->data;

            if (list->size == 1) {
                list->tail = list->head = NULL;
            }
            else {
                Node temp = NULL;                   /* Used to traverse the list */

                for (temp = list->head; temp->next != list->tail; temp = temp->next) ;

                list->tail = temp;
                temp->next = NULL;
            }

            list->size--;

            memset(node, 0, sizeof(struct _node));
            free(node);
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return data;
}

/* ================================ */

void List_destroy(List* list) {
    Data data = NULL;

    if ((list != NULL) && (*list != NULL)) {
        while ((*list)->size > 0) {
            data = List_remove_first(*list);
            
            if ((*list)->fptr_destroy != NULL) {
                (*list)->fptr_destroy(data);

                Data* ptr_data = &data;
                *ptr_data = NULL;
            }
        }

        /* Deallocate memory */
        free(*list);

        *list = NULL;
    }

    return ;
}

/* ================================ */

extern int8_t List_merge(List* dest, List* src) {
    int8_t result = 0;

    /* Test for dest */
    if ((dest != NULL) && (*dest != NULL)) {
        /* Test fot src */
        if ((src != NULL) && (*src != NULL)) {
            (*dest)->tail->next = (*src)->head;
            (*dest)->tail = (*src)->tail;
            (*dest)->size += (*src)->size;

            /* After the merge, the `src` list is eliminated */
            *src = NULL;

            result = 1;
        }
    }

    return result;
}

/* ================================ */

Data List_remove_node(List list, Node node) {
    Data data = NULL;                   /* Returned data */

    /* 
        * It's safe to specify node as NULL because it doesn't cause run-time errors.
        * However, we simply return from function.
    */
    if (node == NULL) {
        return data;
    }

    if (list != NULL) {
        if (list->size > 0) {
            if (node == list->head) {
                data = List_remove_first(list); 
            }
            else if (node == list->tail) {
                data = List_remove_last(list);
            }
            else {
                Node temp = NULL;                   /* Used to traverse the list */

                /* Make sure the specified node is in the list */
                for (temp = list->head; temp != NULL && temp->next != node; temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {
                    data = temp->next->data;
                    temp->next = temp->next->next;

                    list->size--;
                    
                    /* Clear any sensitive data */
                    memset(node, 0, sizeof(struct _node));
                    /* Dealocate memory */
                    free(node);
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }
    
    return data;
}

/* ================================ */

/* ================================================================ */
/* ================================================================ */
/*
    * `List_insert_after` and `List_insert_before` functions add a new element
    * with the specified data after and before the specified node respectively.
    * 
    * Traversing a list is a time-consuming operation which depends on the number of elements in the list.
    * 
    * The thing is to decide whether we should create a node first or traverse the list
    * in search for the node.
    * 
    * In the first variant, we don't need to traverse the list which may
    * have thousands of elements just to realize that `data` is NULL (e.g., we can't have nodes with NULL
    * as its data). When the new node is allocated and we know that the specifid node is not in the list
    * we need to deallocate the node and its data field according to the list `fptr_destroy` "member".
    * If memory allocation failure occurs while we are creating a node, meaning we don't have enough memory
    * for another node, we don't need to traverse a list too. Keep in mind that nothing stops you from
    * specifying a node which is not in the list, meaning the list is traversed until its end.
    * 
    * Another solution is to traverse the list first and then create a node. In this scenario the list is
    * traversed every time we insert data into the list (except several condition described below).
    * 
    * I decided to stick with the first solution because it 
*/

int8_t List_insert_after(List list, const Data data, const Node node) {
    int8_t result = 0;

    if (list != NULL) {
        if ((list->size == 0) || (node == NULL) || (node == list->tail)) {
            result = List_insert_last(list, data);
        }
        else {
            Node new_node = NULL;

            if ((new_node = Node_new(data)) != NULL) {
                Node temp = NULL;
                /* Make sure the specified node is in the list */
                for (temp = list->head; temp != NULL && temp != node; temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {
                    new_node->next = temp->next;
                    temp->next = new_node;

                    list->size++;

                    result = 1;
                }
                else {
                    if (list->fptr_destroy != NULL) {
                        list->fptr_destroy(data);
                    }

                    free(new_node);
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return result;
}

/* ================================ */

int8_t List_insert_before(List list, const Data data, const Node node) {
    int8_t result = 0;

    if (list != NULL) {
        if ((list->size == 0) || (node == NULL) || (node == list->head)) {
            result = List_insert_first(list, data);
        }
        else {
            Node new_node = NULL;

            if ((new_node = Node_new(data)) != NULL) {
                Node temp = NULL;
                /* Make sure the specified node is in the list */
                for (temp = list->head; temp != NULL && temp->next != node; temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {
                    new_node->next = temp->next;
                    temp->next = new_node;

                    list->size++;

                    result = 1;
                }
                else {
                    if (list->fptr_destroy != NULL) {
                        list->fptr_destroy(data);
                    }

                    free(new_node);
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "list can't be NULL");
    }

    return result;
}

/* ================================ */

/* ================================================================ */
/* ================================================================ */