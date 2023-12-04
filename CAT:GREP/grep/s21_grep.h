#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <ctype.h>
#include <getopt.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

FILE *open_file(char *name);
void close_file(FILE *fd);
void main_func(int argc, char *argv[]);




#endif // SRC_GREP_S21_GREP_H_

