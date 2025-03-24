#include "s21_string.h"
void *s21_memcpy(void *dest, const void *src, size_t n) {
  char *char_dest = (char *)dest;
  char *char_src = (char *)src;
  size_t i = 0;
  while (i != n) {
    char_dest[i] = char_src[i];
    i++;
  }
  return dest;
}