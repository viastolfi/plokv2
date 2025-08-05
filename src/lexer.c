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
  l->index = 0;

  l->tokens.items = NULL;
  l->tokens.count = 0;
  l->tokens.capacity = 0;

  return 0;
}

PLOK_char_optionnal_value peek(PLOK_lexer *l, int step) {
  if (l->index + step >= (int) strlen(l->content)) 
    return (PLOK_char_optionnal_value) {.has_value = false};
  else
    return (PLOK_char_optionnal_value) {.has_value = true, .value = l->content[l->index + step]};
}

PLOK_string_optionnal_value consume(PLOK_lexer* l, int offset) {
  if (offset == 0) {
    puts("[ERROR] - Lexer error on consume, offset might be > 0");
    return (PLOK_string_optionnal_value) {.has_value = false};
  }  

  char* s = malloc(offset + 1);

  if (s == NULL) {
    puts("[ERROR] - Lexer error on consume, mem error");
    return (PLOK_string_optionnal_value) {.has_value = false};
  }

  for (int i = 0; i < offset; ++i) {
    s[i] = l->content[l->index];
    l->index++;
  }

  s[offset] = '\0';
  return (PLOK_string_optionnal_value) {.has_value = true, .value = s};
}

int get_tokens(PLOK_lexer* l) {
  PLOK_char_optionnal_value c;

  while ((c = peek(l, 0)).has_value) {
    if (isdigit(c.value)) {
      int res = tokenize_intlit(l);
      if (res != 0) {
        puts("[ERROR] - Lexer error on tokenize_int");
        return 1;
      }

      continue;
    }   

    if (c.value == ' ') {
      PLOK_string_optionnal_value dummy = consume(l, 1); 
      free(dummy.value);
      l->column++;

      continue;
    }

    if (c.value == '\n') {
      PLOK_string_optionnal_value dummy = consume(l, 1); 
      free(dummy.value);
      l->row++;

      continue;
    }
  } 

  return 0;
}

int tokenize_intlit(PLOK_lexer* l) {
  int number_length = 0;
  PLOK_char_optionnal_value c;
  
  while((c = peek(l, number_length)).has_value)
  {
    if(!isdigit(c.value))
      break;

    ++number_length;
  }

  PLOK_string_optionnal_value number = consume(l, number_length); 

  if (!number.has_value) {
    puts("[ERROR] - Lexer error on tokenize_intlit, couldn't get intlit value");
    return 1;
  }

  PLOK_token token = {.token_type = (PLOK_tokens_def) PLOK_intlit, .int_value = atoi(number.value)};
  da_append(&(l->tokens), token);
  l->column += number_length;

  return 0;
}
