/* The header of the library we are using. */
#include "template.h"

/*
Description
===========
Prints help for the user on stdout.

Returns
=======
The return value of the printf call.
*/
int print_help(void);

int main(int argc, const char **argv) {
  /* A cursor used to loop. */
  int cursor = 0;
  /* The current path on which we are working. */
  const char *path;
  /* A variable used to store the length of the string of the path */
  size_t length;
  /* We get the user name from, the environment. */
  const char *author;
  /* Sme for the contact, we will also get it from the environment. */
  const char *contact;

  /* We get the user name, we see if the dedicated variable is set. */
  author = getenv("TEMPLATE_USER");

  if (author == NULL) {
    /* If the dedicated variable is not set, we default to the Linux user name.
     */
    author = getenv("USER");
  }

  /* We get the user contact. */
  contact = getenv("TEMPLATE_CONTACT");

  if (contact == NULL) {
    /* If not contact is provided, we leave an empty field. */
    contact = "";
  }

  /* We simply loop over the given paths and create them all. */
  for (; cursor < argc; cursor++) {
    /* We get the new file to create. */
    path = *(argv + cursor);
    /* We compute the length pf the given string. */
    length = strlen(path);

    /* We branch to the desired template based on the file extension. */
    if (strncmp(path + length - 2, ".c", 2) == 0) {
      template_c(path, author, contact);
    } else if (strncmp(path + length - 2, ".h", 2) == 0) {
      template_header(path, author, contact);
    } else if (strncmp(path, "Makefile", 8) == 0) {
      template_makefile(path, author, contact);
    } else if (strncmp(path + length - 3, ".pl", 3) == 0) {
      template_perl(path, author, contact);
    } else if (strncmp(path + length - 3, ".py", 3) == 0) {
      template_python(path, author, contact);
    } else if (strncmp(path + length - 3, ".md", 3) == 0) {
      template_markdown(path, author, contact);
    } else if (strncmp(path, "-h", 2) == 0 || strncmp(path, "--help", 6) == 0) {
      /* We treat -h or --help differently, it prints some help for the user. */
      print_help();
    } else {
      /* If the file type is not recognized, we default to the blank template.
       */
      template_blank(path, author, contact);
    }
  }

  /* Execution was successfull. */
  return 0;
}

int print_help(void) {
  return printf("%s\n",
                "Usage: template [-h|--help] [filenames...]\n"
                "\n"
                "Description\n"
                "===========\n"
                "Creates the given files from templates based on their "
                "extensions.");
}
