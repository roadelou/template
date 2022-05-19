/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2021-11-14
* Language: C Source
* Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
*/

/********************************** INCLUDES **********************************/

/* Used for the test macros. */
#include <template/test.h>

/* The library under test. */
#include <template/util/base.h>

/* Used for EXIT_SUCCESS. */
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Test for the occurence function. */
void test_occurence(void);

/************************************ MAIN ************************************/

int main(int argc, char **argv) {
	test_occurence();
	return EXIT_SUCCESS;
}

/********************************* FUNCTIONS **********************************/

void test_occurence(void) {
	/* No occurence. */
	TEST_INTEGER(-1, occurence("sample text.", '/', FIRST_OCCURENCE));
	TEST_INTEGER(-1, occurence("sample text.", '/', LAST_OCCURENCE));

	/* Middle of string. */
	TEST_INTEGER(5, occurence("sample text.", 'e', FIRST_OCCURENCE));
	TEST_INTEGER(8, occurence("sample text.", 'e', LAST_OCCURENCE));

	/* First character. */
	TEST_INTEGER(0, occurence("sample text.", 's', FIRST_OCCURENCE));
	TEST_INTEGER(0, occurence("sample text.", 's', LAST_OCCURENCE));

	/* Last character. */
	TEST_INTEGER(11, occurence("sample text.", '.', FIRST_OCCURENCE));
	TEST_INTEGER(11, occurence("sample text.", '.', LAST_OCCURENCE));
}

/************************************ EOF *************************************/
