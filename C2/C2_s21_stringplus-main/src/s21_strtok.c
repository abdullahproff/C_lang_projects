#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* last_str = s21_NULL;
  char* start;
  if (str != s21_NULL) {
    start = str;
  } else if (last_str == s21_NULL) {
    return s21_NULL;
  } else {
    start = last_str;
  }
  while (*start) {
    bool is_delim = false;
    for (const char* d = delim; *d; ++d) {
      if (*start == *d) {
        is_delim = true;
        break;
      }
    }
    if (!is_delim) {
      break;
    }
    ++start;
  }
  if (*start == '\0') {
    last_str = s21_NULL;
    return s21_NULL;
  }
  char* end = start + 1;
  while (*end) {
    bool is_delim = false;
    for (const char* d = delim; *d; ++d) {
      if (*end == *d) {
        is_delim = true;
        break;
      }
    }
    if (is_delim) {
      break;
    }
    ++end;
  }
  if (*end == '\0') {
    last_str = s21_NULL;
  } else {
    *end = '\0';
    last_str = end + 1;
  }
  return start;
}
