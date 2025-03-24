#include "testing_sscanf.h"

START_TEST(one_sscanf) {
  char *str = "1";
  char *format = "%d";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(two_sscanf) {
  char *str = "-1";
  char *format = "%d";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(tree_sscanf) {
  char *str = "12345";
  char *format = "%4d";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(fore_sscanf) {
  char *str = "-12345";
  char *format = "%4d";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(five_sscanf) {
  char *str = "123";
  char *format = "%hd";
  short int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(six_sscanf) {
  char *str = "123";
  char *format = "%hhd";
  signed char d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(seven_sscanf) {
  char *str = "123";
  char *format = "%lld";
  long long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  // printf("\ns21_sscanf %lld \n", d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(eight_sscanf) {
  char *str = "123";
  char *format = "%ld";
  long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(symbol_sscanf) {
  char *str = "c s";
  char *format = "%c";
  char symbol1, symbol2;

  int result1 = sscanf(str, format, &symbol1);
  int result2 = s21_sscanf(str, format, &symbol2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(symbol1, symbol2);

  format = "%*c %c";
  result1 = sscanf(str, format, &symbol1);
  result2 = s21_sscanf(str, format, &symbol2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(symbol1, symbol2);

  format = "%lc";
  wchar_t lsymbol1, lsymbol2;
  result1 = sscanf(str, format, &lsymbol1);
  result2 = s21_sscanf(str, format, &lsymbol2);
  ck_assert_int_eq(result1, result2);
  symbol1 = (char)lsymbol1;
  symbol2 = (char)lsymbol2;
  ck_assert_int_eq(symbol1, symbol2);
}
END_TEST

START_TEST(n_sscanf) {
  char *str = "nnn";
  char *format = "%n";
  int symbol1 = 0;
  int symbol2 = 0;

  int result1 = sscanf(str, format, &symbol1);
  int result2 = s21_sscanf(str, format, &symbol2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(symbol1, symbol2);

  format = "%*n";
  result1 = sscanf(str, format, &symbol1);
  result2 = s21_sscanf(str, format, &symbol2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(symbol1, symbol2);
}
END_TEST
START_TEST(proc_sscanf) {
  char *str = "%";
  char *format = "%%";
  char symbol1, symbol2;

  int result1 = sscanf(str, format, &symbol1);
  int result2 = s21_sscanf(str, format, &symbol2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(symbol1, symbol2);

  format = "%*%";
  result1 = sscanf(str, format, &symbol1);
  result2 = s21_sscanf(str, format, &symbol2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(symbol1, symbol2);
}
END_TEST

//   float

START_TEST(f_one_sscanf) {
  char *str = "1.2";
  char *format = "%f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST
START_TEST(f_two_sscanf) {
  char *str = "-1.23";
  char *format = "%f";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST
START_TEST(f_tree_sscanf) {
  char *str = "12345";
  char *format = "%4f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST
START_TEST(f_fore_sscanf) {
  char *str = "-12345.6789";
  char *format = "%4f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(f_five_sscanf) {
  char *str = "1.0";  // ??????????
  char *format = "%Lf";
  long double d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(f_six_sscanf) {
  char *str = "-12345.0000";
  char *format = "%4f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(f_seven_sscanf) {
  char *str = "1.345e-05";
  char *format = "%7f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(f_eight_sscanf) {
  char *str = "1.345e-05";
  char *format = "%f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST
START_TEST(f_nine_sscanf) {
  char *str = "1.345e+05";
  char *format = "%f";
  float d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(f_ten_sscanf) {
  char *str = "1.345e+05";
  char *format = "%Lf";
  long double d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(d1, d2, 0.0001);
}
END_TEST

//  o   eight

START_TEST(o_one_sscanf) {
  char *str = "12";
  char *format = "%o";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(o_two_sscanf) {
  char *str = "14";
  char *format = "%o";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(o_tree_sscanf) {
  char *str = "12345";
  char *format = "%4o";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(o_fore_sscanf) {
  char *str = "-12345";
  char *format = "%4o";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}

START_TEST(o_five_sscanf) {
  char *str = "123";
  char *format = "%ho";
  short int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(o_six_sscanf) {
  char *str = "123";
  char *format = "%hho";
  signed char d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(o_seven_sscanf) {
  char *str = "123453456555555";
  char *format = "%llo";
  long long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  // printf("\ns21_sscanf %lld \n", d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(o_eight_sscanf) {
  char *str = "123444444";
  char *format = "%lo";
  long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

// test xxxxxxxx

START_TEST(x_one_sscanf) {
  char *str = "12aAb";
  char *format = "%x";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(x_two_sscanf) {
  char *str = "14";
  char *format = "%X";
  int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(x_tree_sscanf) {
  char *str = "12345";
  char *format = "%hx";
  short int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(x_fore_sscanf) {
  char *str = "123";
  char *format = "%hhx";
  signed char d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}

START_TEST(x_five_sscanf) {
  char *str = "12345";
  char *format = "%lX";
  long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(x_six_sscanf) {
  char *str = "123adf3";
  char *format = "%llx";
  long long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(x_seven_sscanf) {
  char *str = "123453456555555";
  char *format = "%6llx";
  long long int d1, d2;
  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  // printf("\ns21_sscanf %lld \n", d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

// u test
START_TEST(u_sscanf) {
  char *str = "1";
  char *format = "%u";
  unsigned int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(d1, d2);

  short unsigned int sd1, sd2;
  format = "%hu";
  result1 = sscanf(str, format, &sd1);
  result2 = s21_sscanf(str, format, &sd2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(sd1, sd2);

  long unsigned int ld1, ld2;
  format = "%lu";
  result1 = sscanf(str, format, &ld1);
  result2 = s21_sscanf(str, format, &ld2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(ld1, ld2);

  format = "%*lu";
  result1 = sscanf(str, format, &ld1);
  result2 = s21_sscanf(str, format, &ld2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(ld1, ld2);
}
END_TEST

START_TEST(hh_sscanf) {
  char *str = "122";
  char *format = "%hhu";
  unsigned char d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(d1, d2);

  unsigned short int sd1, sd2;
  format = "%hu";
  result1 = sscanf(str, format, &sd1);
  result2 = s21_sscanf(str, format, &sd2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(sd1, sd2);
}
END_TEST
START_TEST(ll_sscanf) {
  char *str = "12224352345234324";
  char *format = "%llu";
  unsigned long long int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(nu_sscanf) {
  char *str = "12224352345234324";
  char *format = "%10llu";
  unsigned long long int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

//  i test
START_TEST(i_sscanf) {
  char *str = "01111";
  char *format = "%i";
  unsigned int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(ix_sscanf) {
  char *str = "0X1111";
  char *format = "%i";
  unsigned int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(id_sscanf) {
  char *str = "-1111";
  char *format = "%i";
  int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(id_minus_sscanf) {
  char *str = "-1111";
  char *format = "%4i";
  int d1, d2;

  int result1 = sscanf(str, format, &d1);
  int result2 = s21_sscanf(str, format, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

// p test

START_TEST(p_sscanf) {
  char str[20] = "0x123456a";

  char *format = "%p";
  void *p1, *p2;

  int result1 = sscanf(str, format, &p1);
  int result2 = s21_sscanf(str, format, &p2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST
START_TEST(pn_sscanf) {
  char str[] = "0x123456a";

  char *format = "%3p";
  void *p1, *p2;

  int result1 = sscanf(str, format, &p1);
  int result2 = s21_sscanf(str, format, &p2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

// s test
START_TEST(string_sscanf) {
  char *str = "school_21 school_21";
  char *format = "%s%s";
  char str1[30], str2[30];

  int result1 = sscanf(str, format, str1, str2);
  int result2 = s21_sscanf(str, format, str1, str2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);

  format = "%*s";
  result1 = sscanf(str, format, str1);
  result2 = s21_sscanf(str, format, str2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);

  format = "%3s";
  result1 = sscanf(str, format, str1);
  result2 = s21_sscanf(str, format, str2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(dot_sscanf) {
  char *str = "1; 1";
  char *format = "%d;%d";
  int d1, d2;
  int result1 = sscanf(str, format, &d1, &d2);
  int result2 = s21_sscanf(str, format, &d1, &d2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
START_TEST(dot_2_sscanf) {
  char *str = "1, 1";
  char *format = "%d;%d";
  int d1, d2;
  int result1 = sscanf(str, format, &d1, &d2);
  int result2 = s21_sscanf(str, format, &d1, &d2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

// ========================================== s21_string.h
// s21_strlen.c

START_TEST(test_1) {
  char test[] = "djdjdjd";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST
START_TEST(test_2) {
  char test[] = "";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST
START_TEST(test_3) {
  char test[] = "\0";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST
START_TEST(test_4) {
  char test[] = "\n";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

Suite *s21_sscanf_suit(void) {
  Suite *s;
  TCase *one_test, *two_test, *tree_test, *fore_test, *five_test, *six_test,
      *p_test, *s_test, *dot_test;

  s = suite_create("s21_sscanf");

  one_test = tcase_create("One test");  // %d
  tcase_add_test(one_test, one_sscanf);
  tcase_add_test(one_test, two_sscanf);
  tcase_add_test(one_test, tree_sscanf);
  tcase_add_test(one_test, fore_sscanf);
  tcase_add_test(one_test, five_sscanf);
  tcase_add_test(one_test, six_sscanf);
  tcase_add_test(one_test, seven_sscanf);
  tcase_add_test(one_test, eight_sscanf);
  tcase_add_test(one_test, symbol_sscanf);
  tcase_add_test(one_test, n_sscanf);
  tcase_add_test(one_test, proc_sscanf);
  suite_add_tcase(s, one_test);

  two_test = tcase_create("float One test");  // %f
  tcase_add_test(one_test, f_one_sscanf);
  tcase_add_test(one_test, f_two_sscanf);
  tcase_add_test(one_test, f_tree_sscanf);
  tcase_add_test(one_test, f_fore_sscanf);
  tcase_add_test(one_test, f_five_sscanf);
  tcase_add_test(one_test, f_six_sscanf);
  tcase_add_test(one_test, f_seven_sscanf);
  tcase_add_test(one_test, f_eight_sscanf);
  tcase_add_test(one_test, f_nine_sscanf);
  tcase_add_test(one_test, f_ten_sscanf);
  suite_add_tcase(s, two_test);

  tree_test = tcase_create("eight One test");  // %o
  tcase_add_test(one_test, o_one_sscanf);
  tcase_add_test(one_test, o_two_sscanf);
  tcase_add_test(one_test, o_tree_sscanf);
  tcase_add_test(one_test, o_fore_sscanf);
  tcase_add_test(one_test, o_five_sscanf);
  tcase_add_test(one_test, o_six_sscanf);
  tcase_add_test(one_test, o_seven_sscanf);
  tcase_add_test(one_test, o_eight_sscanf);
  suite_add_tcase(s, tree_test);

  fore_test = tcase_create("sixteen fore test");
  tcase_add_test(one_test, x_one_sscanf);
  tcase_add_test(one_test, x_two_sscanf);
  tcase_add_test(one_test, x_tree_sscanf);
  tcase_add_test(one_test, x_fore_sscanf);
  tcase_add_test(one_test, x_five_sscanf);
  tcase_add_test(one_test, x_six_sscanf);
  tcase_add_test(one_test, x_seven_sscanf);
  suite_add_tcase(s, fore_test);

  five_test = tcase_create("unsigned fore test");
  tcase_add_test(one_test, u_sscanf);
  tcase_add_test(one_test, hh_sscanf);
  tcase_add_test(one_test, ll_sscanf);
  tcase_add_test(one_test, nu_sscanf);
  suite_add_tcase(s, five_test);

  six_test = tcase_create("i fore test");
  tcase_add_test(one_test, i_sscanf);
  tcase_add_test(one_test, ix_sscanf);
  tcase_add_test(one_test, id_sscanf);
  tcase_add_test(one_test, id_minus_sscanf);
  suite_add_tcase(s, six_test);

  p_test = tcase_create("n fore test");
  tcase_add_test(one_test, p_sscanf);
  tcase_add_test(one_test, pn_sscanf);
  suite_add_tcase(s, p_test);

  s_test = tcase_create("s string test");
  tcase_add_test(one_test, string_sscanf);
  suite_add_tcase(s, s_test);

  dot_test = tcase_create("; : test");
  tcase_add_test(one_test, dot_sscanf);
  tcase_add_test(one_test, dot_2_sscanf);
  suite_add_tcase(s, dot_test);

  return s;
}

Suite *s21_strlen_suit(void) {
  Suite *s;
  TCase *strlen;
  s = suite_create("s21_sscanf");

  strlen = tcase_create("s21_strlen");
  tcase_add_test(strlen, test_1);
  tcase_add_test(strlen, test_2);
  tcase_add_test(strlen, test_3);
  tcase_add_test(strlen, test_4);
  suite_add_tcase(s, strlen);

  return s;
}
START_TEST(testcat_1) {
  char str1[20] = "djdjdjdf";
  char str2[20] = "00000";
  size_t n = 8;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(testcat_2) {
  char str1[20] = "djd";
  char str2[20] = "000444400";
  size_t n = 8;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(testcat_3) {
  char str1[20] = "djd";
  char str2[20] = "000444400";
  size_t n = 0;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(testcat_4) {
  char str1[20] = "";
  char str2[20] = "";
  size_t n = 12;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *suite = suite_create("s21_strncat.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на длину строки");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, testcat_1);
  tcase_add_test(tcase_core, testcat_2);
  tcase_add_test(tcase_core, testcat_3);
  tcase_add_test(tcase_core, testcat_4);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(memchr_1) {
  char str1[20] = "djdjdjdf";
  int i = 'f';
  size_t n = 8;
  ck_assert_ptr_eq(s21_memchr(str1, i, n), memchr(str1, i, n));
}
END_TEST
START_TEST(memchr_2) {
  char str1[20] = "djdjdjdf";
  int i = 's';
  size_t n = 8;
  ck_assert_ptr_eq(s21_memchr(str1, i, n), memchr(str1, i, n));
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *suite = suite_create("s21_memchr.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на длину строки");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, memchr_1);
  tcase_add_test(tcase_core, memchr_2);  // проверка на  NULL

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(memcpy_1) {
  char str1[20] = "djdjdjdf";
  char str2[20] = "00000000";
  size_t n = 8;
  ck_assert_str_eq(s21_memcpy(str1, str2, n), memcpy(str1, str2, n));
}
END_TEST
START_TEST(memcpy_2) {
  char str1[20] = "djdjdjdf";
  char str2[20] = "";
  size_t n = 8;
  ck_assert_str_eq(s21_memcpy(str1, str2, n), memcpy(str1, str2, n));
}
END_TEST
START_TEST(memcpy_3) {
  char str1[20] = "djdjdjdf";
  char str2[1] = "";
  size_t n = 8;
  ck_assert_str_eq(s21_memcpy(str1, str2, n), memcpy(str1, str2, n));
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *suite = suite_create("s21_memcpy.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на длину строки");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, memcpy_1);
  tcase_add_test(tcase_core, memcpy_2);
  tcase_add_test(tcase_core, memcpy_3);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

END_TEST
START_TEST(memset_1) {
  char str1[] = "1234567890";
  char str2[] = "1234567890";
  int i = 'a';
  size_t n = 9;
  size_t t = 9;
  for (; i < 127; i++) {
    ck_assert_str_eq(s21_memset(str1, i, n), memset(str2, i, t));
  }
}
END_TEST

START_TEST(memset_2) {
  char str1[] = "1234567890";
  char str2[] = "1234567890";
  int i = 'a';
  size_t n = 0;
  size_t t = 0;
  for (; i < 127; i++) {
    ck_assert_str_eq(s21_memset(str1, i, n), memset(str2, i, t));
  }
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *suite = suite_create("s21_memset.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, memset_1);
  tcase_add_test(tcase_core, memset_2);
  // tcase_add_test(tcase_core, memcpy_3);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(strcspn_1) {
  char str1[] = "1234567890";
  char str2[] = "890";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(strcspn_2) {
  char str1[] = "1234567890";
  char str2[] = "f";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}

Suite *s21_strcspn_suite(void) {
  Suite *suite = suite_create("s21_strcspn.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strcspn_1);
  tcase_add_test(tcase_core, strcspn_2);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(strncmp_1) {
  char str1[] = "1234567890";
  char str2[] = "1234567890";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
START_TEST(strncmp_2) {
  char str1[] = "1234567890";
  char str2[] = "1234507890";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST
START_TEST(strncmp_3) {
  char str1[] = "1234507890";
  char str2[] = "1234567890";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST
START_TEST(strncmp_4) {
  char str1[] = "";
  char str2[] = "1234567890";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *suite = suite_create("s21_strncmp.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strncmp_1);
  tcase_add_test(tcase_core, strncmp_2);
  tcase_add_test(tcase_core, strncmp_3);
  tcase_add_test(tcase_core, strncmp_4);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}
START_TEST(strpbrk_1) {
  char str1[] = "1234567890";
  char str2[] = "890";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST
START_TEST(strpbrk_2) {
  char str1[] = "1234567890";
  char str2[] = "";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *s21_strpbrk_suite(void) {
  Suite *suite = suite_create("s21_strpbrk.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strpbrk_1);
  tcase_add_test(tcase_core, strpbrk_2);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}
START_TEST(strchr_1) {
  char str1[] = "1234567890";
  int i = '8';

  ck_assert_ptr_eq(s21_strchr(str1, i), strchr(str1, i));
}
END_TEST
START_TEST(strchr_2) {
  char str1[] = "1234567790";
  int i = '8';

  ck_assert_ptr_eq(s21_strchr(str1, i), strchr(str1, i));
}
END_TEST
START_TEST(strchr_3) {
  char str1[] = "1234567790";
  int i = '\0';

  ck_assert_ptr_eq(s21_strchr(str1, i), strchr(str1, i));
}
END_TEST
START_TEST(strchr_4) {
  char str1[] = "";
  int i = '\0';

  ck_assert_ptr_eq(s21_strchr(str1, i), strchr(str1, i));
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *suite = suite_create("s21_strchr.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strchr_1);
  tcase_add_test(tcase_core, strchr_2);
  tcase_add_test(tcase_core, strchr_3);
  tcase_add_test(tcase_core, strchr_4);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}
START_TEST(strrchr_1) {
  char str1[] = "123456389";
  int i = '3';

  ck_assert_ptr_eq(s21_strrchr(str1, i), strrchr(str1, i));
}
END_TEST

START_TEST(strrchr_2) {
  char str1[] = "123456389";
  int i = 'f';

  ck_assert_ptr_eq(s21_strrchr(str1, i), strrchr(str1, i));
}
END_TEST

START_TEST(strrchr_3) {
  char str1[] = "123456389";
  int i = '\n';

  ck_assert_ptr_eq(s21_strrchr(str1, i), strrchr(str1, i));
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *suite = suite_create("s21_strrchr.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strrchr_1);
  tcase_add_test(tcase_core, strrchr_2);
  tcase_add_test(tcase_core, strrchr_3);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(strstr_1) {
  char str1[] = "123456389";
  char str2[] = "456";

  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST
START_TEST(strstr_2) {
  char str1[] = "123456389";
  char str2[] = "";  //  проверка на NULL

  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST
START_TEST(strstr_3) {
  char str1[] = "123456389";
  char str2[] = "abc";  //  проверка на NULL

  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *suite = suite_create("s21_strstr.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка на заполняемость");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strstr_1);
  tcase_add_test(tcase_core, strstr_2);
  tcase_add_test(tcase_core, strstr_3);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(to_upper_1) {
  char str1[] = "abcd";
  char str2[] = "ABCD";

  ck_assert_str_eq(s21_to_upper(str1), str2);
}
END_TEST
START_TEST(to_upper_2) {
  char str1[] = "aBcdefghijklmnopqrstuvwxyz";
  char str2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  ck_assert_str_eq(s21_to_upper(str1), str2);
}
END_TEST

Suite *s21_to_upper_suite(void) {
  Suite *suite = suite_create("s21_to_upper.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка Курсива");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, to_upper_1);
  tcase_add_test(tcase_core, to_upper_2);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(to_lower_1) {
  char str1[] = "ABCD";
  char str2[] = "abcd";

  ck_assert_str_eq(s21_to_lower(str1), str2);
}
END_TEST
START_TEST(to_lower_2) {
  char str1[] = "AbCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";

  ck_assert_str_eq(s21_to_lower(str1), str2);
}
END_TEST

Suite *s21_to_lower_suite(void) {
  Suite *suite = suite_create("s21_to_lower.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка Курсива");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, to_lower_1);
  tcase_add_test(tcase_core, to_lower_2);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(to_insert_1) {
  char str1[] = "ABCD";
  char str2[] = "123";
  char res[] = "A123BCD";
  s21_size_t n = 1;

  ck_assert_str_eq(s21_insert(str1, str2, n), res);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *suite = suite_create("s21_to_lower.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Проверка Курсива");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, to_insert_1);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(to_trim_1) {
  char str1[] = "123ABCD";
  char str2[] = "123";
  char res[] = "ABCD";

  ck_assert_str_eq(s21_trim(str1, str2), res);
}
END_TEST
START_TEST(to_trim_2) {
  char str1[] = "123ABCD";
  char *str2 = s21_NULL;
  char *res = s21_NULL;

  ck_assert_ptr_eq(s21_trim(str1, str2), res);
}
END_TEST
START_TEST(to_trim_3) {
  char str1[] = "123  ABCD";
  char str2[] = "123";
  char res[] = "ABCD";

  ck_assert_str_eq(s21_trim(str1, str2), res);
}

START_TEST(test_trim_1) {
  char s1[30] = "-?hello, world!";
  char s3[] = "!?-";
  char s4[] = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_3) {
  char *s1 = s21_NULL;
  char s3[] = "";
  char *s4 = s21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_4) {
  char s1[30] = "!!!abcdefghij!?!";
  char s3[] = "!?";
  char s4[] = "abcdefghij";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = "abc";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_6) {
  char s1[30] = "hello, world!";
  char s3[] = "?!";
  char *s4 = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_7) {
  char *s1 = s21_NULL;
  char *s3 = s21_NULL;
  char *s4 = s21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_9) {
  char s1[] = " wtf ";
  char *s3 = s21_NULL;
  char *s4 = "wtf";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_10) {
  char s1[] = " wtf ";
  char *s3 = "";
  char *s4 = " wtf ";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_11) {
  char s1[30] = "       hello, world!  ";
  char s3[] = " ";
  char *s4 = "hello, world!";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_12) {
  char s1[30] = "we will we will rock ya    ";
  char *s3 = s21_NULL;
  char *s4 = "we will we will rock ya";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_13) {
  char s1[30] = "we will we will rock ya    ";
  char s3[] = " ";
  char *s4 = "we will we will rock ya";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

Suite *s21_trim_suite(void) {
  Suite *suite = suite_create("s21_trim.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Trim");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, to_trim_1);
  tcase_add_test(tcase_core, to_trim_2);
  tcase_add_test(tcase_core, to_trim_3);
  tcase_add_test(tcase_core, test_trim_1);
  tcase_add_test(tcase_core, test_trim_2);
  tcase_add_test(tcase_core, test_trim_3);
  tcase_add_test(tcase_core, test_trim_4);
  tcase_add_test(tcase_core, test_trim_5);
  tcase_add_test(tcase_core, test_trim_6);
  tcase_add_test(tcase_core, test_trim_7);
  tcase_add_test(tcase_core, test_trim_8);
  tcase_add_test(tcase_core, test_trim_9);
  tcase_add_test(tcase_core, test_trim_10);
  tcase_add_test(tcase_core, test_trim_11);
  tcase_add_test(tcase_core, test_trim_12);
  tcase_add_test(tcase_core, test_trim_13);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(strtok_1) {
  char str[] = "123 - 4567 . 890";
  char delim[] = " ";

  ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST
START_TEST(strtok_2) {
  char str[] = "123 - 4567 . 890";
  char delim[] = "";

  ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST
START_TEST(strtok_3) {
  char str[] = "";
  char delim[] = "";

  ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_4) {
  char str[] = "1234";
  char delim[] = "1234";

  ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strtok_5) {
  char *str;
  str = NULL;
  char delim[] = "1234";

  ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST
Suite *s21_strtok_suite(void) {
  Suite *suite = suite_create("s21_strtok.c");
  // Набор разбивается на группы тестов разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("strtok");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, strtok_1);
  tcase_add_test(tcase_core, strtok_2);
  tcase_add_test(tcase_core, strtok_3);
  tcase_add_test(tcase_core, strtok_4);
  tcase_add_test(tcase_core, strtok_5);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

START_TEST(test_s21_memcmp_equal_strings) {
  const char str1[] = "Hello";
  const char str2[] = "Hello";
  int result = s21_memcmp(str1, str2, sizeof(str1));
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_memcmp_different_strings) {
  const char str1[] = "Hello";
  const char str2[] = "World";
  int result = s21_memcmp(str1, str2, sizeof(str1));
  ck_assert_int_ne(result, 0);
}
END_TEST

START_TEST(test_s21_memcmp_partial_match) {
  const char str1[] = "Hello World";
  const char str2[] = "Hello";
  int result = s21_memcmp(str1, str2, sizeof(str2));
  int result2 = memcmp(str1, str2, sizeof(str2));
  ck_assert_int_eq(result, result2);
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *test_case = tcase_create("Core");

  tcase_add_test(test_case, test_s21_memcmp_equal_strings);
  tcase_add_test(test_case, test_s21_memcmp_different_strings);
  tcase_add_test(test_case, test_s21_memcmp_partial_match);

  suite_add_tcase(suite, test_case);
  return suite;
}

START_TEST(all_strerror) {
  for (int i = -200; i <= 200; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *suite = suite_create("s21_strerror");
  TCase *test_case = tcase_create("error");

  /// Тест всех целочисленных значений ошибок из отрезка [-200; 200].
  tcase_add_test(test_case, all_strerror);
  suite_add_tcase(suite, test_case);

  return suite;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

*/
START_TEST(c_sprintf) {
  struct input_data {
    const char *format;
    const char c;
  };
  struct input_data testcases[] = {{"%c", 'a'},   {"%c", ' '},  {"%-09c", 'a'},
                                   {"%09c", 'a'}, {"%4c", 'a'}, {"%-4c", 'a'},
                                   {"%4.9c", 'a'}};
  s21_size_t n = sizeof(testcases) / sizeof(testcases[0]);

  for (s21_size_t i = 0; i < n; i++) {
    char result[255] = {0};
    char expected_result[255] = {0};
    s21_sprintf(result, testcases[i].format, testcases[i].c);
    sprintf(expected_result, testcases[i].format, testcases[i].c);
    ck_assert_pstr_eq(result, expected_result);
  }
}
END_TEST
START_TEST(d_sprintf) {
  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result,
              "%d %3d %04d %-4d %+4d % d %12d %.3d %+5.5d %d %d %-1d %04d %ld",
              123, 123, 123, 123, 123, 123, 123, 123456, 123456, 123, -12345,
              -12345, -12345, 123456L);
  sprintf(expected_result,
          "%d %3d %04d %-4d %+4d % d %12d %.3d %+5.5d %d %d %-1d %04d %ld", 123,
          123, 123, 123, 123, 123, 123, 123456, 123456, 123, -12345, -12345,
          -12345, 123456L);
  ck_assert_str_eq(result, expected_result);
}
END_TEST

START_TEST(s_sprintf) {
  char str[255] = {0};
  char str1[255] = {0};
  char format[] = "%s %5s %-5s %+5s %-015s %%%";

  s21_sprintf(str, format, "testline", "testline", "testline", "testline",
              "testline");
  sprintf(str1, format, "testline", "testline", "testline", "testline",
          "testline");

  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(u_sprintf) {
  char format[] = "%u %10u %010u %+10u % u %-10u ";

  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, 12345, 12345, 12345, 12345, 12345, 12345);
  sprintf(expected_result, format, 12345, 12345, 12345, 12345, 12345, 12345);
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST
START_TEST(f_sprintf) {
  char format[] = "%f %10f %010f %-010f %+010.2f % f %-f %-015f %f %#f %.0f";

  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, 123.45, 123.45, 123.45, 123.45, 123.45, 123.45,
              -123.45, -123.45, -123.45, -123.45, -123.45, -123.0);
  sprintf(expected_result, format, 123.45, 123.45, 123.45, 123.45, 123.45,
          123.45, -123.45, -123.45, -123.45, -123.45, -123.0);
  ck_assert_str_eq(result, expected_result);
}
END_TEST
START_TEST(g_sprintf) {
  char format[] = "% 10g %20g % g %+020g %-020g %-5.3g %10g %2g %#g";

  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, -1234.567, 1234.567, 1234.567, 1234.567,
              -1234.567, 1234.567, -1234.567, -1234.567, 1234.567);
  sprintf(expected_result, format, -1234.567, 1234.567, 1234.567, 1234.567,
          -1234.567, 1234.567, -1234.567, -1234.567, 1234.567);
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST

START_TEST(size_sprintf) {
  char format[] = "%llg %hhg ";  // %+020g %-020g %-5.3g %10g %2g %#g

  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, -1234.567, 1234.567, 1234.567, 1234.567,
              -1234.567, 1234.567, -1234.567, -1234.567, 1234.567);
  sprintf(expected_result, format, -1234.567, 1234.567, 1234.567, 1234.567,
          -1234.567, 1234.567, -1234.567, -1234.567, 1234.567);
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST

START_TEST(e_sprintf) {
  char format[] =
      "%e %e %10e %010e %-014e %14e %014e  %-20e  %-020e %20e  %020e % e % 12e "
      "%+e %+016e  ";  // 16

  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, -14E+05, 14E+05, -14E+05, -14E+05, -14E+05,
              -14E+05, -14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05,
              14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05);  // 20

  sprintf(expected_result, format, -14E+05, 14E+05, -14E+05, -14E+05, -14E+05,
          -14E+05, -14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05,
          14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05, 14E+05);  // 20
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST

START_TEST(p_sprintf) {
  char format[] = "%p";  // 1
  int a = 0;
  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, &a);  // 1

  sprintf(expected_result, format, &a);  // 1
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST

START_TEST(x_sprintf) {
  char format[] =
      "%x %2x %10x %#010x %#10x % 10x  %-10x %010x %#x %#-x  ";  // 4  %#x
  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, 1567, 1567, 1567, 1567, 1567, 1567, 1567, 1567,
              1567, 1567, 1567, 1567, 1567, 1567, 1567);  // 15

  sprintf(expected_result, format, 1567, 1567, 1567, 1567, 1567, 1567, 1567,
          1567, 1567, 1567, 1567, 1567, 1567, 1567, 1567);  // 15
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST

START_TEST(o_sprintf) {
  char format[] =
      "%o %2o %10o %-10o % 10o %#o %#-o %#10o %#o %#-o %010o";  // 4  %#x
  char result[255] = {0};
  char expected_result[255] = {0};
  s21_sprintf(result, format, 1567, 1567, 1567, 1567, 1567, 1567, 1567, 1567,
              1567, 1567, 1567, 1567, 1567, 1567, 1567);  // 15

  sprintf(expected_result, format, 1567, 1567, 1567, 1567, 1567, 1567, 1567,
          1567, 1567, 1567, 1567, 1567, 1567, 1567, 1567);  // 15
  ck_assert_pstr_eq(result, expected_result);
}
END_TEST

/*
START_TEST(sixth_sprintf) {
  char str1[100];
  char str2[100];
  char *str3 = "Test %o Tes%%%%t %o";
  int val = 012;
  int val2 = 017;
  ck_assert_int_eq(sprintf(str1, str3, val, val2),
                   s21_sprintf(str2, str3, val, val2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(seventh_sprintf) {
  char str1[200];
  char str2[200];
  char *str3 = "%5.8G TEST\n%.6g TEST\n";
  float num = 0.83865400000;
  float num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(eighth_sprintf) {
  char str1[100];
  char str2[100];
  char *str3 = "%e\n%E\n%4e\n%4E\n%5.10e!";
  float num = -764231539.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
  num = 0.000023467;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
  num = -0.000023467;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
  num = 9999999.0;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
  float num2 = 0;
  num /= num2;
  ck_assert_int_eq(sprintf(str1, "%E", num), s21_sprintf(str2, "%E", num));
  ck_assert_pstr_eq(str1, str2);
  num /= num;
  ck_assert_int_eq(sprintf(str1, "%E", num), s21_sprintf(str2, "%E", num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST


START_TEST(tenth_sprintf) {
  char str1[200];
  char str2[200];
  char *str3 = "%*o Test %-*o Test %*.*o TEST %.*o";
  int val = 32;
  int val2 = 8899;
  int val3 = 919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

*/
Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *first_tc, *size_test;

  s = suite_create("s21_sprintf");

  // d
  first_tc = tcase_create("D test");
  tcase_add_test(first_tc, d_sprintf);
  tcase_add_test(first_tc, c_sprintf);
  tcase_add_test(first_tc, s_sprintf);
  tcase_add_test(first_tc, u_sprintf);
  tcase_add_test(first_tc, f_sprintf);
  tcase_add_test(first_tc, g_sprintf);
  tcase_add_test(first_tc, e_sprintf);
  tcase_add_test(first_tc, x_sprintf);
  tcase_add_test(first_tc, o_sprintf);

  suite_add_tcase(s, first_tc);

  size_test = tcase_create("Size test");
  tcase_add_test(first_tc, size_sprintf);
  tcase_add_test(first_tc, p_sprintf);
  suite_add_tcase(s, size_test);

  return s;
}
