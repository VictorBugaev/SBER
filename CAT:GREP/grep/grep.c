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
// 8) все что после шаблона - файл !!!!!!!!!!!
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
   int j = 0;
    int k = 0;
   int count = 0;
   int rez;
   int flag = 1;
   int tmp = 1;
   int sem = 0;
   while ((rez = getopt(argc, argv, "e:ivcl:n")) != -1) {
       
       while (optind + tmp< argc){
           if( rez == 'l' && !j ){
               tmp=0;
               j=1;
           }
           if (rez == 'e' && !k ){
               tmp ++;
               k = 1;
           }
           fd = open_file(argv[optind + tmp]);
           //printf("%c ", rez);
           //printf("%s\n", argv[optind+tmp]);
           
           while (fgets(line, sizeof(line), fd) != NULL) {
               reti = regcomp(&regex, argv[optind], 0);
               switch (rez) {
                  case 'e':
                       //printf("scs");
                      printf("%s ", argv[optind-1]);
                      reti = regcomp(&regex, argv[optind-1], 0);
                      reti = regexec(&regex, line, 0, NULL, 0);
                      if (!reti) {
                          //flag = 0;
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
                      if (!reti && sem < 1) {
                          flag = 0;
                          snprintf(line, sizeof(line), "%s ", argv[optind+tmp]);
                          sem++;
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
               
               if(!flag){
                  printf("%s", line);
               }
               
               flag = 1;
           }
           sem = 0;
           tmp++;
           k=0;
       }
       
   }
   return 0;
}
