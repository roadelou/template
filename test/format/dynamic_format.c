/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2023-12-22
* Language: C Source
* Compiler: cc (Debian 12.2.0-14) 12.2.0
*/

/********************************** INCLUDES **********************************/

/* Used for the testing macros. */
#include <template/test.h>

/* The library under test. */
#include <template/format/dynamic_format.h>

/* Used for set_log_level. */
#include <template/util.h>

/* Used for the EXIT_SUCCESS value. */
#include <stdlib.h>

/* Used for alloca. */
#include <alloca.h>

/* Used to copy strings. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Test for the dynamic_format function. */
void test_dynamic_format(void);

/* Test for the find_format function. */
void test_find_format(void);

/************************************ MAIN ************************************/

int main(int argc, char **argv) {
	/* We initialize the thread pool, needed by dynamic template. */
    GLOBAL_THREAD_POOL = new_thread_pool(1);
    /* We silence the logging from the called functions. */
    set_log_level(ERROR_MSG);
    /* We run the tests. */
    test_find_format();
    test_dynamic_format();
    return EXIT_SUCCESS;
}

/********************************* FUNCTIONS **********************************/

void test_dynamic_format(void) {
	/* We open a temporary file for all of our tests. */
	FILE *handle = tmpfile();
	/* Used to check the error code of the function. */
	int status;
	/* Used to hold the strings. */
	char *buffer = alloca(100 * sizeof(char));

	/* Testing the function with a NULL FILE. */
	status = dynamic_format("test", NULL);
	TEST_INTEGER(status, ERROR);

	/* Testing the function with a NULL string. */
	status = dynamic_format(NULL, handle);
	rewind(handle);
	TEST_INTEGER(status, ERROR);

	fclose(handle);
	handle = tmpfile();

	/* Testing the function with an EMPTY string. */
	status = dynamic_format("", handle);
	rewind(handle);
	TEST_FILE("", handle);
	TEST_INTEGER(status, SUCCESS);

	fclose(handle);
	handle = tmpfile();
	
	/* Testing the function with a single character. */
	status = dynamic_format("a", handle);
	rewind(handle);
	TEST_FILE("a", handle);
	TEST_INTEGER(status, SUCCESS);

	fclose(handle);
	handle = tmpfile();
	
	/* Testing the function with a long string character. */
	status = dynamic_format("Hello, World!", handle);
	rewind(handle);
	TEST_FILE("Hello, World!", handle);
	TEST_INTEGER(status, SUCCESS);

	fclose(handle);
	handle = tmpfile();
	
	/* Testing the function with a partial format string. */
	status = dynamic_format("%/test", handle);
	rewind(handle);
	TEST_FILE("%/test", handle);
	TEST_INTEGER(status, WARNING);

	fclose(handle);
	handle = tmpfile();
	
	/* Note that the strings provided to dynamic format need to be writable
	 * if they contain a format specifier, so they cannot be litteral
	 * strings. */
	strcpy(buffer, "%/echo test/");

	/* Testing the function with a valid format string. */
	status = dynamic_format(buffer, handle);
	rewind(handle);
	TEST_FILE("test", handle);
	TEST_INTEGER(status, SUCCESS);

	fclose(handle);
}

void test_find_format(void) {
    /* We create a MatchList for the tests. */
    struct MatchList match_list;
	/* Used to check the error code of the function. */
	int status;

	/* We test the function with a valid text but a NULL MatchList. */
    status = find_format("text", NULL);
	TEST_INTEGER(status, ERROR);

	/* We test the function with a valid MatchList but a NULL text. */
    status = find_format(NULL, &match_list);
	TEST_INTEGER(status, ERROR);

	/* We test the function with an empty text. */
    status = find_format("", &match_list);
	TEST_INTEGER(status, SUCCESS);
	TEST_INTEGER(match_list.count, 0);

	delete_match_list(&match_list);

	/* We test the function with a single character, but no match. */
    status = find_format("a", &match_list);
	TEST_INTEGER(status, SUCCESS);
	TEST_INTEGER(match_list.count, 0);

	delete_match_list(&match_list);

	/* We test the function with a single character, which is a broken match. */
    status = find_format("%", &match_list);
	TEST_INTEGER(status, WARNING);
	TEST_INTEGER(match_list.count, 0);

	delete_match_list(&match_list);

	/* We test the function with a short text but no match. */
    status = find_format("Hello, World!", &match_list);
	TEST_INTEGER(status, SUCCESS);
	TEST_INTEGER(match_list.count, 0);

	delete_match_list(&match_list);

	/* We test the function with a short text and a broken match. */
    status = find_format("%/test", &match_list);
	TEST_INTEGER(status, WARNING);
	TEST_INTEGER(match_list.count, 0);

	delete_match_list(&match_list);

	/* We test the function with a trailing match of one character. */
    status = find_format("test%", &match_list);
	TEST_INTEGER(status, WARNING);
	TEST_INTEGER(match_list.count, 0);

	delete_match_list(&match_list);

	/* We test the function with a real match. */
    status = find_format("Today is the %$date +%F$.", &match_list);
	TEST_INTEGER(status, SUCCESS);
	TEST_INTEGER(match_list.count, 1);
	TEST_INTEGER(*(match_list.head + 0), 13);
	TEST_INTEGER(*(match_list.tail + 0), 23);

	delete_match_list(&match_list);

	/* We test the function with two matches using different delimiters. */
    status = find_format("%/test/ %!test!", &match_list);
	TEST_INTEGER(status, SUCCESS);
	TEST_INTEGER(match_list.count, 2);
	TEST_INTEGER(*(match_list.head + 0), 0);
	TEST_INTEGER(*(match_list.tail + 0), 6);
	TEST_INTEGER(*(match_list.head + 1), 8);
	TEST_INTEGER(*(match_list.tail + 1), 14);

	delete_match_list(&match_list);
}

/************************************ EOF *************************************/
