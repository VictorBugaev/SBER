#define _POSIX_C_SOURCE 200809L
#include "s21_grep.h"

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

void main_func(int argc, char *argv[]) {
  regex_t regex;
  int reti, rez;
  FILE *fd;
  char line[256], buf[512], comp_arg[256];
  int flag = 1, flag_l = 0, flag_v= 0, flag_c= 0, mass_count = 0, comp_num = 0, count_c = 0, count_n = 0, count_l = 0, flag_l2=0;
  char *mass[256];
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
            snprintf(comp_arg, sizeof(comp_arg), "%s", optarg);
                reti = regcomp(&regex, comp_arg, comp_num);
                reti = regexec(&regex, line, 0, NULL, 0);
                if (!reti){
                    flag = 0;
                }
            break;
          case 'i':
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
            strcpy(line, buf);
            break;
            default:
                regfree(&regex);
                break;
        }
      }
        if (line[strlen(line) - 1] != '\n') {
            strcat(line, "\n");
        }
        if (!flag && mass_count > 1 && !flag_l) {
        
            snprintf(mass[i], strlen(mass[i])+1, "%s:", mass[i]);
            snprintf(line, strlen(mass[i])+strlen(line), "%s%s", mass[i], line);
        }
    
        reti = regcomp(&regex, comp_arg, comp_num);
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti && !flag_v) {
            flag = 0;
            count_l ++;
            count_c ++;
            flag_l2 = 1;
        }
        if (flag_v && reti){
            flag = 0;
            count_l ++;
            count_c ++;
        }
        if (flag_l || flag_c){
            flag = 1;
        }
        if (flag_l && flag_c){
            count_c = flag_l2;
        }
        if (!flag) {
          printf("%s", line);
        }
        
        optind = 1;
        flag = 1;
    }
    if (flag_c && feof(fd)) {
        if (mass_count > 1){
            printf("%s:", mass[i]);
        }
        printf("%d\n", count_c);
    }
    if(flag_l && count_l > 0 && feof(fd)) printf("%s\n", mass[i]);
    count_n = 0;
    count_c = 0;
    count_l = 0;
    flag_l2 = 0;
    close_file(fd);
  }
  regfree(&regex);
}

int main(int argc, char *argv[]){
    main_func(argc, argv);
    return 0;
}
