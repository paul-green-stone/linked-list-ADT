#include "list.h"

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

/**
 *  Destroy the node.
 * 
 * @param node pointer to the Node_t node to be destroyed
 * @param caller_name name of the function that calls a Node_destroy function or NULL
 * 
 * @return a pointer to data to be deleted.
*/
static Data __Node_destroy(Node_t* node, const char* func_name) {
    /* =========== VARIABLES ========== */

    /* Data to be destroyed */
    Data data = NULL;

    /* Operation result */
    int result = 1;

    /* ================================= */



    /* ================================================================ */
    /* ================= Make sure a node is not NULL ================= */
    /* ================================================================ */

    if ((node != NULL) && (*node != NULL)) {

        /* Keep a pointer to data */
        data = (*node)->data;

        /* Clear memory*/
        memset(*node, 0, sizeof(struct _node));

        /* Deallocate memory */
        free(*node);

        /* Explicitly set a node to NULL */
        *node = NULL;

        /* ================================= */

        /* Success */
        result = 0;
    }
    else {
        warn_with_user_msg((func_name == NULL) ? __func__ : func_name, "provided node is NULL");
    }

    /* ================================= */

    return Data;
}

/* ================================================================ */
/* ============================ EXTERN ============================ */
/* ================================================================ */

Node_t Node_create(const Data data) {
    /* =========== VARIABLES ========== */

    /* Node we are creating */
    Node_t node = NULL;

    /* ================================= */


    
    /* ================================================================ */
    /* ====== Dynamically allocate memory for a linked list node ====== */
    /* ============= YOU NEED TO CALL free ON THIS OBJECT ============= */
    /* ================================================================ */

    if ((node = (Node_t) malloc(sizeof(struct _node))) != NULL) {

        /* Cast to avoid a warning message */
        node->data = (Data) data;

        /* A new node is isolated after creation */
        node->next = NULL;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    /* ================================= */

    return node;
}

/* ================================================================ */

List_t List_create(destroy_fptr destroy, print_fptr print, match_fptr match) {
    /* =========== VARIABLES ========== */

    /* List we are creating */
    List_t list = NULL;

    /* ================================= */



    /* ================================================================ */
    /* ======== Dynamically allocate memory for a linked list ========= */
    /* ============= YOU NEED TO CALL free ON THIS OBJECT ============= */
    /* ================================================================ */

    if ((list = (List_t) malloc(sizeof(struct _linked_list))) != NULL) {

        /* Clear the memory */
        memset(list, 0, sizeof(struct _linked_list));

        /* ================================= */

        /* Set a destroy function */
        list->destroy = destroy;

        /* Set a print function */
        list->print = print;

        /* Set a match function */
        list->match = match;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    /* ================================= */

    return list;
}

/* ================================================================= */

void List_print(const List_t list, print_fptr print) {
    /* =========== VARIABLES ========== */

    /* Alternative print function */
    print_fptr alt_print = NULL;

    /* Node we are using to traverse the list */
    Node_t node = NULL;

    /* ================================= */


    
    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        /* ============= Make sure there is a function to use ============= */
        if ((list->print == NULL) && (print == NULL)) {
            warn_with_user_msg(__func__, "there is no associated `print` function with the given list");

            return ;
        }

        /* ================================= */

        printf("[");

        if (list->size > 0) {

            /* Use alternative print function if provided */
            alt_print = (print != NULL) ? print : list->print;

            for (node = list->head; node != NULL; node = node->next) {

                /* Print the node data */
                alt_print(node->data);

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

    /* ================================= */

    return ;
}

/* ================================================================ */

int List_insert_first(List_t list, const Data data) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node we want to place data into */
    Node_t node = NULL;

    /* ================================= */



    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        /* ====================== Create a new node  ====================== */
        if ((node = Node_create(data)) != NULL) {

            switch (list->size) {

                /* If the list is empty */
                case 0:
                    list->head = list->tail = node;

                    break ;

                /* If there are nodes in the list */
                default:

                    /* Connect a new node with the list head */
                    node->next = list->head;

                    /* Set a new node to be the head of the list */
                    list->head = node;

                    break ;
            }

            /* Update the list size */
            list->size++;

            /* Success */
            result = 0;
        }

        /* Node_create function will tell you if there is an error occured while node creation */
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

int List_insert_last(List_t list, const Data data) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node we want to place data into */
    Node_t node = NULL;

    /* ================================= */



    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        /* ====================== Create a new node  ====================== */
        if ((node = Node_create(data)) != NULL) {

            /* If the list is empty */
            switch (list->size) {
                case 0:
                    list->tail = list->head = node;

                    break ;

                default:

                    /* Insert an element at the end */
                    list->tail->next = node;

                    /* Set a node to be the new tail of the list */
                    list->tail = node;

                    break ;
            }

            /* Update the list size */
            list->size++;

            /* Success */
            result = 0;
        }

        /* Node_create function will tell you if there is an error occured while node creation */
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

Node_t List_find(const List_t list, const Data data, match_fptr match) {
    /* =========== VARIABLES ========== */

    /* Alternative print function */
    match_fptr alt_match = NULL;

    /* Node we are using to traverse the list */
    Node_t node = NULL;

    /* ================================= */



    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        if (data != NULL) {

            /* ============= Make sure there is a function to use ============= */
            if ((list->match == NULL) && (match == NULL)) {
                warn_with_user_msg(__func__, "there is no associated `match` function with the given list");

                return NULL;
            }

            /* ================================= */



            /* Use alternative match function if provided */
            alt_match = (match != NULL) ? match : list->match;

            /* Traverse the list and compare its data */
            for (node = list->head; (node != NULL) && (alt_match(node->data, data) != 0); node = node->next) ;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    /* ================================ */

    return node;
 }

 /* ================================================================ */

int List_remove_first(List_t list) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node to be deleted */
    Node_t node = NULL;

    /* Data to be deleted */
    Data data = NULL;

    /* ================================= */



    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        /* If the list is not empty */
        if (list->size > 0) {

            node = list->head;

            /* Set a new list head */
            list->head = node->next;

            if (list->size == 1) {
                list->tail = list->head = NULL;
            }

            /* Update the list size */
            list->size--;

            /* Destroy the node */
            data = __Node_destroy(&node, __func__);

            /* destroy data if needed */
            if (list->destroy != NULL) {
                list->destroy(data);
            }

            /* ================================ */

            /* Success */
            result = 0;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

int List_remove_last(List_t list) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node to be deleted */
    Node_t node = NULL;

    /* Node that is used to traverse the list */
    Node_t temp = NULL;

    /* Data to be deleted */
    Data data = NULL;   

    /* ================================ */

    

    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        /* If the list is not empty */
        if (list->size > 0) {

            node = list->tail;

            /* Special case */
            if (list->size == 1) {
                list->tail = list->head = NULL;
            }
            /* Default case */
            else {
                
                /* Traverse the list */
                for (temp = list->head; temp->next != list->tail; temp = temp->next) ;

                /* Set a new list tail */
                list->tail = temp;

                temp->next = NULL;
            }

            /* Update the list size */
            list->size--;

            /* Destroy the node */
            data =  __Node_destroy(&node, __func__);

            if (list->destroy != NULL) {
                list->destroy(data);
            }

            /* ================================ */

            /* Success */
            result = 0;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

int List_destroy(List_t* list) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* ================================ */



    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if ((list != NULL) && (*list != NULL)) {

        /* Repeatedly delete elements */
        while ((*list)->size > 0) {
            List_remove_first(*list);
        }

        /* Clear memory */
        memset(*list, 0, sizeof(struct _linked_list));

        /* Deallocate memory */
        free(*list);

        *list = NULL;

        /* Success */
        result = 0;
    }



    /* ================================ */

    return result;
}

/* ================================================================ */

extern int List_merge(const List_t* dest, List_t* src) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* ================================ */



    /* ================================================================ */
    /* ================== Make sure dest is not NULL ================== */
    /* ================================================================ */

    if ((dest != NULL) && (*dest != NULL)) {

        /* ================================================================ */
        /* ================== Make sure src is not NULL =================== */
        /* ================================================================ */

        if ((src != NULL) && (*src != NULL)) {
            
            /* Add the src head to the tail of the dest list */
            (*dest)->tail->next = (*src)->head;

            /* Make the tail of the src list to be the tail of the dest list */
            (*dest)->tail = (*src)->tail;

            /* Compute a new size */
            (*dest)->size += (*src)->size;

            /* After the merge, the `src` list is eliminated */
            *src = NULL;

            /* ================================ */

            /* Success */
            result = 0;
        }
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

int List_remove_node(List_t list, Node_t node) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node that is used to traverse the list */
    Node_t temp = NULL;

    /* ================================ */



    /* ================================================================ */
    /* ================= Make sure a node is not NULL ================= */
    /* ================================================================ */

    if (node == NULL) {
        return result;
    }



    /* ================================================================ */
    /* ================= Make sure a list is not NULL ================= */
    /* ================================================================ */

    if (list != NULL) {

        /* If the list is not empty */
        if (list->size > 0) {

            /* Case 1. Remove the head */
            if (node == list->head) {
                List_remove_first(list); 
            }

            /* Case 2. Remove the tail */
            else if (node == list->tail) {
                List_remove_last(list);
            }

            /* Case 3. Somewhere in between head and tail */
            else {

                /* Make sure the specified node is in the list */
                for (temp = list->head; temp != NULL && temp->next != node; temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {

                    /**/
                    temp->next = temp->next->next;

                    /* Update the size */
                    list->size--;

                    __Node_destroy(&node, list->destroy, __func__);
                }
            }

            /* Success */
            result = 0;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }



    /* ================================ */
    
    return result;
}

/* ================================================================ */

int List_insert_after(List_t list, const Data data, const Node_t node) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node that is used to traverse the list */
    Node_t temp = NULL;

    /* Node we are creating */
    Node_t new_node = NULL;

    /* ================================ */



    /* ================================================================ */
    /* ================== Make sure list is not NULL ================== */
    /* ================================================================ */

    if (list != NULL) {

        /* Special case. When there is no any node in the list */
        if ((list->size == 0) || (node == NULL) || (node == list->tail)) {
            result = List_insert_last(list, data);
        }

        /* Default case  */
        else {

            /* ====================== Create a new node  ====================== */
            if ((new_node = Node_create(data)) != NULL) {

                /* Make sure the specified node is in the list */
                for (temp = list->head; temp != NULL && temp != node; temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {

                    /* "Rearrange" the list */
                    new_node->next = temp->next;
                    temp->next = new_node;

                    /* Update size */
                    list->size++;

                    /* ================================ */

                    /* Success */
                    result = 0;
                }
                /* If the list doesn't contain such a node */
                else {
                    __Node_destroy(&new_node, __func__);

                    if (list->destroy != NULL) {
                        list->destroy(data);
                    }
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    return result;
}

/* ================================================================ */

int List_insert_before(List_t list, const Data data, const Node_t node) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    /* Node that is used to traverse the list */
    Node_t temp = NULL;

    /* Node we are creating */
    Node_t new_node = NULL;

    /* ================================ */



    /* ================================================================ */
    /* ================== Make sure list is not NULL ================== */
    /* ================================================================ */

    if (list != NULL) {

         /* Special case. When there is no any node in the list */
        if ((list->size == 0) || (node == NULL) || (node == list->head)) {
            result = List_insert_first(list, data);
        }
        else {
            
            /* ====================== Create a new node  ====================== */
            if ((new_node = Node_create(data)) != NULL) {

                /* Make sure the specified node is in the list */
                for (temp = list->head; (temp != NULL) && (temp->next != node); temp = temp->next) ;

                /* The node IS in the list */
                if (temp != NULL) {

                    /* "Rearrange" the list */
                    new_node->next = temp->next;
                    temp->next = new_node;

                    /* Update the size */
                    list->size++;

                    /* ================================ */
                    
                    /* Success */
                    result = 0;
                }
                /* Node is not in the list */
                else {
                    __Node_destroy(&new_node, __func__);

                    if (list->destroy != NULL) {
                        list->destroy(data);
                    }
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided list is NULL");
    }

    /* ================================ */

    return result;
}