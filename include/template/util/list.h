/* Include once header guard */
#ifndef TEMPLATE_UTIL_LIST_INCLUDED
#define TEMPLATE_UTIL_LIST_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-14
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

// Used for size_t
#include <stddef.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

// Description
// ===========
// A structure used to represent a list of strings. This is used at various
// points in the template codebase, for instance to handle the search path.
//
// Fields
// ======
//  - length: The number of strings currently present in the list.
//  - strings: The array of null-terminated string held in the list.
//
struct List {
    size_t length;
    char **strings;
};

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

// Description
// ===========
// Variadic list constructor.
//
// Arguments
// =========
//  - length: The number of elements to build the list with.
//  - ...: A list of null-terminated strings. The number of arguments given
//  should be equal to the value given as the length argument. The strings
//  are copied into heap-allocated buffers.
//
// Returns
// =======
// A pointer to the new heap-allocated list containing pointer references to
// heap-allocated copies of the provided strings.
//
struct List *new_list(size_t length, ...);

// Description
// ===========
// Creates a list made of `length` NULL elements. This is used to initialize
// lists of know sizes which are meant to be used with `move_into_list`.
//
// Arguments
// =========
//  - length: The number of elements to build the list with.
//
// Returns
// =======
// A new List of length elements all set to NULL.
//
struct List *null_list(size_t length);

// Description
// ===========
// Destructor for the list struct. Will free the memory associated with the
// given list.
//
// Arguments
// =========
//  - list: A pointer to list whose memory should be collected. This pointer
//  should not be NULL nor a List which has already been collected.
//
// Side-effects
// ============
// All the strings held by the list are freed, and the memory for list itself is
// also collected.
//
void delete_list(struct List *list);

// Description
// ===========
// Adds an element at the end of the provided list.
//
// Arguments
// =========
//  - list: A pointer to the list to which the element should be added.
//  - element: The string which should go at the end of the list.
//
// Notes
// =====
// A copy of the element is allocated on the heap and used for the List.
//
void append_list(struct List *list, char *element);

// Description
// ===========
// Replaces the element of the list at the given index with a new string. The
// string isn't copied and MUST be heap-allocated. The caller loses ownership
// of the string which will be freed when the destructor of the list is called.
//
// Arguments
// =========
//  - list: A pointer to the list to which the element should be set.
//  - index: The index at which the provided string should be placed. It must be
//  smaller than the size of the string, otherwise the replacement won't happen.
//  - element: The heap-allocated string we want to insert in our list.
//
// Returns
// =======
// SUCCESS if the operation worked, ERROR otherwise. In particular, this method
// will fail if the list is too short for the provided index.
//
// Side-effects
// ============
// If the call succeeds, the element is inserted in the string at the provided
// index, replacing any existing string, which is in turn freed. If the call
// fails, the list is left untouched.
//
// Note
// ====
// This function is optimized for performance and shouldn't be used carelessly.
int move_into_list(struct List *list, size_t index, char *element);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
