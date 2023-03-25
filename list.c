#include "list.h"

static struct Node* Node_create(const void* data) {
    struct Node* node = NULL;

    #ifndef NULL_ELMS
        if (data == NULL) {
            return NULL;
        }
    #endif

    if ((node = (struct Node*) malloc(sizeof(struct Node))) != NULL) {
        node->data = (void*) data;
        node->next = NULL;
    }
    else {
        fprintf(stderr, "%s\n", strerror(errno));
    }

    return node;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

int List_init(struct List* list, void (*destroy)(void* data), void (*print)(const void* data), int (*match)(const void* data_1, const void* data_2)) {
    int status_code = EXIT_SUCCESS;

    if (list != NULL) {
        status_code |= ((list->print = print) == NULL) ? PRINT_NULL : EXIT_SUCCESS;
        status_code |= ((list->match = match) == NULL) ? MATCH_NULL : EXIT_SUCCESS;

        if (status_code != EXIT_SUCCESS) {
            return status_code;
        }

        list->destroy = destroy;
        list->print = print;
        list->match = match;

        list->head = list->tail = NULL;

        list->size = 0;
    }

    return status_code;
}

/* ================================================================ */

int List_insert_first(struct List* list, const void* data) {
    int status_code = EXIT_FAILURE;

    struct Node* node = NULL;

    if (list != NULL) {
        if ((node = (struct Node*) Node_create(data)) != NULL) {
            switch (list->size) {
                case 0:
                    list->head = list->tail = node;
                    break;

                default: 
                    node->next = list->head;
                    list->head = node;
                    break;
            }

            list->size++;
            status_code = EXIT_SUCCESS;
        }
    }

    return status_code;
}

/* ================================================================ */

void List_display(const struct List* list, void (*print)(const void* data)) {
    #ifdef NULL_ELMS
        size_t n = 0;
    #endif

    void (*printrout_t)(const void* data);

    if (list != NULL) {
        if (list->print == NULL) {
            /* 
             * The list has not been initialized.
             * You cannot avoid specifying the list->print callback in List_init function.
             * This does not allow the List_display function to dispaly "[]".
            */
            return ;
        }

        printrout_t = (print == NULL) ? list->print : print;

        if (list->size > 0) {
            for (struct Node* node = list->head; node != NULL; node = node->next) {
                if (node->data == NULL) {
                    #ifdef NULL_ELMS
                        n += 1;
                    #endif

                    continue;
                }

                printrout_t(node->data);

                if (node->next != NULL) {
                    printf(", ");
                }
            }

            #ifdef NULL_ELMS
                printf("\n(%lu/%zu)", list->size - n, list->size);
            #endif
        }
        else {
            printf("[]");
        }

        printf("\n");
    }

    return ;
}

/* ================================================================ */

int List_insert_last(struct List* list, const void* data) {
    int status_code = EXIT_FAILURE;

    struct Node* node = NULL;
    struct Node* t;

    if (list != NULL) {
        if ((node = (struct Node*) Node_create(data)) != NULL) {
            switch (list->size) {
                case 0:
                    list->tail = list->head = node;
                    break;

                default: 
                    list->tail->next = node;
                    list->tail = node;
            }

            list->size++;
            status_code = EXIT_SUCCESS;
        }
    }

    return status_code;
}

/* ================================================================ */

struct Node* List_find(const struct List* list, const void* data, int (*match)(const void* data_1, const void* data_2)) {
    int (*matchroute_t)(const void*, const void*);
    struct Node* node = NULL;

    if (list != NULL) {
        matchroute_t = (match == NULL) ? list->match : match;

        for (node = list->head; node != NULL; node = node->next) {
            if (matchroute_t(node->data, data) == 0) {
                break ;
            }
        }
    }

    return node;
}

/* ================================================================ */

void* List_remove_first(struct List* list) {
    void* data = NULL;
    struct Node* node = NULL;

    if (list != NULL) {
        if (list->size > 0) {
            data = list->head->data;
            node = list->head;

            switch (list->size) {
                case 1:
                    list->head = list->tail = NULL;
                    break;

                default:
                    list->head = list->head->next;
                    break;
            }

            list->size--;

            free(node);
        }
    }

    return data;
}

/* ================================================================ */

void* List_remove_last(struct List* list) {
    void *data = NULL;
    struct Node* node = NULL;
    struct Node* temp = NULL;

    if (list != NULL) {
        if (list->size > 0) {
            data = list->tail->data;
            node = list->tail;

            switch (list->size) {
                case 1:
                    list->head = list->tail = NULL;
                    break;

                default:
                    for (temp = list->head; temp->next != list->tail; temp = temp->next) ;

                    temp->next = NULL;
                    list->tail = temp;
            }

            list->size--;

            free(node);
        }
    }

    return data;
}

/* ================================================================ */

void* List_remove_node(struct List* list, struct Node* node) {
    void* data = NULL;
    struct Node* temp = NULL;

    if (list != NULL && node != NULL) {
        if (list->size > 0) {
            if (node == list->head) {
                data = List_remove_first(list); 
            }
            else if (node == list->tail) {
                data = List_remove_last(list);
            }
            else {
                for (temp = list->head; temp != NULL && temp->next != node; temp = temp->next) ;

                if (temp == NULL) {
                    return data;
                }

                data = temp->next->data;
                temp->next = temp->next->next;

                list->size--;

                free(node);
            }
        }
    }
    
    return data;
}

/* ================================================================ */

int List_insert_before(struct List* list, const void* data, const struct Node* node) {
    int status_code = EXIT_FAILURE;
    struct Node* new_node = NULL;
    struct Node* temp = NULL;

    if (list != NULL) {
        if (list->size == 0 || node == NULL || node == list->head) {
            status_code = List_insert_first(list, data);
        }
        else {
            for (temp = list->head; temp != NULL && temp->next != node; temp = temp->next) ;

            if (temp != NULL) {
                if ((new_node = Node_create(data)) != NULL) {
                    new_node->next = temp->next;
                    temp->next = new_node;

                    list->size++;

                    status_code = EXIT_SUCCESS;
                }
            }
        }
    }

    return status_code;
}

/* ================================================================ */

int List_insert_after(struct List* list, const void* data, const struct Node* node) {
    int status_code = EXIT_FAILURE;
    struct Node* new_node = NULL;
    struct Node* temp = NULL;

    if (list != NULL) {
        if (list->size == 0 || node == NULL || node == list->tail) {
            status_code = List_insert_last(list, data);
        }
        else {
            for (temp = list->head; temp != NULL && temp != node; temp = temp->next) ;

            if (temp != NULL) {
                if ((new_node = Node_create(data)) != NULL) {
                    new_node->next = temp->next;
                    temp->next = new_node;

                    list->size++;

                    status_code = EXIT_SUCCESS;
                }
            }
        }
    }

    return status_code;
}

/* ================================================================ */

void List_destroy(struct List* list) {
    void* data;

    if (list != NULL) {
        while (list->size > 0) {
            data = List_remove_last(list);

            if (list->destroy) {
                list->destroy(data);
            }
        }

        memset(list, 0, sizeof(struct List));
    }

    return ;
}

/* ================================================================ */

int List_each(const struct List* list, void (*callback)(void* data)) {
    int status_code = EXIT_FAILURE;

    if (Lis_init(list) && callback != NULL) {
        if (list->size > 0) {
            for (struct Node* node = list->head; node != NULL; node = node->next) {
                callback(node->data);
            }

            status_code = EXIT_SUCCESS;
        }
    }

    return status_code;
}