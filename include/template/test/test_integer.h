/* Include once header guard */
#ifndef TEMPLATE_TEST_INTEGER_INCLUDED
#define TEMPLATE_TEST_INTEGER_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-14
 * Language: C Header
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* The includes for your header go here */

/*********************************** MACROS ***********************************/

/**
Description
===========
Tests that the computed integer value matches the expected one. Returns the
result of the equality test, and logs a warning message on error. The location
of the test will also be displayed.

Arguments
=========
 - expected: The expected value, should be an integer value.
 - computed: The computed value, also an integer value.

Returns
=======
1 if the test passed, 0 otherwise.

Side-effects
============
Prints the information about the test in the expected CSV format.
*/
#define TEST_INTEGER(expected, computed)                                       \
    test_integer_function(expected, computed, __LINE__, __FILE__, __func__)

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/*
Description
===========
Tests that the computed integer value matches the expected one. Returns the
result of the equality test, and logs a warning message on error. Implementation
of the TEST_INTEGER macro.

Arguments
=========
 - expected: The expected value, should be an integer value.
 - computed: The computed value, also an integer value.
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
int test_integer_function(int expected, int computed, int line,
                          const char *file, const char *function);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
