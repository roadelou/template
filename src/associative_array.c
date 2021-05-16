/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-16
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

// The header we are implementing.
#include <associative_array.h>

// Used for the definitions of SUCCESS and ERROR.
#include <template_base.h>

// Used for malloc and free.
#include <stdlib.h>

// Used for string manipulation.
#include <string.h>

// Used for POSIX associative arrays.
#include <search.h>

/********************************* SINGLETONS *********************************/

// Description
// ===========
// This one-time struct is used to hold some information used for the
// associative array manipulations (in particular freeing the memory) but which
// are not handled by the POSIX functions.
//
// Fields
// ======
//  - length: The number of key-value pairs in the associative array.
//  - keys: Pointers to the heap-allocated key copies.
//  - values: Pointer to the heap-allocated value copies.
//
struct AssociativeArrayInfo {
    size_t length;
    char **keys;
    char **values;
};
//
// We create a global instance of the AssociativeArrayInfo struct.
static struct AssociativeArrayInfo ASSOCIATIVE_ARRAY_INFO;

/********************************* PROTOYPES **********************************/

// Description
// ===========
// Creates a heap-allocated array holding copies of the provided strings.
//
// Arguments
// =========
//  - length: The number of strings in the array.
//  - elements: The list of strings to copy to the new array.
//  - destination: A pointer to the location where the array should be created.
//
// Returns
// =======
// SUCCESS if the destination was correctly updates, ERROR otherwise.
//
static int copy_heap(size_t length, const char **elements, char ***destination);

// Description
// ===========
// Helper function used to free a heap-allocated array created with heap_copy.
//
// Arguments
// =========
//  - length: The number of elements in the array.
//  - destination: A pointer to the array which should be freed.
//
static void delete_heap(size_t length, char ***destination);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int new_associative_array(size_t length, const char **keys,
                          const char **values) {
    // Variable used for error checking.
    int status;
    // Variable to insert key-value pairs in the POSIX associative array.
    ENTRY item;
    //
    // We start by creating copies of all the keys and values in the
    // ASSOCIATIVE_ARRAY_INFO struct.
    ASSOCIATIVE_ARRAY_INFO.length = length;
    //
    // We create heap copies of the argument strings.
    status = copy_heap(length, keys, &ASSOCIATIVE_ARRAY_INFO.keys);
    //
    // Checking for errors.
    if (status == ERROR) {
        // We have no allocated memory, we simply forward the error.
        return ERROR;
    }
    // else...
    //
    // We also create copies of the values.
    status = copy_heap(length, values, &ASSOCIATIVE_ARRAY_INFO.values);
    //
    // Checking for errors.
    if (status == ERROR) {
        // We free the memory associated with the keys.
        delete_heap(length, &ASSOCIATIVE_ARRAY_INFO.keys);
        // We forward the error.
        return ERROR;
    }
    //
    // We initialize the associative array. For the sake of performance, we
    // slightly overestimate the number of elements, as advised by the
    // documentation.
    status = hcreate((5 * length) / 4);
    //
    // Checking for errors. According to the documentation, hcreate returns
    // nonzero on success.
    if (status == 0) {
        // We free the copied strings.
        delete_heap(length, &ASSOCIATIVE_ARRAY_INFO.keys);
        delete_heap(length, &ASSOCIATIVE_ARRAY_INFO.values);
        // We forward the error.
        return ERROR;
    }
    //
    // We insert all the key value pais into the POSIX associative array.
    for (int i = 0; i < length; i++) {
        item.key = *(ASSOCIATIVE_ARRAY_INFO.keys + i);
        item.data = *(ASSOCIATIVE_ARRAY_INFO.values + i);
        //
        // If the key-value pair doesn't already exist, we insert it. We check
        // if the insertion fails at the same time. No error should ever occur
        // here since there was enough space given to hcreate, but we check it
        // defensively.
        if (hsearch(item, ENTER) == NULL) {
            // We destroy the allocated strings and the associative array before
            // returning the error.
            delete_associative_array();
            return ERROR;
        }
    }
    //
    // If we reach this line, the execution was a success.
    return SUCCESS;
}

const char *search_associative_array(char *key) {
    // Variable used to perform the search in the POSIX associative array.
    ENTRY item;
    //
    // We fill the item with our key.
    item.key = key;
    //
    // To avoid a false warning, we initialize the value of data.
    item.data = NULL;
    //
    // We search the associative array and check for errors.
    if (hsearch(item, FIND) == NULL) {
        // The provided key is not bound to any value.
        return NULL;
    } else {
        // We return the expected string, which is allocated on the heap.
        return item.data;
    }
}

void delete_associative_array(void) {
    // We destroy the POSIX associative array.
    hdestroy();
    //
    // We free the heap-allocated copies of the keys and values.
    delete_heap(ASSOCIATIVE_ARRAY_INFO.length, &ASSOCIATIVE_ARRAY_INFO.keys);
    delete_heap(ASSOCIATIVE_ARRAY_INFO.length, &ASSOCIATIVE_ARRAY_INFO.values);
    //
    // We defensively set the length of heap arrays to 0.
    ASSOCIATIVE_ARRAY_INFO.length = 0;
}

// Helper functions.
static int copy_heap(size_t length, const char **elements,
                     char ***destination) {
    // Variable used to hold the length of the elements.
    size_t string_length;
    //
    // Before creating the copies, we need to allocate some memory to hold the
    // pointers to the keys and values. We assume that malloc will never fail
    // here.
    *destination = malloc(length * sizeof(char *));
    //
    // We check if the malloc call failed.
    if (*destination == NULL) {
        // We could not create the heap copy because the system is (probably)
        // out of memory.
        return ERROR;
    }
    //
    // We now go over all the keys and create copies on the heap.
    for (int i = 0; i < length; i++) {
        // We compute the length of the key + 1 is for the NULL terminating
        // byte.
        string_length = strlen(*(elements + i)) + 1;
        //
        // We allocate the memory for the key. We assume that malloc will never
        // fail here.
        *(*destination + i) = malloc(string_length * sizeof(char));
        //
        // We check if malloc failed.
        if (*(*destination + i) == NULL) {
            // There isn't enough memory on the system (apparently) to create
            // the heap-copy. We free all the memory we have allocated so far.
            for (i--; i > 0; i--) {
                free(*(*destination + i));
            }
            //
            // We also free the memory give to the destination array.
            free(*destination);
            //
            // We return an error.
            return ERROR;
        }
        //
        // If the allocation succeeded, we copy the key to the heap.
        strncpy(*(*destination + i), *(elements + i), string_length);
    }
    //
    // If we reach this line, the execution was a success and destinaion can now
    // be used.
    return SUCCESS;
}

static void delete_heap(size_t length, char ***destination) {
    // We first go over each string in the array and free them.
    for (int i = 0; i < length; i++) {
        free(*(*destination) + i);
    }
    //
    // Finally we free the memory associated with the pointer in the array
    // themselves.
    free(*destination);
}
/************************************ EOF *************************************/
