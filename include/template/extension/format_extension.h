/* Include once header guard */
#ifndef TEMPLATE_EXTENSION_FORMAT_INCLUDED
#define TEMPLATE_EXTENSION_FORMAT_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-13
 * Language: C Header
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* Used for the List type declaration. */
#include <template/util/list.h>

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
Looks in the filesystem for the appropriate format string to use for the given
extension. The template file for the extension <ext> will be searched first in
the user specific location (HOME)/.config/roadelou_template/<ext>.template, and
if no suitable template is found then the system-wide location
/etc/roadelou_template/<etc>.template will be used.

The template files are specified with printf-inspired format strings, see
safe_format for more details.

Arguments
=========
 - list: The search path, i.e. list of directories in which we should find the
 template files.
 - extension: The file extension for which we are trying to find the format
 string.

Returns
=======
The allocated format string if it was found, NULL otherwise.

Note
====
The pointer returned by this function has to be freed later on.
*/
char *format_extension(const struct List *list, const char *extension);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
