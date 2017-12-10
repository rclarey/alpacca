#pragma once

typedef enum Symbol {
  // non-accepting symbols
  S_START,
  // accepting symbols
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

  T_BANG_EQUAL,
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
} Symbol;

typedef struct AST {
  Symbol symbol;

} AST;
