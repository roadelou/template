/* The template library, providing all the functionalities we need to treat the
 * extensions and apply the formatting. */
#include <template.h>

/* Used to write the templated file. */
#include <stdio.h>

/* Used for string manipulations (strlen for instance). */
#include <string.h>

/* Used to get access to environment variables for the user name and contact. */
#include <stdlib.h>

/* Used for getopt. */
#include <getopt.h>

/* Used for the alloca in default_search_paths. */
#include <alloca.h>

/* Description
 * ===========
 * An enum type used to specify the matching algorithm to use for the
 * extensions.
 *
 * Values
 * ======
 *  - OLD: The old algorithm, will only match the entire extension.
 *  - NEW: The new algorithm, with hierachical extension match.
 * */
enum ExtensionMatchAlgorithm {
    OLD,
    NEW,
};

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
A small helper function which returns the List holding the default search paths.

Returns
=======
The expected List.
*/
struct List *default_search_paths(void);

int main(int argc, const char **argv) {
    /* A cursor used to loop. */
    int cursor;
    /* A variable used to hold the getopt option. */
    int getopt_option;
    /* The current path on which we are working. */
    const char *path;
    /* The buffer used to hold the current date. */
    char current_date[11];
    /* We get the user name from, the environment. */
    const char *author = NULL;
    /* Sme for the contact, we will also get it from the environment. */
    const char *contact = NULL;
    /* Used to store the extension of the file we will be creating. */
    char *extension;
    /* A pointer used to store the format string for the given extension. */
    char *buffer;
    /* The file handle used to create the template files. */
    FILE *created_file;
    /* The list of the path to search the template files through. */
    struct List *list = default_search_paths();
    /* The return code of the process, will rise by 1 each time we fail to build
     * a file. */
    int status = 0;
    /* The extension match algorithm, defaults to new. */
    enum ExtensionMatchAlgorithm match_algorithm = NEW;
    /* The format specifyer syntax, defaults to the new dynamic one. */
    enum FormatStyle format_style = DYNAMIC;
    /* Description of the long command line options for getopt. See man 3
     * getopt. */
    static struct option long_options[] = {
        {"author", required_argument, NULL, 'a'},
        {"contact", required_argument, NULL, 'c'},
        {"verbose", no_argument, NULL, 'v'},
        {"quiet", no_argument, NULL, 'q'},
        {"old", no_argument, NULL, 'o'},
        {"new", no_argument, NULL, 'n'},
        {"static", no_argument, NULL, 's'},
        {"dynamic", no_argument, NULL, 'd'},
        {"license", no_argument, NULL, 'l'},
        {"help", no_argument, NULL, 'h'}};

    /* Just in case, we assert the set the log level to its default, which is
     * WARNING_MSG. */
    set_log_level(WARNING_MSG);

    /* Handling getopt arguments. */
    while ((getopt_option = getopt_long(argc, (char *const *)argv,
                                        "+a:c:hlvqosdn", long_options, NULL)) !=
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
        case 'o':
            /* Using the old matching algorithm. */
            match_algorithm = OLD;
            break;
        case 'n':
            /* Using the new extension matching algorithm (the default). */
            match_algorithm = NEW;
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

    /* We get the user name, we see if the dedicated variable is set and it
     * wasn't overriden through the command line. */
    if (author == NULL) {
        author = getenv("TEMPLATE_USER");
    }

    /* If the dedicated variable is not set, we default to the Linux user
     * name. */
    if (author == NULL) {
        author = getenv("USER");
        /* We also log an information for the user. */
        log_message(INFO_MSG, "Defaulted author to \"%s\"\n", author);
    }

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

    /* We set the TEMPLATE_USER and TEMPLATE_CONTACE environment variables for
     * the subprocesses. This is particularly usefull for the dynamic formatting
     * style, otherwise the --author and --contact flags would be ignored. */
    setenv("TEMPLATE_USER", author, 1);
    setenv("TEMPLATE_CONTACT", contact, 1);

    /* We simply loop over the given paths and create them all. */
    for (cursor = optind; cursor < argc; cursor++) {
        /* We get the new file to create. */
        path = *(argv + cursor);

        /* We first get the extension of our file. The algorithm used can be
         * overriden by the user. */
        switch (match_algorithm) {
        case OLD:
            /* We have to discard the const here, but it is important to not
             * attempt to free that string. */
            extension = (char *)get_extension(path);
            break;
        case NEW:
            extension = get_format_extension(list, path);
            break;
        default:
            /* If we received a garbage value, we print a warning to the
             * user and default to the default new algorithm. */
            log_message(WARNING_MSG,
                        "Invalid algorithm \"%X\", defaulted to NEW (%X)\n",
                        match_algorithm, NEW);
            extension = get_format_extension(list, path);
        }

        /* If we found no valid extension, we use .txt instead. */
        if (extension == NULL) {
            /* We log a warning for the user. */
            log_message(INFO_MSG,
                        "Could not fetch template for extension of \"%s\", "
                        "using default template instead\n",
                        path);
            /* We try to fill the buffer with the default template. */
            buffer = format_extension(list, "txt");
            /* If our buffer is still NULL, then we just skip creating this
             * file and move on to the next one. */
            if (buffer == NULL) {
                /* We log an error to the user. */
                log_message(ERROR_MSG, "%s\n",
                            "Could not fetch default template, installation "
                            "may be broken");
                status += 1;
                continue;
            }
        } else {
            /* We get the format string for our extension type. */
            buffer = format_extension(list, extension);
            /* If we can't grab a format for this extension, we try again with
             * the default txt format. */
            if (buffer == NULL) {
                /* We log an error for the user. */
                log_message(
                    ERROR_MSG,
                    "Could not use found template for (reversed) extension "
                    "\"%s\" of \"%s\", template file might be broken\n",
                    extension, path);
                /* We try to fill the buffer with the default template. */
                buffer = format_extension(list, "txt");
                /* If our buffer is still NULL, then we just skip creating this
                 * file and move on to the next one. */
                if (buffer == NULL) {
                    /* We log an error to the user. */
                    log_message(ERROR_MSG, "%s\n",
                                "Could not fetch default template, "
                                "installation may be broken");
                    status += 1;
                    continue;
                }
            }
        }

        /* We open the file we are going to create. */
        created_file = fopen(path, "w");
        if (created_file == NULL) {
            /* We could not open this file for some reason, we skip it and raise
             * the error code. We also log an error for the user. */
            log_message(ERROR_MSG,
                        "Could not open file \"%s\" to write template, you may "
                        "not have the necessary permissions\n",
                        path);
            status += 1;
            free(buffer);
            continue;
        }

        /* We print our formatted content to the file. */
        switch (format_style) {
        case STATIC:
            safe_format(created_file, buffer, author, contact, current_date);
            break;
        default:
            log_message(
                WARNING_MSG,
                "Invalid formatting style \"%X\", defaulted to DYNAMIC (%X)\n",
                format_style, DYNAMIC);
            /* No break, we fall through to the dynamic case. */
        case DYNAMIC:
            dynamic_format(buffer, created_file);
            break;
        }

        /* We flush the file by closing it. */
        fclose(created_file);

        /* We free the buffer used for our format string. */
        free(buffer);

        /* We no longer need the dynamically allocated extension either. */
        switch (match_algorithm) {
        case OLD:
            /* If we used the OLD matching algorithm, no memory was
             * allocated for the extension hence we shouldn't attempt to
             * free it. */
            break;
        default:
            /* The other algorithms do allocate some memory that we have to
             * free. */
            free(extension);
            break;
        }
    }
    /* We exit and end the process. */
    return status;
}

int print_help(void) {
    return printf(
        "%s\n",
        "Usage: template [options] [filenames...]\n"
        "\n"
        "Description\n"
        "===========\n"
        "Creates the given files from templates based on their "
        "extensions.\n\n"
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
        " -o, --old\n"
        "    Old matching algorithm, needs whole extension match.\n"
        "\n"
        " -n, --new\n"
        "    New matching algorithm, uses hierarchical match.\n"
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

struct List *default_search_paths(void) {
    /* The HOME environment variable, used to find the template files. */
    char *home_path = getenv("HOME");
    size_t home_length = strlen(home_path);
    /* The user-specific path to find template files. */
    char *search_path = alloca(28 + home_length);
    /* We use snprintf to create the user-specific path. */
    snprintf(search_path, 28 + home_length, "%s/.config/roadelou_template",
             home_path);
    /* We use the variadic constructor to return the expected list. */
    return new_list(2, search_path, "/etc/roadelou_template");
}
