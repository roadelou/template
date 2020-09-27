/* The header of the library we are implementing here.  */
#include "template.h"

int template_c(const char *path, const char *author, const char *contact) {
  /* The buffer used to hold our title lines. */
  char title_line[81];
  /* The buffer used to hold the current date. */
  char current_date[11];
  /* The symbol that we are going to use to build our comments. */
  char symbol = '*';
  /* The file handle that we are going to use to write the templated file. */
  FILE *file_handle;
  /* A variable used to monitor the different calls and watch out for errors. */
  int return_code;

  /* We get the current date. */
  return_code = date_now((char *)&current_date);
  if (return_code == ERROR) {
    /* Something went wrong when getting the current date, we should stop here.
     */
    return ERROR;
  }
  /* We open the file we are going to write.*/
  file_handle = fopen(path, "w");
  /* We check the value of file_handle to see if there is some error. */
  if (file_handle == NULL) {
    /* Could not open the file. */
    return ERROR;
  }

  /* Now that everything has been set up, we can start building our file. */

  /* We build a title for the metadata section. */
  title(title_line, "METADATA", symbol, 78);
  /* We print that line to the target file. */
  fprintf(file_handle, "/%s/\n", title_line);
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Printing the metadata of the document. */
  fprintf(file_handle, "%s\n", "/*");
  fprintf(file_handle, "* Contributors: %s\n", author);
  fprintf(file_handle, "* Contacts: %s\n", contact);
  fprintf(file_handle, "* Creation Date: %s\n", current_date);
  fprintf(file_handle, "* Language: %s\n", "C Source");
  fprintf(file_handle, "%s\n", "*/");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We build a title for the includes. */
  title(title_line, "INCLUDES", symbol, 78);
  /* We print that line to the target file. */
  fprintf(file_handle, "/%s/\n", title_line);
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Small message for the body of the document. */
  fprintf(file_handle, "/* %s */\n", "The includes for your code go here.");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We build a title for the prototypes. */
  title(title_line, "PROTOYPES", symbol, 78);
  /* We print that line to the target file. */
  fprintf(file_handle, "/%s/\n", title_line);
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Small message for the body of the document. */
  fprintf(file_handle, "/* %s */\n",
          "The prototypes of your functions go here.");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We build a title for the main. */
  title(title_line, "BODY", symbol, 78);
  /* We print that line to the target file. */
  fprintf(file_handle, "/%s/\n", title_line);
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Small message for the body of the document. */
  fprintf(file_handle, "/* %s */\n",
          "The main function of your code goes here.");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We build a title for the functions. */
  title(title_line, "FUNCTIONS", symbol, 78);
  /* We print that line to the target file. */
  fprintf(file_handle, "/%s/\n", title_line);
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Small message for the body of the document. */
  fprintf(file_handle, "/* %s */\n", "The functions for your code go here.");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We build the end of file title. */
  title(title_line, "EOF", symbol, 78);
  /* We print that line to the target file. */
  fprintf(file_handle, "/%s/\n", title_line);

  /* Closing the file. */
  fclose(file_handle);

  return SUCCESS;
}
