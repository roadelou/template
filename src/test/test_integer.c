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
#include <template/test/test_integer.h>

/* Used for printf. */
#include <stdio.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int test_integer_function(int expected, int computed, int line,
                          const char *file, const char *function) {
    /* The result of the equality test. */
    int result = (expected == computed);
    /* A string telling whether the test failed or not. */
    char *status;
    if (result) {
        status = "PASSED";
    } else {
        status = "FAILED";
    }
    /* We print a CSV line for the status of the test. */
    printf("%s;%s;%s;%d;%d;%d\n", status, file, function, line, expected,
           computed);
    return result;
}

/************************************ EOF *************************************/
