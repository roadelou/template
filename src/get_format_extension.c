/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-04-17
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The library that we are implementing. */
#include <template.h>

/* Used for the implementation of the extension matching. */
#include <extension_match.h>

/* Used for strlen and strncmp. */
#include <string.h>

/* Used for malloc. */
#include <stdlib.h>

/* Used for readdir and opendir. */
#include <dirent.h>

/* Used for alloca. */
#include <alloca.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Description
 * ===========
 * Improves the provided extension match by searching for a template file in the
 * provided directory.
 *
 * Arguments
 * =========
 *  - search_path: The path of the directory in which the solution should be
 *  searched.
 *  - path: The path for which we are trying to match the extension.
 *  - best_fit: A pointer to a null terminated string holding a null-terminated
 *  string of the current best match. The size allocated for best_fit should be
 *  superior or equal to strlen(path) + strlen("template").
 *  - best_score: A pointer to the score of the current best fit.
 *
 * Returns
 * =======
 * SUCCESS if the search could be performed and the solutions were updated,
 * ERROR otherwise.
 * */
static int improve_extension_match(const char *search_path, const char *path,
                                   char **best_fit, size_t *best_score);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

/* The public function we are implementing. */
char *get_format_extension(const struct List *list, const char *path) {
    /* The name to the template file with the best mathcing extension, allocated
     * in dirent.h */
    char *best_fit = NULL;
    /* The number of characters matching with the current best fit. */
    size_t best_score = 0;
    /* The current search path. */
    char *search_path;

    /* We go through all the provided candidates in order. */
    for (size_t i = 0; i < list->length; i++) {
        /* We get the ith path from the list. */
        search_path = *(list->strings + i);
        /* We update our best match. For now, we assume no error will occur. */
        improve_extension_match(search_path, path, &best_fit, &best_score);
    }

    /* If we found no best match, we simply return NULL. */
    if (best_fit == NULL) {
        return NULL;
    } else {
        /* We create a heap-allocated copy of the extension to return it.
         * That way it won't be subject to strange behaviors from dirent. */
        size_t extension_size =
            strlen(best_fit) - 9; /* 9 = strlen(".template"). */
        char *returned_extension =
            malloc(extension_size + 1); /* 1 is for NULL byte. */
        /* We copy the extension part of the template file name, which comes at
         * the beginning. */
        memcpy(returned_extension, best_fit, extension_size);
        /* Setting the final NULL byte. */
        *(returned_extension + extension_size) = '\0';
        /* We return the expected string. */
        return returned_extension;
    }
}

// Helper functions.
static int improve_extension_match(const char *search_path, const char *path,
                                   char **best_fit, size_t *best_score) {
    /* A variable used to hold the directory entries as we go through them. */
    struct dirent *directory_entry;
    /* We open the system-wide directory for inspection. */
    DIR *search_dir = opendir(search_path);
    /* We only search the directory if it exists. */
    if (search_dir != NULL) {
        /* We read the entry for all the files in the directory. */
        while ((directory_entry = readdir(search_dir)) != NULL) {
            /* We skip the entry if it doesn't end in ".template". */
            if (!correct_ending(directory_entry->d_name)) {
                continue;
            }
            /* We score the new entry. */
            size_t current_score =
                extension_match_size(path, directory_entry->d_name);
            if ((*best_fit != NULL) && (current_score == *best_score) &&
                (strlen(directory_entry->d_name) < strlen(*best_fit))) {
                /* If the current score is equal to the best scroe and not 0, we
                 * favor the template with the shortest name. This ensures that
                 * the hierachical resolution of extensions is performed
                 * correctly. */
                *best_fit = directory_entry->d_name;
            } else if (current_score > *best_score) {
                /* We update our best match. */
                *best_score = current_score;
                *best_fit = directory_entry->d_name;
            }
            /* Else the previous fit is better. */
        }
        /* We return once we have inspected all the possible templates. */
        return SUCCESS;
    } else {
        /* We could not open the provided path, we raise an error for the
         * caller. */
        return ERROR;
    }
}
/************************************ EOF *************************************/
