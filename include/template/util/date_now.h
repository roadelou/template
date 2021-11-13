/* Include once header guard */
#ifndef TEMPLATE_UTIL_DATE_INCLUDED
#define TEMPLATE_UTIL_DATE_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-13
 * Language: C Header
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* The includes for your header go here */

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/*
Description
===========
Stores a string representation of the current date in the provided buffer. The
date is provided according to the ISO 8601 format (YYYY-MM-DD).

Arguments
=========
 - buffer: The buffer in which the string representation of the current date
 will be stored. The buffer should be at least 11 bytes wide to fit the entire
 date and the null terminating byte.

Returns
=======
SUCCESS if the call succeeded, ERROR otherwise.
*/
int date_now(char *buffer);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
