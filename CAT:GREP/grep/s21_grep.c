
#include <ctype.h>
#include <getopt.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

FILE *open_file(char *name);
void close_file(FILE *fd);
void main_func(int argc, char *argv[]);

FILE *open_file(char *name) {
  FILE *fd;
  if ((fd = fopen(name, "r")) == NULL) {
    printf("Ошибка открытия файла\n");
  }
  return fd;
}

int file_check(char *name) {
  FILE *fd;
  if ((fd = fopen(name, "r")) == NULL) {
    return 0;
  }
  fclose(fd);
  return 1;
}
void close_file(FILE *fd) { fclose(fd); }

int main(int argc, char *argv[]) {
  regex_t regex;
  int reti;
  FILE *fd;
  char line[256];
  int count = 0;
  int rez;
  int flag = 1;
  int flag_n = 0;
  char *mass[256];
  char buf[512];
  int flag_l = 0;
  int flag_v= 0;
    int flag_c= 0;
    int flag_e = 0;
    int flag_i = 0;
    int stop = 1;
  int help = 0;
  int mass_count = 0;
    char comp_arg[256];
    int comp_num = 0;
    int count_c = 0;
    int count_n = 0;
    int count_l = 0;
    
  for (int i = 0; i + optind < argc; i++) {
    if (file_check(argv[optind + i])) {
      mass[mass_count] = argv[optind + i];
      mass_count++;
    }
  }
  for (int i = 0; i < mass_count; i++) {
    fd = open_file(mass[i]);
    while (fgets(line, sizeof(line), fd) != NULL) {
      reti = regcomp(&regex, argv[1], 0);
      reti = regexec(&regex, line, 0, NULL, 0);
      if (!reti) {
        flag = 0;
      }
      while ((rez = getopt(argc, argv, "e:ivcln")) != -1) {
        switch (rez) {
          case 'e':
            flag_e = 1;
            snprintf(comp_arg, sizeof(comp_arg), "%s", optarg);
                reti = regcomp(&regex, comp_arg, comp_num);
                reti = regexec(&regex, line, 0, NULL, 0);
                if (!reti){
                    flag = 0;
                }
            break;
          case 'i':
            flag_i = 1;
            comp_num = 2;
            snprintf(comp_arg, sizeof(comp_arg), "%s", argv[optind]);
            break;
          case 'v':
            flag_v = 1;
            snprintf(comp_arg, sizeof(comp_arg), "%s", argv[optind]);
            break;
          case 'c':
            flag_c = 1;
            snprintf(comp_arg, sizeof(comp_arg), "%s", argv[optind]);
            break;
          case 'l'://исключение
            flag_l = 1;
            snprintf(comp_arg, sizeof(comp_arg), "%s", argv[optind]);
            break;
          case 'n':
            count_n += 1;
            snprintf(comp_arg, sizeof(comp_arg), "%s", argv[optind]);
            snprintf(buf, sizeof(buf), "%d:%s", count_n, line);
            snprintf(line, sizeof(line), "%s", buf);
            break;
        }
      }
        if (line[strlen(line) - 1] != '\n') {
            strcat(line, "\n");
        }
        if (!flag && mass_count > 1 && !flag_l) {
          snprintf(buf, sizeof(buf), "%s:%s", mass[i], line);
          snprintf(line, sizeof(line), "%s", buf);
        }
        //printf("%s ", comp_arg);
        reti = regcomp(&regex, comp_arg, comp_num);
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti && !flag_v) {
            flag = 0;
            count_l ++;
            count_c ++;
        }
        if (flag_v && reti){
            flag = 0;
            count_l ++;
            count_c ++;
        }
        if (flag_l || flag_c){
            flag = 1;
        }
        if (!flag) {
          printf("%s", line);
        }
        if(flag_l && count_l > 0 && feof(fd)) printf("%s\n", mass[i]);
        if (flag_c && feof(fd)) {
            if (mass_count > 1){
                printf("%s:", mass[i]);
            }
            printf("%d\n", count_c);
        }
        optind = 1;
        flag = 1;
    }
    count_n = 0;
    count_c = 0;
    count_l = 0;
    close_file(fd);
  }
  regfree(&regex);
  return 0;
}

