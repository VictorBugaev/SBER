#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

// 1) Регулярные выражения V
// 2) Простой grep V
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

int main(int argc,char *argv[]){
    //main_func(argc, argv);
    regex_t regex;
    int reti;
  
    FILE *fd;
    char line[256];
   // char buf[256];
    //char buf2[512];
    int j = argc - 1;
    fd = open_file(argv[j]);
    int count = 1;
    int rez;
    /*if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }*/
    reti = regcomp(&regex, argv[2], 0);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return 1;
        }
    
    while (fgets(line, sizeof(line), fd) != NULL) {
        
        while ((rez = getopt(argc, argv, "eivcln")) != -1) {
            
            switch (rez) {
              case 'e':
                  /*  reti = regcomp(&regex, argv[optind], 0);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    optind += 1;
                    if ((rez = getopt(argc, argv, "eivcln")) == 'e'){
                        
                    }
                    if (!reti) {
                        printf("%s", line);
                    }
                    break;*/
              case 'i':
                    reti = regcomp(&regex, argv[optind], REG_ICASE);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (!reti) {
                        printf("%s", line);
                        
                    }
                break;
              case 'v':
                break;
              case 'c':
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (!reti) {
                        count += 1;
                    }
                    snprintf(line, sizeof(line), "\r%d", count);
                break;
              case 'l':
                    reti = regcomp(&regex, argv[optind], 0);
                    reti = regexec(&regex, line, 0, NULL, 0);
                    if (!reti) {
                        snprintf(line, sizeof(line), "%s", argv[j]);
                    }else{
                        for (unsigned long int i = 0; i < strlen(line); i++){
                            line[i] = '\0';
                        }
                    }
                break;
              case 'n':
                    reti = regexec(&regex, line, 0, NULL, 0);
                    count += 1;
                    if (!reti) {
                        printf("%d:", count);
                    }else{
                        for (unsigned long int i = 0; i < strlen(line); i++){
                            line[i] = '\0';
                        }
                    }
                break;
              default:
                reti = regexec(&regex, line, 0, NULL, 0);
                if (!reti) {
                    printf("%s", line);
                }
                break;
                
            }
            
          }
        optind = 1;
        printf("%s", line);
    }
    regfree(&regex);
    return 0;
}
