#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *ins_str = s21_NULL;

  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t size_src = s21_strlen(src);
    s21_size_t size_str = s21_strlen(str);
    s21_size_t size = size_src + size_str;

    if (start_index <= size_src) {
      ins_str = (char *)calloc((size + 1), sizeof(char));
      for (s21_size_t i = 0, j = 0; i <= size; i++) {
        if (start_index == i) {
          while (j < size_str) {
            ins_str[i] = str[j];
            j++;
            i++;
          }
        }
        ins_str[i] = src[i - j];
      }
    }
  }
  return (void *)ins_str;
}
