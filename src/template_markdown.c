/* The header of the library we are implementing here.  */
#include "template.h"

int template_markdown(const char *path, const char *author,
                      const char *contact) {
  /* The buffer used to hold the current date. */
  char current_date[11];
  /* There is no symbol in a markdown file. */
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

  /* We print a line for the body of the document. */
  fprintf(file_handle, "# %s\n", "BODY OF THE DOCUMENT");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Small message for the body of the document. */
  fprintf(file_handle, "__%s__\n", "The body of your document goes here");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We print a line for the metadata section. */
  fprintf(file_handle, "### %s\n", "METADATA");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* Printing the metadata of the document in a table. */
  fprintf(file_handle, "%s\n", "Field | Value");
  fprintf(file_handle, "%s\n", "--- | ---");
  fprintf(file_handle, ":pencil: Contributors | %s\n", author);
  fprintf(file_handle, ":email: Contacts | %s\n", contact);
  fprintf(file_handle, ":date: Creation Date | %s\n", current_date);
  fprintf(file_handle, ":bulb: Language | %s\n", "Markdown Document");
  /* Empty line. */
  fprintf(file_handle, "%s", "\n");

  /* We print a line for the end of the file file. */
  fprintf(file_handle, "### %s\n", "EOF");

  /* Closing the file. */
  fclose(file_handle);

  return SUCCESS;
}
