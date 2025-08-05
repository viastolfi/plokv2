#include <stdio.h>
#include <string.h>

#include "lexer.h"

int main(int argc, char **argv)
{
  if (argc == 1) {
    puts("[ERROR] - No plok file found, use it like so : ./plok example.pk"); 
    return 1;
  }

  size_t fnl = strlen(argv[1]);
  char extension[4];

  if (fnl >= 4) {
    strncpy(extension, argv[1] + fnl - 3, 3);
    extension[3] = '\0';
  } else {
    puts("[ERROR] - Extension file not recognize, use  please plok file only");
    return 1;
  }

  if (strcmp(extension, ".pk") != 0) {
    puts("[ERROR] - Extension file not recognize, use  please plok file only");
    return 1;
  }

  puts("[INFO] - Start lexing");
  puts("[INFO] - Init lexer");
  PLOK_lexer lexer = {0};
  if (init_lexer(&lexer, argv[1]) != 0) {
    puts("[ERROR] - Couldn't initialize lexer");
  } 

  return 0;
}
