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

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

/* The public function we are implementing. */
char *get_format_extension(const char *path) {
    /* The name to the template file with the best mathcing extension, allocated
     * in dirent.h */
    char *best_fit = NULL;
    /* The number of characters matching with the current best fit. */
    size_t best_score = 0;
    /* The HOME environment variable, used to find the template files. */
    char *home_path = getenv("HOME");
    size_t home_length = strlen(home_path);
    /* The current search directory. Is large enough to hold both the
     * user-specific folder and the system-wide one. */
    char *search_path = alloca(28 + home_length);
    /* A variable used to hold the directory entries as we go through them. */
    struct dirent *directory_entry;

    /* We first go over all the candidates in the user-specific location. */
    snprintf(search_path, 28 + home_length, "%s/.config/roadelou_template",
             home_path);
    /* We open the user-specific directory, if it exists. */
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
            if ((best_fit != NULL) && (current_score == best_score) &&
                (strlen(directory_entry->d_name) < strlen(best_fit))) {
                /* If the current score is equal to the best scroe and not 0, we
                 * favor the template with the shortest name. This ensures that
                 * the hierachical resolution of extensions is performed
                 * correctly. */
                best_fit = directory_entry->d_name;
            } else if (current_score > best_score) {
                /* We update our best match. */
                best_score = current_score;
                best_fit = directory_entry->d_name;
            }
            /* Else the previous fit is better. */
        }
    }

    /* We also try the system wide location. */
    strncpy(search_path, "/etc/roadelou_template", 23);
    /* We open the system-wide directory for inspection. */
    search_dir = opendir(search_path);
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
            if ((best_fit != NULL) && (current_score == best_score) &&
                (strlen(directory_entry->d_name) < strlen(best_fit))) {
                /* If the current score is equal to the best scroe and not 0, we
                 * favor the template with the shortest name. This ensures that
                 * the hierachical resolution of extensions is performed
                 * correctly. */
                best_fit = directory_entry->d_name;
            } else if (current_score > best_score) {
                /* We update our best match. */
                best_score = current_score;
                best_fit = directory_entry->d_name;
            }
            /* Else the previous fit is better. */
        }
    }

    /* If we found no best match, we simply return NULL. */
    if (best_fit == NULL) {
        return NULL;
    } else {
        /* We create a statically allocated copy of the extension to return it.
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

/************************************ EOF *************************************/
