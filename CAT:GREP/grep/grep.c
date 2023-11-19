#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

// 1) Регулярные выражения
// 2) Простой grep
// 3) *1-2 флага

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

/*void main_func(int argc, char *argv[]) {
  int rez;
    regex_t regex;
       int reti;
       reti = regcomp(&regex, "your_regex", 0);
  FILE *fd;
  int j = argc - 1;
  fd = open_file(argv[j]);
  int option_index = 0;
  while ((line = fgetc(fd)) != EOF) {
      while ((rez = getopt(argc, argv, "eivcln");) != -1) {
          switch (rez) {
            case 'e':
              break;
            case 'i':
              break;
            case 'v':
              break;
            case 'c':
              break;
            case 'l':
              break;
            case 'n':
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
  regfree(&regex);*/
//}
int main(int argc,char *argv[]){
    //main_func(argc, argv);
    regex_t regex;
    int reti;
    reti = regcomp(&regex, argv[1], 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    FILE *fd;
    char line[256];
    int j = argc - 1;
    fd = open_file(argv[j]);
    fgets(line, sizeof(line), fd);
    reti = regexec(&regex, line, 0, NULL, 0);
    if (!reti) {
        printf("%s", argv[1]);
    }
    regfree(&regex);
    return 0;
}
