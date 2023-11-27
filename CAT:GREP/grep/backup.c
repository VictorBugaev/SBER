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
    int rez;
    int flag = 1;
    while (fgets(line, sizeof(line), fd) != NULL) {
        reti = regcomp(&regex, argv[1], 0);
        reti = regexec(&regex, line, 0, NULL, 0);
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
                    reti = regcomp(&regex, argv[optind-1], 0);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    printf("%d", optind);
                    if (!reti) {
                        //flag = 0;
                        //snprintf(line, sizeof(line), "%s", argv[j]);
                        printf("%s", argv[optind]);
                        optind++;
                        while()
                    }
                    optind+=1;

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
        if (rez == -1 && !reti){// не тестил
            flag = 0;
        }
        if(!flag){
            printf("%s", line);
        }
        
        flag = 1;
    }
    regfree(&regex);
    return 0;
}

