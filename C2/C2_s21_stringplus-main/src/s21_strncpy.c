#include "s21_string.h"

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  char* char_dest = (char*)dest;
  char* char_src = (char*)src;

  for (s21_size_t i = 0; i < n; i++) {
    char_dest[i] = char_src[i];
  }

  return dest;
}