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

/* Used for the SUCCESS and ERROR values. */
#include <template/util/base.h>

/* Used for the EXIT_SUCCESS value. */
#include <stdlib.h>

/* Used for strncpy. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Testing the new_list function. */
void test_new_list(void);

/* Testing the delete_list function is not possible, it acts by side-effect. */

/* Testing the append_list function. */
void test_append_list(void);

/* Testing the move_into_list method. */
void test_move_into_list(void);

/************************************ MAIN ************************************/

int main(int argc, const char **argv) {
    test_new_list();
    test_append_list();
    test_move_into_list();
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

void test_move_into_list(void) {
    /* Defining our variables. */
    struct List *test_list;
    /* Setting the heap-allocated string for the tests. */
    char *buffer = malloc(6 * sizeof(char));
    strncpy(buffer, "rouge", 6);

    /* Test moving into NULL. */
    test_list = NULL;
    TEST_INTEGER(ERROR, move_into_list(test_list, 0, buffer));

    /* Test moving into an empty list. */
    test_list = new_list(0);
    TEST_INTEGER(ERROR, move_into_list(test_list, 0, buffer));
    delete_list(test_list);

    /* Test moving into a list of 1 element. */
    test_list = new_list(1, NULL);
    /* Trying to move within the bounds of the List. */
    TEST_INTEGER(SUCCESS, move_into_list(test_list, 0, buffer));
    TEST_STRING(buffer, *(test_list->strings + 0));
    /* Trying to move outside the bounds of the List. */
    TEST_INTEGER(ERROR, move_into_list(test_list, 1, buffer));
    /* Manually overwriting the list content to avoid freeing the test buffer
     * when delete_list will be called. */
    *(test_list->strings + 0) = NULL;
    delete_list(test_list);

    /* Test moving into a bigger list. */
    test_list = new_list(3, NULL, NULL, NULL);
    /* Trying to move within the bounds of the List. */
    TEST_INTEGER(SUCCESS, move_into_list(test_list, 1, buffer));
    TEST_NULL(*(test_list->strings + 0));
    TEST_STRING(buffer, *(test_list->strings + 1));
    TEST_NULL(*(test_list->strings + 2));
    /* Trying to move outside the bounds of the List. */
    TEST_INTEGER(ERROR, move_into_list(test_list, 3, buffer));
    /* Manually overwriting the list content to avoid freeing the test buffer
     * when delete_list will be called. */
    *(test_list->strings + 1) = NULL;
    delete_list(test_list);

    /* Freeing the test buffer. */
    free(buffer);
}

/************************************ EOF *************************************/
