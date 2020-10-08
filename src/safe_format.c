/********************************** METADATA **********************************/

/*
* Contributors: roadelou
* Contacts: 
* Creation Date: 2020-10-08
* Language: C Source
*/

/********************************** INCLUDES **********************************/

/* The header for which we are providing an implementation. */
#include "template.h"

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

int safe_format(FILE *stream, const char *format, const char *author,
                const char *contact, const char *date_now) {
	/* A cursor used to iterate through the format string. */
	int cursor;
	/* The length of the format string. */
	int length = strlen(format);
	/* Scanning each char of the format string. */
	for (cursor=0; cursor<length; cursor++) {
		if (*(format+cursor) == '%') {
			/* We take a decision based on the next character. Note that if '%' is the last character of the string, the next character that we will pick is the termination byte, so there will be no segmentation fault here. */
			switch (*(format + cursor + 1)) {
				case '1':
					/* The format for the author. */
					if (fputs(author, stream) == EOF) {
						/* A problem appeared, we cannot write to the file and have to exit. */
						return ERROR;
					}
					/* We increment the cursor to avoid reading the number again. */
					cursor++;
					break;
				case '2':
					/* The format for the contact. */
					if (fputs(contact, stream) == EOF) {
						/* A problem appeared, we cannot write to the file and have to exit. */
						return ERROR;
					}
					/* We increment the cursor to avoid reading the number again. */
					cursor++;
					break;
				case '3':
					/* The format for the date. */
					if (fputs(date_now, stream) == EOF) {
						/* A problem appeared, we cannot write to the file and have to exit. */
						return ERROR;
					}
					/* We increment the cursor to avoid reading the number again. */
					cursor++;
					break;
				case '%':
					/* We print a single '%' and move the cursor. */
					if (fputc('%', stream) == EOF) {
						/* A problem appeared, we cannot write to the file and have to exit. */
						return ERROR;
					}
					cursor++;
					break;
				default:
					/* There is no interpretation for this '%', we just leave it as is. */
					if (fputc('%', stream) == EOF) {
						/* A problem appeared, we cannot write to the file and have to exit. */
						return ERROR;
					}
					/* We don't move the cursor because we haven't used the next character yet. */
					break;
			}

		}
		else {
			/* We just encountered an normal character, we print it. */
			if (fputc(*(format+cursor), stream) == EOF) {
				/* A problem appeared, we cannot write to the file and have to exit. */
				return ERROR;
			}
		}
	}
	/* If we reach this line, the formatting was successfull. */
	return SUCCESS;
}

/************************************ EOF *************************************/
