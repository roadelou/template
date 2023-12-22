/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-06
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The library we are trying to implement. */
#include <template/util/base.h>

/* Used for strlen. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

size_t occurence(const char *string, char letter, int first) {
    /* The length of the string, we shouldn't try to look any further. */
    size_t length = strlen(string);
    /* Now that we know the exact length we call the optimized variant of the 
	 * routine. */
	return occurence_fast(string, letter, first, length);
}

size_t occurence_fast(
	const char *string,
	char letter,
	int first,
	size_t length
) {
    /* The result we will return, it will be set once we find a match. */
    size_t result = -1;
	/* If we search for the first occurence we search forward, otherwise we will
	 * search backwards. This done to avoid branching everytime on first. */
	int increment = first? 1 : -1;
    /* The cursor that we use to go through the string. */
    size_t cursor = first? 0 : length - 1;

    /* We look for a match. As a small optimization, we directly decrement
	 * length (local to this function) to count iterations. */
    for (; length > 0; length--) {
        if (*(string + cursor) == letter) {
            return cursor;
        }
		/* else... */
		cursor += increment;
    }
    return result;
}

/************************************ EOF *************************************/
