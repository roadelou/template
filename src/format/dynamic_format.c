/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-06
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The library we are trying to implement. */
#include <template/format/dynamic_format.h>

/* Used for the SUCCESS, WARNING and ERROR constants as well as the occurence
 * function, the logging functions and the List type. */
#include <template/util.h>

/* Used for malloc and free. */
#include <stdlib.h>

/* Used for popen and pclose. */
#include <stdio.h>

/* Used for strlen. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/*
Description
===========
Helper function used to append a match to the MatchList with an automatic
management of the resizing.

Arguments
=========
 - match_list: The MatchList we should add the match to. The head and tail
elements of the MatchList must be either heap-allocated or NULL (for realloc).
 - head: The beginning of the match.
 - tail: The end of the match.

Returns
=======
SUCCESS if the match was added to the list, FAILURE otherwise.
*/
static int append_match_list(struct MatchList *match_list, size_t head,
                             size_t tail);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int find_format(const char *text, struct MatchList *match_list) {
    /* The current location we are inspecting. */
    size_t cursor = 0;
    /* The next value for the cursor. */
    size_t next_cursor;
    /* The total size of the text we are working on. */
    size_t text_length = strlen(text);
    /* We start by resetting the provided MatchList to avoid bugs. */
    match_list->count = 0;
    match_list->head = NULL;
    match_list->tail = NULL;
    /* We start looking for the leading character of the format specifier. */
    while ((cursor < text_length) &&
           ((next_cursor = occurence(text + cursor, '%', FIRST_OCCURENCE)) !=
            -1)) {
        /* We offset the next_cursor to take into account the part of the string
         * we have already gone through. */
        next_cursor += cursor;

        /* We check if the '%' is the last character of the provided text. */
        switch (text_length - next_cursor) {
        case 0:
            /* Absurd, we cannot have a '%' past the end of the string. */
            log_message(ERROR_MSG, "%s\n",
                        "Internal bug, found a character past the end of the "
                        "provided template string. This is absurd and most "
                        "likely due to a mistake in the code.");
            /* we stop the execution here to prevent further damage. */
            return ERROR;
        case 1:
            /* We have found a trailing '%' and send a warning to the user. */
            log_message(WARNING_MSG, "%s\n",
                        "Template ends with a trailing '%' character.");
            /* We do not take the trailing '%' into account, instead we end the
             * execution here, since there can be no other format specifier past
             * the last character. */
            return WARNING;
        case 2:
            /* We have a trailing "%$", but there is no closing '$'. */
            log_message(
                WARNING_MSG,
                "Template ends with incomplete format specifier \"%s\".\n",
                text + next_cursor);
            /* We have no match here, and the execution ends. */
            return WARNING;
        default:
            /* We have to find the closing '$', which requires more code (below
             * the switch). */
            break;
        }

        /* We move the cursor to its new value. */
        cursor = next_cursor;
        /* We know that we have an opening delimiter and at least one character
         * after said character. Thus we can use the occurence function to look
         * for a matching closing delimiter. The current layout is:
         *
         * "XXXXXXXX ... % $ XXXX \0"
         * ^             ^ ^ ^
         * |- text       | | |- text + cursor + 2
         *               | |
         *               | |-  text + cursor + 1
         *               |
         *               |- text + cursor
         *
         * */
        next_cursor =
            occurence(text + cursor + 2, *(text + cursor + 1), FIRST_OCCURENCE);
        /* If we didn't find a match, the format specifier is malformed and we
         * do not take it into account. */
        if (next_cursor == -1) {
            log_message(WARNING_MSG,
                        "Found malformed specifier in template text starting "
                        "at character %ld.\n",
                        cursor);
            /* We update the cursor to move after the '%' and start scanning
             * again. We know that is possible since there is more than one
             * character after the '%'. */
            cursor++;
            continue;
        }
        /* else... */

        /* Otherwise, we have found a well-formed format specifier. We include
         * it in our MatchList. We have to be acrefull to offset the next_cursor
         * correctly once again to account for the beginning of the text. */
        append_match_list(match_list, cursor, next_cursor + cursor + 2);
        /* We move the cursor beyound the end of the format specifier for the
         * next iteration. Note that we can end up outside the memory bounds
         * that way, but that will be checked at the beginning of the next hence
         * there is not problem. */
        cursor += next_cursor + 1;
        /* Implicit, we start looking for the next format specifier. */
        continue;
    }
    /* If we reach this line, we have found and registered all the possible
     * format specifiers, hence the execution is a success. */
    return SUCCESS;
}

int append_match_list(struct MatchList *match_list, size_t head, size_t tail) {
    /* We check if there is room for one more element in the allocated
     * match_list. */
    if (match_list->count % MATCH_LIST_CHUNK_SIZE == 0) {
        /* We have to reallocate space for the new element.
         *
         * NOTE
         * ====
         * We assume that malloc never fails here.
         * */
        match_list->head = realloc(match_list->head,
                                   (match_list->count + MATCH_LIST_CHUNK_SIZE) *
                                       sizeof(size_t));
        match_list->tail = realloc(match_list->tail,
                                   (match_list->count + MATCH_LIST_CHUNK_SIZE) *
                                       sizeof(size_t));
    }
    /* We register the new match in the dedicated arrays. */
    *(match_list->head + match_list->count) = head;
    *(match_list->tail + match_list->count) = tail;
    /* We increment the count of elements in the match_list. */
    match_list->count++;
    return SUCCESS;
}

char *get_command_output(const char *command) {
    /* The number of characters copied in the current loop iteration. */
    size_t buffered_bytes;
    /* We start by allocating some memory for the copy buffer. */
    char *copy_buffer = malloc(COMMAND_OUTPUT_CHUNK_SIZE * sizeof(char));
    /* A pointer used to check for errors in realloc. */
    char *next_copy_buffer;
    /* The current size of the string in the buffer. */
    size_t copied_bytes = 0;
    /* Error checking. */
    if (copy_buffer == NULL) {
        /* We print a warning to the user and return NULL. The output of this
         * command will not be written to the output file. */
        log_message(WARNING_MSG,
                    "Out of memory, output of command \"%s\" will be skipped\n",
                    command);
        return NULL;
    }
    /* We use popen to get the output of the provided command. */
    FILE *command_output = popen(command, "r");
    /* Checking for errors. */
    if (command_output == NULL) {
        /* Note that although the function encountered an error, the failure to
         * run a single command is only considered a warning for the whole
         * execution. */
        log_message(WARNING_MSG, "Command \"%s\" failed.\n", command);
        /* We free the allocated memory. */
        free(copy_buffer);
        return NULL;
    }

    /* We consume the output of the shell command. */
    while (!feof(command_output) && !ferror(command_output)) {
        /* We copy the output of the command by chunks. */
        buffered_bytes = fread(copy_buffer + copied_bytes, sizeof(char),
                               COMMAND_OUTPUT_CHUNK_SIZE, command_output);
        /* We increment the count of copied bytes according to what fwrite
         * returned. */
        copied_bytes += buffered_bytes;

        /* We allocate more memory for the next iteration. */
        next_copy_buffer =
            realloc(copy_buffer, copied_bytes + COMMAND_OUTPUT_CHUNK_SIZE);

        /* Error checking */
        if (next_copy_buffer == NULL) {
            /* We print a warning to the user and return NULL. The output of
             * this command will not be written to the output file. */
            log_message(
                WARNING_MSG,
                "Out of memory, output of command \"%s\" will be skipped\n",
                command);
            /* We free the memory we had previously allocated. */
            free(copy_buffer);
            return NULL;
        }
        /* else... */

        /* We update the copy_buffer pointer to point to the new allocated
         * space. */
        copy_buffer = next_copy_buffer;
    }

    /* We have copied the output of the command into memory, we need to ensure
     * that it is null-terminated. We if a trailing '\n' should be replaced by a
     * '\0' to end the string. */
    if ((*(copy_buffer + copied_bytes - 1) == '\n')) {
        /* We simply overwrite this last byte. */
        *(copy_buffer + copied_bytes - 1) = '\0';
        /* NOTE
         * ====
         * The handling of the trailing newline might be buggy when the output
         * of the subcommand yields exactly COMMAND_OUTPUT_CHUNK_SIZE bytes. */

    } else {
        /* EDGE CASE
         * =========
         * If the maximum amount of bytes has been read into the buffer,
         * we can't write the null-byte without overflowing. We have to
         * resize the memory in order to have that last byte fit. We
         * will only request a single byte, but the allocator may send
         * more for various reasons. */
        if (copied_bytes % COMMAND_OUTPUT_CHUNK_SIZE == 0) {
            /* resize the memory in order to have that last byte fit. We will
             * only request a single byte, but the allocator may send more for
             * various reasons. */
            next_copy_buffer = realloc(copy_buffer, copied_bytes + 1);
            /* Error checking */
            if (next_copy_buffer == NULL) {
                /* We print a warning to the user and return NULL. The output of
                 * this command will not be written to the output file. */
                log_message(
                    WARNING_MSG,
                    "Out of memory, output of command \"%s\" will be skipped\n",
                    command);
                /* We free the memory we had previously allocated. */
                free(copy_buffer);
                return NULL;
            }
            /* else... */
        }

        /* We write the terminating null-byte to the buffer. */
        *(copy_buffer + copied_bytes) = '\0';
    }

    /* If we reach this line, the execution was a success. We end the child
     * process. */
    pclose(command_output);
    /* We return the output of the shell command. */
    return copy_buffer;
}

struct List *
get_commands_output_match_list(char *text, const struct MatchList *match_list) {
    /* The index of the format specifier we are currently working on. */
    size_t specifier;

    /* A variable used for the propagation of errors. */
    size_t status = 0;

    /* Sanity check, we fail if a NULL argument is provided. */
    if (text == NULL || match_list == NULL) {
        log_message(WARNING_MSG,
                    "The internal function %s received a NULL pointer as "
                    "argument and will fail.\n",
                    __func__);
        /* We fail as gracefully as we can. */
        return NULL;
    }

    /* Since we know how many commands there are, we create the entire List at
     * once to use it at an array later. This will enable multithreading since
     * each thread accesses a different part of the List. */
    struct List *output_list = null_list(match_list->count);

    /* We also create a subroutine for the asynchronous execution of each
     * command. */
    struct TemplateRoutine **routines =
        malloc(match_list->count * sizeof(struct TemplateRoutine *));

    /* We go over each format specifier. */
    for (specifier = 0; specifier < match_list->count; specifier++) {
        /* We modify the template string in order to isolate the format
         * specifier command. This little trick is the reason why we want the
         * input text to be mutable. */
        *(text + *(match_list->tail + specifier)) = '\0';

        /* We initialize the routine which is going to be used for the execution
         * of the shell command. */
        *(routines + specifier) =
            new_template_routine((raw_routine *)get_command_output,
                                 text + *(match_list->head + specifier) + 2);

        /* We queue the routine for execution. */
        push_job_queue(GLOBAL_THREAD_POOL->queue, *(routines + specifier));
    }

    /* We log a message to help debugging, in particular to help find if a
     * command takes forever to execute. */
    log_message(INFO_MSG, "Waiting for %llu shell commands to complete\n",
                match_list->count);

    /* We wait for every subroutine to return. */
    join_template_routines(match_list->count, routines);

    /* We log a message to help debugging, in particular to help find if a
     * command takes forever to execute. */
    log_message(INFO_MSG, "Done waiting for %llu shell commands\n",
                match_list->count);

    /* Now that every shell command has been run, we gather their results. */
    for (specifier = 0; specifier < match_list->count; specifier++) {
        /* A pointer to the output of the command corresponding to the match
         * of this iteration. */
        char *command_output;

        /* We use the substring from the original text to run the command see
         * the comment in find_format to see where the +2 comes from. */
        command_output = (*(routines + specifier))->result;
        /* Error checking. */
        if (command_output == NULL) {
            /* We propagate the error. */
            status += 1;
            log_message(ERROR_MSG,
                        "Could not get the output of shell command %s.\n",
                        (*(routines + specifier))->argument);
            return NULL;
        } else {
            /* We move the command_output into the List. It will be freed by the
             * destructor of the List. */
            move_into_list(output_list, specifier, command_output);
        }

        /* Finally, we free the memory associated with the subroutine itself. */
        delete_template_routine(*(routines + specifier));
    }

    /* We free the memory that we had needed to hold the pointer of the
     * subroutines. */
    free(routines);

    /* Error checking. */
    if (status != 0) {
        /* We log an error message. */
        log_message(ERROR_MSG, "%llu shell commands failed to run.\n", status);
        /* We free the memory that we had allocated. */
        delete_list(output_list);
        /* We propagate the error. */
        return NULL;
    }

    /* If we reach this line, the execution was a success and we return the
     * expected List. */
    return output_list;
}

int dynamic_format(char *text, FILE *output_file) {
    /* The current status of the execution. */
    int status;
    /* The cursor to our current location in the template file. */
    size_t cursor = 0;
    /* The index of the format specifier we are currently working on. */
    size_t specifier;
    /* Used to check errors from fwrite. */
    size_t copy_count;
    /* The length of the entire text, computed at the end for a small
     * optimization. */
    size_t text_length;
    /* The list used to store the output of every shell command. */
    struct List *output_list;
    /* Our first task is to find all of the format specifiers. */
    struct MatchList match_list;

    /* We find the format specifiers in the text to locate the subcommands. */
    status = find_format(text, &match_list);
    /* Error checking. */
    if (status == ERROR) {
        /* A bug was encountered when parsing the template file, there is no
         * need to go any further as the execution will fail regardless. We free
         * the memory used for the MatchList. */
        delete_match_list(&match_list);
        return ERROR;
    }

    /* We run every subcommand and store their outputs in a List. */
    output_list = get_commands_output_match_list(text, &match_list);
    /* Error checking. */
    if (output_list == NULL) {
        /* We have failed to call the function and will no write the expected
         * file at all. Failure to run even every command would not trigger
         * this, one of the inputs must be invalid... We exit as gracefully
         * as we can. */
        delete_match_list(&match_list);
        log_message(ERROR_MSG, "%s\n",
                    "Could not get the output of shell commands.\n");
        return ERROR;
    }

    /* We go over each format specifier. */
    for (specifier = 0; specifier < match_list.count; specifier++) {
        /* We copy any character from the current position of the cursor until
         * the beginning of the specifier, that is to say
         * *(match_list.head + specifier) - cursor characters. */
        copy_count =
            fwrite(text + cursor, sizeof(char),
                   *(match_list.head + specifier) - cursor, output_file);
        /* Error checking. */
        if (copy_count != *(match_list.head + specifier) - cursor) {
            log_message(ERROR_MSG,
                        "Could not write %ld characters to the output file.\n",
                        *(match_list.head + specifier) - cursor);
            delete_match_list(&match_list);
            return ERROR;
        }

        /* We then write the output of the command to the file. Since the output
         * of the command is NULL-terminated, we can just use fputs here. */
        status = fputs(*(output_list->strings + specifier), output_file);
        /* Error checking. */
        if (status == EOF) {
            /* Note that the command string (which is a substring of text) will
             * be null-ter;inated because of the manipulations done in
             * get_commands_output_match_list. */
            log_message(
                ERROR_MSG,
                "Could not write output of command %s to the output file.\n",
                *(match_list.head + specifier));
            delete_match_list(&match_list);
            delete_list(output_list);
            return ERROR;
        }

        /* We update the cursor for the next iteration. */
        cursor = *(match_list.tail + specifier) + 1;
        /* Implicit, we go to the next format specifier. */
        continue;
    }

    /* We still have to handle the characters between the last format specifier
     * (if any) and the end of the text. */
    text_length = strlen(text + cursor);
    copy_count = fwrite(text + cursor, sizeof(char), text_length, output_file);
    /* Error checking. */
    if (copy_count != text_length) {
        log_message(ERROR_MSG,
                    "Could not write %ld characters to the output file.\n",
                    text_length);
        delete_match_list(&match_list);
        return ERROR;
    }

    /* If we reach this line, the execution was a success, maybe with some
     * warnings. */
    delete_match_list(&match_list);
    return status;
}

void delete_match_list(struct MatchList *match_list) {
    /* If any memory was allocated for the head and tail arrays, we free it. */
    if (match_list->count != 0) {
        free(match_list->head);
        free(match_list->tail);
    }
}

/************************************ EOF *************************************/
