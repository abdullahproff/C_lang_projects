#include "s21_string.h"
size_t s21_strlen(const char *string) {
  size_t length = 0;

  if (string) {
    while (*(string++)) length++;
  }

  return length;
}