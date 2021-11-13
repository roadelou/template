/* Include once header guard */
#ifndef TEMPLATE_UTIL_LOG_INCLUDED
#define TEMPLATE_UTIL_LOG_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-05-09
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

/* The includes for your header go here */

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* Desription
 * ==========
 * An enum used to quantify the importance of a message. Used to determine
 * whether the message will be shown to the user or not.
 * */
enum LOG_LEVEL {
    INFO_MSG,    // No problem occured, not intervention is required.
    WARNING_MSG, // A recoverable problem occured, no intervention is required.
    ERROR_MSG,   // An irrecoverable problem occured, needs user intervention.
};

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/* Description
 * ===========
 * Sets the log level to the desired value. Message with an importance lower
 * than the log level will not be printed to the user.
 *
 * Arguments
 * =========
 *  - level: One of INFO, WARNING or ERROR. Any other value will be interpreted
 *  as WARNING. Only messages of priority higher or equal to the level will be
 *  printed.
 * */
void set_log_level(enum LOG_LEVEL level);

/* Description
 * ===========
 * Logs a message for the user to stdout or stderr. INFO is logged in white,
 * WARNING is logged in orange and ERROR is logged in red.
 *
 * Arguments
 * =========
 *  - importance: The importance of the message, which will only be displayed to
 *  the user if the importance is higher than the current log level. INFO and
 *  WARNING are printed to STDOUT, while ERROR is printed to STDERR.
 *  - format: A constant format string for printf, see its documentation for
 *  more details.
 *  - ...: Variadic arguments for printf, see its documentation for more
 *  details.
 *
 * Returns
 * =======
 * The return code of printf.
 * */
int log_message(enum LOG_LEVEL importance, const char *format, ...);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
