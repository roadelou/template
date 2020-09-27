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
Creates a templated text file at the given path. Thi is the default template
used when the file type is not recognized.

Arguments
=========
 - path: The path where the file should be written. If the file already exists,
it will be overwritten.
 - author: The name of the author of this file, will be used as the first
contributor.
 - contact: The contact to use to reach the original author, if needs be.

Returns
=======
SUCCESS if the call was a success, ERROR otherwise.
*/
int template_blank(const char *path, const char *author, const char *contact);

/*
Description
===========
Same as template_blank, but for C source files.
*/
int template_c(const char *path, const char *author, const char *contact);

/*
Description
===========
Same as template_blank, but for C header files.
*/
int template_header(const char *path, const char *author, const char *contact);

/*
Description
===========
Same as template_blank, but for Makefiles.
*/
int template_makefile(const char *path, const char *author,
                      const char *contact);

/*
Description
===========
Same as template_blank, but for python files.
*/
int template_python(const char *path, const char *author, const char *contact);

/*
Description
===========
Same as template_blank, but for perl scripts.
*/
int template_perl(const char *path, const char *author, const char *contact);

/*
Description
===========
Same as template_blank, but for bash scripts.
*/
int template_bash(const char *path, const char *author, const char *contact);

/*
Description
===========
Same as template_blank, but for markdown documents.
*/
int template_markdown(const char *path, const char *author,
                      const char *contact);

#endif /* end of include guard: TEMPLATE_LIBRARY_INCLUDED */
