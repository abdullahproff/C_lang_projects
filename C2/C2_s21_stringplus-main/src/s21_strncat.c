#include "s21_string.h"
char *s21_strncat(char *dest, const char *src, size_t n) {
  char *char_dest = (char *)dest;
  char *char_src = (char *)src;
  int i = 0;
  int c = 0;
  while (dest[i] != '\0') {
    i++;
  }
  while (n--) {
    char_dest[i] = char_src[c];
    c++;
    i++;
  }
  i++;
  dest[i] = '\0';

  return dest;
}