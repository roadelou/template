/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-14
 * Language: C Source
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* The library we are implementing. */
#include <template/test/test_string.h>

/* Used for printf. */
#include <stdio.h>

/* Used for the string manipulations. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int test_string_function(const char *expected, const char *computed, int line,
                         const char *file, const char *function) {
	/* The length of the string we expect. */
	size_t length = strlen(expected);
    /* The result of the equality test. */
    int result = strncmp(expected, computed, length) == 0;
    /* A string telling whether the test failed or not. */
    char *status;
    if (result) {
        status = "PASSED";
    } else {
        status = "FAILED";
    }
    /* We print a CSV line for the status of the test. */
    printf("%s;%s;%s;%d;%s;%s\n", status, file, function, line, expected,
           computed);
    return result;
}

/************************************ EOF *************************************/
