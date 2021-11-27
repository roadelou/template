/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-13
 * Language: C Source
 * Compiler: cc (GCC) 11.2.1 20210728 (Red Hat 11.2.1-1)
 */

/********************************** INCLUDES **********************************/

/* The template library, providing the formatting related functionalities. */
#include <template.h>

/* Used to write the templated file. */
#include <stdio.h>

/* Used for string manipulations (strlen for instance). */
#include <string.h>

/* Used for getopt. */
#include <getopt.h>

/* Used for malloc. */
#include <stdlib.h>

/*
Description
===========
Choice for the formatting style. Static uses the old , while dynamic will

Values
======
 - STATIC: Uses the old %1, %2 etc... and doesn't execute shell commands
 - DYNAMIC: Uses the newer %$ [...] $ subcommands, more powerful but risky.
*/
enum FormatStyle {
    STATIC,
    DYNAMIC,
};

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/*
Description
===========
Prints help for the user on stdout.

Returns
=======
The return value of the printf call.
*/
int print_help(void);

/*
Description
===========
Prints the GPL license message.

Returns
=======
The return value of the printf call.
*/
int print_license(void);

/*
Description
===========
Reads the file at the provided path and returns it content as a string. The
returned pointer should be freed after use.

Arguments
=========
 - path: The path to the file which should be read.

Returns
=======
A pointer to a heap-allocated string holding the content of the file, or NULL
if an error was encountered.
*/
char *read_file(const char *path);

/************************************ MAIN ************************************/

int main(int argc, const char **argv) {
    /* A variable used to hold the getopt option. */
    int getopt_option;
    /* The buffer used to hold the current date. */
    char current_date[11];
    /* We get the user name from, the environment. */
    const char *author = NULL;
    /* Sme for the contact, we will also get it from the environment. */
    const char *contact = NULL;
    /* A pointer used to store the format string from the provided file. */
    char *buffer;
    /* The format specifyer syntax, defaults to the new dynamic one. */
    enum FormatStyle format_style = DYNAMIC;
    /* Description of the long command line options for getopt. See man 3
     * getopt. */
    static struct option long_options[] = {
        {"author", required_argument, NULL, 'a'},
        {"contact", required_argument, NULL, 'c'},
        {"verbose", no_argument, NULL, 'v'},
        {"quiet", no_argument, NULL, 'q'},
        {"static", no_argument, NULL, 's'},
        {"dynamic", no_argument, NULL, 'd'},
        {"license", no_argument, NULL, 'l'},
        {"help", no_argument, NULL, 'h'}};

    /* Just in case, we assert the set the log level to its default, which is
     * WARNING_MSG. */
    set_log_level(WARNING_MSG);

    /* Handling getopt arguments. */
    while ((getopt_option = getopt_long(argc, (char *const *)argv,
                                        "+a:c:hlvqsd", long_options, NULL)) !=
           -1) {
        switch (getopt_option) {
        case 'a':
            /* A new value for the author was supplied, it overwrites the
             * environment one. */
            author = optarg;
            break;
        case 'c':
            /* A new value for the contact was supplied, it overwrites the
               environment one. */
            contact = optarg;
            break;
        case 'h':
            /* Printing help for the user and exiting. */
            print_help();
            return SUCCESS;
        case 'l':
            /* Printing the license and then exiting. */
            print_license();
            return SUCCESS;
        case 'v':
            /* Verbose execution, we lower the log level. */
            set_log_level(INFO_MSG);
            break;
        case 'q':
            /* Quiet execution, we raise the log level. */
            set_log_level(ERROR_MSG);
            break;
        case 's':
            /* Using the old static formatting. */
            format_style = STATIC;
            break;
        case 'd':
            /* Using the new dynamic formatting. */
            format_style = DYNAMIC;
            break;
        default:
            /* getopt encountered and invalid character and already printed an
             * error message, we may just leave. */
            return ERROR;
        }
    }

    /* We get the current date and check for an error at the same time. */
    if (date_now((char *)current_date) == ERROR) {
        /* Something went wrong when getting the current date, we use a default
         * errored one.
         */
        strncpy((char *)current_date, "ERROR", 11);
        /* We also log a warning for the user. */
        log_message(WARNING_MSG,
                    "Could not fetch date from OS, defaulted to \"%s\"\n",
                    current_date);
    }
    /* Adding a debug message. */
    log_message(INFO_MSG, "Using date \"%s\"\n", current_date);

    /* We get the user name, we see if the dedicated variable is set and it
     * wasn't overriden through the command line. */
    if (author == NULL) {
        author = getenv("TEMPLATE_USER");
    }

    /* If the dedicated variable is not set, we default to the Linux user
     * name. */
    if (author == NULL) {
        author = getenv("USER");
        /* In some cases USER may not be defined, for instance when logged-in
         * as root. In that case, we default to an empty string. */
        if (author == NULL) {
            author = "";
            /* We also log a message for the user. */
            log_message(INFO_MSG,
                        "Both TEMPLATE_USER and USER are undefined, defaulted "
                        "author to \"%s\"\n",
                        author);
        } else {
            /* We also log a message for the user. */
            log_message(INFO_MSG, "Defaulted author to \"%s\"\n", author);
        }
    }
    /* Adding a debug message. */
    log_message(INFO_MSG, "Using author \"%s\"\n", author);

    /* We get the user contact if it hasn't been overriden. */
    if (contact == NULL) {
        contact = getenv("TEMPLATE_CONTACT");
    }

    /* If not contact is provided, we leave an empty field. */
    if (contact == NULL) {
        contact = "";
        /* We also log an information for the user. */
        log_message(INFO_MSG, "Defaulted contact to \"%s\"\n", contact);
    }
    /* Adding a debug message. */
    log_message(INFO_MSG, "Using contact \"%s\"\n", contact);

    /* We set the TEMPLATE_USER and TEMPLATE_CONTACE environment variables for
     * the subprocesses. This is particularly usefull for the dynamic formatting
     * style, otherwise the --author and --contact flags would be ignored. */
    setenv("TEMPLATE_USER", author, 1);
    setenv("TEMPLATE_CONTACT", contact, 1);
    /* Adding a debug message. */
    log_message(INFO_MSG, "%s\n",
                "TEMPLATE_USER and TEMPLATE_CONTACT have been set");

    /* We check that a template file has been provided as argument. */
    if (optind == argc) {
        log_message(WARNING_MSG, "%s\n",
                    "No template file provided, nothing to do.");
        /* This is not an error, although it is a bit odd. */
        return SUCCESS;
    }
    /* else... */
    /* Adding a debug message. */
    log_message(INFO_MSG, "Executing template file \"%s\"\n", *(argv + optind));

    /* We try to read the content of the file. */
    buffer = read_file(*(argv + optind));
    /* Error checking. */
    if (buffer == NULL) {
        /* Some error message has already been logged, we just need to exit. */
        return ERROR;
    }
    /* Adding a debug message. */
    log_message(INFO_MSG,
                "Fetched the content of the template file \"%s\", it has %ld "
                "characters\n",
                *(argv + optind), strlen(buffer));

    /* We print our formatted content to the file. */
    switch (format_style) {
    case STATIC:
        safe_format(stdout, buffer, author, contact, current_date);
        break;
    default:
        log_message(
            WARNING_MSG,
            "Invalid formatting style \"%X\", defaulted to DYNAMIC (%X)\n",
            format_style, DYNAMIC);
        /* No break, we fall through to the dynamic case. */
    case DYNAMIC:
        dynamic_format(buffer, stdout);
        break;
    }
    /* Adding a debug message. */
    log_message(INFO_MSG,
                "Filled stdout with templated content from source \"%s\"\n",
                *(argv + optind));

    /* We free the buffer used for our format string. */
    free(buffer);
    /* Adding a debug message. */
    log_message(INFO_MSG,
                "Cleaned ressources for execution of template \"%s\"\n",
                *(argv + optind));

    /* If we reach this line, the execution was a success. */
    return SUCCESS;
}

/********************************* FUNCTIONS **********************************/

int print_help(void) {
    return printf(
        "%s\n",
        "Usage: template-run [options] filename\n"
        "\n"
        "Description\n"
        "===========\n"
        "Executes the provided template file and prints the result to "
        "stdout.\n\n"
        "Options\n"
        "=======\n"
        " -a, --author <author>\n"
        "    Overrides the environment supplied author value.\n"
        "\n"
        " -c, --contact <contact>\n"
        "    Overrides the contact value.\n"
        "\n"
        " -v, --verbose\n"
        "    Raises the verbosity.\n"
        "\n"
        " -q, --quiet\n"
        "    Lowers the verbosity.\n"
        "\n"
        " -s, --static\n"
        "    Older static format style, does not run any commands.\n"
        "\n"
        " -d, --dynamic\n"
        "    New dynamic format style which uses the %/ [...] / subcommands.\n"
        "\n"
        " -l, --license\n"
        "    Prints the license message and exits.\n"
        "\n"
        " -h, --help\n"
        "    Prints this help message and exits.");
}

int print_license(void) {
    return printf(
        "%s\n",
        "template is a small C executable to build templated files from the\n"
        "command line. Copyright (C) 2021  roadelou\n"
        "\n"
        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or\n"
        "(at your option) any later version.\n"
        "\n"
        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU General Public License\n"
        "along with this program.  If not, see "
        "<https://www.gnu.org/licenses/>.");
}

char *read_file(const char *path) {
    /* A pointer to the buffer used to hold the content of the file. */
    char *buffer;
    /* The opaque struct used for file manipulations. */
    FILE *file;
    /* Variable used to store the length of the file. */
    size_t file_size;
    /* A variable used to check if all the bytes from the file were correctly
     * read. */
    size_t read_bytes;

    /* We attempt to open the file at the provided path. */
    file = fopen(path, "rb");
    /* Error checking. */
    if (file == NULL) {
        log_message(ERROR_MSG, "Could not open file %s\n", path);
        return NULL;
    }
    /* else... */

    /* We compute the length of the file before reading the bytes. */
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    /* We allocated the memory to store the content of the file. */
    buffer = malloc((file_size + 1) * sizeof(char));
    /* We assume that malloc does not fail here. */

    /* We read the content of the file into te buffer. */
    read_bytes = fread(buffer, sizeof(char), file_size, file);
    /* Error checking. */
    if (read_bytes != file_size) {
        log_message(
            ERROR_MSG,
            "Error while reading file %s, expected %ld bytes, only found %ld\n",
            path, file_size, read_bytes);
        fclose(file);
        free(buffer);
        return NULL;
    }
    /* else... */

    /* Adding a termination byte. */
    *(buffer + file_size) = '\0';
    /* Closing the copied file. */
    fclose(file);
    /* Returning the expected pointer. */
    return buffer;
}

/************************************ EOF *************************************/
