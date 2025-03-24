#include "s21_string.h"
size_t s21_strcspn(const char *str1, const char *str2) {
  size_t lent = 0;
  int i = 0;
  int c = 0;
  while (str1[i] != '\0') {
    while (str2[c] != str1[i] && str2[c] != '\0') {
      c++;
    }
    if (str2[c] != str1[i]) {
      lent++;
    } else {
      return lent;
    }
    i++;
    c = 0;
  }
  return lent;
}