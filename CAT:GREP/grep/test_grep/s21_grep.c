
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
  int kk = 1;
  int rez;
  int flag = 1;
  int tmp = 0;
  int flag_n = 0;
    int sem = 0;
  char *mass[256];
    char buf[512];
    int flag_l = 0;
    int flag_2l = 0;
    int help = 0;
  int mass_count = 0;
  for (int i = 0; i + optind < argc; i++) {
      if (file_check(argv[optind+i])) {
          mass[mass_count] = argv[optind+i];
          mass_count++;
      }
  }
 
    for(int i = 0; i < mass_count; i++){
        fd = open_file(mass[i]);
        
        while (fgets(line, sizeof(line), fd) != NULL) {
            reti = regcomp(&regex, argv[1], 0);
            reti = regexec(&regex, line, 0, NULL, 0);
            if(!reti){
                flag = 0;
                flag_l =1;
            }
            while ((rez = getopt(argc, argv, "e:ivcl:n")) != -1) {
                    switch (rez) {
                       case 'e':
                           reti = regcomp(&regex, argv[optind-1], 0);
                           reti = regexec(&regex, line, 0, NULL, 0);
                           if (!reti) {
                               flag = 0;
                           }
                           else{
                               flag_l = 1;
                           }
                           break;
                       case 'i':
                           reti = regcomp(&regex, argv[optind], REG_ICASE);
                           reti = regexec(&regex, line, 0, NULL, 0);
                           if (!reti) {
                               flag = 0;
                           }else{
                               flag_l = 1;
                           }
                           break;
                       case 'v':
                           reti = regcomp(&regex, argv[optind], 0);
                           reti = regexec(&regex, line, 0, NULL, 0);
                           if (reti) {
                               if (line[strlen(line) - 1] != '\n' && ((i+1)==mass_count)) {
                                      strcat(line, "\n");
                                  }
                               flag = 0;
                           }
                           break;
                       case 'c':
                           reti = regcomp(&regex, argv[optind], 0);
                           reti = regexec(&regex, line, 0, NULL, 0);
                           if (!reti) {
                               count += 1;
                           }
                            if (feof(fd) && ((i+1)==mass_count)){
                                flag = 0;
                                snprintf(line, sizeof(line), "%d\n", count);
                            }else if(feof(fd) && !((i+1)==mass_count)){
                                flag = 0;
                                snprintf(line, sizeof(line), "%d", count);
                            }
                           break;
                       case 'l':
                           reti = regcomp(&regex, argv[optind-1], 0);
                           reti = regexec(&regex, line, 0, NULL, 0);
                            if (!reti){
                                help = 1;
                           }else{
                               flag_2l = 1;
                               flag_l = 1;
                           }
                            if (help && feof(fd))
                                flag = 0;
                                snprintf(line, sizeof(line),"%s\n", mass[i]);
                           break;
                        case 'n':
                            flag_n = 1;
                            reti = regcomp(&regex, argv[optind], 0);
                            reti = regexec(&regex, line, 0, NULL, 0);
                            count += 1;
                            if (!reti) {
                                snprintf(buf, sizeof(buf),"%d:%s", count, line);
                                snprintf(line, sizeof(line),"%s", buf);
                                flag = 0;
                            }
                            break;
                        default:{
                            reti = regcomp(&regex, argv[1], 0);
                            reti = regexec(&regex, line, 0, NULL, 0);
                            if (!reti) {
                            
                                flag = 0;
                            }
                            break;
                        }
                        }
                        
                }
            optind = 1;
            if(!flag && mass_count > 1 && !flag_2l){
                printf("%s:", mass[i]);
            }
            if(!flag){
                printf("%s", line);
                
            }
            flag = 1;
            }
        if (!((i+1)==mass_count) && !flag_n && !flag_l){
            printf("\n");
        }
        count = 0;
        sem = 0;
        }
    regfree(&regex);
    return 0;
}
