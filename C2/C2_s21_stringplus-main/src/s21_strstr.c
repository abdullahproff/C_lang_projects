#include "s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  char *p_str1;
  char *p_str2;
  p_str1 = (char *)haystack;
  p_str2 = (char *)needle;

  size_t i = s21_strlen(p_str1);
  size_t n = s21_strlen(p_str2);
  while (i != 0) {
    if (s21_strncmp(p_str1, p_str2, n) == 0) {
      return p_str1;
    }
    p_str1++;
    i--;
  }
  return s21_NULL;
}