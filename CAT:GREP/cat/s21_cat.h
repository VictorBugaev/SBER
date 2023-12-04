#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>


FILE *open_file(char *name);
void close_file(FILE *fd);
int b_cat(char line, int is_empty_line, int *nonEmptyLineNumber);
void e_cat(char line);
char s_cat(char line, int *count,int is_empty_line );
int n_cat(char line, int start, int *nonEmptyLineNumber);
char t_cat(char line);
char v_cat(char line);
void main_func(int argc, char *argv[]);



#endif // SRC_CAT_S21_CAT_H_

