/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-09
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

// The header we are implementing.
#include <template/util/log.h>

// Used for vfprintf
#include <stdarg.h>
#include <stdio.h>

/********************************* SINGLETONS *********************************/

// The current log level. Default value is WARNING.
static enum LOG_LEVEL LEVEL = WARNING_MSG;

/********************************* PROTOYPES **********************************/

/* Description
 * ===========
 * Tells whether a message should be displyed depending on the log level.
 *
 * Arguments
 * =========
 *  - importance: The importance of the message. Value should be one of INFO,
 *  WARNING or ERROR. Garbage values will be treated as INFO.
 *
 * Returns
 * =======
 * A boolean value based of the following table:
 *
 * |====================|======|=========|=======|
 * | importance \ LEVEL | INFO | WARNING | ERROR |
 * |====================|======|=========|=======|
 * |       INFO         |   1  |    0    |   0   |
 * |====================|======|=========|=======|
 * |       WARNING      |   1  |    1    |   0   |
 * |====================|======|=========|=======|
 * |       ERROR        |   1  |    1    |   1   |
 * |====================|======|=========|=======|
 *
 * */
static int should_log(enum LOG_LEVEL importance);

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

// The functions we are implementing.
void set_log_level(enum LOG_LEVEL level) {
    // We assign a value based on the provided level. We need a switch to handle
    // garbage values correctly.
    switch (level) {
    case INFO_MSG:
    case WARNING_MSG:
    case ERROR_MSG: {
        LEVEL = level;
        break;
    }
    default: {
        // If we received a garbage input, we set the log level to WARNING.
        LEVEL = WARNING_MSG;
        break;
    }
    }
}

int log_message(enum LOG_LEVEL importance, const char *format, ...) {
    // The return value of the function.
    int return_value;
    //
    // If the value shouldn't be logged, we simply return 1.
    if (!should_log(importance)) {
        return 1;
    }
    // else...
    //
    // We create the variadic list to handle variadic arguments.
    va_list variadic_list;
    //
    // We initialize our variadic list.
    va_start(variadic_list, format);
    //
    // We emit the ASCII color sequence for our message based on its type.
    switch (importance) {
    case WARNING_MSG:
        // Warning goes in orange.
        fprintf(stderr, "%s", "\033[33m");
        break;
    case ERROR_MSG:
        // Error goes in red.
        fprintf(stderr, "%s", "\033[31m");
        break;
    default:
        // INFO and garbage are printed in white.
        fprintf(stderr, "%s", "\033[37m");
        break;
    }
    //
    // We print the logged message itself.
    return_value = vfprintf(stderr, format, variadic_list);
    //
    // Finally we end the ASCII color sequence.
    fprintf(stderr, "%s", "\033[m");
    //
    // We return the expected value.
    return return_value;
}

// Helper functions.
static int should_log(enum LOG_LEVEL importance) {
    // We switch based on the importance value to handle garbage correctly.
    switch (importance) {
    case INFO_MSG: {
        return LEVEL == INFO_MSG;
    }
    case WARNING_MSG: {
        return LEVEL != ERROR_MSG;
    }
    case ERROR_MSG: {
        return 1;
    }
    default: {
        // Garbage importance is treated like INFO.
        return LEVEL == INFO_MSG;
    }
    }
}

/************************************ EOF *************************************/
