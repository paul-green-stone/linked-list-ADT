#ifndef DATA_H
#define DATA_H

/* ================================================================ */
/* ======================= TYPES DEFINITIONS ====================== */
/* ================================================================ */

/**
 * Data type used in a list node
*/
typedef void* Data;

/* ================================ */

/**
 * A pointer to a user defined function that outputs data
*/
typedef void (*print_fptr)(const Data data);

/* ================================ */

/**
 * A pointer to a user defined function that handles the deletion of data
*/
typedef void (*destroy_fptr)(Data data);

/* ================================ */

/**
 * A pointer to a user defined function that handles the comparison of data against another data
*/
typedef int (*match_fptr)(const Data data_1, const Data data_2);

/* ================================================================ */

#endif