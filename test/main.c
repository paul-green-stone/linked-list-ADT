#include "../src/list.h"

#include <time.h>

#define NUM 12

void print_int(const Data data) {
    printf("%d", *((int*) data));
}

int int_match(const Data data_1, const Data data_2) {
    return (*((int*) data_1) - *((int*) data_2));
}

/* ================================================================ */

int main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = -1;

    time_t t;

    int* x = NULL;

    /* Target */
    int a = 10;

    /* ================================ */



    /* Initialize a random number initializer */
    srand((unsigned) &t);

    List_t listA = NULL;
    List_t listB = NULL;

    listA = List_create(free, print_int, int_match);
    listB = List_create(free, print_int, int_match);

    for (size_t i = 0; i < NUM; i++) {
        x = (int*) malloc(sizeof(int));

        *x = rand() % 100;

        List_insert_first(listA, x);
    }

    for (size_t i = 0; i < NUM; i++) {
        x = (int*) malloc(sizeof(int));

        *x = rand() % 100;

        List_insert_first(listB, x);
    }

    printf("ListA: ");
    List_print(listA, NULL);

    printf("ListB: ");
    List_print(listB, NULL);

    printf("List size: %lu\n", List_size(listA));

    List_merge(&listA, &listB);

    printf("ListA: ");
    List_print(listA, NULL);

    printf("List size: %lu\n", List_size(listA));

    List_print(listB, NULL);

    x = (int*) malloc(sizeof(int));
    *x = 100;

    List_insert_before(listA, x, listA->head);

    printf("ListA: ");
    List_print(listA, NULL);
    printf("List size: %lu\n", List_size(listA));

    x = (int*) malloc(sizeof(int));
    *x = 1000;

    List_insert_before(listA, x, listA->tail);

    printf("ListA: ");
    List_print(listA, NULL);
    printf("List size: %lu\n", List_size(listA));

    List_remove_node(listA, listA->head->next);

    printf("ListA: ");
    List_print(listA, NULL);
    printf("List size: %lu\n", List_size(listA));

    List_destroy(&listA);
    List_destroy(&listB);

    
    return EXIT_SUCCESS;
}

/* ================================================================ */