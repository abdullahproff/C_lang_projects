#include "testing_sscanf.h"

int main(void) {
  int failed_count;
  Suite *suite[] = {
      s21_sscanf_suit(),    s21_strlen_suit(),    s21_strncat_suite(),
      s21_memchr_suite(),   s21_memcpy_suite(),   s21_memset_suite(),
      s21_strcspn_suite(),  s21_strncmp_suite(),  s21_strpbrk_suite(),
      s21_strchr_suite(),   s21_strrchr_suite(),  s21_strstr_suite(),
      s21_to_upper_suite(), s21_to_lower_suite(), s21_insert_suite(),
      s21_trim_suite(),     s21_strtok_suite(),   s21_memcmp_suite(),
      s21_strerror_suite(), s21_sprintf_suite()};
  for (int i = 0; i < 20; i++) {
    SRunner *suite_runner = srunner_create(suite[i]);
    srunner_run_all(suite_runner, CK_NORMAL);
    // Получаем количество проваленных тестов.
    failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }

  if (failed_count != 0) {
    // Сигнализируем о том, что тестирование прошло неудачно.
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}