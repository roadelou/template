/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2020-10-07
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The header with the function we are trying to implement. */
#include <template/extension/get_extension.h>

/* Used for the occurence and log_message functions. */
#include <template/util.h>

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

const char *get_extension(const char *path) {
    /* EDGE CASE
     * =========
     * The input pointer could be NULL. */
    if (path == NULL) {
        /* We log a warning before failing. */
        log_message(WARNING_MSG,
                    "Internal function `%s` received a null pointer as "
                    "argument and fails.\n",
                    __func__);
        /* We fail as gracefully as we can. */
        return NULL;
    }
    /* The integer we will use to build the returned pointer. */
    size_t cursor;
    /* We try to get the position of the first dot in the path. */
    cursor = occurence(path, '.', FIRST_OCCURENCE);
    if (cursor == -1) {
        /* There is no dot in this path, we look for the last slash for the path
         * separator. */
        cursor = occurence(path, '/', LAST_OCCURENCE);
    }
    /* We return everything after the cursor, cursor excluded. */
    return path + cursor + 1;
}

/************************************ EOF *************************************/
