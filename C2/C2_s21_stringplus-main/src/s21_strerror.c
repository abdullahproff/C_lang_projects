#include "s21_string.h"

void itoa(int number, char *string_number) {
  s21_size_t index = 0;
  int is_neg = number < 0;
  number = is_neg ? -number : number;
  char tmp;

  while (number) {
    string_number[index++] = number % 10 + '0';
    number /= 10;
  }

  if (is_neg) {
    string_number[index++] = '-';
  }

  for (s21_size_t i = 0; i < index / 2; i++) {
    tmp = string_number[i];
    string_number[i] = string_number[index - i - 1];
    string_number[index - i - 1] = tmp;
  }

  string_number[index++] = '\0';
}

char *s21_strerror(int errorNumber) {
  static char error_out[30];
  for (int i = 0; i < 30; i++) {
    error_out[i] = '\0';
  }
  static char string_errnum[20];
  itoa(errorNumber, string_errnum);

  if (errorNumber < MAX_ERRLIST && errorNumber > MIN_ERRLIST) {
    return (char *)errorList[errorNumber];
  } else {
    s21_strcat(error_out, ERROR);
    s21_strcat(error_out, " ");
    s21_strcat(error_out, string_errnum);

    return error_out;
  }
}