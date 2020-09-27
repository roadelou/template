/* The header of the library for which we are implementing the title function.
 */
#include "template.h"

int title(char *buffer, const char *word, const char symbol,
          const size_t length) {
  /* The length of the word we are going to use as a title. */
  size_t title_length = strlen(word);
  /* We now compute the number os symbols that we will put on the left. We have
   * to fill half of the line, except for the title word and the two spaces
   * before and after it.*/
  size_t symbols_left = (length - title_length - 2) / 2;
  /* From here we can deduce the number of symbols to put on the right. */
  size_t symbols_right = length - title_length - 2 - symbols_left;
  /* We are now going to write the content of the buffer. We start by setting
   * the first symbols using the memset function. */
  memset(buffer, symbol, symbols_left);
  /* We write the first space before the title. */
  *(buffer + symbols_left) = ' ';
  /* We write the title to the buffer using memcpy. */
  memcpy(buffer + symbols_left + 1, word, title_length);
  /* We add the space after the title. */
  *(buffer + symbols_left + title_length + 1) = ' ';
  /* We write the trailing symbols with memset. */
  memset(buffer + symbols_left + title_length + 2, symbol, symbols_right);
  /* Finally, we add the terminating null byte. */
  *(buffer + symbols_left + title_length + 2 + symbols_right) = '\0';
  /* The function call was successfull, we return our success code. */
  return 0;
}
