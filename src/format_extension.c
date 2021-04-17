/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2020-10-07
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The header containing the functions we are trying to implement. */
#include <template.h>

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

char *format_extension(const char *extension) {
    /* The HOME environment variable, used to find the template files. */
    char *home_path = getenv("HOME");
    /* The first thing to do is to create the name of the file where the
     * template string should be stored. Because this is only usefull at the
     * beginning, we will reuse the variable long later on to hold the size of
     * the format file. This is why it is a long and not an int. */
    long length = strlen(extension) + strlen(home_path);
    /* We allocate on the stack an array big enough to fit the name of the file
     * we are going to try to read. This will be reused later on to hold the
     * format string we will return. */
    char format_path[length + 37];
    /* This is the buffer that we will dynamically allocate to hold the format
     * string. */
    char *format_string;
    /* The handle to the format file, once we will have opened it. */
    FILE *format_file;
    /* First location tried: in ~/.config/roadelou_template. */
    /* We create the name of the format file. This should never fail because our
     * buffer is big enough to hold the path. */
    snprintf((char *)format_path, sizeof(format_path),
             "%s/.config/roadelou_template/%s.template", home_path, extension);
    /* We try to open the file. */
    format_file = fopen((char *)format_path, "r");
    /* We fail if the file could not be opened. */
    if (format_file == NULL) {
        /* Second location tried: in /etc/roadelou_template. */
        /* Note that /etc is always shorter than /home/..., hence this will fit
         * in our buffer. */
        snprintf((char *)format_path, sizeof(format_path),
                 "/etc/roadelou_template/%s.template", extension);

        /* We try to open the file. */
        format_file = fopen((char *)format_path, "r");
        /* We fail if the file could not be opened. */
        if (format_file == NULL) {
            /* If this also fails, then we return NULL. */
            return NULL;
        }
    }
    /* Else we grab the size of the file. Notice that we reuse the variable
     * length from the beginning. */
    length = file_size(format_file);
    /* We allocate some memory dynamically to hold the big format string. */
    format_string = malloc(length + 1);
    /* We have enough room in out buffer, so we simply copy the format string
     * from our file. We check for errors at the same time. Because we have a
     * single condition here, the call to fread will always take place. */
    if (fread(format_string, 1, length, format_file) < length) {
        fclose(format_file);
        free(format_string);
        /* We failed for some mysterious reason. */
        return NULL;
    }
    /* We have successfully gotten our format string, we just have to close the
     * file and return our result. */
    fclose(format_file);
    /* We add a null termination byte. */
    *(format_string + length) = '\0';
    return format_string;
}

/************************************ EOF *************************************/
