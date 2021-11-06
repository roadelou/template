/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2020-10-07
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The header with the function we are trying to implement. */
#include <template.h>

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

const char *get_extension(const char *path) {
    /* The integer we will use to build the returned pointer. */
    size_t cursor;
    /* We try to get the position of the first dot in the path. */
    cursor = occurence(path, '.', 1);
    if (cursor == -1) {
        /* There is no dot in this path, we look for the last slash for the path
         * separator. */
        cursor = occurence(path, '/', 0);
    }
    /* We return everything after the cursor, cursor excluded. */
    return path + cursor + 1;
}

/************************************ EOF *************************************/
