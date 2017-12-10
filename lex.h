#pragma once

// we purposefully put non-accepting states first so we can do
// `state > START` to check if `state` is accepting
typedef enum TokenType {
  // non-accepting states
  T_BAD_STATE = 0,
  T_EQUAL,
  T_BACKSLASH,
  T_START,

  // "accepting" states for the purpose of nice errors
  T_INTALPHA,
  T_STRING_UNCLOSED,
  T_CANCEL_QUOTE,

  // accepting states
  T_BANG,
  T_MINUS,
  T_PLUS,
  T_SLASH,
  T_LTHAN,
  T_GTHAN,
  T_STAR,
  T_MOD,
  T_AND,
  T_NOT,
  T_OR,
  T_XOR,
  T_LPAREN,
  T_RPAREN,
  T_LBRACK,
  T_RBRACK,
  T_LBRACE,
  T_RBRACE,
  T_COMMA,
  T_COLON,
  T_NEWLINE,

  T_BANG_EQUAL,
  T_PLUS_PLUS,
  T_EQUAL_EQUAL,
  T_FAT_ARROW,
  T_ARROW,
  T_SLASH_SLASH,
  T_LTHAN_EQUAL,
  T_GTHAN_EQUAL,
  T_STAR_STAR,
  T_AND_AND,
  T_OR_OR,

  T_TYPE_STR,
  T_TYPE_INT,
  T_TYPE_UINT,
  T_TYPE_DBL,
  T_TYPE_BOOL,
  T_ELSE,

  T_IDENTIFIER,
  T_BOOLEAN,
  T_INTEGER,
  T_COMMENT,
  T_COMMENT_END,
  T_STRING,
  T_WHITESPACE,

  T_ID_S,
  T_ID_ST,
  T_ID_I,
  T_ID_IN,
  T_ID_U,
  T_ID_UI,
  T_ID_UIN,
  T_ID_D,
  T_ID_DB,
  T_ID_B,
  T_ID_BO,
  T_ID_BOO,
  T_ID_E,
  T_ID_EL,
  T_ID_ELS,
  T_ID_T,
  T_ID_TR,
  T_ID_TRU,
  T_ID_F,
  T_ID_FA,
  T_ID_FAL,
  T_ID_FALS,
} TokenType;

typedef struct Token {
  TokenType type;
  void* value;
  struct Token* next;
  int line;
  int col;
} Token;

Token* lex(const char* input);
