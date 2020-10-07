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
Creates a styled title line (excluding the EOL character) and puts it in the
given buffer.

Arguments
=========
 - buffer: The buffer where the build line should be written. The size of this
buffer should be at least length + 1 (for the null termination).
 - word: The word to put in the middle of the line, should be a null-terminated
string.
 - symbol: The symbol used to fill the line.
 - length: The visible length of the line.

Returns
=======
SUCCESS if the call was a success, ERROR otherwise.

Example
=======
The call title(buffer, "WORD", '*', 80) would build the line:

************************************* WORD *************************************
*/
int title(char *buffer, const char *word, const char symbol,
          const size_t length);

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
extension. The template file for the extension <ext> should be
$(HOME)/.config/roadelou_template/<ext>.template. The template files are in fact
printf format strings.

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

#endif /* end of include guard: TEMPLATE_LIBRARY_INCLUDED */
