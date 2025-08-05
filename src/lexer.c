#include "lexer.h"

int init_lexer(PLOK_lexer* l, char* path) {
  FILE* file;
  long length;

  file = fopen(path, "rb");
  if (file == NULL)
  {
    puts("[ERROR] - Couldn't open file");
    return 1; 
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  l->content = malloc(length + 1);
  if (l->content)
  {
    size_t bytes_read = fread(l->content, 1, length, file);
    l->content[bytes_read] = '\0'; 
  }
  else
  {
    puts("[ERROR] - Couldn't read file content");
    fclose(file);
    return 1; 
  }

  fclose(file);

  l->row = 0;
  l->column = 0;

  l->tokens.items = NULL;
  l->tokens.count = 0;
  l->tokens.capacity = 0;

  return 0;
}
