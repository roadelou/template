/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2022-05-23
 * Language: C Source
 * Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
 */

/********************************** INCLUDES **********************************/

/* Used for the testing macros. */
#include <template/test.h>

/* The library under test. */
#include <template/extension/get_extension.h>

/* Used for set_log_level. */
#include <template/util.h>

/* Used for the EXIT_SUCCESS value. */
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Test for the get_extension function. */
void test_get_extension(void);

/************************************ MAIN ************************************/

int main(int argc, char **argv) {
    /* We silence the logging from the called functions. */
    set_log_level(ERROR_MSG);
    /* We run the test. */
    test_get_extension();
    return EXIT_SUCCESS;
}

/********************************* FUNCTIONS **********************************/

void test_get_extension(void) {
    /* Test with NULL. */
    TEST_NULL((void *)get_extension(NULL));

    /* Test with empty string. */
    TEST_STRING("", get_extension(""));

    /* Test with single dot. */
    TEST_STRING("", get_extension("."));

    /* Test with leading dot. */
    TEST_STRING("foo", get_extension(".foo"));

    /* Test with dot and slash. */
    TEST_STRING("", get_extension("/."));

    /* Tests from the header documentation of `get_extension`. */
    TEST_STRING("txt", get_extension("example.txt"));
    TEST_STRING("txt", get_extension("foo/bar/example.txt"));
    TEST_STRING("Makefile", get_extension("Makefile"));
    TEST_STRING("Makefile", get_extension("foo/bar/Makefile"));
    TEST_STRING("foo.bar", get_extension("example.foo.bar"));
}

/************************************ EOF *************************************/
