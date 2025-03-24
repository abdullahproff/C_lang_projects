#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_

#include "s21_string.h"

typedef struct {
  unsigned char minus : 1;  // флаг -
  unsigned char zero : 1;   // флаг 0
  unsigned char plus : 1;   // флаг +
  unsigned char space : 1;  // флаг пробел
  unsigned char hash : 1;   // флаг #
} flags;

typedef struct {
  flags flag;

  unsigned char
      sign_minus : 1;  // наличие минуса числа (отрицательное число или нет)
  unsigned int width;  // параметр ширина
  int precision;       // параметр точность
  unsigned char precision_init : 1;  // показатель того, была ли задана точность
                                     // в форматной строке
  unsigned char length : 3;  // параметр длина
  char*
      specificator;  // указатель на положение спецификатора в форматной строке

} func;

// #define S21_NAN 0./0.
// #define S21_INF 1./0.
// #define S21_MINUS_INF -1./0.

// макросы-сокращения
#define SPEC sPrintf.specificator
#define LENGTH sPrintf.length
#define PRECISION sPrintf.precision
#define PRECIS_INIT sPrintf.precision_init
#define WIDTH sPrintf.width
#define FLAG sPrintf.flag
#define NEGATIVE_NUM sPrintf.sign_minus
#define G_SPEC_OK (*sPrintf.specificator == 'g' || *sPrintf.specificator == 'G')
#define INF_NAN_CAPS (*SPEC == 'G' || *SPEC == 'E')

#define VARG(type) num = va_arg(*next_arg, type)
#define NEXT_CASE __attribute__((fallthrough))

// разные модификаторы длины
#define h_LONG 1
#define hh_LONG 2
#define l_LONG 3
#define ll_LONG 4
#define L_LONG 5

// булевы константы
#define false 0
#define true 1

//свич-кейс макросы для считывания аргументов в зависимости от параметра длины

#define READ_VARGS_UNSIGNED_DECIMAL \
  switch (LENGTH) {                 \
    case hh_LONG:                   \
      VARG(unsigned int);           \
      break;                        \
    case h_LONG:                    \
      VARG(unsigned int);           \
      break;                        \
    case l_LONG:                    \
      VARG(unsigned long);          \
      break;                        \
    case ll_LONG:                   \
      VARG(unsigned long long);     \
      break;                        \
    case 0:                         \
      VARG(unsigned int);           \
      break;                        \
  }

#define READ_VARGS_DECIMAL \
  switch (LENGTH) {        \
    case hh_LONG:          \
      VARG(int);           \
      break;               \
    case h_LONG:           \
      VARG(int);           \
      break;               \
    case l_LONG:           \
      VARG(long);          \
      break;               \
    case ll_LONG:          \
      VARG(long long);     \
      break;               \
    case 0:                \
      VARG(int);           \
      break;               \
  }

/* char *s21_strcat(char *dest, const char *src) {
    s21_size_t size = s21_strlen(dest);
    int i = 0;
    for (; *(src + i) != '\0'; i++) {
        *(dest + size + i) = *(src + i);
    }
    *(dest + size + i) = '\0';
    return dest;
}

 */

int s21_sprintf(char* string, const char* format, ...);

long double s21_fpow(long double basis, int power);

//В случае успеха, возвращает 1 - значит число было отрицательным, либо 0 -
//значит было положительным
int s21_fabs(long double* number);

// считает количество символов в целой части числа до точки
int count_integer(long double number, int base);

// Конвертация числа long double в string
char* number_to_string(long double number, long double float_part, char* str,
                       int point, int len_full, int len_science,
                       int science_expo_power, int sign_expo, int base);

int count_length_number(long double number, int* point,
                        // int precision,
                        int base);

void check_precision(func* sPrintf);

long double float_part_powered_up_by_precision(
    long double number,  // int precision,
    int base);

int make_positive_number(long double* number);

int calculate_power_for_science(long double* number, int* sign_expo);

void invert_sign_number(long double* number);

char* record_num_to_str(long double number, char* str,
                        int base);  // пока не используется

void init_static_string(char* string, int length);

void rec_sci_nota_expo_to_str(char* str, int len_science, char E, int sign_expo,
                              int science_expo_power);

char* rec_dbl_num_to_str(char* str, int len_full_number,
                         int point_position  //, int precision
                         ,
                         char ch_addon, long double number,
                         long double float_part, int base);

void approximate(long double* number, long double* float_part,
                 int base  //, int precision
);

void inf_conditions_output();
void nan_conditions_output();

void add_c(char* string, char* str);
void add_d(char* string, char* str);
void add_f(char* string, char* str);
void add_s(char* string, char* str);
void add_u(char* string, char* str);
void add_e(char* string, char* str);
void add_p(char* string, char* str);
void add_x(char* string, char* str);
void add_o(char* string, char* str);
void add_g(char* string, char* str);

#endif  // S21_SPRINTF_H_