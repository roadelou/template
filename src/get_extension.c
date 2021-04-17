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

/*
Description
===========
Returns the index of the first or last occurence of a character in a string.

Arguments
=========
 - string: The string in which we are looking for the character.
 - letter: The character we are looking for.
 - first: If set to 0, we return the last occurence. Else we return the first
        occurence.

Returns
=======
The index of the occurence if the letter was found, -1 otherwise.
*/
static int occurence(const char *string, int letter, int first);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int occurence(const char *string, int letter, int first) {
    /* The length of the string, we shouldn't try to look any further. */
    int length = strlen(string);
    /* The result we will return, it will be set once we find a match. */
    int result = -1;
    /* The cursor that we use to go through the string. */
    int cursor;

    /* We look for a match. */
    for (cursor = 0; cursor < length; cursor++) {
        if (*(string + cursor) == letter) {
            result = cursor;
            if (first) {
                break;
            }
        }
    }
    return result;
}

const char *get_extension(const char *path) {
    /* The integer we will use to build the returned pointer. */
    int cursor;
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
