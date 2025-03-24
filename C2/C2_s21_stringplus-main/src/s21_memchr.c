#include "s21_string.h"
void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *result = (unsigned char *)str;
  while (n--) {
    if (*result++ == (unsigned char)c) {
      return (result - 1);
    }
  }
  return s21_NULL;
}