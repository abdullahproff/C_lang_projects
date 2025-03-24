#include "s21_string.h"
char* s21_strchr(const char* str, int c);

char* s21_strpbrk(const char* str1, const char* str2) {
  char* first = s21_NULL;

  while (*str2) {
    char* ptr = s21_strchr(str1, *str2++);

    if (ptr) ptr < first || first == s21_NULL ? first = ptr : s21_NULL;
  }

  return first;
}