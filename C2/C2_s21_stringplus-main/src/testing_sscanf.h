#ifndef TESTING_H_
#define TESTING_H_

#include <check.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <errno.h>

// #include "s21_string.h"
#include "s21_sscanf.h"

Suite *s21_sscanf_suit(void);
Suite *s21_strlen_suit(void);
Suite *s21_strncat_suite(void);
Suite *s21_memchr_suite(void);
Suite *s21_memcpy_suite(void);
Suite *s21_memset_suite(void);
Suite *s21_strcspn_suite(void);
Suite *s21_strncmp_suite(void);
Suite *s21_strpbrk_suite(void);
Suite *s21_strchr_suite(void);
Suite *s21_strrchr_suite(void);
Suite *s21_strstr_suite(void);
Suite *s21_to_upper_suite(void);
Suite *s21_to_lower_suite(void);
Suite *s21_insert_suite(void);
Suite *s21_trim_suite(void);
Suite *s21_strtok_suite(void);
Suite *s21_memcmp_suite(void);
Suite *s21_strerror_suite(void);
Suite *s21_sprintf_suite(void);

#endif  // TESTING_H_
