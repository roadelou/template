/* Include once header guard */
#ifndef TEMPLATE_LIST_INCLUDED
#define TEMPLATE_LIST_INCLUDED

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
    char *strings;
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
//  should outlive the list, as they are passed by reference and not copied.
//
// Returns
// =======
// A pointer to the new heap-allocated list containing pointer references to the
// provided strings.
//
struct List *new_list(size_t length, ...);

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
// The "length" field of the list is reset to 0 and the memory allocated for the
// list is collected. The "strings" field becomes NULL. Note that the strings
// themselves are left untouched.
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
// Since the list will now contain a reference to the element, it is important
// that the element outlives the list.
//
void append_list(struct List *list, char *element);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
