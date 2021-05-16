/* Include once header guard */
#ifndef ASSOCIATIVE_ARRAY_INCLUDED
#define ASSOCIATIVE_ARRAY_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-16
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

// Used for the size_t type.
#include <stddef.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

// Description
// ===========
// Creates the associative array with the provided values. Under the hood, the
// POSIX hcreate function is used. There can only be a single associative array
// at a time, and it is immutable. Note that copies of the keys and values are
// created.
//
// Arguments
// =========
//  - length: The number of key-value pairs to insert in the hashmap.
//  - keys: The array of pointers to use as keys. Should hold "length" keys. No
//  two keys should be identical.
//  - values: The array of values associated with the keys. Should hold "length"
//  values.
//
// Returns
// =======
// SUCCESS if the initialization could be perfomed, ERROR otherwise. This call
// could fail if the system runs out of memory.
//
// Notes
// =====
// The function doesn't return any hypothetical "AssociativeArray" instances,
// instead it initializes the global one provided by POSIX.
//
int new_associative_array(size_t length, const char **keys,
                          const char **values);

// Description
// ===========
// Searches the values associated with the given key in the global associative
// array. The POSIX hsearch is used under the hood.
//
// Arguments
// =========
//  - key: The key for which we should find the value.
//
// Returns
// =======
// NULL if the key is not associated with any value or the expected value. Note
// that the string returned in case of success is heap-allocated and owned by
// the associative array, hence the caller should not attempt to free not modify
// it.
//
const char *search_associative_array(char *key);

// Description
// ===========
// Destructor for the global associative array. The POSIX hdestroy is called
// under the hood. The strings owned by the associative array are also
// collected.
//
void delete_associative_array(void);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
