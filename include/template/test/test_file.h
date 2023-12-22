/* Include once header guard */
#ifndef YOUR_HEADER_GUARD
#define YOUR_HEADER_GUARD

/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2023-12-22
* Language: C Header
* Compiler: cc (Debian 12.2.0-14) 12.2.0
*/

/********************************** INCLUDES **********************************/

/* Used for the FILE definition. */
#include <stdio.h>

/*********************************** MACROS ***********************************/

/**
Description
===========
Tests that the content of the text file matches the expected one. Returns the
result of the equality test, and logs a warning message on error. The location
of the test will also be displayed.

Arguments
=========
 - expected: The expected value, should be a null-terminated string.
 - computed: The path of the file whose content should be checked.

Returns
=======
1 if the test passed, 0 otherwise.

Side-effects
============
Prints the information about the test in the expected CSV format.
*/
#define TEST_FILE(expected, computed)                                        \
    test_file_function(expected, computed, __LINE__, __FILE__, __func__)

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/**
Description
===========
Tests that the content of a tex tfile matches the expected one. Returns the
result of the equality test, and logs a warning message on error. Implementation
of the TEST_FILE macro.

Arguments
=========
 - expected: The expected value, should be a null-terminated string.
 - computed: FILE handle whose content should be tested, should be in read mode.
 - line: The number of the line of code associated with the test.
 - file: The name of the file associated with the test.
 - function: The name of the function associated with the test.

Returns
=======
1 if the test passed, 0 otherwise.

Side-effects
============
Prints the information about the test in the expected CSV format.
*/
int test_file_function(const char *expected, FILE *computed, int line,
                         const char *file, const char *function);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
