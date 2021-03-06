#ifndef TEMPLATE_LIBRARY_INCLUDED
#define TEMPLATE_LIBRARY_INCLUDED

/* Used to write the templated file. */
#include <stdio.h>

/* Used for string manipulations (strlen for instance). */
#include <string.h>

/* Used for time related manipulations, including getting the current date. */
#include <time.h>

/* Used to get access to environment variables for the user name and contact. */
#include <stdlib.h>

/* We define SUCCESS and ERROR that will be used to make our return codes more
 * explicit. */
#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef ERROR
#define ERROR -1
#endif

/*
Description
===========
Stores a string representation of the current date in the provided buffer. The
date is provided according to the ISO 8601 format (YYYY-MM-DD).

Arguments
=========
 - buffer: The buffer in which the string representation of the current date
	will be stored. The buffer should be at least 11 bytes wide to fit the
	entire date and the null terminating byte.

Returns
=======
SUCCESS if the call succeeded, ERROR otherwise.
*/
int date_now(char *buffer);

/*
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

/*
Description
===========
Looks in the filesystem for the appropriate format string to use for the given
extension. The template file for the extension <ext> will be searched first in
the user speicfic location $(HOME)/.config/roadelou_template/<ext>.template, and
if no suitable template is found then the system-wide location
/etc/roadelou_template/<etc>.template will be used.

The template files are specified with printf-inspired format strings, see
safe_format for more details.

Arguments
=========
 - extension: The file extension for which we are trying to find the format
	string.

Returns
=======
The allocated format string if it was found, NULL otherwise.

Note
====
The pointer returned by this function has to be freed later on.
*/
char *format_extension(const char *extension);

/*
Description
===========
Safe implementation of a format function for the template files.

Arguments
=========
 - stream: The file stream to which the content of the string should be written
	to.
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

#endif /* end of include guard: TEMPLATE_LIBRARY_INCLUDED */
