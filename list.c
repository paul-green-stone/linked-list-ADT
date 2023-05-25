#include "list.h"

/* ================================================================ */

/* Allocate a new instance of a linked list node */
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
        warn_with_sys_msg(__func__);
    }

    return node;
}

/* ================================ */

/* Clear the memory region occupied by the linked list node and deallocate it */
static Data Node_destroy(Node* node) {
    Data data = NULL;

    if ((node != NULL) && (*node != NULL)) {
        data = (*node)->data;
        (*node)->next = NULL;

        /* Clear memory*/
        memset(*node, 0, sizeof(struct _node));
        /* Deallocate memory */
        free(*node);

        *node = NULL;
    }

    return data;
}

/* ================================ */
/* ================================ */
/* ================================ */

List_t List_create(fptr_destroy destroy_func, fptr_print print_func, fptr_match match_func) {
    List_t list = NULL;

    if ((list = (List_t) malloc(sizeof(struct _linked_list))) != NULL) {
        list->size = 0;
        list->head = list->tail = NULL;

        list->destroy = destroy_func;
        list->print = print_func;
        list->match = match_func;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    return list;
}

/* ================================ */

void List_print(const List_t list, fptr_print print_func) {
    void (*alt_fptr_print)(const Data) = NULL;

    if (list != NULL) {
        if ((list->print == NULL) && (print_func == NULL)) {
            warn_with_user_msg(__func__, "there is no associated `print` function with the given list");

            return ;
        }

        printf("[");

        if (list->size > 0) {
            /* If the alternative `print` function provided, use it instead of default one */
            alt_fptr_print = (print_func != NULL) ? print_func : list->print;

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
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return ;
}

/* ================================ */

int List_insert_first(List_t list, const Data data) {
    int8_t result = -1;
    Node node = NULL;

    if (list != NULL) {
        /* Create a new node */
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
            result = 0;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return result;
}

/* ================================ */

int List_insert_last(List_t list, const Data data) {
    int8_t result = -1;
    Node node = NULL;

    if (list != NULL) {
        /* Create a new node */
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
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return result;
}

/* ================================ */

 Node List_find(const List_t list, const Data data) {
    Node node = NULL;

    if (list != NULL) {
        if (data != NULL) {
            if (list->match != NULL) {
                for (node = list->head; node != NULL; node = node->next) {
                    if (list->match(node->data, data) == 0) {
                        break ;
                    }
                }
            }
            else {
                warn_with_user_msg(__func__, "there is no associated `match` function with the given list");
            }
        }
        else {
            warn_with_user_msg(__func__, "data can't be NULL");
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return node;
 }

 /* ================================ */

Data List_remove_first(List_t list) {
    Node node = NULL;
    Data data = NULL;

    if (list != NULL) {
        if (list->size > 0) {
            node = list->head;

            list->head = node->next;

            if (list->size == 1) {
                list->tail = list->head;
            }

            list->size--;

            data = Node_destroy(&node);
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return data;
}

/* ================================ */

size_t List_get_size(const List_t list) {
    return (list != NULL) ? list->size : -1;
}

/* ================================ */

Data List_remove_last(List_t list) {
    Node node = NULL;
    /* Data to be returned */
    Data data = NULL;

    if (list != NULL) {
        if (list->size > 0) {
            node = list->tail;

            if (list->size == 1) {
                list->tail = list->head = NULL;
            }
            else {
                /* Used to traverse the list */
                Node temp = NULL;

                for (temp = list->head; temp->next != list->tail; temp = temp->next) ;

                list->tail = temp;
                temp->next = NULL;
            }

            list->size--;

            /* Destroy the node. Return data it contained */
            data = Node_destroy(&node);
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return data;
}

/* ================================ */

void List_destroy(List_t* list) {
    Data data = NULL;

    if ((list != NULL) && (*list != NULL)) {
        /* Repeatedly delete elements */
        while ((*list)->size > 0) {
            data = List_remove_first(*list);
            
            if ((*list)->destroy != NULL) {
                (*list)->destroy(data);
            }
        }

        /* Clear memory */
        memset(*list, 0, sizeof(struct _linked_list));
        /* Deallocate memory */
        free(*list);

        *list = NULL;
    }

    return ;
}

/* ================================ */

extern int List_merge(List_t* dest, List_t* src) {
    int result = -1;

    /* Test for dest */
    if ((dest != NULL) && (*dest != NULL)) {
        /* Test fot src */
        if ((src != NULL) && (*src != NULL)) {
            (*dest)->tail->next = (*src)->head;
            (*dest)->tail = (*src)->tail;
            (*dest)->size += (*src)->size;

            /* After the merge, the `src` list is eliminated */
            *src = NULL;

            result = 0;
        }
    }

    return result;
}

/* ================================ */

Data List_remove_node(List_t list, Node node) {
    /* Data to be returned */
    Data data = NULL;

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
                /* Used to traverse the list */
                Node temp = NULL;

                /* Make sure the specified node is in the list */
                for (temp = list->head; temp != NULL && temp->next != node; temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {
                    temp->next = temp->next->next;

                    list->size--;

                    data = Node_destroy(&node);
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }
    
    return data;
}

/* ================================ */

int List_insert_after(List_t list, const Data data, const Node node) {
    int result = -1;

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

                    result = 0;
                }
                else {
                    if (list->destroy != NULL) {
                        list->destroy(data);
                    }

                    free(new_node);
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return result;
}

/* ================================ */

int List_insert_before(List_t list, const Data data, const Node node) {
    int result = -1;

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

                    result = 0;
                }
                else {
                    if (list->destroy != NULL) {
                        list->destroy(data);
                    }

                    free(new_node);
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return result;
}