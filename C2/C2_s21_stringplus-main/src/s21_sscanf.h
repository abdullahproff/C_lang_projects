#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include "s21_string.h"

#define MAX 40

struct contain {
  double f_float;
  long double long_double_res;
  signed char hh_res_memory;
  short int h_res_memory;
  int res;  // хранение всех чисел будет производится в этом формате, до
  long int l_res_memory;
  long long int ll_res_memory;
  long int addres;  //  адрес для хранения P

  int s_break;
  int minus;
  char s_char;
  int skip;    // указатель на звездочку
  char point;  // проверка на наличие        ", ;"
  int width;
  int space;
  char pice[MAX];
  char *stroka;

  // дальнейшего использования.
  char kinde;  // буквенное обозначение принимаемого типа.
  int long_type;  // хранение типа Llh
  int size_str;  // длина строки в контейнере  ... нужно при определениие
                 // читаемой длины    %n
};

int s21_sscanf(char *orig, char *format, ...);
void set_kinde(struct contain *strok, int n);
long long int s21_atoi(char *s);
void set_contain(struct contain *strok, int n);
int pars_format(char *format, struct contain *strok);
long long int eight(long long int octal);
int sixteen(const char *hexNumber);
void reset_contain(struct contain *strok, char *orig, int n);
void *size_switch(struct contain *strok, long long int *loc, int i);
void str_union(struct contain *strok, char *orig, int n);
int set_long_type(struct contain *strok, int i);
void notation(struct contain *strok, int i, char *orig);
void *process_kind_x(struct contain *strok, char *orig, int i);
void *process_kind_o(struct contain *strok, char *orig, int i);
void *process_kind_c(struct contain *strok, char *orig, int i);
void *process_kind_s(struct contain *strok, char *orig, int i);
void *process_kind_d(struct contain *strok, char *orig, int i);
void *process_kind_u(struct contain *strok, char *orig, int i);
void *process_kind_i(struct contain *strok, char *orig, int i);
void *process_kind_f(struct contain *strok, char *orig, int i);
void *process_kind_p(struct contain *strok, char *orig, int i);

#endif  // S21_SSCANF_H_