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

/* Used for error handling of strtoul. */
#include <errno.h>

/* Used for uintptr_t. */
#include <stdint.h>

/* The default number of threads needed to run this application. In the case of
 * template this would be 2:
 *  - One to run the execution of each file.
 *  - One to run the execution of the commands for each file. */
#define APPLICATION_MINIMUM_THREADS 2

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
Arguments for the template_file function, we use a struct to pass them as a
single pointer, which is needed for a template_routine thread.
*/
struct TemplateFileArguments {
    const char *path;    // The path of the file which should be created.
    const char *author;  // The author, used for the old format style.
    const char *contact; // The contact, used for the old format style.
    const char
        *current_date; // The current date, used for the old format style.
    const enum ExtensionMatchAlgorithm
        match_algorithm; // The match algorithm to use for the extension.
    const enum FormatStyle
        format_style;        // The formatting style to apply to the file.
    const struct List *list; // The list of paths in which the template files
                             // should be searched.
};

/*
Description
===========
Routine used to create a single templated file. This routine will be used to
create a single file from its template. It always returns NULL.

Arguments
=========
 - template_file_arguments: The struct of arguments needed to create the new
 file.

Returns
=======
ERROR if the execution failed, SUCCESS otherwise.
*/
int template_file(const struct TemplateFileArguments *template_arguments);

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
    /* The buffer used to hold the current date. */
    char current_date[11];
    /* We get the user name from, the environment. */
    const char *author = NULL;
    /* Sme for the contact, we will also get it from the environment. */
    const char *contact = NULL;
    /* A variable containing the number of threads, used to create the
     * threadpool. */
    size_t job_count = APPLICATION_MINIMUM_THREADS;
    /* The number of threads specified by the user, if any. */
    char *job_count_string = NULL;
    /* Used for error checking of strtoul on job_count_string. */
    char *unparsed_job_count_string;
    /* A pointer used to tell why the parsing of job_count_string_failed. */
    char *reason_job_count_string;
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
        {"jobs", required_argument, NULL, 'j'},
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
    while ((getopt_option =
                getopt_long(argc, (char *const *)argv, "+a:c:j:hlvqosdn",
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
        case 'j':
            /* The user specified a number of jobs to run the application with.
             * For now we accept it, but we will need to check it later. */
            job_count_string = optarg;
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

    /* Setting up the global threadpool. We start by parsing the value defined
     * on the command line. */
    if (job_count_string != NULL) {
        /* To distinguish between success and failure. */
        errno = 0;
        /* We parse the user-provided value. */
        job_count = strtoul(job_count_string, &unparsed_job_count_string, 10);
        /* Error checking. */
        if (errno != 0 || *unparsed_job_count_string != '\0') {
            /* The value provided by the user was not a valid integer. Even
             * though we could recover by using the default value, this likely
             * would not be the expected behavior, so instead we raise an
             * error. The reason why the error triggered depends on how we got
             * here. */
            if (errno != 0) {
                reason_job_count_string = strerror(errno);
            } else {
                reason_job_count_string = "Value contains non digit characters";
            }
            log_message(ERROR_MSG,
                        "Requested number of jobs '%s' is not a valid number "
                        "of threads since %s\n",
                        job_count_string, reason_job_count_string);
            /* We exit the process here before doing any real work. */
            exit(EXIT_FAILURE);
        }
    }
    /* The job_count value has been updated, we now check whether it is valid.
     */
    if (job_count < APPLICATION_MINIMUM_THREADS) {
        /* The user requested less threads than the application needs to run
         * correctly. If we move forward with that value the code will deadlock,
         * so instead we reset to the minimum allowed value. This likely happens
         * because the end user gave -j 1 without knowing that the application
         * has this limitation. */
        log_message(WARNING_MSG,
                    "Application %s requires at least %lu threads to run "
                    "correctly, but user requested %lu threads be used. "
                    "Defaulting to minimal value %lu to avoid deadlocks\n",
                    *argv, APPLICATION_MINIMUM_THREADS, job_count,
                    APPLICATION_MINIMUM_THREADS);
        /* Resetting to the smallest possible value. */
        job_count = APPLICATION_MINIMUM_THREADS;
    }
    /* We initialize the threadpool with the required amount of threads. */
    GLOBAL_THREAD_POOL = new_thread_pool(job_count);
    /* Error checking. */
    if (GLOBAL_THREAD_POOL == NULL) {
        /* The thread pool could not be initialized, probably because too many
         * threads were requested. */
        log_message(ERROR_MSG,
                    "The GLOBAL_THREAD_POOL could not be initialized with %lu "
                    "threads. Please check that your system is able to handle "
                    "your requirements\n",
                    job_count);
        exit(EXIT_FAILURE);
    } else {
        /* Adding a debug message. */
        log_message(
            INFO_MSG,
            "The GLOBAL_THREAD_POOL has been initialized with %lu thread(s)\n",
            GLOBAL_THREAD_POOL->size);
    }

    /* We create an array to hold every thread we will have to way for. */
    struct TemplateRoutine **routines =
        malloc((argc - optind) * sizeof(struct TemplateRoutine *));

    /* We simply loop over the given paths and create them all. */
    for (cursor = optind; cursor < argc; cursor++) {
        /* We prepare the arguments for the template_file subroutine. We
         * allocate the memory on the heap so that it won't be shared between
         * the threads. */
        struct TemplateFileArguments *template_file_arguments =
            malloc(sizeof(struct TemplateFileArguments));
        /* To preserve the const attributes we have to create a copy of the
         * arguments that we are going to put on the heap. */
        struct TemplateFileArguments const_args = {
            .path = *(argv + cursor),
            .author = author,
            .contact = contact,
            .current_date = current_date,
            .match_algorithm = match_algorithm,
            .format_style = format_style,
            .list = list,
        };
        /* We copy the arguments to the heap. */
        memcpy(template_file_arguments, &const_args,
               sizeof(struct TemplateFileArguments));
        /* We initialize the routine to create the current file. */
        *(routines + cursor - optind) = new_template_routine(
            (raw_routine *)&template_file, (void *)template_file_arguments);
        /* We submit the subroutine to the threadpool. */
        push_job_queue(GLOBAL_THREAD_POOL->queue,
                       *(routines + cursor - optind));
    }
    /* We log a message to help debugging, in particular to help find if a
     * file takes forever to execute. */
    log_message(INFO_MSG, "Waiting for %d files to be created\n",
                argc - optind);

    /* We wait for every subroutine to return. */
    join_template_routines(argc - optind, routines);

    /* We log a message to help debugging, in particular to help find if a
     * command takes forever to execute. */
    log_message(INFO_MSG, "Done waiting for %llu files to be created\n",
                argc - optind);

    /* We check the return code for every file. */
    for (cursor = 0; cursor < argc - optind; cursor++) {
        if ((uintptr_t)(*(routines + cursor))->result == ERROR) {
            /* We propagate the error. */
            status += 1;
            /* We also log an error message. */
            log_message(ERROR_MSG, "Failed to create file \"%s\"\n",
                        *(argv + optind + cursor));
        }
        /* We free the memory associated with the arguments of the subroutine.
         */
        free((*(routines + cursor))->argument);
        /* We free the memory associated with the subroutine itself. */
        free(*(routines + cursor));
    }

    /* We free the memory associated with the array of subroutines. */
    free(routines);

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

int template_file(const struct TemplateFileArguments *template_arguments) {
    /* We unwrap our arguments for the sake of convenience. */
    const char *path = template_arguments->path;
    const char *author = template_arguments->author;
    const char *contact = template_arguments->contact;
    const char *current_date = template_arguments->current_date;
    const enum ExtensionMatchAlgorithm match_algorithm =
        template_arguments->match_algorithm;
    const enum FormatStyle format_style = template_arguments->format_style;
    const struct List *list = template_arguments->list;
    /* Used to store the extension of the file we will be creating. */
    char *extension;
    /* A pointer used to store the format string for the given extension. */
    char *buffer;
    /* The file handle used to create the template files. */
    FILE *created_file;

    /* Adding a debug message. */
    log_message(INFO_MSG, "Working on path \"%s\"\n", path);

    /* We first get the extension of our file. The algorithm used can be
     * overriden by the user. */
    switch (match_algorithm) {
    case OLD:
        /* We have to discard the const here, but it is important to not
         * attempt to free that string. */
        extension = (char *)get_extension(path);
        break;
    default:
        /* If we received a garbage value, we print a warning to the
         * user and default to the default new algorithm. */
        log_message(WARNING_MSG,
                    "Invalid algorithm \"%X\", defaulted to NEW (%X)\n",
                    match_algorithm, NEW);
    case NEW:
        extension = get_format_extension(list, path);
        break;
    }
    /* Adding a debug message. */
    log_message(INFO_MSG, "Matched extension \"%s\"\n", extension);

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
            /* The execution failed. */
            return ERROR;
        }
    } else {
        /* We get the format string for our extension type. */
        buffer = format_extension(list, extension);
        /* If we can't grab a format for this extension, we try again with
         * the default txt format. */
        if (buffer == NULL) {
            /* We log an error for the user. */
            log_message(ERROR_MSG,
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
                /* The execution failed. */
                return ERROR;
            }
        }
    }
    /* Adding a debug message. */
    log_message(INFO_MSG,
                "Fetched the format for the extension \"%s\", it has %ld "
                "characters\n",
                extension, strlen(buffer));

    /* We open the file we are going to create. */
    created_file = fopen(path, "w");
    if (created_file == NULL) {
        /* We could not open this file for some reason, we skip it and raise
         * the error code. We also log an error for the user. */
        log_message(ERROR_MSG,
                    "Could not open file \"%s\" to write template, you may "
                    "not have the necessary permissions\n",
                    path);
        free(buffer);
        /* The execution failed. */
        return ERROR;
    }
    /* Adding a debug message. */
    log_message(INFO_MSG, "Opened the file at path \"%s\"\n", path);

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
    /* Adding a debug message. */
    log_message(INFO_MSG, "Filled target file \"%s\" with templated content\n",
                path);

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
    /* Adding a debug message. */
    log_message(INFO_MSG, "Cleaned ressources for creation of file \"%s\"\n",
                path);

    /* If we reach this line, the execution was a success. */
    return SUCCESS;
}
