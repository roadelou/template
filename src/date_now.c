/* The header of the library we are currently implementing. */
#include "template.h"

int date_now(char *buffer) {
  /* We allocate some memory to hold the current time information. */
  time_t now;
  /* We also allocate a structure to hold the detailed time informations. */
  struct tm *now_struct;
  /* A value used to hold the return code of strftime to check for issues. */
  size_t return_code;
  /* We get the current time from the system. */
  time(&now);
  /* We build the struct representation of this current time. */
  now_struct = localtime(&now);
  /* We write the string representation of the current date to the buffer. */
  return_code = strftime(buffer, 11, "%F", now_struct);
  /* We check the return code for errors. */
  if (return_code == 0) {
    /* A problem arose. */
    return ERROR;
  } else {
    /* The call was a success. */
    return SUCCESS;
  }
}
