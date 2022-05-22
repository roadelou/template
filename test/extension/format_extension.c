/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2022-05-22
* Language: C Source
* Compiler: cc (GCC) 12.1.1 20220507 (Red Hat 12.1.1-1)
*/

/********************************** INCLUDES **********************************/

/* Used for the testing macros. */
#include <template/test.h>

/* Used to silence the log function. */
#include <template/util.h>

/* The library under test. */
#include <template/extension/format_extension.h>

/* Used for the EXIT_SUCCESS value. */
#include <stdlib.h>

/* Used for strncpy. */
#include <string.h>

/* Used for mkdir and the enum for the mode definition. */
#include <sys/stat.h>

/* Used for fputs and remove. */
#include <stdio.h>

/********************************* SINGLETONS *********************************/

/* Some MACRO magic to define the files we want to create and the directory
 * where they will live. */
#define PATH_ROOT ".test.format_string."
#define TEST_HOME PATH_ROOT "full."
#define TEST_EMPTY PATH_ROOT "empty."
/* We imagine that this path doesn't exist. */
#define TEST_INVALID PATH_ROOT "invalid."
#define FILE_FOO TEST_HOME "/foo.template"
#define FILE_BAR_FOO TEST_HOME "/bar.foo.template"
#define FILE_BAZ TEST_HOME "/baz.template"

/********************************* PROTOYPES **********************************/

/* Description
 * ===========
 * This helper function is used to set up the test environment. It will create a
 * directory where some controlled template files exist.
 * */
static void set_test_environment(void);

/* Description
 * ===========
 * This function is used to clean the environment once the test is over.
 * */
static void unset_test_environment(void);

/* Description
 * ===========
 * This function is used to test the implementation of format_extension.
 * */
static void test_format_extension(void);

/************************************ MAIN ************************************/

int main(int argc, char **argv) {
	/* Silencing the log function. */
	set_log_level(ERROR_MSG);
	/* Setting up the environment. */
	set_test_environment();
	/* Running the tests. */
	test_format_extension();
	/* Cleaning up the environment. */
	unset_test_environment();
	return EXIT_SUCCESS;
}

/********************************* FUNCTIONS **********************************/

static void set_test_environment(void) {
	/* We start by creating a temporary directory. */
	char *test_home = TEST_HOME;
	mkdir(test_home, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	/* We also create an empty directory. */
	test_home = TEST_EMPTY;
	mkdir(test_home, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	/* We create the empty template files. */
	FILE *file_handle = fopen(FILE_FOO, "w");
	fputs("TEST_FOO_STRING", file_handle);
	fclose(file_handle);
	/* The second file. */
	file_handle = fopen(FILE_BAR_FOO, "w");
	fputs("TEST_BAR_FOO_STRING", file_handle);
	fclose(file_handle);
	/* The last file. */
	file_handle = fopen(FILE_BAZ, "w");
	fputs("TEST_BAZ_STRING", file_handle);
	fclose(file_handle);
}

static void unset_test_environment(void) {
	/* We start by removing every file. */
	remove(FILE_FOO);
	remove(FILE_BAR_FOO);
	remove(FILE_BAZ);
	remove(TEST_HOME);
	remove(TEST_EMPTY);
}


static void test_format_extension(void) {
	/* Testing the function with a NULL search path. */
	struct List *test_search_path = NULL;
	/* Test with NULL extension. */
	char *extension = format_extension(test_search_path, NULL);
	TEST_NULL(extension);
	/* Test with empty extension. */
	extension = format_extension(test_search_path, "");
	TEST_NULL(extension);
	/* Test with simple extension. */
	extension = format_extension(test_search_path, "foo");
	TEST_NULL(extension);
	/* Test with a complex extension. */
	extension = format_extension(test_search_path, "bar.foo");
	TEST_NULL(extension);

	/* Testing the function with an empty search path. */
	test_search_path = new_list(0);
	/* Test with NULL extension. */
	extension = format_extension(test_search_path, NULL);
	TEST_NULL(extension);
	/* Test with empty extension. */
	extension = format_extension(test_search_path, "");
	TEST_NULL(extension);
	/* Test with simple extension. */
	extension = format_extension(test_search_path, "foo");
	TEST_NULL(extension);
	/* Test with a complex extension. */
	extension = format_extension(test_search_path, "bar.foo");
	TEST_NULL(extension);

	/* Testing with an invalid directory in the search path. */
	append_list(test_search_path, TEST_INVALID);
	/* Test with NULL extension. */
	extension = format_extension(test_search_path, NULL);
	TEST_NULL(extension);
	/* Test with empty extension. */
	extension = format_extension(test_search_path, "");
	TEST_NULL(extension);
	/* Test with simple extension. */
	extension = format_extension(test_search_path, "foo");
	TEST_NULL(extension);
	/* Test with a complex extension. */
	extension = format_extension(test_search_path, "bar.foo");
	TEST_NULL(extension);

	/* Testing with an empty directory in the search path. */
	append_list(test_search_path, TEST_EMPTY);
	/* Test with NULL extension. */
	extension = format_extension(test_search_path, NULL);
	TEST_NULL(extension);
	/* Test with empty extension. */
	extension = format_extension(test_search_path, "");
	TEST_NULL(extension);
	/* Test with simple extension. */
	extension = format_extension(test_search_path, "foo");
	TEST_NULL(extension);
	/* Test with a complex extension. */
	extension = format_extension(test_search_path, "bar.foo");
	TEST_NULL(extension);

	/* Testing with a file (not directory) in the search path. */
	append_list(test_search_path, FILE_BAZ);
	/* Test with NULL extension. */
	extension = format_extension(test_search_path, NULL);
	TEST_NULL(extension);
	/* Test with empty extension. */
	extension = format_extension(test_search_path, "");
	TEST_NULL(extension);
	/* Test with simple extension. */
	extension = format_extension(test_search_path, "foo");
	TEST_NULL(extension);
	/* Test with a complex extension. */
	extension = format_extension(test_search_path, "bar.foo");
	TEST_NULL(extension);

	/* Testing with a real search directory. */
	append_list(test_search_path, TEST_HOME);
	/* Test with NULL extension. */
	extension = format_extension(test_search_path, NULL);
	TEST_NULL(extension);
	/* Test with empty extension. */
	extension = format_extension(test_search_path, "");
	TEST_NULL(extension);
	/* Test with simple extension. */
	extension = format_extension(test_search_path, "foo");
	TEST_STRING("TEST_FOO_STRING", extension);
	/* Test with a complex extension. */
	extension = format_extension(test_search_path, "bar.foo");
	TEST_STRING("TEST_BAR_FOO_STRING", extension);
}

/************************************ EOF *************************************/
