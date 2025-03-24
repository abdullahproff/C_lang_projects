#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  char *in_str = (char *)str;
  size_t len = s21_strlen(in_str);
  res = (char *)calloc(len + 1, sizeof(char));
  if (res != s21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        res[i] = str[i] - 32;
      } else {
        res[i] = str[i];
      }
    }
  }
  return res;
}