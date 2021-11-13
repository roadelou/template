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
 * function. */
#include <template/util/base.h>

/* Used to log warnings about incomplete format specifiers. */
#include <template/util/log.h>

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

int write_command_output(const char *command, FILE *output_file) {
    /* The number of characters copied in the current loop iteration. */
    size_t buffered_bytes;
    /* We start by allocating some memory for the copy buffer.
     *
     * NOTE
     * ====
     * We assume that malloc doesn't fail here.
     * */
    char *copy_buffer = malloc(COMMAND_OUTPUT_CHUNK_SIZE * sizeof(char));
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
        return WARNING;
    }

    /* NOTE
     * ====
     * The handling of the trailing newline might be buggy when the output of
     * the subcommand yields exactly COMMAND_OUTPUT_CHUNK_SIZE bytes.
     * */

    /* We consume the output of the shell command. */
    while (!feof(command_output) && !ferror(command_output)) {
        /* We copy the output of the command by chunks. */
        buffered_bytes = fread(copy_buffer, sizeof(char),
                               COMMAND_OUTPUT_CHUNK_SIZE, command_output);

        /* We check wether the EOF has been reached, in which case a trailing
         * '\n' should be removed. */
        if (feof(command_output) &&
            (*(copy_buffer + buffered_bytes - 1) == '\n')) {
            /* We simply won't be copying this last byte. */
            buffered_bytes--;
        }
        /* We copy the buffered bytes. */
        if (fwrite(copy_buffer, sizeof(char), buffered_bytes, output_file) !=
            buffered_bytes * sizeof(char)) {
            log_message(ERROR_MSG, "%s\n",
                        "Could not write command output to the provided file.");
            free(copy_buffer);
            pclose(command_output);
            return ERROR;
        }
    }
    /* If we reach this line, the execution was a success. We end the child
     * process. */
    pclose(command_output);
    return SUCCESS;
}

int dynamic_format(char *text, FILE *output_file) {
    /* The current status of the execution. */
    int status;
    /* The cursor to our current location in the template file. */
    size_t cursor = 0;
    /* The number of the format specifier we are currently working on. */
    size_t specifier = 0;
    /* Used to check errors from fwrite. */
    size_t copy_count;
    /* The length of the entire text, computed at the end for a small
     * optimization. */
    size_t text_length;
    /* Our first task is to find all of the format specifiers. */
    struct MatchList match_list;

    status = find_format(text, &match_list);
    /* Error checking. */
    if (status == ERROR) {
        /* A bug was encountered when parsing the template file, there is no
         * need to go any further as the execution will fail regardless. We free
         * the memory used for the MatchList. */
        delete_match_list(&match_list);
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

        /* We modify the template string in order to isolate the format
         * specifier command. This little trick is the reason why we want the
         * input text to be mutable. */
        *(text + *(match_list.tail + specifier)) = '\0';
        /* We use the substring from the original text to run the command see
         * the comment in find_format to see where the +2 comes from. */
        status |= write_command_output(
            text + *(match_list.head + specifier) + 2, output_file);
        /* Error checking. */
        if (status == ERROR) {
            /* We propagate the error. */
            delete_match_list(&match_list);
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
