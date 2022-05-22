/* Include once header guard */
#ifndef TEMPLATE_TEST_NULL_INCLUDED
#define TEMPLATE_TEST_NULL_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-05-22
 * Language: C Header
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

/* The includes for your header go here */

/*********************************** MACROS ***********************************/

/*
Description
===========
Tests that the computed pointer value is NULL. Returns the result of the
equality test, and logs a warning message on error. The location of the test
will also be displayed.

Arguments
=========
 - computed: The computed value, should be a pointer.

Returns
=======
1 if the test passed, 0 otherwise.

Side-effects
============
Prints the information about the test in the expected CSV format.
*/
#define TEST_NULL(computed)                                                    \
    test_null_function(computed, __LINE__, __FILE__, __func__)

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/*
Description
===========
Tests that the computed pointer value is NULL. Returns the result of the
equality test, and logs a warning message on error. Implementation of the
TEST_NULL macro.

Arguments
=========
 - computed: The computed value, should be a pointer.
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
int test_null_function(void *computed, int line, const char *file,
                       const char *function);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
