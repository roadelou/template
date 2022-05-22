/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2022-05-22
* Language: C Source
* Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
*/

/********************************** INCLUDES **********************************/

/* The library we are implementing. */
#include <template/test/test_null.h>

/* Used for printf. */
#include <stdio.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int test_null_function(void *computed, int line,
                          const char *file, const char *function) {
    /* The result of the equality test. */
    int result = (NULL == computed);
    /* A string telling whether the test failed or not. */
    char *status;
    if (result) {
        status = "PASSED";
    } else {
        status = "FAILED";
    }
    /* We print a CSV line for the status of the test. */
    printf("%s;%s;%s;%d;%p;%p\n", status, file, function, line, NULL,
           computed);
    return result;
}

/************************************ EOF *************************************/
