/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-14
 * Language: C Source
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* Used for the testing macros. */
#include <template/test.h>

/* The library under test. */
#include <template/extension/extension_match.h>

/* Used for the EXIT_SUCCESS value. */
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Test for the next_extension_part function. */
void test_next_extension_part(void);

/* Test for the directory_part_size function. */
void test_directory_part_size(void);

/* Test for the correct_ending function. */
void test_correct_ending(void);

/* Test for the extension_match_size function. */
void test_extension_match_size(void);

/************************************ MAIN ************************************/

int main(int argc, char **argv) {
    test_next_extension_part();
    // test_directory_part_size();
    // test_correct_ending();
    // test_extension_match_size();
    return EXIT_SUCCESS;
}

/********************************* FUNCTIONS **********************************/

void test_next_extension_part(void) {
    /* Cursor argument for the function. */
    size_t cursor;

    /* Testing documentation examples. */
    /* BACWARDS examples. */
    cursor = 16;
    TEST_INTEGER(
        13, (int)next_extension_part("test/foo.bar.baz", &cursor, BACKWARDS));
    TEST_INTEGER(16, cursor);

    cursor = 13;
    TEST_INTEGER(
        9, (int)next_extension_part("test/foo.bar.baz", &cursor, BACKWARDS));
    TEST_INTEGER(12, cursor);

    cursor = 9;
    TEST_INTEGER(
        5, (int)next_extension_part("test/foo.bar.baz", &cursor, BACKWARDS));
    TEST_INTEGER(8, cursor);

    cursor = 5;
    TEST_INTEGER(
        5, (int)next_extension_part("test/foo.bar.baz", &cursor, BACKWARDS));
    TEST_INTEGER(5, cursor);

    /* FORWARDS examples. */
    cursor = 5;
    TEST_INTEGER(5,
                 (int)next_extension_part("test/bar.foo", &cursor, FORWARDS));
    TEST_INTEGER(8, cursor);

    cursor = 8;
    TEST_INTEGER(9,
                 (int)next_extension_part("test/bar.foo", &cursor, FORWARDS));
    TEST_INTEGER(12, cursor);

    cursor = 12;
    TEST_INTEGER(12,
                 (int)next_extension_part("test/bar.foo", &cursor, FORWARDS));
    TEST_INTEGER(12, cursor);

    cursor = 0;
    TEST_INTEGER(0,
                 (int)next_extension_part("test/bar.foo", &cursor, FORWARDS));
    TEST_INTEGER(8, cursor);

    /* Testing empty string. */
    cursor = 0;
    TEST_INTEGER(0, (int)next_extension_part("", &cursor, BACKWARDS));
    TEST_INTEGER(0, cursor);

    cursor = 0;
    TEST_INTEGER(0, (int)next_extension_part("", &cursor, FORWARDS));
    TEST_INTEGER(0, cursor);
}

/************************************ EOF *************************************/
