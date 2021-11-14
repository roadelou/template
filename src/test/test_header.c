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
#include <template/test/test_header.h>

/* Used for printf. */
#include <stdio.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

void test_header(void) {
    printf("%s;%s;%s;%s;%s;%s\n", "STATUS", "FILE", "FUNCTION", "LINE",
           "EXPECTED", "COMPUTED");
}

/************************************ EOF *************************************/
