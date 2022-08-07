/* Include once header guard */
#ifndef TEMPLATE_FORMAT_DYNAMIC_FORMAT_INCLUDED
#define TEMPLATE_FORMAT_DYNAMIC_FORMAT_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-06
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

/* Used for the FILE type. */
#include <stdio.h>

/*********************************** MACROS ***********************************/

/** The chunk size used to bulk allocate space for the MatchList field arrays.
 */
#ifndef MATCH_LIST_CHUNK_SIZE
#define MATCH_LIST_CHUNK_SIZE 32
#endif

/** The chunk size used when copying the output of a command to the target file.
 */
#ifndef COMMAND_OUTPUT_CHUNK_SIZE
#define COMMAND_OUTPUT_CHUNK_SIZE 1024
#endif

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/**
Description
===========
This struct holds a list of positions within a specific text where a dynamic
format specifier has been found. A format specifier looks like %$ [...] $ where
'$' can be any ASCII character.

Fields
======
 - count: The number of format specifiers found in the given text.
 - head: The array of start positions of the format specifier in the text. This
 will be the position of the intial '%'.
 - tail: Tha array of last positions of the format specifier in the text. This
 will be the position of the terminating '$', where '$' is the character which
 followed the leading '%'.
*/
struct MatchList {
    size_t count;
    size_t *head;
    size_t *tail;
};

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/**
Description
===========
This function is used to locate the format specifiers in the provided string
before replacing them with the corresponding outputs.

Arguments
=========
 - text: The text in which we want to locate all the format specifiers. For the
 description of a format specifier, see the documentation of the MatchList
 struct.
 - match_list: A pointer to a MatchList which will be modified by the call. When
 the function returns, match_list will contain all of the positions where the
 format specifiers where found.

Returns
=======
A return code indicating whether the execution suceeded. Will be one of SUCCESS,
ERROR or WARNING.

Side-effects
============
If a format specifier isn't well formed, like a trailing '%' or a "%$" without
the closing '$', a warning will be logged, and the malformed format specifier
will not be part of the returned MatchList.

Examples
========
For the text: "Today is the %$date +%F$.", the corresponding MatchList would be
{count=1; head=[13]; tail=[23]}. The call shall return SUCCESS.

For the text "Today is the %/date +%F/.", the corresponding MatchList would also
be {count=1; head=[13]; tail=[23]}. The delimiting character has just been
changed to a '/'. The call shall return SUCCESS.

For the text "Today is the %", the corresponding MatchList should be {count=0;
head=[]; tail=[]} because there is no delimiter after the '%'. A warning will be
sent about the trailing '%'. The call shall return WARNING.

For the text "Today is the %$date +%F/.", the corresponding MatchList should be
{count=0; head=[]; tail=[]} since the delimiter '$' which follows the leading
'%' is never matched. A warning will be logged. The call shall return WARNING.
*/
int find_format(const char *text, struct MatchList *match_list);

/**
Description
===========
This function gathers every command described in match_list from text, executes
them and gathers their outputs into the returned list. Note that the text
argument will be mutated by the function to take advantage of slight
optimizations.

The GLOBAL_THREAD_POOL must have been initialized before this function is
called, since it is multithreaded.

Arguments
=========
 - text: The text from which the commands should be extracted.
 - match_list: A MatchList pointer describing the commands found in the text..

Returns
=======
A heap-allocated list of copies of the outputs from the commands which were
described in the match_list.

Side-effects
============
Any side-effect of the provided command will take place. The provided file will
be written to, and if the command outputs something to stderr, it will be
visible on the stderr of the main parent process. Warning and error messages can
also be emitted. The provided text argument will also be mutated.

Examples
========
For the text "Today is the %/echo foo/.", and the match_list
{count=1; head=[13]; tail=[23]}, the returned list would be:
{length=1, strings=["foo"]}.
*/
struct List *get_commands_output_match_list(char *text,
                                            const struct MatchList *match_list);

/**
Description
===========
This function is used to get the output of the provided (shell) command to a
heap-allocated string.

Arguments
=========
 - command: The shell command whise output shall be written to the provided
 file. This command will be executed in a subprocess using popen.

Returns
=======
This function will return the output of the command in a memory allocated string
if it can, otherwise NULL will be returned. In particular, this code can fail
if:
 - The output file could not be written to.
 - The shell command could not be executed.
 - The application runs out of memory.

Side-effects
============
Any side-effect of the provided command will take place. The provided file will
be written to, and if the command outputs something to stderr, it will be
visible on the stderr of the main parent process. Warning and error messages can
also be emitted.
*/
char *get_command_output(const char *command);

/**
Description
===========
High-level function used to fill the provided output_file according to the
template provided in the text. Note that the text argument will be mutated by
the function to take advantage of slight optimizations. The commands required by
the dynamic format specifiers will also be executed.

Arguments
=========
 - text: The text containing the format string and specifying how the
 output_file should be filled.
 - output_file: The file to which the template result should be written.

Returns
=======
SUCCESS if the execution could take place, WARNING if some recoverable error was
encountered and ERROR if the formatting could not be performed.

Side-effects
============
See write_commad_output. Also, the provided text file will be overwritten.
*/
int dynamic_format(char *text, FILE *output_file);

/**
Description
===========
Destructor for the MatchList struct.
*/
void delete_match_list(struct MatchList *match_list);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
