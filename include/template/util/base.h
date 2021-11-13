/* Include once header guard */
#ifndef TEMPLATE_UTIL_BASE_INCLUDED
#define TEMPLATE_UTIL_BASE_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-16
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

/* Used for size_t. */
#include <stddef.h>

/*********************************** MACROS ***********************************/

/* We define SUCCESS and ERROR that will be used to make our return codes more
 * explicit. */
#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef ERROR
#define ERROR -1
#endif

#ifndef WARNING
#define WARNING -2
#endif

/* We define some constant for the use of the occurence function. */
#ifndef FIRST_OCCURENCE
#define FIRST_OCCURENCE 1
#endif

#ifndef LAST_OCCURENCE
#define LAST_OCCURENCE 0
#endif

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

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
size_t occurence(const char *string, char letter, int first);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
