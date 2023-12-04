#define _POSIX_C_SOURCE 200809L
#include "s21_cat.h"
FILE *open_file(char *name) {
  FILE *fd;
  if ((fd = fopen(name, "r")) == NULL) {
    printf("Ошибка открытия файла\n");
  }
  return fd;
}

void close_file(FILE *fd) { fclose(fd); }

int b_cat(char line, int is_empty_line, int *nonEmptyLineNumber) {
  if (is_empty_line && line != '\n') {
    printf("%6d\t", *nonEmptyLineNumber);
    is_empty_line = 0;
    (*nonEmptyLineNumber)++;
  }
  if (line == '\n') {
    is_empty_line = 1;
  }
  return is_empty_line;
}

void e_cat(char line) {
  if (line == '\n') {
    printf("$");
  }
}

char s_cat(char line, int *count,int is_empty_line ) {
    if (is_empty_line && line != '\n') {
         is_empty_line = 0;
         (*count) = 0;
     }
     if (line == '\n') {
         is_empty_line = 1;
         (*count)++;
     }
     if ((*count) > 2) {
         line = '\0';
     }
     return line;
}

int n_cat(char line, int start, int *nonEmptyLineNumber) {
  if (start) {
    printf("%6d\t", *nonEmptyLineNumber);
    (*nonEmptyLineNumber)++;
    start = 0;
  }
  if (line == '\n') {
    start = 1;
  }
  return start;
}

char t_cat(char line) {
  if (line == '\t') {
    line ^= 0x40;
    printf("^");
  }
  return line;
}

char v_cat(char line) {
  if ((line < 32 || line > 126) && line != 9 && line != 10) {
    line ^= 0x40;
    printf("^");
  }
  return line;
}

void main_func(int argc, char *argv[]) {
  int rez;
  FILE *fd;
  int j = argc - 1;
  char line;
  int is_empty_line;
  int start;
  int nonEmptyLineNumber = 1;
  int count = 0;
  int buf_rez;
  fd = open_file(argv[j]);
  int option_index = 0;
  static struct option long_options[] = {{"squeeze-blank", 0, NULL, 's'},
                                         {"number-nonblank", 0, NULL, 'b'},
                                         {"number", 0, NULL, 'n'},
                                         {0, 0, 0, 0}};
  const char *short_options = "bEensTtv";
  while ((line = fgetc(fd)) != EOF) {
  
    while ((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
         if (rez == 'n') {
             buf_rez=getopt_long(argc,argv,short_options,long_options,&option_index);
             if(buf_rez == 'b'){
                 rez = buf_rez;
             }else{
                 optind = 0;
                 rez = getopt_long(argc,argv,short_options,long_options,&option_index);
                 printf("%c ", rez);
            }
      }
      switch (rez) {
        case 'b':
         is_empty_line = b_cat(line, is_empty_line, &nonEmptyLineNumber);
          break;
        case 'E':
          e_cat(line);
          break;
        case 'n':
          start = n_cat(line, start, &nonEmptyLineNumber);
          break;
        case 's':
          line = s_cat(line, &count, is_empty_line);
          break;
        case 'T':
          line = t_cat(line);
          break;
        case 'v':
          line = v_cat(line);
          break;
          case 't':
            line = t_cat(line);
            line = v_cat(line);
            break;
          case 'e':
            e_cat(line);
            line = v_cat(line);
            break;
        default:
          break;
      }
    }
if(rez == -1 && line != EOF){
          optind = 0;
      }
      if (line == '\0'){
          continue;
      }
      printf("%c", line);
  }
  close_file(fd);
}

int main(int argc, char *argv[]){
    main_func(argc, argv);
    return 0;
}
