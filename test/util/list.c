/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-14
 * Language: C Source
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* The testing macros. */
#include <template/test.h>

/* The library under test. */
#include <template/util/list.h>

/* Used for the EXIT_SUCCESS value. */
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Testing the new_list function. */
void test_new_list(void);

/* Testing the delete_list function. */
void test_delete_list(void);

/* Testing the append_list function. */
void test_append_list(void);

/************************************ MAIN ************************************/

int main(int argc, const char **argv) {
    test_new_list();
    test_delete_list();
    test_append_list();
}

/********************************* FUNCTIONS **********************************/

void test_new_list(void) {
    /* Testing empty list creation. */
    struct List *test_list = new_list(0);

    TEST_INTEGER(0, test_list->length);

    /* Freing the memory. */
    delete_list(test_list);

    /* Testing normal list. */
    test_list = new_list(2, "rouge", "bleu");

    TEST_INTEGER(2, test_list->length);
    TEST_STRING("rouge", *(test_list->strings + 0));
    TEST_STRING("bleu", *(test_list->strings + 1));

    /* Freing the memory. */
    delete_list(test_list);

    /* Testing list with empty string. */
    test_list = new_list(2, "rouge", "");

    TEST_INTEGER(2, test_list->length);
    TEST_STRING("rouge", *(test_list->strings + 0));
    TEST_STRING("", *(test_list->strings + 1));

    /* Freing the memory. */
    delete_list(test_list);
}

void test_delete_list(void) {
    /* Testing empty list deletion. */
    struct List *test_list = new_list(0);

    /* Freing the memory. */
    delete_list(test_list);

    TEST_INTEGER(0, test_list->length);
    TEST_INTEGER(1, NULL == test_list->strings);

    /* Testing normal list. */
    test_list = new_list(2, "rouge", "bleu");

    /* Freing the memory. */
    delete_list(test_list);

    TEST_INTEGER(0, test_list->length);
    TEST_INTEGER(1, NULL == test_list->strings);
}

void test_append_list(void) {
    /* Testing append to empty list. */
    struct List *test_list = new_list(0);

    append_list(test_list, "rouge");

    TEST_INTEGER(1, test_list->length);
    TEST_STRING("rouge", *(test_list->strings + 0));

    /* Freing the memory. */
    delete_list(test_list);

    /* Testing normal list. */
    test_list = new_list(2, "rouge", "bleu");

    append_list(test_list, "vert");

    TEST_INTEGER(3, test_list->length);
    TEST_STRING("rouge", *(test_list->strings + 0));
    TEST_STRING("bleu", *(test_list->strings + 1));
    TEST_STRING("vert", *(test_list->strings + 2));

    /* Freing the memory. */
    delete_list(test_list);

    /* Testing append list with empty string. */
    test_list = new_list(2, "rouge", "bleu");

    append_list(test_list, "");

    TEST_INTEGER(3, test_list->length);
    TEST_STRING("rouge", *(test_list->strings + 0));
    TEST_STRING("bleu", *(test_list->strings + 1));
    TEST_STRING("", *(test_list->strings + 2));

    /* Freing the memory. */
    delete_list(test_list);
}

/************************************ EOF *************************************/
