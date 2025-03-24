#include "s21_string.h"
char *s21_strrchr(char *str, int c) {
  char *res = s21_NULL;

  while (*str != '\0') {
    if (*str == c) {
      res = str;
    }
    str++;
  }

  return res;
}