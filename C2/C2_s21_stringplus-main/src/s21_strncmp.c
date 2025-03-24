#include "s21_string.h"
int s21_strncmp(const char* str1, const char* str2, size_t n) {
  char* first = (char*)str1;
  char* second = (char*)str2;

  while (n--) {
    if (*first++ != *second++) {
      return *(first - 1) - *(second - 1);
    }
  }

  return 0;
}