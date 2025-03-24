CC=gcc
TESTFLAGS=-lcheck
GCCFLAGS=-Wall -Werror -Wextra -std=c11 #-fsanitize=address
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LIB_SOURCES=s21_insert.c s21_strcat.c s21_trim.c s21_sprintf.c s21_memcmp.c s21_strerror.c s21_sscanf.c s21_to_upper.c s21_to_lower.c s21_strtok.c s21_strstr.c s21_strrchr.c s21_strchr.c s21_strpbrk.c s21_strncmp.c s21_strncpy.c s21_strcspn.c s21_memset.c s21_memchr.c s21_memcpy.c s21_strlen.c s21_strncat.c
CHECK=-I/opt/homebrew/include -L/opt/homebrew/lib# для домашнего компа, при проверке в школе убрать этоу команду

all: clean test s21_string.a gcov_report


s21_string.a: clean
	$(CC) $(GCCFLAGS) -c s21_insert.c s21_strcat.c s21_sprintf.c s21_strerror.c s21_trim.c s21_memcmp.c s21_sscanf.c s21_to_upper.c s21_to_lower.c s21_strtok.c s21_strstr.c s21_strrchr.c s21_strchr.c s21_strpbrk.c s21_strncmp.c s21_strncpy.c s21_strcspn.c s21_memset.c s21_memchr.c s21_memcpy.c s21_strlen.c s21_strncat.c
	ar rc s21_string.a *.o
test: clean s21_string.a
	$(CC) $(GCCFLAGS) $(TESTFLAGS) $(GCOVFLAGS) s21_string.a testing_sscanf.c test_sscanf.c -o gcovreport
	./gcovreport
gcov_report: clean s21_string.a
	$(CC) $(GCCFLAGS) $(TESTFLAGS) $(GCOVFLAGS) $(LIB_SOURCES) testing_sscanf.c test_sscanf.c -o gcovreport
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	open report/index.html

clang-format:
	clang-format -i -style=Google *.c *.h

clang-check:
	clang-format -n -style=Google *.c *.h

cppcheck:
	cppcheck *.c *.h

clean:
	rm -rf *.o *.a *.gcda *.gcno *.gcov ./report *.info gcovreport *.out

rebuild: clean all

make gcc: s21_string.a
	$(CC) s21_sprintf.c main.c s21_string.a -g -fsanitize=address
	./a.out


# curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh  установка brew