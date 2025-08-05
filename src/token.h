#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  PLOK_intlit,
  PLOK_id,
  PLOK_eq,
  PLOK_charlit
} PLOK_tokens_def;

typedef struct {
  PLOK_tokens_def token_type;

  int int_value;
  char* string_value;
  int string_len;
} PLOK_token;

#endif // TOKEN_H
