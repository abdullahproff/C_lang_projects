#include "s21_sscanf.h"

int n_count(char *format) {
  int n = 0;
  char *str = format;
  while (*format) {
    if (*format == '%' || *format == ':' || *format == ';') {
      n++;
    }
    format++;
  }
  format = str;
  return n;
}

long long int s21_atoi(char *s) {
  long long int n = 0;
  while (*s == ' ') {  // убираем пробелы в нашей строке orig
    s++;
  }
  while (*s >= '0' && *s <= '9') {
    n *= 10;
    n += *s++;
    n -= '0';
  }

  return n;
}

void notation(struct contain *strok, int i, char *orig) {
  int stepen_i = 0;
  double p = 0.0;
  char stepen[3];

  stepen[0] = *(orig + 2);
  stepen[1] = *(orig + 3);
  stepen[2] = '\0';

  if (*(orig + 1) == '-') {
    p = 0.1;
  }
  if (*(orig + 1) == '+') {
    p = 10.0;
  }

  stepen_i = s21_atoi(stepen);
  if (strok[i].long_type == 0) {
    for (int f = 0; f < stepen_i; f++) {
      strok[i].f_float *= p;
    }
  }
  if (strok[i].long_type == 16) {
    for (int f = 0; f < stepen_i; f++) {
      strok[i].long_double_res *= p;
    }
  }
}
void reset_contain(struct contain *strok, char *orig, int n) {
  for (int i = 0; i < n; i++) {
    strok[i].f_float = 0.0;
    strok[i].long_double_res = 0.0;
    strok[i].hh_res_memory = 0;
    strok[i].h_res_memory = 0;
    strok[i].res = 0;
    strok[i].l_res_memory = 0;
    strok[i].ll_res_memory = 0;
    strok[i].addres = 0x0;
    strok[i].minus = 1;
    strok[i].skip = 0;
    strok[i].point = '\0';
    strok[i].width = 0;
    strok[i].s_break = 1;
    strok[i].space = 0;
    strok[i].pice[0] = '\0';

    // strok[i].stroka[0] = '\0';

    strok[i].stroka = malloc(sizeof(char) * (s21_strlen(orig) + 1));
    if (strok[i].stroka == NULL) {
      // обработка ошибки выделения памяти
      // например, вывод сообщения об ошибке и завершение программы
      printf("Ошибка выделения памяти\n");
      exit(1);
    }
    strok[i].stroka[0] = '\0';
    strok[i].s_char = '\0';
    strok[i].kinde = '\0';
    strok[i].long_type = 0;
  }
}
int set_long_type(struct contain *strok, int i) {
  char *c = strok[i].pice;
  int h = 0;
  int l = 0;
  int big_l = 0;
  int res = 0;
  while (*c) {
    if (*c == 'h') {
      h++;
    }
    if (*c == 'l') {
      l += 4;
    }
    if (*c == 'L') {
      big_l += 16;
    }
    c++;
  }

  return res + h + l + big_l;
}
int pars_format(char *format, struct contain *strok) {
  char *c = format;
  int i = 0;
  int n = 0;

  // разбиваю строку format на отдельные части. Первый пробелы ставятся только
  // перед строкой.

  while (*c) {
    if (*c == '%' && *(c + 1) == '%') {  // выходит из цыкла если встречает %%
      break;
    }
    if (*c == ' ') {
      strok[n].space++;
      c++;
    }
    if (*c != ' ') {
      strok[n].pice[i++] = *c;
      c++;
      if (*c == ',' || *c == ';') {  // этот кусок отвечает за разделитель.
                                     // Будет он вотдельном контейнере или нет.
        strok[n].pice[i] = '\0';
        n++;
        i = 0;
      }
      if (*c == ' ') {
        strok[n].pice[i] = '\0';
        n++;
        i = 0;
      }
      if (*c == '%') {
        strok[n].pice[i] = '\0';
        n++;
        i = 0;
      }
    }
  }
  strok[n].pice[i] =
      '\0';  // завершение последней строки \0 так как из цыкла выбрасывает.
  // n количество принятых аргументов форматной строки

  return n;
}
int sixteen(const char *hexNumber) {
  int decimalNumber = 0;

  int i = 0;
  while (hexNumber[i] != '\0') {
    char currentChar = hexNumber[i];
    int currentValue = 0;

    if (currentChar >= '0' && currentChar <= '9') {
      currentValue = currentChar - '0';
    } else if (currentChar >= 'A' && currentChar <= 'F') {
      currentValue = currentChar - 'A' + 10;
    } else if (currentChar >= 'a' && currentChar <= 'f') {
      currentValue = currentChar - 'a' + 10;
    } else {
      // Некорректный символ в строке, выход из цикла
      break;
    }

    decimalNumber = decimalNumber * 16 + currentValue;
    i++;
  }

  return decimalNumber;
}
long long int eight(long long int octal) {
  long long int res = 0;
  long long int base = 1;

  while (octal > 0) {
    long long int lastDigit = octal % 10;
    res += lastDigit * base;
    base *= 8;
    octal /= 10;
  }

  return res;
}
void *size_switch(struct contain *strok, long long int *loc, int i) {
  if (strok[i].long_type == 0) {
    *(int *)loc = strok[i].res;
  } else if (strok[i].long_type == 4) {
    *(long int *)loc = strok[i].l_res_memory;
  } else if (strok[i].long_type == 1) {
    *(short int *)loc = strok[i].h_res_memory;
  } else if (strok[i].long_type == 8) {
    *(long long int *)loc = strok[i].ll_res_memory;
  } else if (strok[i].long_type == 2) {
    *(signed char *)loc = strok[i].hh_res_memory;
  }
  return loc;
}
void set_contain(struct contain *strok,
                 int n) {  // установка параметров для единицы формата формата
  // printf("set_contain %s",strok[n].pice );
  int i = 0;

  while (i <= n) {
    strok[i].size_str =
        s21_strlen(strok[i].pice);  // узнаем размер нашего kотейнера pice что
                                    // бы не выйти за границы
    char *c = strok[i].pice;
    while (*c) {
      if (*c == '*') {
        strok[i].skip = 1;
      }
      if (*c >= '0' &&
          *c <= '9') {  // установка длины width для формата чтения строки
        strok[i].width = s21_atoi(c);
        for (; *c >= '0' && *c <= '9'; c++)
          ;
      }
      c++;
    }
    i++;
  }
}

void set_kinde(
    struct contain *strok,
    int n) {  // установка типов данных и длины выводимых значений lobg
  for (int i = 0; i <= n; i++) {
    if (s21_strpbrk(strok[i].pice, "dcsoxXuifpgGeE") != NULL) {
      strok[i].kinde = *s21_strpbrk(strok[i].pice, "dcsoxXuifpgGeE");
    }
    if (s21_strpbrk(strok[i].pice, "hlL") !=
        NULL) {  // указания на класс хранения
      strok[i].long_type = set_long_type(strok, i);
    }
    if (s21_strpbrk(strok[i].pice, ",;") != NULL) {
      strok[i].point = *s21_strpbrk(strok[i].pice, ",;");
    }
  }
}

void str_union(struct contain *strok, char *orig,
               int n) {  // orig  отправка оригинальной строки с текстом который
                         // будем парсить
  int i = 0;
  while (i <= n) {
    if ((strok[i].point == ',' && *(orig) != ',') ||
        (strok[i].point == ';' &&
         *(orig) !=
             ';')) {  // отановка объединения вводной строки с форматной. Если
                      // нет соответствия симола   "  ,  "   в формате и вводе.
      // printf("\n остаток строки не считанный:%s\n", orig);
      for (; i <= n; i++) {  // утсановка флага * в положение включено.
                             // Последующие контейнеры не читаются.
        strok[i].skip = 1;
      }
      break;
    }
    if ((strok[i].point == ',' && *(orig) == ',') ||
        (strok[i].point == ';' &&
         *(orig) == ';')) {  // если знаки пунктуации совпадают в формате и
                             // вводе, предвигаем на один элемент orig++
      orig++;
      strok[i].skip = 1;
    }
    if (strok[i].kinde == 'd') {
      orig = process_kind_d(strok, orig, i);
      // printf("\norig d %s\n", orig);
    }
    if (strok[i].kinde == 'c') {
      orig = process_kind_c(strok, orig, i);
    }
    if (strok[i].kinde == 's') {
      orig = process_kind_s(strok, orig, i);
    }
    if (strok[i].kinde == 'o' /* && strok[i].skip == 0 */) {
      orig = process_kind_o(strok, orig, i);
    }
    if (strok[i].kinde == 'x' || strok[i].kinde == 'X') {
      orig = process_kind_x(strok, orig, i);
    }
    if (strok[i].kinde ==
        'u') {  // НЕ РАБОТАЕТ НУЖНО РАЗОБРАТЬСЯ ЛОГИКУ ОБРАБОТКИ     числа со
                // знаком минус воспринимает как положительное.
      orig = process_kind_u(strok, orig, i);
    }
    if (strok[i].kinde == 'i') {
      orig = process_kind_i(
          strok, orig,
          i);  //  распознает формат написания чисел в     10й 8й 16й
    }
    if (strok[i].kinde == 'f' || strok[i].kinde == 'G' ||
        strok[i].kinde == 'g' || strok[i].kinde == 'E' ||
        strok[i].kinde == 'e') {
      orig = process_kind_f(strok, orig, i);
    }
    if (strok[i].kinde == 'p') {
      orig = process_kind_p(strok, orig, i);
    }
    i++;
  }
}

void *process_kind_c(struct contain *strok, char *orig, int i) {
  if (strok[i].space > 0) {
    for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
      ;  // убираю пробелы во входящей строке, если в формате стоит пробел space
         // > 0;
  }
  strok[i].s_char = *orig;
  // printf("\norig =%s.\n", orig);
  orig++;
  // printf("process_kinde_c  str %c\n", strok[i].stroka[0]);
  return orig;
}

void *process_kind_d(struct contain *strok, char *orig, int i) {
  int c = 0;
  char str[MAX] = {0};
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.
  if (*orig ==
      '-') {  // если после пробелов первый символ '-' флаг устанавливаем в -1
    strok[i].minus = -1;
    orig++;
    if (strok[i].width >
        0) {  // знак минус учитывается при выводе количества знаков
      strok[i].width--;
    }
  }
  if (strok[i].width == 0) {  // обработка строки если НЕТ  указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
           *orig <= '9') {  // отработка поведения для спецификатора %d
      str[c] = *orig;
      c++;
      orig++;
    }
  }
  if (strok[i].width > 0) {  // обработка строки если есть указание ширины %n
    while (*orig && *orig != ' ' && c < strok[i].width) {
      str[c] = *orig;
      c++;
      orig++;
    }
  }
  str[c] = '\0';
  if (strok[i].long_type == 0) {
    strok[i].res =
        s21_atoi(str) * strok[i].minus;  // перевод из строки в цифру результата
  }
  if (strok[i].long_type == 2) {
    strok[i].hh_res_memory = s21_atoi(str) * strok[i].minus;
  }
  if (strok[i].long_type == 1) {
    strok[i].h_res_memory = s21_atoi(str) * strok[i].minus;
  }
  if (strok[i].long_type == 4) {
    strok[i].l_res_memory = s21_atoi(str) * strok[i].minus;
  }
  if (strok[i].long_type == 8) {
    strok[i].ll_res_memory = s21_atoi(str) * strok[i].minus;
  }

  c = 0;
  return orig;
}

void *process_kind_f(struct contain *strok, char *orig, int i) {
  int c = 0;
  double minus = 1.0;
  double a = 0.0;
  double b = 0.0;
  int s = 0;
  int noll = 0;
  int g = 0;

  char str1[MAX] = {0};
  char str2[MAX] = {0};
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.
  if (*orig ==
      '-') {  // если после пробелов первый символ '-' флаг устанавливаем в -1
    minus = -1.0;
    orig++;
    if (strok[i].width >
        0) {  // знак минус учитывается при выводе количества знаков
      strok[i].width--;
    }
  }
  if (strok[i].width == 0) {  // обработка строки если НЕТ  указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
           *orig <= '9') {  // отработка поведения для спецификатора %d
      str1[c] = *orig;
      c++;
      orig++;
    }
    if (*orig == '.') {
      orig++;
      c = 0;
    }
    if (*orig == '0') {
      while (*orig == '0') {  // подсчет нулей после точки
        noll++;
        orig++;
      }
    }
    while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
           *orig <= '9') {  // отработка поведения для спецификатора %d
      str2[c] = *orig;
      c++;
      orig++;
    }
  }
  if (strok[i].width > 0) {  // обработка строки если ЕСТЬ указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
           *orig <= '9' &&
           c < strok[i].width) {  // отработка поведения для спецификатора %d
      str1[c] = *orig;
      c++;
      orig++;
    }
    if (*orig == '.') {
      c++;
      orig++;
      if (*orig == '0') {  // подсчет нулей после точки
        while (*orig == '0') {
          noll++;
          orig++;
        }
      }
      while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
             *orig <= '9' &&
             c < strok[i].width) {  // отработка поведения для спецификатора %d
        str2[s] = *orig;
        s++;
        c++;
        orig++;
      }
    }
  }
  a = (double)s21_atoi(str1);
  b = (double)s21_atoi(str2);
  for (int f = 0; b > 1.0; f++) {
    b /= 10;
  }
  for (int f = 0; f < noll; f++) {
    b /= 10;
  }

  g = (int)s21_strlen(str1) + (int)s21_strlen(str2) + 1;
  // printf("wight = %d\n", strok[i].width);

  a = a + b;
  strok[i].f_float = a * (double)minus;
  strok[i].long_double_res = a * (double)minus;

  if ((*orig == 'e' || *orig == 'E') &&
      (strok[i].f_float >= 1.0 && strok[i].f_float < 10.0) &&
      (*(orig + 1) == '-' || *(orig + 1) == '+') &&
      (*(orig + 2) >= '0' && *(orig + 2) <= '9') &&
      (*(orig + 3) >= '0' && *(orig + 3) <= '9' && g > strok[i].width)) {
    notation(strok, i, orig);
    orig += 4;
  }

  return orig;
}

void *process_kind_i(struct contain *strok, char *orig, int i) {
  int flag = 0;  // флаг не дает заходить в условие  if если одна из операций
                 // уже выполнилась
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.
  if (*orig ==
      '-') {  // если после пробелов первый символ '-' флаг устанавливаем в -1
    strok[i].minus = -1;
    orig++;
    if (strok[i].width >
        0) {  // знак минус учитывается при выводе количества знаков
      strok[i].width--;
    }
  }

  if (*orig == '0' && (*(orig + 1) == 'x' ||
                       (*(orig + 1) == 'X' && flag == 0))) {  // формат 16 числа
    orig = process_kind_x(strok, orig, i);
    flag = 1;  // установить флаг на то что был в условии
  }
  if (*orig == '0' && *(orig + 1) != 'x' &&
      *(orig + 1) != 'X') {  // формат 8 числа
    orig = process_kind_o(strok, orig, i);
    flag = 1;
  }
  if (*orig >= '1' && *orig <= '9') {  // //формат 10 числа
    orig = process_kind_d(strok, orig, i);

    flag = 1;
  }

  return orig;
}

void *process_kind_o(struct contain *strok, char *orig,
                     int i) {  // перевод в восмеричную систему
  int c = 0;
  char str[MAX] = {0};
  int minus = 1;

  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.
  if (*orig == '-') {
    minus = -1;
    orig++;
    if (strok[i].width > 0) {
      strok[i].width--;
    }
  }
  if (strok[i].width == 0) {  // обработка строки если НЕТ  указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
           *orig <= '9') {  // отработка поведения для спецификатора %d
      str[c] = *orig;
      c++;
      orig++;
    }
  }
  if (strok[i].width > 0) {  // обработка строки если есть указание ширины %n
    while (*orig && *orig != ' ' && c < strok[i].width) {
      str[c] = *orig;
      c++;
      orig++;
    }
  }
  str[c] = '\0';

  if (strok[i].long_type == 0) {
    strok[i].res = s21_atoi(str);  // перевод из строки в цифру результата
    strok[i].res =
        eight(strok[i].res) *
        minus;  // перевод значения int десятичной системы в int восмеричной
  }
  if (strok[i].long_type == 2) {
    strok[i].hh_res_memory =
        s21_atoi(str);  // перевод из строки в цифру результата
    strok[i].hh_res_memory =
        eight(strok[i].hh_res_memory) *
        minus;  // перевод значения int десятичной системы в int восмеричной
  }
  if (strok[i].long_type == 1) {
    strok[i].h_res_memory =
        s21_atoi(str);  // перевод из строки в цифру результата
    strok[i].h_res_memory =
        eight(strok[i].h_res_memory) *
        minus;  // перевод значения int десятичной системы в int восмеричной
  }
  if (strok[i].long_type == 4) {
    strok[i].l_res_memory = s21_atoi(str);
    strok[i].l_res_memory = eight(strok[i].l_res_memory) * minus;
  }
  if (strok[i].long_type == 8) {
    strok[i].ll_res_memory = s21_atoi(str);
    strok[i].ll_res_memory = eight(strok[i].ll_res_memory) * minus;
  }
  c = 0;
  return orig;
}

void *process_kind_p(struct contain *strok, char *orig,
                     int i) {  // функция обработки X x в тексте могут быть как
                               // заглавные так и прописные
  int c = 0;
  char str[MAX] = {0};
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.

  if (*orig == '0' && (*(orig + 1) == 'x' || *(orig + 1) == 'X')) {
    orig += 2;
  }

  if (strok[i].width == 0) {  // обработка строки если НЕТ  указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' &&
           ((*orig >= '0' && *orig <= '9') || (*orig >= 'A' && *orig <= 'F') ||
            (*orig >= 'a' &&
             *orig <= 'f'))) {  // отработка поведения для спецификатора %x
      str[c] = *orig;
      c++;
      orig++;
    }
  }

  if (strok[i].width > 0) {  // обработка строки если есть указание ширины %n
    while ((*orig && *orig != ' ' && *orig != '\0' &&
            ((*orig >= '0' && *orig <= '9') || (*orig >= 'A' && *orig <= 'F') ||
             (*orig >= 'a' && *orig <= 'f')) &&
            c < strok[i].width - 2)) {
      str[c] = *orig;
      c++;
      orig++;
    }
  }

  str[c] = '\0';
  strok[i].addres = (int)sixteen(str);

  // printf("strok = %lx\n",strok[i].addres);
  c = 0;
  return orig;
}

void *process_kind_s(struct contain *strok, char *orig, int i) {
  int c = 0;
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю все пробельные символы
  if (strok[i].width == 0) {
    while (*orig && *orig != ' ' && *orig != '\n' &&
           *orig != '\t') {  // считываю до первых пробельных символов
      strok[i].stroka[c] = *orig;
      orig++;
      c++;
    }
  }
  if (strok[i].width > 0) {
    while (*orig && *orig != ' ' && *orig != '\n' && *orig != '\t' &&
           c < strok[i].width) {  // считываю до первых пробельных символов
      strok[i].stroka[c] = *orig;
      orig++;
      c++;
    }
  }
  strok[i].stroka[c] = '\0';

  return orig;
}

void *process_kind_u(struct contain *strok, char *orig, int i) {
  int c = 0;
  char str[MAX] = {0};
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.

  if (strok[i].width == 0) {  // обработка строки если НЕТ  указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' && *orig >= '0' &&
           *orig <= '9') {  // отработка поведения для спецификатора %d
      str[c] = *orig;
      c++;
      orig++;
    }
  }
  if (strok[i].width > 0) {  // обработка строки если есть указание ширины %n
    while (*orig && *orig != ' ' && c < strok[i].width) {
      str[c] = *orig;
      c++;
      orig++;
    }
  }
  str[c] = '\0';

  strok[i].res = s21_atoi(str);  // перевод из строки в цифру результата
                                 // printf("process_kinde_d  str %s\n", str);
  if (strok[i].long_type == 0) {
    strok[i].res = s21_atoi(str);
  }
  if (strok[i].long_type == 2) {
    strok[i].hh_res_memory = s21_atoi(str);
  }
  if (strok[i].long_type == 1) {
    strok[i].h_res_memory = s21_atoi(str);
  }
  if (strok[i].long_type == 4) {
    strok[i].l_res_memory = s21_atoi(str);
  }
  if (strok[i].long_type == 8) {
    strok[i].ll_res_memory = s21_atoi(str);
  }
  c = 0;
  return orig;
}

void *process_kind_x(struct contain *strok, char *orig,
                     int i) {  // функция обработки X x в тексте могут быть как
                               // заглавные так и прописные
  int c = 0;
  char str[MAX] = {0};
  for (; *orig == ' ' || *orig == '\n' || *orig == '\t'; orig++)
    ;  // убираю пробелы во входящей строке, что бы дойти до символов, так как
       // не заходит в функцию ниже.

  if (*orig == '0' && (*(orig + 1) == 'x' || *(orig + 1) == 'X')) {
    orig += 2;
  }

  if (strok[i].width == 0) {  // обработка строки если НЕТ  указание ширины
    while (*orig && *orig != ' ' && *orig != '\0' &&
           ((*orig >= '0' && *orig <= '9') || (*orig >= 'A' && *orig <= 'F') ||
            (*orig >= 'a' &&
             *orig <= 'f'))) {  // отработка поведения для спецификатора %x
      str[c] = *orig;
      c++;
      orig++;
    }
  }

  if (strok[i].width > 0) {  // обработка строки если есть указание ширины %n
    while ((*orig && *orig != ' ' && *orig != '\0' &&
            ((*orig >= '0' && *orig <= '9') || (*orig >= 'A' && *orig <= 'F') ||
             (*orig >= 'a' && *orig <= 'f')) &&
            c < strok[i].width)) {
      str[c] = *orig;
      c++;
      orig++;
    }
  }

  str[c] = '\0';
  if (strok[i].long_type == 0) {
    strok[i].res = sixteen(str);
  }
  if (strok[i].long_type == 2) {
    strok[i].hh_res_memory = sixteen(str);
  }
  if (strok[i].long_type == 1) {
    strok[i].h_res_memory = sixteen(str);
  }
  if (strok[i].long_type == 4) {
    strok[i].l_res_memory = sixteen(str);
  }
  if (strok[i].long_type == 8) {
    strok[i].ll_res_memory = sixteen(str);
  }

  // printf("process_kind_x %ld \n", strok[i].res);
  c = 0;
  return orig;
}

int s21_sscanf(char *orig, char *format, ...) {
  int n = 0;
  n = n_count(format);
  struct contain strok[n];
  reset_contain(strok, orig, n);

  int succes = 0;
  n = pars_format(format, strok);
  set_contain(strok, n);
  set_kinde(strok, n);
  str_union(strok, orig, n);
  va_list factor;  // указатель на необязательный параметр
  va_start(factor, format);  // устанавливаем указатель
  for (int i = 0; i <= n;
       i++) {  // объединение результатов с адресом внешней перенной в main
    if (strok[i].skip == 0 &&
        strok[0].kinde == 'c') {  // отправляем по адресу значение  с
      char *loc = va_arg(factor, char *);
      *loc = strok[i].s_char;
      succes++;
    }
    if (strok[i].skip == 0 &&
        strok[i].kinde == 'd') {  // отправляем по адресу значение  d
      long long int *loc = va_arg(factor, long long int *);
      loc = size_switch(
          strok, loc,
          i);  // присваивание адреса с результатом согласно типу lhL
      succes++;
    }
    if (strok[i].skip == 0 &&
        strok[i].kinde == 's') {  // отправляем по адресу значение  s
      char *loc = va_arg(factor, char *);
      loc = s21_strncpy(loc, strok[i].stroka,
                        (s21_strlen(strok[i].stroka) +
                         1));  // Копирую результат в указатель на строку.
      succes++;
    }
    if (strok[i].skip == 0 &&
        strok[i].kinde == 'o') {  // отправляем по адресу значение  o
      long long int *loc = va_arg(factor, long long int *);
      loc = size_switch(strok, loc, i);

      succes++;
    }
    if (strok[i].skip == 0 &&
        (strok[i].kinde == 'x' ||
         strok[i].kinde == 'X')) {  // отправляем по адресу значение  X
      long long int *loc = va_arg(factor, long long int *);
      loc = size_switch(strok, loc, i);
      succes++;
    }
    if (strok[i].skip == 0 &&
        strok[i].kinde == 'u') {  // отправляем по адресу значение  u
      long long int *loc =
          va_arg(factor,
                 long long int *);  // РАЗОБРАТЬСЯ КАК ДОЛЖНО ПРАВИЛЬНО РАБОТАТЬ
      loc = size_switch(strok, loc, i);
      succes++;
    }
    if (strok[i].skip == 0 &&
        strok[i].kinde == 'i') {  // отправляем по адресу значение  i
      long long int *loc = va_arg(factor, long long int *);
      loc = size_switch(strok, loc, i);
      succes++;
    }
    if (strok[i].skip == 0 &&
        (strok[i].kinde == 'f' || strok[i].kinde == 'g' ||
         strok[i].kinde == 'G' || strok[i].kinde == 'e' ||
         strok[i].kinde == 'E') &&
        strok[i].long_type == 16) {  // отправляем по адресу значение  f
      long double *loc = va_arg(factor, long double *);
      *loc = strok[i].long_double_res;
      succes++;
    }
    if (strok[i].skip == 0 &&
        (strok[i].kinde == 'f' || strok[i].kinde == 'g' ||
         strok[i].kinde == 'G' || strok[i].kinde == 'e' ||
         strok[i].kinde == 'E') &&
        strok[i].long_type == 0) {  // отправляем по адресу значение  f
      float *loc = va_arg(factor, float *);
      *loc = (float)strok[i].f_float;
      succes++;
    }
    if (strok[i].skip == 0 &&
        strok[i].kinde == 'p') {  // отправляем по адресу значение  f
      int **p = va_arg(factor, int **);  // взятие адресе
      *p = (void *)strok[i].addres;  // прописываю новый адрес
                                     // printf("p =  %p\n", &p);
      succes++;
    }
  }
  va_end(factor);

  /* for (int f = 0; f <= n; f++) {
  printf("pice %s, long type = %d, stroka = %s\n",
             strok[f].pice,
             strok[f].long_type, strok[f].stroka);
  } */
  for (int f = 0; f <= n; f++) {
    free(strok[f].stroka);
  }
  orig = s21_NULL;
  format = s21_NULL;

  return succes;
}