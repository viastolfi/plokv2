#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define DA_LIB_IMPLEMENTATION
#include "da.h"

// TODO define this
typedef struct {
  int dummy;
} token_t;

typedef struct {
  token_t* items;
  size_t count;
  size_t capacity;
} PLOK_tokens;

typedef struct {
  char* content;

  int column, row;

  PLOK_tokens tokens;
} PLOK_lexer;

int init_lexer(PLOK_lexer* l, char* path);

#endif
