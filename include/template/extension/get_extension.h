/* Include once header guard */
#ifndef TEMPLATE_EXTENSION_GET_EXTENSION_INCLUDED
#define TEMPLATE_EXTENSION_GET_EXTENSION_INCLUDED

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

/**
Deprecated
==========
Use get_format_extension instead.

Description
===========
Returns the extension part of the given path, excluding the dot. If there is no
dot in the filename, then the complete filename will be returned instead.

Arguments
=========
 - path: The path in which we are searching an extension.

Returns
=======
The pointer to the extension part of the provided path.

Note
====
This function does not allocate memory for the returned pointer, instead it
returns the initial pointer shifted by some bytes.

Examples
========
get_extension("example.txt") -> "txt"
get_extension("foo/bar/example.txt") -> "txt"
get_extension("Makefile") -> "Makefile"
get_extension("foo/bar/Makefile") -> "Makefile"
get_extension("example.foo.bar") -> "foo.bar"
*/
const char *get_extension(const char *path);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
