/* Include once header guard */
#ifndef DYNAMIC_FORMAT_INCLUDED
#define DYNAMIC_FORMAT_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-11-06
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

/* Used for the SUCCESS, WARNING and ERROR constants as well as the occurence
 * function. */
#include <template_base.h>

/* Used for the FILE type. */
#include <stdio.h>

/*********************************** MACROS ***********************************/

/* The chunk size used to bulk allocate space for the MatchList field arrays. */
#ifndef MATCH_LIST_CHUNK_SIZE
#define MATCH_LIST_CHUNK_SIZE 32
#endif

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/*
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

/*
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
If a format specifier isn't well formed (like a trailing '%' or a "%$" without
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

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
