/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2020-10-07
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The header containing the functions we are trying to implement. */
#include <template/extension/format_extension.h>

/* Used for the logging functions. */
#include <template/util.h>

/* Used for realloc and free. */
#include <stdlib.h>

/* Used for the file manipulations. */
#include <stdio.h>

/* Used for the string-related functions. */
#include <string.h>

/********************************* PROTOYPES **********************************/

/*
Description
===========
Used to get the size of the provided file.

Arguments
=========
 - file: The FILE handle to the path for which we would like to know the size.

Returns
=======
The size of the provided file if possible, else return -1.
*/
static long file_size(FILE *file);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

long file_size(FILE *file) {
    /* A variable used to store the size of the file before returning it. */
    long returned_size;
    /* We seek the end of the file. */
    fseek(file, 0L, SEEK_END);
    /* We grab the size of the file. */
    returned_size = ftell(file);
    /* We rewind the FILE to its beginning. */
    rewind(file);
    /* We return the file size. */
    return returned_size;
}

char *format_extension(const struct List *list, const char *extension) {
    /* This buffer is used to temporarily store the format paths during the
     * search. It is set to NULL initialy for realloc. */
    char *format_path = NULL;
    /* This variable will hold the number of characters for the format path, it
     * is used for allocation. */
    size_t format_path_length;
    /* This is the buffer that we will dynamically allocate to hold the format
     * string. */
    char *format_string;
    /* The length of the entire template string, used for memory allocation. */
    size_t format_string_length;
    /* The handle to the format file, once we will have opened it. */
    FILE *format_file = NULL;

	/* EDGE CASE
	 * =========
	 * The arguments could be NULL and we have to handle this correctly. */
	if (list == NULL || extension == NULL) {
		/* We log a warining for the user. */
		log_message(WARNING_MSG, "Internal function `%s` received a null pointer as argument and fails.\n", __func__);
		/* we fail to provide a valid template string. */
		return NULL;
	}

    /* We go through all the provided paths in order until we find one where
     * the extension matches what we have been given. */
    for (size_t i = 0; i < list->length; i++) {
        /* We compute the size of the format path. 9 is for ".template" , 1 is
         * for the NULL byte and the last 1 is for the '/'. */
        format_path_length =
            (strlen(*(list->strings + i)) + strlen(extension) + 9 + 1 + 1) *
            sizeof(char);
        /* We resize our format_path to hold the path to the new file. For now
         * we assume that this never fails. */
        format_path = realloc(format_path, format_path_length);
        /* We create the name of the format file. This should never fail because
         * our buffer is big enough to hold the path. */
        snprintf(format_path, format_path_length, "%s/%s.template",
                 *(list->strings + i), extension);
        /* We try to open the file. */
        format_file = fopen((char *)format_path, "r");
        if (format_file == NULL) {
            /* The file did not exist, we move on to the next search path. */
            continue;
        } else {
            /* We found the template file to use, there is no need to search
             * any further. */
            break;
        }
    }

    /* If we found no valid format file in any of the directories of the
     * list, we simply free the memory used and return NULL. */
    if (format_file == NULL) {
        free(format_path);
        return NULL;
    }

    /* Else we grab the size of the file. Notice that we reuse the variable
     * length from the beginning. */
    format_string_length = file_size(format_file);
    /* We allocate some memory dynamically to hold the big format string. */
    format_string = malloc(format_string_length + 1);
    /* We have enough room in out buffer, so we simply copy the format
     * string from our file. We check for errors at the same time. Because
     * we have a single condition here, the call to fread will always take
     * place. */
    if (fread(format_string, 1, format_string_length, format_file) <
        format_string_length) {
        fclose(format_file);
        free(format_string);
        free(format_path);
        /* We failed for some mysterious reason. */
        return NULL;
    }
    /* We have successfully gotten our format string, we just have to close
     * the file and return our result. */
    fclose(format_file);
    /* We free the memory associated with the format path. */
    free(format_path);
    /* We add a null termination byte. */
    *(format_string + format_string_length) = '\0';
    return format_string;
}

/************************************ EOF *************************************/
