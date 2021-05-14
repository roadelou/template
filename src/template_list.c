/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2021-05-14
* Language: C Source
*/

/********************************** INCLUDES **********************************/

// The header we are trying to implement.
#include <template_list.h>

// Used for malloc, free and realloc.
#include <stdlib.h>

// Used for the variadic constructor.
#include <stdarg.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

// The implementation of the public functions.
struct List *new_list(size_t length, ...) {
	// We first create the list we are going to return.
	struct List *list = malloc(sizeof(struct List));
	//
	// We also create a variadic list to go through the provided arguments.
	va_list strings_argument;
	//
	// We set the length of the list.
	list->length = length;
	//
	// We allocate the memory for the pointers held in the string.
	list->strings = malloc(length * sizeof(char*));
	//
	// We start going through the variadic arguments by providing the address of
	// the last fixed argument.
	va_start(strings_argument, length);
	//
	// We go throught the "length" next variadic arguments and add them to the
	// list.
	for (size_t i=0; i<length; i++) {
		*(list->strings+i) = va_arg(strings_argument, char *);
	}
	//
	// We close the variadic macro.
	va_end(strings_argument);
	//
	// We return the built list.
	return list;
}

void delete_list(struct List *list) {
	// We free the allocated memory for the strings of the list.
	free(list->strings);
	//
	// We defensively set the strings field of the list to NULL.
	list->strings = NULL;
	//
	// We reset the length of the string just in case.
	list->length = 0;
	//
	// Finally we free the memory allocated for the list itself.
	free(list);
}

void append_list(struct List *list, char *element) {
	// We increment the size of the list for the reallocation.
	list->length++;
	//
	// We grow our list. For now we assume that realloc will never fail, which
	// is quite reasonable given the memory used by the program compared to that
	// of a Linux-capable host.
	list->strings = realloc(list->strings, list->length * sizeof(char *));
	//
	// We copy a reference to the provided element at the end of the list.
	*(list->string+list->length-1) = element;
}

/************************************ EOF *************************************/
