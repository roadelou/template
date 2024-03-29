/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-14
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

// The header we are trying to implement.
#include <template/util/list.h>

// Used for the ERROR and SUCCESS values.
#include <template/util/base.h>

// Used for malloc, free and realloc.
#include <stdlib.h>

// Used for the variadic constructor.
#include <stdarg.h>

// Used for strlen and strncpy.
#include <string.h>

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
    // Variable used to hold the length of various arguments.
    size_t argument_length;
    //
    // Variable used to temporarily store the arguments when they are being
    // copied.
    char *argument;
    //
    // We also create a variadic list to go through the provided arguments.
    va_list strings_argument;
    //
    // We set the length of the list.
    list->length = length;
    //
    // We allocate the memory for the pointers held in the List.
    list->strings = malloc(length * sizeof(char *));
    //
    // We start going through the variadic arguments by providing the address of
    // the last fixed argument.
    va_start(strings_argument, length);
    //
    // We go throught the "length" next variadic arguments and add them to the
    // list.
    for (size_t i = 0; i < length; i++) {
        // We first get the next variadic argument.
        argument = va_arg(strings_argument, char *);
        //
        // EDGE CASE
        // =========
        // If an argument is NULL, we still add it but without going through the
        // string operations.
        if (argument == NULL) {
            //
            // We set NULL for the element.
            *(list->strings + i) = NULL;
            //
            // We move to the next element directly.
            continue;
        }
        //
        // We compute the length of the argument.
        argument_length = strlen(argument);
        //
        // We allocate enough memory to hold a copy of the argument.
        *(list->strings + i) = malloc((argument_length + 1) * sizeof(char));
        //
        // We copy the content of the original argument to its List-owned copy.
        strncpy(*(list->strings + i), argument, argument_length);
        //
        // We add the trailing newline character at the end of the list-owned
        // string.
        *(*(list->strings + i) + argument_length) = '\0';
    }
    //
    // We close the variadic macro.
    va_end(strings_argument);
    //
    // We return the built list.
    return list;
}

struct List *null_list(size_t length) {
    // We first create the list we are going to return.
    struct List *list = malloc(sizeof(struct List));
    //
    // We set the length of the string as indicated.
    list->length = length;
    //
    // We allocate the memory for the pointers held in the List.
    list->strings = malloc(length * sizeof(char *));
    //
    // We set every pointer to NULL.
    for (size_t i = 0; i < length; i++) {
        *(list->strings + i) = NULL;
    }
    //
    // We return the built List.
    return list;
}

void delete_list(struct List *list) {
    // Sanity checks, if the provided pointer is NULL we do nothing.
    if (list == NULL) {
        //
        // Assembly-style return, we do nothing here.
        return;
    }
    //
    // EDGE CASE
    // =========
    // If the strings pointer is NULL, probably because the list has already
    // been freed once, we don't attempt to free it again.
    if (list->strings == NULL) {
        //
        // Just in case, we set the lenght of the list to 0.
        list->length = 0;
        //
        // Assembly-style return.
        return;
    }
    //
    // We free all the strings owned by this list.
    for (int i = 0; i < list->length; i++) {
        //
        // If an element of the list is NULL, we skip it and don't attempt to
        // free it.
        if (*(list->strings + i) != NULL) {
            free(*(list->strings + i));
        }
    }
    //
    // We free the allocated memory for the pointer to the strings of the list.
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
    //
    // A variable used to store the length of the new element.
    size_t element_length;
    //
    // Sanity checks, if the list is NULL we don't do anything.
    if (list == NULL) {
        //
        // Assembly-style return.
        return;
    }
    //
    // We increment the size of the list for the reallocation.
    list->length++;
    //
    // We grow our list. For now we assume that realloc will never fail, which
    // is quite reasonable given the memory used by the program compared to that
    // of a Linux-capable host.
    list->strings = realloc(list->strings, list->length * sizeof(char *));
    //
    // EDGE CASE
    // =========
    // If the element is NULL, we still add it to the list, but without the
    // complex operations.
    if (element == NULL) {
        *(list->strings + list->length - 1) = NULL;
        //
        // Assembly-style return.
        return;
    }
    //
    // else...
    //
    // We add 1 for the NULL terminating byte.
    element_length = strlen(element) + 1;
    //
    // We allocate some memory to hold the copy of the element.
    *(list->strings + list->length - 1) = malloc(element_length * sizeof(char));
    //
    // We create a copy of the provided element.
    strncpy(*(list->strings + list->length - 1), element, element_length);
    //
    // We add the trailing newline character at the end of the list-owned
    // string.
    *(*(list->strings + list->length - 1) + element_length) = '\0';
}

int move_into_list(struct List *list, size_t index, char *element) {
    // We start by performing some sanity checks.
    if (list == NULL) {
        //
        // We fail here since there is no way to perform the substitution.
        return ERROR;
    }
    //
    // We check if the index is within the bounds of the list.
    if (index >= list->length) {
        //
        // We fail here since their is no spot to move the element into.
        return ERROR;
    }
    //
    // If we reach this line, the move should be possible. We start by freeing
    // the old element from the list. an edge case appears if the element was
    // NULL, (which is likely given where this function is called in template).
    if (*(list->strings + index) != NULL) {
        free(*(list->strings + index));
    }
    //
    // We insert the provided string into the list. It will be freed when the
    // destructor of the list is called. This will work as expected even if
    // element == NULL.
    *(list->strings + index) = element;
    return SUCCESS;
}

/************************************ EOF *************************************/
