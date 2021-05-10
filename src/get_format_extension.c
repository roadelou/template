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

/* Used for strlen and strncmp. */
#include <string.h>

/* Used for malloc. */
#include <stdlib.h>

/* Used for readdir and opendir. */
#include <dirent.h>

/* Used for alloca. */
#include <alloca.h>

/*
Description
===========
Used to specify the direction to use when matching extensions. FORWARD is used
for the extension of the input file, while BACKWARDS is used for the template
file.
*/
enum Direction {
    FORWARDS,
    BACKWARDS,
};

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/*
Description
===========
Returns the number of characters of the longest matching whole extension
between the provided path and template path. Note that the extension is reversed
in the template path. See "next_extension_part" for more details.

Arguments
=========
 - path: The null-terminated ASCII path to the file for which we want the
        matching format extension.
 - template_path: The null-terminated ASCII path to the template file for which
        we are computing the extension match size.

Returns
=======
The number of matchin characters between the two extensions, excluding the
leading '.' or '/'. This count also excludes the '.' between the parts of the
extension.
*/
static size_t extension_match_size(const char *path, const char *template_path);

/*
Description
===========
Provides the index of the next chunk of extension from the provided path.

Arguments
=========
 - path: The input path to read the extension from.
 - cursor: The position to start looking for a chunk from.
 - direction: The direction in which the chunk should be read.

Returns
=======
The new position of the cursor in the string. If direction is FORWARD, this will
be the end of the extension chunk, and if direction is BACKWARDS this will be
its beginning. The cursor will also be adjusted to make sure that there are no
'.' between index and cursor - 1, i.e. the string starting from the index of
length cursor - index.

Notes
=====
The function will stop making progress upon encountering a '/' in BACKWARDS mode
or a '\0' in FORWARDS mode.

Examples
========

BACKWARDS examples
==================
next_extension_part("test/foo.bar.baz", 16, BACKWARDS)
 -> returns 13, cursor = 16 (for "baz")
next_extension_part("test/foo.bar.baz", 13, BACKWARDS)
 -> returns  9, cursor = 12 (for "bar")
next_extension_part("test/foo.bar.baz", 9, BACKWARDS)
 -> returns  5, cursor =  8 (for "foo")
next_extension_part("test/foo.bar.baz", 5, BACKWARDS)
 -> returns  5, cursor =  5 (for "")

FORWARDS examples
=================
next_extension_part("test/bar.foo",  5, FORWARDS)
 ->  returns  5, cursor =  8 (for "bar")
next_extension_part("test/bar.foo",  8, FORWARDS)
 ->  returns  9, cursor = 12 (for "bar")
next_extension_part("test/bar.foo",  12, FORWARDS)
 ->  returns 12, cursor = 12 (for "")

Exception examples
==================
next_extension_part("test/bar.foo",  0, FORWARDS)
 ->  returns 0, cursor = 8 (for "test/bar")

Undefined Behaviors
===================
The behavior of the function is undefined if the argument cursor value is larger
than the size of the string or if the value given in direction is not BACKWARDS
or FORWARDS.
*/
static size_t next_extension_part(const char *path, size_t *cursor,
                                  enum Direction direction);

/*
Description
===========
Implementation of next_extension_part, BACKWARDS case.
*/
static size_t next_extension_part_backwards(const char *path, size_t *cursor);

/*
Description
===========
Implementation of next_extension_part, FORWARDS case.
*/
static size_t next_extension_part_forwards(const char *path, size_t *cursor);

/*
Description
===========
Finds the length of the directory part of the string, i.e. everything up until
the last '/'.

Arguments
=========
 - path: The NULL-termniated ASCII string of the path.

Returns
=======
The number of characters until the last '/' in the string (included).

Examples
========
directory_part_size("test/foo.bar") -> 5
directory_part_size("foo/bar/baz") -> 8
directory_part_size("foo/bar/baz/") -> 12
directory_part_size("foo.bar.baz") -> 0
*/
static size_t directory_part_size(const char *path);

/*
Description
===========
Returns 1 if the path ends with ".template", 0 otherwise.

Arguments
=========
 - path: Null-terminated path to analyse.
*/
static int correct_ending(const char *path);

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

/* Helper functions. */
static size_t directory_part_size(const char *path) {
    /* We will read the string bacwards and exit after the first '/' we find. */
    size_t path_len = strlen(path);
    size_t cursor = path_len - 1;
    while ((cursor > 0) && (*(path + cursor) != '/')) {
        /* We haven't found a '/' yet, we decrease our cursor. */
        cursor--;
    }
    /* Regardless the exit condition, the length we are interested in is given
     * by the cursor. */
    return cursor;
}

static size_t next_extension_part(const char *path, size_t *cursor,
                                  enum Direction direction) {
    /* We call the appropriate implementation. */
    switch (direction) {
    case BACKWARDS:
        return next_extension_part_backwards(path, cursor);
    case FORWARDS:
        return next_extension_part_forwards(path, cursor);
    default:
        /* Undefined behavior, we do our best to avoid triggering errors. */
        return *cursor;
    }
}

static size_t next_extension_part_backwards(const char *path, size_t *cursor) {
    /* The initial position to use for the cursor. */
    size_t initial_cursor;
    /* The value we are going to return. */
    size_t next_cursor;

    /* First thing, if *cursor-1 lands on a dot, we skip the dot. */
    if (*(path + (*cursor) - 1) == '.') {
        /* We use the brackets to have an lvalue for the decrement operator. */
        initial_cursor = *cursor - 1;
    } else if (*(path + (*cursor) - 1) == '/') {
        /* We have encountered a '/' already, we cannot go any further. */
        return *cursor;
    } else {
        /* In any other cases, the initial simply takes the provided value. */
        initial_cursor = *cursor;
    }

    /* Setting the initial value for our next_cursor. We skip after the NULL
     * byte or the '.' itself. */
    next_cursor = initial_cursor - 1;

    /* We decrement our new cursor until we find a '.' or a '/' or 0. */
    while ((next_cursor > 0) && (*(path + next_cursor) != '.') &&
           (*(path + next_cursor) != '/')) {
        next_cursor--;
    }

    /* We update the cursor variable. */
    *cursor = initial_cursor;

    /*
    By this point, one of those holds true:
     - next_cursor = 0;
     - next_cursor >= 0 and next_cursor points to a '.';
     - next_cursor >= 0 and next_cursor points to a '/';
    In either of the last two cases, we should increment the returned cursor.
    */
    return next_cursor + (*(path + next_cursor) == '.') ||
           (*(path + next_cursor) == '/');
}

static size_t next_extension_part_forwards(const char *path, size_t *cursor) {
    /* Used to hold the initial cursor, also the returned value. */
    size_t initial_cursor;
    /* Used to hold the next value of the cursor. */
    size_t next_cursor;
    /*
    In the forwards case, cursor points to the first character of the string we
    are interested in. A few cases appear for the initial condition.
    */
    if (*(path + (*cursor)) == '.') {
        /* We skip the initial '.' to achieve the desired behavior. */
        initial_cursor = *cursor + 1;
    } else if (*(path + (*cursor)) == '\0') {
        /* We found the terminating NULL byte, we may exit directly. */
        return *cursor;
    } else {
        /* We still have to set the initial cursor. */
        initial_cursor = *cursor;
    }

    /* We set the initial position for the next cursor. */
    next_cursor = initial_cursor;

    /* We iterate through the string until we find either a '.' or a '\0'. */
    while ((*(path + next_cursor) != '.') && (*(path + next_cursor) != '\0')) {
        next_cursor++;
    }

    /* The value of the cursor becomes the next_cursor. */
    *cursor = next_cursor;
    /* We return the initial cursor. */
    return initial_cursor;
}

static size_t extension_match_size(const char *path,
                                   const char *template_path) {
    /* The current extension match found, will be updated during the function.
     */
    size_t extension_match_size = 0;
    /* We set the initial conditions for the path (read from the end) and the
     * template_path (read from the end of the directory part). */
    size_t path_next = strlen(path);
    size_t template_old = directory_part_size(template_path);
    /* We also need a variable for the other bound of each string slice. */
    size_t path_old;
    size_t template_next;

    do {
        /* We move the path_old value for the next iteration, otherwise the
         * backwards propagation is stuck in a loop. The cursor for the next
         * call must be the smallest of path_next and path_old, i.e. path_next,
         * hence the swap. */
        path_old = path_next;
        /* We get the next extension part for the path, reading bacwards. */
        path_next = next_extension_part(path, &path_old, BACKWARDS);

        /* We get the next extension part for the template, reading forwards. */
        template_next =
            next_extension_part(template_path, &template_old, FORWARDS);

        /* We test if the two extension blocks found have the same size. */
        if (template_old - template_next != path_old - path_next) {
            /* String of different size cannot possibly be equals, we have found
             * a mismatch. */
            break;
        } else if (strncmp(path + path_next, template_path + template_next,
                           path_old - path_next) != 0) {
            /* We test if the extensions aren't equal, in which case we have
             * found a mismatch. */
            break;
        } else {
            /* If the two previous conditions were verified, it means that the
             * extension blocks are equal. We update the match size. */
            extension_match_size += path_old - path_next;
        }

        /* We keep iterating until at least one the paths has run out of
         * extensions. */
    } while ((path_next != path_old) && (template_next != template_old));

    /* We return the expected value. */
    return extension_match_size;
}

static int correct_ending(const char *path) {
    /* We first get the length of the path. */
    size_t path_length = strlen(path);
    /* The size of the string ".template" */
    const size_t SIZE = 9;
    /*
    Edge-case
    =========
    The entire path is shorter than the template string. There are 9 characters
    in ".template".
    */
    if (path_length < SIZE) {
        /* The path is too short, it cannot have the right extension. */
        return 0;
    } else {
        /* The end of the path should match the expected ".template" */
        return strncmp(path + path_length - SIZE, ".template", SIZE) == 0;
    }
}

/************************************ EOF *************************************/
