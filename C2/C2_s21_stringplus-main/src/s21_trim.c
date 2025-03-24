#include "s21_string.h"

int s21_isspace(int c) {
  return (c == ' ' || c == '\0' || c == '\t' || c == '\n' || c == '\v' ||
          c == '\f' || c == '\r');
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *trim_str = s21_NULL;
  if (src != s21_NULL && trim_chars != s21_NULL) {
    char *begin_str = (char *)src;
    char *end_str = (char *)src + s21_strlen(src);
    while (*begin_str && s21_strchr(trim_chars, *begin_str)) {
      begin_str++;
    }
    while (end_str != begin_str && s21_strchr(trim_chars, *(end_str - 1))) {
      end_str--;
    }
    trim_str = (char *)calloc((end_str - begin_str + 1), sizeof(char));
    s21_strncpy(trim_str, begin_str, end_str - begin_str);
    *(trim_str + (end_str - begin_str)) = '\0';
  } else if (src != s21_NULL && trim_chars == s21_NULL) {
    char *begin_str = (char *)src;
    char *end_str = (char *)src + s21_strlen(src);
    while (*begin_str && s21_isspace(*begin_str)) {
      begin_str++;
    }
    while (end_str != begin_str && s21_isspace(*(end_str - 1))) {
      end_str--;
    }
    trim_str = (char *)calloc((end_str - begin_str + 1), sizeof(char));
    s21_strncpy(trim_str, begin_str, end_str - begin_str);
    *(trim_str + (end_str - begin_str)) = '\0';
  }
  return (void *)trim_str;
}