/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2021-11-06
* Language: C Source
*/

/********************************** INCLUDES **********************************/

/* The library we are trying to implement. */
#include "template_base.h"

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int occurence(const char *string, char letter, int first) {
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


/************************************ EOF *************************************/
