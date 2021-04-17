/* The header of the library we are using. */
#include <template.h>

/* Used for getopt. */
#include <getopt.h>

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
    const char *author;
    /* Sme for the contact, we will also get it from the environment. */
    const char *contact;
    /* Used to store the extension of the file we will be creating. */
    char *extension;
    /* A pointer used to store the format string for the given extension. */
    char *buffer;
    /* The file handle used to create the template files. */
    FILE *created_file;
    /* The return code of the process, will rise by 1 each time we fail to build
     * a file. */
    int status = 0;
    /* Description of the long command line options for getopt. See man 3
     * getopt.
     */
    static struct option long_options[] = {
        {"author", required_argument, NULL, 'a'},
        {"contact", required_argument, NULL, 'c'},
        {"license", no_argument, NULL, 'l'},
        {"help", no_argument, NULL, 'h'}};

    /* We get the current date and check for an error at the same time. */
    if (date_now((char *)current_date) == ERROR) {
        /* Something went wrong when getting the current date, we use a default
         * errored one.
         */
        strncpy((char *)current_date, "ERROR", 11);
    }

    /* We get the user name, we see if the dedicated variable is set. */
    author = getenv("TEMPLATE_USER");

    if (author == NULL) {
        /* If the dedicated variable is not set, we default to the Linux user
         * name.
         */
        author = getenv("USER");
    }

    /* We get the user contact. */
    contact = getenv("TEMPLATE_CONTACT");

    if (contact == NULL) {
        /* If not contact is provided, we leave an empty field. */
        contact = "";
    }

    /* Handling getopt arguments. */
    while ((getopt_option = getopt_long(argc, (char *const *)argv, "+a:c:h",
                                        long_options, NULL)) != -1) {
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
        default:
            /* getopt encountered and invalid character and already printed an
             * error message, we may just leave. */
            return ERROR;
        }
    }

    /* We simply loop over the given paths and create them all. */
    for (cursor = optind; cursor < argc; cursor++) {
        /* We get the new file to create. */
        path = *(argv + cursor);

        /* We first get the extension of our file. */
        extension = get_format_extension(path);
        /* If we found no valid extension, we use .txt instead. */
        if (extension == NULL) {
            buffer = format_extension("txt");
            /* If our buffer is still NULL, then we just skip creating this
             * ffile and move on to the next one. */
            if (buffer == NULL) {
                status += 1;
                continue;
            }
        } else {
            /* We get the format string for our extension type. */
            buffer = format_extension(extension);
            /* If we can't grab a format for this extension, we try again with
             * the default txt format. */
            if (buffer == NULL) {
                buffer = format_extension("txt");
                /* If our buffer is still NULL, then we just skip creating this
                 * ffile and move on to the next one. */
                if (buffer == NULL) {
                    status += 1;
                    continue;
                }
            }
        }

        /* We open the file we are going to create. */
        created_file = fopen(path, "w");
        if (created_file == NULL) {
            /* We could not open this file for some reason, we skip it and raise
             * the error code. */
            status += 1;
            free(buffer);
            continue;
        }

        /* We print our formatted content to the file. */
        safe_format(created_file, buffer, author, contact, current_date);

        /* We flush the file by closing it. */
        fclose(created_file);

        /* We free the buffer used for our format string. */
        free(buffer);
        /* We no longer need the dynamically allocated extension either. */
        free(extension);
    }
    /* We exit and end the process. */
    return status;
}

int print_help(void) {
    return printf("%s\n",
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
                  " --license\n"
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
