/* Include once header guard */
#ifndef TEMPLATE_EXTENSION_GET_FORMAT_EXTENSION_INCLUDED
#define TEMPLATE_EXTENSION_GET_FORMAT_EXTENSION_INCLUDED

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

/*
Description
===========
Returns the extension of the template file which has the largest common suffix
with the provided path. This is used to find the template file which should be
used for a given file and replaces the use of the older "get_extension". Note
that only whole chunk matches are counted, where a whole chunk is a part of a
string between two '.'. This is clarified in the examples.

Arguments
=========
 - list: The search path, i.e. list of directories in which we should find the
 template files.
 - path: The path of the file for which we want the template file extension.

Returns
=======
The part of the argument string corresponding to the identified extension. If
not template file is found, NULL is returned instead. The returned string is
dynamically allocated and needs to be freed by the caller.

Examples
========
Lets assume that in the search path of the tool one can find three template
files:
 - txt.template: For txt files.
 - c.template: For C source files.
 - c.gplv3.template: For C source files with a gplv3 header.

Then the behavior for this function will be:
get_format_extension("example.foo") -> NULL
get_format_extension("txt") -> "txt"
get_format_extension("foo.gplv3.c") -> "gplv3.c"
get_format_extension("foo_v3.c") -> ".c"	// Because "gplv3" isn't a whole
match.
*/
char *get_format_extension(const struct List *list, const char *path);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
