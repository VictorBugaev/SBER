#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

// 1) Регулярные выражения V
// 2) Простой grep V
// 3) *1-2 флага V
// 4) доделать флаги
// 5) обработать defalut V
// 6) последний флаг
// 7) тесты

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

void close_file(FILE *fd) { fclose(fd); }

int main(int argc,char *argv[]){
    regex_t regex;
    int reti;
    FILE *fd;
    char line[256];
    int j = argc - 1;
    fd = open_file(argv[j]);
    int count = 0;
    int kk=1;
    int rez;
    int flag = 1;
    int tmp = 0;
    int lox = 0;
    while (fgets(line, sizeof(line), fd) != NULL) {
        //reti = regcomp(&regex, argv[1], 0);
        //reti = regexec(&regex, line, 0, NULL, 0);
        while ((rez = getopt(argc, argv, "e:ivcl:n")) != -1) {
            reti = regcomp(&regex, argv[j], 0);
            reti = regexec(&regex, line, 0, NULL, 0);
            switch (rez) {
                case 'e':
                    reti = regcomp(&regex, argv[optind-1], 0);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (!reti) {
                        flag = 0;
                    }
                    break;
                case 'i':
                    reti = regcomp(&regex, argv[optind], REG_ICASE);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (!reti) {
                        flag = 0;
                    }
                    break;
                case 'v':
                    reti = regcomp(&regex, argv[optind], 0);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (reti) {
                        flag = 0;
                    }
                    break;
                case 'c':
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (!reti) {
                        count += 1;
                    }
                        flag = 0;
                    snprintf(line, sizeof(line), "\r%d", count);
                    break;
                case 'l':
                    while (optind < argc){
                        tmp = optind - kk;
                        kk++;
                        fd = open_file(argv[optind]);
                        while (fgets(line, sizeof(line), fd) != NULL) {
                            reti = regcomp(&regex, argv[tmp], 0);
                            reti = regexec(&regex, line, 0, NULL, 0);
                            if (!reti && lox == 0) {
                                //flag = 0;
                                //snprintf(line, sizeof(line), "%s", argv[optind]);
                                printf("%s ", argv[optind]);
                                lox = 1;
                            }
                        }
                        lox = 0;
                        optind ++;
                    }
                    break;
                case 'n':
                    reti = regexec(&regex, line, 0, NULL, 0);
                    count += 1;
                    if (!reti) {
                        flag = 0;
                        printf("%d:", count);
                    }
                    break;
            }
        }
        optind = 1;
        //if (rez == -1 && !reti){// не тестил
          //  flag = 0;
        //}
        if(!flag){
            printf("%s", line);
        }
        
        flag = 1;
    }
    close_file(fd);
    regfree(&regex);
  //  regfree(&regex);
    return 0;
}
