#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DA_LIB_IMPLEMENTATION
#include "da.h"
#include "token.h"
#include "logger.h"

typedef struct {
  char value;
  bool has_value;
} PLOK_char_optionnal_value;

typedef struct {
  char* value;
  bool has_value;
} PLOK_string_optionnal_value;

typedef struct {
  PLOK_token* items;
  size_t count;
  size_t capacity;
} PLOK_tokens;

typedef struct {
  char* content;
  char* file_name;

  int column, row;
  int index;

  PLOK_tokens tokens;
} PLOK_lexer;

int init_lexer(PLOK_lexer* l, char* path);
int get_tokens(PLOK_lexer* l);
PLOK_char_optionnal_value peek(PLOK_lexer *l, int step);
PLOK_string_optionnal_value consume(PLOK_lexer *l, int offset);
int tokenize_intlit(PLOK_lexer *l);
char* get_line(PLOK_lexer* l);
int skip_line(PLOK_lexer* l);

#endif
