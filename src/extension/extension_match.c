/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-15
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The header declaring the functions we are implementing. */
#include <template/extension/extension_match.h>

/* Used for strlen and strncmp. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

/* The implementation of the public functions. */
size_t directory_part_size(const char *path) {
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

size_t next_extension_part(const char *path, size_t *cursor,
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

size_t next_extension_part_backwards(const char *path, size_t *cursor) {
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
    return next_cursor +
           ((*(path + next_cursor) == '.') || (*(path + next_cursor) == '/'));
}

size_t next_extension_part_forwards(const char *path, size_t *cursor) {
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

size_t extension_match_size(const char *path, const char *template_path) {
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

int correct_ending(const char *path) {
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
