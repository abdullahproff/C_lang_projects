
#include "s21_sprintf.h"

// sprintf возвращает число байтов, сохраненных в buffer без учета завершающего
// символа null

// int sprintf(char *str, const char *format, ...) - отправляет форматированный
// вывод в строку, на которую указывает str. где: str − Это С-строка, которую
// функция обрабатывает в качестве источника для извлечения данных; format − это
// С-строка, содержащая один или несколько следующих элементов: пробельный
// символ, непробельный символ и спецификаторы формата.

// Спецификатор формата для печатающих функций следует прототипу:

//    флаги       ширина          точность       длина   спецификатор(%
//    отдельно)
// % [-+ #0]  [(число) или *]  [.(число) или *]  [hlL]  [cdfsugGeExXop]

// Спецификаторы: c, d, f, s, u, %
// Флаги: -, +, (пробел)
// Ширина: (число)
// Точность: .(число)
// Длина: h, l

// допник:
// Спецификаторы: g, G, e, E, x, X, o, p
// Флаги: #, 0
// Ширина: *
// Точность: .*
// Длина: L

// иницилизация полей структуры для записи отсканированных из форматной строки
// параметров на уровне всей программы (глобально)
func sPrintf = {0};

// сканируем флаги
const char* flags_scan(const char* flags_ptr) {
  int next = false;

  while (flags_ptr != SPEC && next == false) {
    switch (*flags_ptr) {
      case '0':
        if (!FLAG.minus) FLAG.zero = 1;
        break;
      case '-':
        FLAG.minus = 1;
        FLAG.zero = 0;
        break;
      case '+':
        FLAG.space = 0;
        FLAG.plus = 1;
        break;
      case ' ':
        if (!FLAG.plus) FLAG.space = 1;
        break;
      case '#':
        FLAG.hash = 1;
        break;

      default:
        next = true;
    }

    if (next == false) flags_ptr++;
  }

  return flags_ptr;
}

// сканируем параметр ширины
const char* width_prec_scan(const char* width_prec, int* buffer_w_p,
                            va_list* next_arg) {
  int func_exit = false;

  while (width_prec != SPEC && func_exit == false) {
    if (*width_prec >=
            ((PRECIS_INIT == false && *buffer_w_p == 0) ? '1' : '0') &&
        *width_prec <= '9') {
      *buffer_w_p = *buffer_w_p * 10 + *width_prec - '0';  // по сути это atoi

      width_prec++;

    } else if (*width_prec == '*' &&
               (PRECIS_INIT == true ||
                (PRECIS_INIT == false && *buffer_w_p == 0))) {
      // если *, то считываем значение из следующего переданного в функцию
      // s21_sprintf аргумента
      *buffer_w_p = va_arg(*next_arg, int);
      width_prec++;
      func_exit = true;

    } else {
      func_exit = true;
    }
  }

  return width_prec;
}

// сканируем параметр точности
const char* precision_scan(const char* precision_ptr, int* buffer_precision,
                           va_list* next_arg) {
  if (*precision_ptr == '.') {
    PRECIS_INIT = true;
    precision_ptr =
        width_prec_scan(++precision_ptr, buffer_precision, next_arg);
  }

  return precision_ptr;
}

// сканируем параметр длины
const char* length_scan(const char* length_ptr) {
  int count = 0;
  int bad_option = false;

  while (length_ptr < SPEC && count++ < 2 && bad_option == false) {
    switch (*length_ptr) {
      case 'l': {
        if (LENGTH == 0)
          LENGTH = l_LONG;
        else if (LENGTH == l_LONG)
          LENGTH = ll_LONG;
        else
          bad_option = true;
        break;
      }
      case 'h': {
        if (LENGTH == 0)
          LENGTH = h_LONG;
        else if (LENGTH == h_LONG)
          LENGTH = hh_LONG;
        else
          bad_option = true;
        break;
      }
      case 'L': {
        if (LENGTH == 0)
          LENGTH = L_LONG;
        else
          bad_option = true;
        break;
      }
      default:
        bad_option = true;
    }
    length_ptr++;
  }

  if (bad_option == true) {
    LENGTH = -1;
    fprintf(
        stderr,
        "\nневерный параметр длины перед спецификатором в форматной подстроке");
  }

  return length_ptr;
}

void scan_format(const char* part_format, va_list* next_arg) {
  // открываем цикл сканирования куска строки от % до спецификатора
  while (part_format != SPEC) {
    // сначала сканируем флаги
    const char* flags_ptr = flags_scan(part_format);

    // теперь сканируем ширину
    int buffer_width = 0;
    const char* width_ptr = width_prec_scan(flags_ptr, &buffer_width, next_arg);
    WIDTH = buffer_width;

    // printf("\nширина в функции scan_format= %d", buffer_width);

    // теперь точность
    int buffer_precision = 0;
    const char* precision_ptr =
        precision_scan(width_ptr, &buffer_precision, next_arg);
    PRECISION = buffer_precision;

    // printf("\nточность в функции scan_format= %d", PRECISION
    // buffer_precision);

    // printf("\nуказатель после функции precision на символе = %c\n\n",
    // *precision_ptr);

    // и наконец длину
    const char* length_ptr = length_scan(precision_ptr);
    // printf("\nдлина в функции scan_format= %d", LENGTH);

    part_format = length_ptr;

    // getchar();
  }
}

/*
==============================================================================
==============================================================================
==============================================================================

                            добавление в строку

==============================================================================
==============================================================================
==============================================================================
*/

void add_c(char* string, char* str) {
  // спецификатор проверен %%
  size_t n = 0;

  if (WIDTH == 0) {
    s21_strncpy(string, str, 1);
  }  // важно, нужно проверить коректность на конец сроки
  if (WIDTH > 0 && FLAG.minus == 0) {
    if (FLAG.zero == 0) {
      while (n < WIDTH - 1) {
        s21_strcat(string, " ");
        n++;
      }
    }
    if (FLAG.zero == 1) {
      while (n < WIDTH - 1) {
        s21_strcat(string, "0");
        n++;
      }
    }
    s21_strcat(string, str);
  }
  if (WIDTH > 0 && FLAG.minus == 1) {
    s21_strcat(string, str);
    if (FLAG.zero == 0) {
      while (n < WIDTH - 1) {
        s21_strcat(string, " ");
        n++;
      }
    }
  }
}

void add_d(char* string, char* str)

{
  size_t n = 0;
  size_t i = 0;
  // int p = 0;
  char numb_buff[100];
  numb_buff[0] = '\0';
  if (PRECISION > 0) {
    int y = s21_strlen(str) - PRECISION - 1;
    str[y] = '\0';
  }

  if (NEGATIVE_NUM > 0 && FLAG.zero == 0 /*  && FLAG.plus == 0 */) {
    s21_strcat(numb_buff, "-");
    s21_strcat(numb_buff, str);
  }

  if (NEGATIVE_NUM == 0 && FLAG.plus == 0) {
    if (FLAG.space == 0) {
      s21_strcat(numb_buff, str);
    }
    if (FLAG.space == 1) {
      s21_strcat(numb_buff, " ");
      s21_strcat(numb_buff, str);
    }
  }
  if (FLAG.plus == 1) {
    if (NEGATIVE_NUM == 0) {
      s21_strcat(numb_buff, "+");
      s21_strcat(numb_buff, str);
    }
  }
  if (WIDTH < WIDTH - s21_strlen(numb_buff) && FLAG.minus == 0) {
    s21_strcat(string, numb_buff);
  }
  if (WIDTH < WIDTH - s21_strlen(numb_buff) && FLAG.minus == 1) {
    s21_strcat(string, numb_buff);
  }

  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.minus == 0) {
    n = WIDTH - s21_strlen(numb_buff);

    if (FLAG.zero == 0) {
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
    if (FLAG.zero == 1) {
      n = WIDTH - s21_strlen(str);
      if (NEGATIVE_NUM > 0) {
        s21_strcat(string, "-");
        i++;
      }
      if (FLAG.plus == 1 && NEGATIVE_NUM == 0) {
        s21_strcat(string, "+");
        i++;
      }
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
      s21_strcat(string, str);
    }
    if (FLAG.zero == 0) {
      s21_strcat(string, numb_buff);
    }
  }
  if (WIDTH > WIDTH - s21_strlen(numb_buff) && FLAG.minus == 1) {
    s21_strcat(string, numb_buff);
    n = WIDTH - s21_strlen(string);
    while (i < n) {
      s21_strcat(string, " ");
      i++;
    }
  }
  if (NEGATIVE_NUM > 0 && WIDTH < WIDTH - s21_strlen(str) && FLAG.zero == 1) {
    s21_strcat(string, "-");
    s21_strcat(string, str);
  }
}

void add_f(char* string, char* str) {
  size_t n = 0;
  size_t i = 0;
  char numb_buff[100];
  numb_buff[0] = '\0';
  int flag_out = 0;

  if (FLAG.hash == 1) {
    if (NEGATIVE_NUM > 0) {
      s21_strcat(numb_buff, "-");
    }
    s21_strcat(numb_buff, str);
    if (PRECISION == 0) {
      s21_strcat(numb_buff, ".");
    }
    flag_out = 1;
  }

  if (NEGATIVE_NUM > 0 && FLAG.zero == 0 && flag_out == 0) {
    s21_strcat(numb_buff, "-");
    s21_strcat(numb_buff, str);
  }

  if (NEGATIVE_NUM == 0 && FLAG.plus == 0 && FLAG.hash == 0) {
    if (FLAG.space == 0) {
      s21_strcat(numb_buff, str);
    }
    if (FLAG.space == 1) {
      s21_strcat(numb_buff, " ");
      s21_strcat(numb_buff, str);
    }
  }
  if (FLAG.plus == 1 && FLAG.hash == 0) {
    if (NEGATIVE_NUM == 0) {
      s21_strcat(numb_buff, "+");
      s21_strcat(numb_buff, str);
    }
  }
  if (WIDTH < WIDTH - s21_strlen(numb_buff) && FLAG.minus == 0) {
    s21_strcat(string, numb_buff);
  }
  if (WIDTH < WIDTH - s21_strlen(numb_buff) && FLAG.minus == 1) {
    s21_strcat(string, numb_buff);
  }

  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.minus == 0) {
    n = WIDTH - s21_strlen(numb_buff);

    if (FLAG.zero == 0) {
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
    if (FLAG.zero == 1) {
      n = WIDTH - s21_strlen(str);
      if (NEGATIVE_NUM > 0) {
        s21_strcat(string, "-");
        i++;
      }
      if (FLAG.plus == 1 && NEGATIVE_NUM == 0) {
        s21_strcat(string, "+");
        i++;
      }
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
      s21_strcat(string, str);
      if (FLAG.hash == 1) {
        s21_strcat(string, ".");
      }
    }
    if (FLAG.zero == 0) {
      s21_strcat(string, numb_buff);
    }
  }
  if (WIDTH > WIDTH - s21_strlen(numb_buff) && FLAG.minus == 1) {
    s21_strcat(string, numb_buff);
    n = WIDTH - s21_strlen(string);
    while (i < n) {
      s21_strcat(string, " ");
      i++;
    }
  }
}

void add_s(char* string, char* str) {
  if ((PRECISION > (int)s21_strlen(str)) || PRECIS_INIT == false)
    PRECISION = s21_strlen(str);

  // обработка параметра ширины. Если ширина меньше чем точность копируемой
  // строки, то ширина = точности копируемой строки
  int string_width = (int)WIDTH > PRECISION ? (int)WIDTH : PRECISION;

  // создаём массив широкой строки с учётом параметра ширины
  char str_with_params[string_width + 1];
  str_with_params[string_width] = '\0';

  // // обработка флага '0'
  char fill_str_with_params = ' ';
  if (FLAG.zero) fill_str_with_params = '0';

  // заполнение строки пробелом или 0 в зависимости от флага 0
  s21_memset(str_with_params, fill_str_with_params,
             sizeof(str_with_params) - 1);

  //обработка флага точности
  int precision_delta = s21_strlen(str) - PRECISION;

  // обработка флага '-'
  int not_minus_flag = 0;
  if (!FLAG.minus)
    not_minus_flag = string_width - s21_strlen(str) + precision_delta;

  //обработка флага длины

  // записывает нашу строку в массив широкой строки
  s21_strncpy(str_with_params + not_minus_flag, str,
              s21_strlen(str) - precision_delta);

  // записываем в целевую строку получившийся массив с учётом параметров от %
  // до спецификатора
  string = s21_strncat(string, str_with_params, s21_strlen(str_with_params));
}

void add_u(char* string, char* str) {
  size_t n = 0;
  size_t i = 0;
  int flag_out = 0;

  if (FLAG.space == 1) {
    s21_strcat(string, str);
    flag_out = 1;
  }
  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.space == 0) {
    n = WIDTH - s21_strlen(str);
    if (FLAG.minus == 1) {
      s21_strcat(string, str);
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
    if (FLAG.zero == 0) {
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
    if (FLAG.zero == 1) {
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
    }
    if (FLAG.minus == 0) {
      s21_strcat(string, str);
    }
  }

  if (WIDTH < WIDTH - s21_strlen(str) && flag_out == 0) {
    s21_strcat(string, str);
  }
}

void add_e(char* string, char* str) {
  size_t n = 0;
  size_t i = 0;

  char numb_buff[100] = {0};
  int flag_out = 0;
  if (WIDTH < WIDTH - s21_strlen(str) && NEGATIVE_NUM == 0 && FLAG.plus == 0) {
    if (FLAG.space == 1) s21_strcat(string, " ");
    s21_strcat(string, str);
  }
  if (WIDTH < WIDTH - s21_strlen(str) && NEGATIVE_NUM == 0 && FLAG.plus > 0) {
    s21_strcat(string, "+");
    s21_strcat(string, str);
  }
  if (WIDTH < WIDTH - s21_strlen(str) && NEGATIVE_NUM > 0) {
    s21_strcat(string, "-");
    s21_strcat(string, str);
  }

  if (WIDTH > WIDTH - s21_strlen(str) && NEGATIVE_NUM > 0) {
    if (FLAG.zero == 0 && FLAG.minus == 0) {
      n = WIDTH - s21_strlen(str);
      if (NEGATIVE_NUM > 0) {
        s21_strcat(numb_buff, "-");
        s21_strcat(numb_buff, str);
        n--;
      }
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
    if (FLAG.zero > 0 && FLAG.minus == 0) {
      n = WIDTH - s21_strlen(str);
      n--;
      s21_strcat(string, "-");
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
      s21_strcat(numb_buff, str);
    }
    if (FLAG.zero == 0 && FLAG.minus == 1) {
      n = WIDTH - s21_strlen(str);
      if (NEGATIVE_NUM > 0) {
        s21_strcat(numb_buff, "-");
        s21_strcat(numb_buff, str);
        n--;
      }
      while (i < n) {
        s21_strcat(numb_buff, " ");
        i++;
      }
    }
    s21_strcat(string, numb_buff);
  }
  if (WIDTH > WIDTH - s21_strlen(str) && NEGATIVE_NUM == 0) {
    if (FLAG.zero == 0 && FLAG.minus == 0) {
      n = WIDTH - s21_strlen(str);
      if (FLAG.space == 1 && n < 1) {
        s21_strcat(string, " ");
      }
      if (FLAG.plus > 0) n--;
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
      if (FLAG.plus > 0) s21_strcat(string, "+");
    }
    if (FLAG.zero > 0 && FLAG.minus == 0) {
      n = WIDTH - s21_strlen(str);
      if (FLAG.plus > 0) {
        n--;
        s21_strcat(string, "+");
      }
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
    }
    if (FLAG.minus == 1 && flag_out == 0) {
      n = WIDTH - s21_strlen(str);
      s21_strcat(string, str);
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
      flag_out = 1;
    }
    if (flag_out == 0) s21_strcat(string, str);
  }
}

void add_p(char* string, char* str) {
  char numb_buff[100] = {0};
  s21_strcat(numb_buff, "0x");
  s21_strcat(numb_buff, str);
  s21_strcat(string, numb_buff);
}

void add_x(char* string, char* str) {
  char up_ox[3] = {0};
  size_t n = 0;
  size_t i = 0;
  int flag_out = 0;
  char numb_buff[100] = {0};
  if (*SPEC == 'x') s21_strcat(up_ox, "0x");
  if (*SPEC == 'X') s21_strcat(up_ox, "0X");

  if (FLAG.hash == 1 && WIDTH < WIDTH - s21_strlen(str)) {
    s21_strcat(numb_buff, up_ox);
    s21_strcat(numb_buff, str);
    s21_strcat(string, numb_buff);
    flag_out = 1;
  }
  if (FLAG.hash == 1 && FLAG.minus == 1 && flag_out == 0) {
    s21_strcat(numb_buff, up_ox);
    s21_strcat(numb_buff, str);
  }
  if (FLAG.hash == 0 && FLAG.zero == 0) s21_strcat(numb_buff, str);

  if (WIDTH < WIDTH - s21_strlen(str) && FLAG.minus == 0 && flag_out == 0) {
    s21_strcat(string, numb_buff);
  }

  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.minus == 0) {
    if (FLAG.zero == 0) {
      n = WIDTH - s21_strlen(str);
      if (FLAG.hash == 1 && n > 2) {
        n -= 2;
      }
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
      if (FLAG.hash == 1) {
        s21_strcat(string, up_ox);
        s21_strcat(string, str);
      }
    }
    if (FLAG.zero > 0) {
      n = WIDTH - s21_strlen(str);
      if (FLAG.hash == 1) {
        s21_strcat(string, up_ox);
      }
      if (n > 2 && FLAG.hash == 1) n -= 2;

      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
      s21_strcat(string, str);
    }

    s21_strcat(string, numb_buff);
  }
  if (WIDTH > WIDTH - s21_strlen(numb_buff) && FLAG.minus == 1) {
    if (FLAG.zero == 0) {
      s21_strcat(string, numb_buff);
      n = WIDTH - s21_strlen(numb_buff);
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
  }
}

void add_o(char* string, char* str) {
  size_t n = 0;
  size_t i = 0;
  int flag_out = 0;
  char numb_buff[100] = {0};
  if (FLAG.hash == 1 && WIDTH < WIDTH - s21_strlen(str)) {
    s21_strcat(numb_buff, "0");
    s21_strcat(numb_buff, str);
    s21_strcat(string, numb_buff);
    flag_out = 1;
  }
  if (FLAG.hash == 1 && FLAG.minus == 1 && flag_out == 0) {
    s21_strcat(numb_buff, "0");
    s21_strcat(numb_buff, str);
  }
  if (FLAG.hash == 0 && FLAG.zero == 0) s21_strcat(numb_buff, str);

  if (WIDTH < WIDTH - s21_strlen(str) && FLAG.minus == 0 && flag_out == 0) {
    s21_strcat(string, numb_buff);
  }

  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.minus == 0) {
    if (FLAG.zero == 0) {
      n = WIDTH - s21_strlen(str);
      if (FLAG.hash == 1 && n > 2) {
        n -= 1;
      }
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
      if (FLAG.hash == 1) {
        s21_strcat(string, "0");
        s21_strcat(string, str);
      }
    }
    if (FLAG.zero > 0) {
      n = WIDTH - s21_strlen(str);
      if (FLAG.hash == 1) {
        s21_strcat(string, "0");
      }
      if (n > 2 && FLAG.hash == 1) n -= 2;

      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
      s21_strcat(string, str);
    }

    s21_strcat(string, numb_buff);
  }
  if (WIDTH > WIDTH - s21_strlen(numb_buff) && FLAG.minus == 1) {
    if (FLAG.zero == 0) {
      s21_strcat(string, numb_buff);
      n = WIDTH - s21_strlen(numb_buff);
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
  }
}

void add_g(char* string, char* str) {
  size_t n = 0;
  size_t i = 0;
  int flag_out = 0;
  if (NEGATIVE_NUM && FLAG.zero == true) {
    s21_strcat(string, "-");
  }
  if (NEGATIVE_NUM == false && FLAG.space == true &&
      WIDTH > WIDTH - s21_strlen(str)) {
    s21_strcat(string, " ");
    flag_out = 1;
  }
  if (NEGATIVE_NUM == false && FLAG.space == true &&
      WIDTH < WIDTH - s21_strlen(str)) {
    s21_strcat(string, " ");
  }

  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.minus == false) {
    n = WIDTH - s21_strlen(str);
    if (FLAG.zero == 0) {
      if (FLAG.plus == 1) n--;
      if (NEGATIVE_NUM > 0) n--;
      if (flag_out == 1) n--;

      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
      if (NEGATIVE_NUM > 0) {
        s21_strcat(string, "-");
      }
      if (FLAG.plus == 1 && NEGATIVE_NUM == 0) {
        s21_strcat(string, "+");
      }
    }
    if (FLAG.zero == 1) {
      if (FLAG.plus == 1 && NEGATIVE_NUM == 0) {
        s21_strcat(string, "+");
        i++;
      }
      if (NEGATIVE_NUM > 0) i++;
      if (flag_out == 1) n--;
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
    }
    s21_strcat(string, str);
  }
  if (WIDTH > WIDTH - s21_strlen(str) && FLAG.minus == 1) {
    if (NEGATIVE_NUM > 0) {
      s21_strcat(string, "-");
    }
    s21_strcat(string, str);
    n = WIDTH - s21_strlen(str);
    if (FLAG.zero == 0) {
      n--;
      while (i < n) {
        s21_strcat(string, " ");
        i++;
      }
    }
    if (FLAG.zero == 1) {
      while (i < n) {
        s21_strcat(string, "0");
        i++;
      }
    }
  }
  if (WIDTH < WIDTH - s21_strlen(str)) {
    if (NEGATIVE_NUM > 0) {
      s21_strcat(string, "-");
    }
    s21_strcat(string, str);
  }
}

char* add_to_string(char* string, char* str) {
  // printf("Ты в функции добавки строки, строка = %s", str);
  // getchar();

  if (*SPEC == 'c') add_c(string, str);

  if (*SPEC == 'd') add_d(string, str);

  if (*SPEC == 'f') add_f(string, str);

  if (*SPEC == 's') add_s(string, str);

  if (*SPEC == 'u') add_u(string, str);

  if (*SPEC == 'e' || *SPEC == 'E') add_e(string, str);

  if (*SPEC == 'p') add_p(string, str);

  if (*SPEC == 'x' || *SPEC == 'X') add_x(string, str);

  if (*SPEC == 'o') add_o(string, str);

  if (G_SPEC_OK) add_g(string, str);

  return string;
}

int G_science_output_check(long double* num, int* sign_expo) {
  int science_notation_output = false;

  /*

  Условия для вывода чисел с использованием спецификатора %g следующие:

  1. Если абсолютное значение числа больше или равно 1e-4 (0.0001) и меньше
      или равно максимальному значению типа double, число будет выведено в
  формате десятичной записи.

  2. Если абсолютное значение числа меньше 1e-4 или больше максимального
      значения типа double, число будет выведено в формате научной нотации
  (экспоненциальной записи).

  3. Если указана точность (например, %.10g), то количество значащих цифр в
      десятичной записи числа будет ограничено указанной точностью. Если
      количество значащих цифр больше точности, число будет округлено до
  указанной точности.

  4. По умолчанию, если точность не указана, то количество значащих цифр в
      десятичной записи числа будет определяться автоматически и зависит от
      точности представления типа double (обычно около 15-17 значащих цифр).

  5. Если число является специальным значением, таким как NaN (Not-a-Number)
      или Inf (Infinity), они будут выведены в соответствующем формате.


  */

  // make_positive_number(num, &sPrintf);

  long double num_check_power = *num;

  int science_expo_power =
      calculate_power_for_science(&num_check_power, sign_expo);

  // printf(" после назначения знак степеней отрицательный?  %s \n", *sign_expo
  // == 0 ? "нет":"да");

  if (PRECISION != 0) PRECISION--;

  // если 0, то выводим 0
  if (*num == 0) PRECISION = 0;

  //вывод числа в научной нотации
  else if (*num < 0.0001 || *num > __DBL_MAX__) {
    science_notation_output = true;

    // вывод числа в десятичном представлении
  } else {
    if (science_expo_power > PRECISION && *num > 1)
      science_notation_output = true;
    else {
      science_expo_power *= *sign_expo ? 1 : -1;
      PRECISION += science_expo_power;
    }
  }
  PRECIS_INIT = true;

  return science_notation_output;
}

char* case_c(char* string, va_list* next_arg) {
  char c[2];
  c[0] = va_arg(*next_arg, int);
  c[1] = '\0';
  string = add_to_string(string, c);
  return string;
}

char* case_s(char* string, va_list* next_arg) {
  string = add_to_string(string, va_arg(*next_arg, char*));
  return string;
}

long double case_gGEefduoxXp(va_list* next_arg, int* base) {
  long double num = 0;

  switch (*SPEC) {
    case 'g':
      NEXT_CASE;
    case 'G':
      NEXT_CASE;
    case 'E':
      NEXT_CASE;
    case 'e':
      NEXT_CASE;
    case 'f': {
      *base = 10;
      if (LENGTH == L_LONG)
        VARG(long double);
      else
        VARG(double);
      break;
    }

    case 'd': {
      *base = 10;
      READ_VARGS_DECIMAL;
      break;
    }

    case 'u':
      *base = 10;
      NEXT_CASE;
    case 'o':
      if (*base == 0) *base = 8;
      NEXT_CASE;
    case 'p':
      if (*SPEC == 'p') {
        LENGTH = ll_LONG;
        FLAG.hash = true;
      }
      NEXT_CASE;
    case 'x':
      NEXT_CASE;
    case 'X': {
      if (*base == 0) *base = 16;
      READ_VARGS_UNSIGNED_DECIMAL;
      break;
    }
  }
  return num;
}

void convert_to_science(long double* float_part, long double* num,
                        int* len_science, int* sign_expo,
                        int* science_expo_power, int base) {
  long double temp_num = *num;

  *science_expo_power = calculate_power_for_science(
      num, sign_expo);  // нахождение степени и знака экспоненты

  int science_precision =
      PRECISION -
      *science_expo_power *
          (*sign_expo ? -1 : 1);  // определение вспомогательной степени для
                                  // аппроксимации от изначального числа

  // printf("\nточность для определения точности числа до конвертации в научн
  // нотацию = %d\n", science_precision);

  temp_num = roundl(temp_num * powl(base, science_precision));

  // printf("\nЧисло после аппроксимации до конвертации в науч нотацию = %Lf",
  // temp_num); getchar();

  *num = temp_num / powl(base, PRECISION);

  int addon = false;
  if (*num >= 10) {
    *num /= 10.L;
    science_expo_power++;
    temp_num /= 10.L;
    addon = true;
  }

  *float_part = temp_num - (int)(*num) * powl(base, PRECISION - addon);

  // printf("\nцелая часть после аппроксимации = %Lf\n", *num);
  // printf("\nвещественная часть после аппроксимации = %Lf\n", *float_part);

  int count_digits_in_expo_power =
      count_integer(*science_expo_power,
                    10);  // подсчёт количества цифр в числе степени экспоненты

  *len_science =
      1 + 1 + (count_digits_in_expo_power < 2 ? 2 : count_digits_in_expo_power);
  //             ^Ee   ^-+       ^количество цифр в числе степени экпоненты(от
  //             2х и больше)
}

// проверка числа на бесконечность и нечисло
int nan_infinity_check(long double* number, char* str_nan_inf) {
  int check = false;

  char* ptr = str_nan_inf;

  if (isinf(*number)) {
    inf_conditions_output();
    if (*number < 0) NEGATIVE_NUM = true;
    check = true;
  } else if (isnan(*number)) {
    nan_conditions_output();
    s21_strncpy(ptr, "nan", 3);
    check = true;
  }

  if ((INF_NAN_CAPS) && check == true) {
    while (*ptr != '\0') *ptr++ -= 32;
  }

  if (check) printf("str_nan = %s", str_nan_inf);

  return check;
}

void inf_conditions_output() {
  FLAG.zero = false;
  PRECISION = false;
  PRECIS_INIT = false;
  FLAG.hash = false;
}

void nan_conditions_output() {
  inf_conditions_output();
  FLAG.plus = false;
  FLAG.space = false;
}

void prepare_to_get_string_from_num(long double* num, long double* float_part,
                                    int* len_science, int* sign_expo,
                                    int* science_expo_power, int base) {
  make_positive_number(num);  // делаем число положительным

  if (G_SPEC_OK)
    *len_science = G_science_output_check(
        num, sign_expo);  // определяем точность и условие вывода как десятичное
                          // или научная нотация

  if (*len_science == true)
    convert_to_science(float_part, num, len_science, sign_expo,
                       science_expo_power, base);
  else
    approximate(num, float_part, base);
}

// функция обработки аргумента в зависимости от спецификатора
char* track_spec(char* string, va_list* next_arg) {
  // параметры, необходимые для научной нотации
  int len_science =
      false;  // длина строки экспоненты для случая научной нотации
  int sign_expo = false;  // знак степени экспоненты
  // printf(" знак степеней отрицательный?  %s \n", sign_expo == 0 ?
  // "нет":"да");

  switch (*SPEC) {
    case 'c':
      string = case_c(string, next_arg);
      break;

    case 's':
      string = case_s(string, next_arg);
      break;
    case 'e':
      NEXT_CASE;
    case 'E':
      len_science = true;
      NEXT_CASE;
    case 'g':
      NEXT_CASE;
    case 'G':
      NEXT_CASE;
    case 'f':
      if (PRECIS_INIT == false) {
        PRECISION = 6;
        PRECIS_INIT = true;
      }
      NEXT_CASE;
    case 'd':
      NEXT_CASE;
    case 'u':
      NEXT_CASE;
    case 'o':
      NEXT_CASE;
    case 'p':
      NEXT_CASE;
    case 'x':
      NEXT_CASE;
    case 'X': {
      int base = 0;  // инициализация экспоненты

      long double num = case_gGEefduoxXp(
          next_arg,
          &base);  // считывание числа из аргумента и определение экспоненты

      char str_nan_inf[] = "inf";
      int check_nan_inf = nan_infinity_check(&num, str_nan_inf);

      long double float_part = 0;
      int science_expo_power = 0;

      if (check_nan_inf == false)
        prepare_to_get_string_from_num(&num, &float_part, &len_science,
                                       &sign_expo, &science_expo_power, base);

      int point = 0;  //положение точки в строке числа
      int len_full = 0;

      if (check_nan_inf == false)
        len_full = count_length_number(
            num, &point,
            base);  //количество символов в числе,включая точку, но не включая
                    //знак минуса если число отрицательное

      char str[len_full + len_science +
               1];  // создаём статический массив для цифры.
      init_static_string(
          str,
          len_full +
              len_science);  //записываем 0 в конец и заполняем массив пробелами

      // основная функция конвертирования числа в строку
      char* str_out = s21_NULL;
      if (check_nan_inf == false)
        str_out = number_to_string(
            num, float_part, str, point, len_full, len_science,
            science_expo_power, sign_expo,
            base);  // конвертируем цифру в строку и заполняем массив

      string = add_to_string(string, check_nan_inf ? str_nan_inf : str_out);

      break;
    }

    default:
      printf("\nОшибка! нет такого спецификатора = >%c<!", *SPEC);
  }
  return string;
}

int s21_sprintf(char* string, const char* format, ...) {
  char* begin = string;

  // если есть форматная строка
  if (format) {
    // инициализируем переменную next_arg для перемещения по аргрументам
    // процедуры, идущим после форматной строки
    va_list next_arg;
    va_start(next_arg, format);

    // начинаем сканировать посимвольно форматную строку
    while (*format) {
      // ищем первый символ % в форматной строке
      char* percent = s21_strchr(format, '%');

      if (percent) {
        s21_strncat(string, format, percent - format);

        int count_percent = 1;

        while (*(++percent) == '%') {
          count_percent++;

          if (count_percent == 2) {
            count_percent = 0;
            s21_strcat(string, "%");
          }
        }

        format = percent;

        if (count_percent) {
          // ищем в оставшемся куске форматной строки следующий символ %
          char* next_percent = s21_strchr(format, '%');

          // иначе ищем в последующем остатке форматной строки спецификатор

          char* find_specificator = s21_strpbrk(format, "csduoxXpfeEgG");

          // если спецификатор найден, то:
          if (find_specificator) {
            // если следующего символа % в остатке строки не оказалось или же он
            // стоит дальше чем символ спецификатора, то:
            if (!next_percent || (next_percent > find_specificator)) {
              SPEC = find_specificator;  // инициализируем спецификатор для
                                         // данной строчки записи в string

              // вызов основной процедуры для сканирования куска форматной
              // строки от символа % до спекцификатора
              scan_format(format, &next_arg);

              // вызов функции заполнения результирующей строки в зависимости от
              // спецификаторов
              string = track_spec(string + s21_strlen(string), &next_arg);

              //обнуляем флаги и параметры для следующего скаринования форматной
              //строки
              s21_memset(&sPrintf, 0, sizeof(sPrintf));

              // переходим на след после спецификатора символ
              format = find_specificator + 1;

            }
            // если след символ % встретился раньше чем спецификатор, значит
            // кусок строки до след. % просто записывам в строку вывода
            else if (next_percent && next_percent < find_specificator) {
              s21_strncat(string, format, next_percent - format);

              // переводим каретку на символ след. %
              format = next_percent;
            }

          }
          // если же в остатке строки после символа % не оказалось спецификатора
          else {
            // printf("\n\nошибка! Отсутствует спецификатор в части строки
            // %.*s", next_percent ? (int)(next_percent-format) :
            // (int)s21_strlen(format), format);
          }
        }
      }
      // если символ % в остатке строки не найден, то просто копируем остаток
      // строки в строку вывода и перемещаемся на последний символ форматной
      // строки для выхода из её сканирования
      else {
        s21_strncat(string, format, s21_strlen(format));
        format = format + s21_strlen(format);
      }
    }

    //  printf("\n\n%d", va_arg(next_arg, int));
    va_end(next_arg);
  }
  // пока что возвращает не совсем верно
  return s21_strlen(begin);
}

// делает число положительным.
//В случае успеха, возвращает 1 - значит число было отрицательным, либо 0 -
//значит было положительным
int s21_fabs(long double* number) {
  int check = 0;

  if (*number < 0) {
    check = 1;
    invert_sign_number(number);
  }

  return check;
}

// считает количество символов в целой части числа до точки
int count_integer(long double number, int base) {
  s21_fabs(&number);

  int len_celoe = 0;

  do len_celoe++;
  while ((number /= base) > 1);

  return len_celoe;
}

// считает сколько всего нужно ячеек выделить для строки в которую посимвольно
// запишем всё число
int count_length_number(long double number, int* point,  // int precision,
                        int base) {
  *point =
      count_integer(number, base);  // длина целой части числа до точки
                                    // совпадает с положением точки в строке

  // итоговая длина строки для числа
  int len_full = *point + 1 + PRECISION;
  //                      ^точка
  // если precision = 0, то вычитаем один знак, так как точки не будет в выводе
  if (PRECISION == 0) len_full--;

  return len_full;
}

// забираем дробную часть, конвертируя её в целую с учётом точности
long double float_part_powered_up_by_precision(
    long double number,  // int precision,
    int base) {
  return fmodl(number, 1.L) * powl(base, PRECISION);
}

// если число отрицательное, делаем его положительным и записываем знак в поле
// структуры
int make_positive_number(long double* number) {
  return !NEGATIVE_NUM ? NEGATIVE_NUM = s21_fabs(number) : true;
}

//просто меняет знак числа на противоположный
void invert_sign_number(long double* number) { *number = -*number; }

// инициализация пустого статического строкового массива
void init_static_string(char* string, int length) {
  string[length] = '\0';            // нулевой символ в конце
  s21_memset(string, '#', length);  //заполняем пробелами
}

// Определение количества степеней экспоненты и их знака для перевода числа в
// научную нотацию
int calculate_power_for_science(long double* number, int* sign_expo) {
  long double temp_num = *number;

  int power_count = 0;  // счётчик степени экспоненты

  if (temp_num != 0) {
    if (temp_num < 0) temp_num *= -1;

    if (temp_num < 1) {
      do power_count++;
      while ((temp_num *= 10) < 1);
      *sign_expo =
          true;  // флаг минуса для степени экспоненты. Минус есть, если true
    } else if (temp_num >= 10)
      do power_count++;
      while ((temp_num /= 10) >= 10);
  }

  return power_count;
}

// аппроксимирует число до необходимой точности.
// Отделяет дробную часть от целой, аппроксимирует их и записывает новые
// значения дробной и целой частей
void approximate(long double* number, long double* float_part,
                 int base  //, int precision
) {
  *float_part = float_part_powered_up_by_precision(*number  //, precision
                                                   ,
                                                   base);

  if (roundl(*float_part) - *float_part > 0) {
    *float_part = roundl(*float_part);  //округление до заданной точности

    if (*float_part >= powl(base, PRECISION)) {
      *float_part -= powl(base, PRECISION);
      (*number)++;
    }
  }

  *number = truncl(*number) + fmodl(*float_part / powl(base, PRECISION), 1.L);
}

// запись экспоненты и её степени в строку
void rec_sci_nota_expo_to_str(char* str, int len_science, char E, int sign_expo,
                              int science_expo_power) {
  s21_memset(str, '0', len_science);  // заполняем нулями строчку числа

  *str++ =
      E;  // записываем букву Е в строку и перемещаем указатель на след. символ
  *str-- = sign_expo ? '-' : '+';  // записываем знак экспоненты и возвращаем
                                   // указатель на прежнее место
  str = str + len_science;  // помещаем указатель на место нулевого символа
  *str-- = '\0';  // выставляем нулевой символ и перемещаем указатель на
                  // предыдущий символ

  while (science_expo_power >=
         1) {  // записываем цифры числа степени экспоненты в ячейки строки
    *str-- = science_expo_power % 10 + '0';
    science_expo_power /= 10;
  }
}

// запись вещественного числа с плавающей точкой в строку, включая десятичные,
// 8-ми ричные и 16-ти ричные числа
char* rec_dbl_num_to_str(char* str, int len_full_number,
                         int point_position  //, int precision
                         ,
                         char ch_addon, long double number,
                         long double float_part, int base) {
  for (int i = len_full_number; i >= 0; i--) {
    if (i == len_full_number)
      str[i] = '\0';
    else if (i == point_position && PRECISION != 0)
      str[i] = '.';
    else if (i > point_position) {
      str[i] = fmodl(float_part, 10.L) + '0';
      float_part /= 10.L;
    } else {
      int num = fmodl(number, base);
      str[i] = num > 9 ? num - 10 + ch_addon : num + '0';
      number /= base;
    }
  }

  return str;
}

// для спецификатора G считает нули в конце мантиссы, чтобы сократить их потом
// при записи в строку
int g_sciense_count_last_zeroes_mantisse(
    long double* float_part  //, int precision
) {
  int precision = PRECISION;
  int count_zeroes = 0;
  int check = true;
  while (precision-- > 0 && check == true)
    if (fmodl(*float_part, 10.L) == 0) {
      count_zeroes++;
      *float_part /= 10.L;
    } else
      check = false;

  // поправка на убирание точки, если не будет дробной части после точки
  if (count_zeroes == PRECISION && PRECISION != 0) count_zeroes++;

  return count_zeroes;
}

// Запись числа long double в строку string
char* number_to_string(long double number, long double float_part, char* str,
                       int point_position, int len_full_number, int len_science,
                       int science_expo_power, int sign_expo, int base) {
  // int precision = PRECISION;

  // поправка смещения строки левее для записи экспоненты для спецификатора G,
  // если в конце мантиссы окажутся нули
  int count_zeroes = 0;
  if (G_SPEC_OK)
    count_zeroes =
        g_sciense_count_last_zeroes_mantisse(&float_part  //, precision
        );

  // запись вещественного или целого числа в строку, в том числе и 8миричных или
  // 16ричных
  char ch = *(SPEC) == 'X'
                ? 'A'
                : 'a';  // нужно для записи в строку шестнадцатиричных чисел
  str = rec_dbl_num_to_str(str, len_full_number - count_zeroes,
                           point_position,               // PRECISION,
                           ch, number, float_part, base  //, approximate_addon
  );

  // запись в строку экспоненты для случая научной нотации (спецификатор e или
  // E)
  if (len_science) {  // если длина строки числа с экспонентой не нулевая

    ch = *(SPEC) >= 'e' ? 'e' : 'E';
    rec_sci_nota_expo_to_str(str + len_full_number - count_zeroes, len_science,
                             ch, sign_expo, science_expo_power);

    // printf("\n\n\n ЧИСЛО В НАУЧНОЙ НОТАЦИИ = %s%s", NEGATIVE_NUM? "-":"",
    // str);
  }

  return str;
}
