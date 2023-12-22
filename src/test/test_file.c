/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2023-12-22
* Language: C Source
* Compiler: cc (Debian 12.2.0-14) 12.2.0
*/

/********************************** INCLUDES **********************************/

/* The library we are implementing. */
#include <template/test/test_file.h>

/* Used to test string equality. */
#include <template/test/test_string.h>

/* Used for printf. */
#include <stdio.h>

/* Used for the string manipulations. */
#include <string.h>

/* Used for malloc. */
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int test_file_function(const char *expected, FILE *computed, int line,
                         const char *file, const char *function) {
	/* The length of the string we expect. */
	size_t length = strlen(expected);
	/* A buffer with the content of the text file. The +1 is for the termination
	 * byte. */
	char *buffer = malloc((length + 1) * sizeof(char));
	/* We zero the initial array since fread won't do it. */
	memset(buffer, '\0', (length + 1) * sizeof(char));
	// DEBUG
	test_string_function("", buffer, line, file, function);
	/* Whether the test passed or not. */
	int status = 0;

	/* The number of bytes we read from the tested file. */
	size_t read_bytes = fread(buffer, 1, length, computed);

	/* If we didn't get enough bytes the test fails, otherwise we keep
	 * going. */
	if (read_bytes == length) {
		/* We reuse the code for the test_string function at this point. */
		status = test_string_function(expected, buffer, line, file, function);
		/* We free the memory we used for the content of the file. */
		free(buffer);
		/* We propagate the status to our caller. */
		return status;
	}

	/* If we reach this line then the test has failed. */

    /* We print a CSV line for the status of the test. */
    printf("FAILED;%s;%s;%d;%s;%s\n", file, function, line, expected, buffer);

	/* Freeing the memory we had used. */
	free(buffer);
    return 0;
}

/************************************ EOF *************************************/
