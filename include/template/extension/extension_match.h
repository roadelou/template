/* Include once header guard */
#ifndef TEMPLATE_EXTENSION_MATCH_INCLUDED
#define TEMPLATE_EXTENSION_MATCH_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-15
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

// Used for the size_t definition.
#include <stddef.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/*
Description
===========
Used to specify the direction to use when matching extensions.

Values
======
 - FORWARD is used for the extension of the input file.
 - BACKWARDS is used for the template file.
*/
enum Direction {
    FORWARDS,
    BACKWARDS,
};

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/*
Description
===========
Returns the number of characters of the longest matching whole extension
between the provided path and template path. Note that the extension is reversed
in the template path. See "next_extension_part" for more details.

Arguments
=========
 - path: The null-terminated ASCII path to the file for which we want the
        matching format extension.
 - template_path: The null-terminated ASCII path to the template file for which
        we are computing the extension match size.

Returns
=======
The number of matchin characters between the two extensions, excluding the
leading '.' or '/'. This count also excludes the '.' between the parts of the
extension.
*/
size_t extension_match_size(const char *path, const char *template_path);

/*
Description
===========
Provides the index of the next chunk of extension from the provided path.

Arguments
=========
 - path: The input path to read the extension from.
 - cursor: The position to start looking for a chunk from.
 - direction: The direction in which the chunk should be read.

Returns
=======
The new position of the cursor in the string. If direction is FORWARD, this will
be the end of the extension chunk, and if direction is BACKWARDS this will be
its beginning. The cursor will also be adjusted to make sure that there are no
'.' between index and cursor - 1, i.e. the string starting from the index of
length cursor - index.

Notes
=====
The function will stop making progress upon encountering a '/' in BACKWARDS mode
or a '\0' in FORWARDS mode.

Examples
========

BACKWARDS examples
==================
next_extension_part("test/foo.bar.baz", 16, BACKWARDS)
 -> returns 13, cursor = 16 (for "baz")
next_extension_part("test/foo.bar.baz", 13, BACKWARDS)
 -> returns  9, cursor = 12 (for "bar")
next_extension_part("test/foo.bar.baz", 9, BACKWARDS)
 -> returns  5, cursor =  8 (for "foo")
next_extension_part("test/foo.bar.baz", 5, BACKWARDS)
 -> returns  5, cursor =  5 (for "")

FORWARDS examples
=================
next_extension_part("test/bar.foo",  5, FORWARDS)
 ->  returns  5, cursor =  8 (for "bar")
next_extension_part("test/bar.foo",  8, FORWARDS)
 ->  returns  9, cursor = 12 (for "bar")
next_extension_part("test/bar.foo",  12, FORWARDS)
 ->  returns 12, cursor = 12 (for "")

Exception examples
==================
next_extension_part("test/bar.foo",  0, FORWARDS)
 ->  returns 0, cursor = 8 (for "test/bar")

Undefined Behaviors
===================
The behavior of the function is undefined if the argument cursor value is larger
than the size of the string or if the value given in direction is not BACKWARDS
or FORWARDS.
*/
size_t next_extension_part(const char *path, size_t *cursor,
                           enum Direction direction);

/*
Description
===========
Implementation of next_extension_part, BACKWARDS case.
*/
size_t next_extension_part_backwards(const char *path, size_t *cursor);

/*
Description
===========
Implementation of next_extension_part, FORWARDS case.
*/
size_t next_extension_part_forwards(const char *path, size_t *cursor);

/*
Description
===========
Finds the length of the directory part of the string, i.e. everything up until
the last '/'.

Arguments
=========
 - path: The NULL-termniated ASCII string of the path.

Returns
=======
The number of characters until the last '/' in the string (included).

Examples
========
directory_part_size("test/foo.bar") -> 5
directory_part_size("foo/bar/baz") -> 8
directory_part_size("foo/bar/baz/") -> 12
directory_part_size("foo.bar.baz") -> 0
*/
size_t directory_part_size(const char *path);

/*
Description
===========
Returns 1 if the path ends with ".template", 0 otherwise.

Arguments
=========
 - path: Null-terminated path to analyse.
*/
int correct_ending(const char *path);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
