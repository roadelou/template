/* Include once header guard */
#ifndef TEMPLATE_FORMAT_SAFE_FORMAT_INCLUDED
#define TEMPLATE_FORMAT_SAFE_FORMAT_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-13
 * Language: C Header
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* Used for the FILE declaration. */
#include <stdio.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/**
Description
===========
Safe implementation of a format function for the template files.

Arguments
=========
 - stream: The file stream to which the content of the string should be written.
 - format: The format string to use to create the templated file.
 - author: The name of the author to use for the template.
 - contact: The name of the contact to use for the template.
 - date_now: The date string to use for the template.

Returns
=======
SUCCESS if the file could be written, ERROR otherwise.

Note
====
About the format string, the special character used is '%' like in printf, but
for the sake of safety the formatting is much simpler:
 - %1 will be replaced by the author value,
 - %2 will be replaced by the contact value,
 - %3 will be replaced by the current date,
 - %% will be replaced by a single %,
 - any other occurence of '%' will be left as is.
*/
int safe_format(FILE *stream, const char *format, const char *author,
                const char *contact, const char *date_now);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
