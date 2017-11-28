#include <stdlib.h>
#include <string.h>


/*
TOKENS
----------
BANG:   !
EQUAL:  =
MINUS:  -
PLUS:   +
SLASH:  /
LTHAN:  <
GTHAN:  >
DOT:    .
STAR:   *
MOD:    %
AND:    &
NOT:    ~
OR:     |
XOR:    ^
LPAREN: (
RPAREN: )
LBRACK: [
RBRACK: ]
LBRACE: {
RBRACE: }
QUOTE: '
COMMA:  ,
COLON:  :
POUND:  #

BANG_EQUAL:  !=
EQUAL_EQUAL: ==
ARROW:       ->
SLASH_SLASH: //
LTHAN_EQUAL: <=
GTHAN_EQUAL: >=
STAR_STAR:   **
AND_AND:     &&
OR_OR:       ||
NULL_TUPLE:  ()

TYPE_STR:  str
TYPE_INT:  int
TYPE_UINT: uint
TYPE_DBL:  dbl
TYPE_BOOL: bool

IDENTIFIER: [A-Za-z_][A-Za-z0-9_]*
NUMBER:     [+-]?(0x|0o|0b)?\d+
STRING:     '(\')?(.+(\'))*?'
COMMENT:    #.*?[#\n]
WHITESPACE: [ \t\n\r\f]
*/

// we purposefully put non-accepting states first so we can do
// `state > START` to check if `state` is accepting
typedef enum TokenType {
  // non-accepting states
  BAD_STATE = 0,
  ZERO_X,
  ZERO_O,
  ZERO_B,
  QUOTE,
  EQUAL,
  BACKSLASH,
  STRING,
  CANCEL_QUOTE,
  START,
  // accepting states
  BANG,
  MINUS,
  PLUS,
  SLASH,
  LTHAN,
  GTHAN,
  DOT,
  STAR,
  MOD,
  AND,
  NOT,
  OR,
  XOR,
  LPAREN,
  RPAREN,
  LBRACK,
  RBRACK,
  LBRACE,
  RBRACE,
  COMMA,
  COLON,
  BANG_EQUAL,
  EQUAL_EQUAL,
  ARROW,
  SLASH_SLASH,
  LTHAN_EQUAL,
  GTHAN_EQUAL,
  STAR_STAR,
  AND_AND,
  OR_OR,
  TYPE_STR,
  TYPE_INT,
  TYPE_UINT,
  TYPE_DBL,
  TYPE_BOOL,
  ELSE,
  IDENTIFIER,
  ZERO,
  NUMBER,
  NUMBER_2,
  NUMBER_8,
  NUMBER_16,
  COMMENT,
  COMMENT_END,
  WHITESPACE,
  ID_S,
  ID_ST,
  ID_I,
  ID_IN,
  ID_U,
  ID_UI,
  ID_UIN,
  ID_D,
  ID_DB,
  ID_B,
  ID_BO,
  ID_BOO,
  ID_E,
  ID_EL,
  ID_ELS,
} TokenType;

typedef struct DFA {
  TokenType start;
  TokenType (*dfaStep)(char ch, TokenType state);
} DFA;

typedef struct Token {
  TokenType type;
  char* lexeme;
} Token;

enum TokenType dfaStep(char ch, TokenType state) {
  switch (state) {
    case START:
      switch (ch) {
        case '\\': return BACKSLASH;
        case '!': return BANG;
        case '=': return EQUAL;
        case '-': return MINUS;
        case '+': return PLUS;
        case '/': return SLASH;
        case '<': return LTHAN;
        case '>': return GTHAN;
        case '.': return DOT;
        case '*': return STAR;
        case '%': return MOD;
        case '&': return AND;
        case '|': return OR;
        case '~': return NOT;
        case '^': return XOR;
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '[': return LBRACK;
        case ']': return RBRACK;
        case '{': return LBRACE;
        case '}': return RBRACE;
        case ',': return COMMA;
        case ':': return COLON;
        case 'b': return ID_B;
        case 'd': return ID_D;
        case 'e': return ID_E;
        case 'i': return ID_I;
        case 's': return ID_S;
        case 'u': return ID_U;
        case '0': return ZERO;
        case '#': return COMMENT;
        case '\'': return QUOTE;
        default:
          if (isspace(ch)) return WHITESPACE;
          if (isalpha(ch)) return IDENTIFIER;
          if (isdigit(ch)) return NUMBER;
          return BAD_STATE;
      }
    case BANG:
      switch (ch) {
        case '=': return BANG_EQUAL;
        default: return BAD_STATE;
      }
    case MINUS:
      switch (ch) {
        case '>': return ARROW;
        default: return BAD_STATE;
      }
    case SLASH:
      switch (ch) {
        case '/': return SLASH_SLASH;
        default: return BAD_STATE;
      }
    case LTHAN:
      switch (ch) {
        case '=': return LTHAN_EQUAL;
        default: return BAD_STATE;
      }
    case GTHAN:
      switch (ch) {
        case '=': return GTHAN_EQUAL;
        default: BAD_STATE;
      }
    case STAR:
      switch (ch) {
        case '*': return STAR_STAR;
        default: return BAD_STATE;
      }
    case AND:
      switch (ch) {
        case '&': return AND_AND;
        default: return BAD_STATE;
      }
    case OR:
      switch (ch) {
        case '|': return OR_OR;
        default: return BAD_STATE;
      }
    case ID_B:
      switch (ch) {
        case 'o': return ID_BO;
        default: return IDENTIFIER;
      }
    case ID_D:
      switch (ch) {
        case 'b': return ID_DB;
        default: return IDENTIFIER;
      }
    case ID_E:
      switch (ch) {
        case 'l': return ID_EL;
        default: return IDENTIFIER;
      }
    case ID_I:
      switch (ch) {
        case 'n': return ID_IN;
        default: return IDENTIFIER;
      }
    case ID_S:
      switch (ch) {
        case 't': return ID_ST;
        default: return IDENTIFIER;
      }
    case ID_U:
      switch (ch) {
        case 'i': return ID_UI;
        default: return IDENTIFIER;
      }
    case ID_BO:
      switch (ch) {
        case 'o': return ID_BOO;
        default: return IDENTIFIER;
      }
    case ID_DB:
      switch (ch) {
        case 'l': return TYPE_DBL;
        default: return IDENTIFIER;
      }
    case ID_EL:
      switch (ch) {
        case 's': return ID_ELS;
        default: return IDENTIFIER;
      }
    case ID_IN:
      switch (ch) {
        case 't': return TYPE_INT;
        default: return IDENTIFIER;
      }
    case ID_ST:
      switch (ch) {
        case 'r': return TYPE_STR;
        default: return IDENTIFIER;
      }
    case ID_UI:
      switch (ch) {
        case 'n': return ID_UIN;
        default: return IDENTIFIER;
      }
    case ID_BOO:
      switch (ch) {
        case 'l': return TYPE_BOOL;
        default: return IDENTIFIER;
      }
    case ID_ELS:
      switch (ch) {
        case 'e': return ELSE;
        default: return IDENTIFIER;
      }
    case ID_UIN:
      switch (ch) {
        case 't': return TYPE_UINT;
        default: return IDENTIFIER;
      }
    case COMMENT:
      switch (ch) {
        case '\n':
        case '\r':
        case '\f':
        case '#': return COMMENT_END;
        default: return COMMENT;
      }
    case QUOTE:
      switch (ch) {
        case '\\': return CANCEL_QUOTE; 
        default: return STRING;
      }
    case ZERO:
      switch (ch) {
        case 'b': return ZERO_B;
        case 'o': return ZERO_O;
        case 'x': return ZERO_X;
        default:
          if (isdigit(ch)) return NUMBER;
          return BAD_STATE;
      }
    case ZERO_B:
      if (isdigit(ch)) return NUMBER_2;
      return BAD_STATE;
    case ZERO_O:
      if (isdigit(ch)) return NUMBER_8;
      return BAD_STATE;
    case ZERO_X:
      if (isdigit(ch)) return NUMBER_16;
      return BAD_STATE;
    case NUMBER:
      if (isdigit(ch)) return NUMBER;
      return BAD_STATE;
    // purposfully accept bad number literals (ex: 0b1234) so we can give nice
    // errors later on
    case NUMBER_2:
      if (isdigit(ch)) return NUMBER_2;
      return BAD_STATE;
    case NUMBER_8:
      if (isdigit(ch)) return NUMBER_8;
      return BAD_STATE;
    case NUMBER_16:
      if (isdigit(ch) && ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))) {
        return NUMBER_16;
      }
      return BAD_STATE;
    default:
      if (isdigit(ch)) return NUMBER;
      return BAD_STATE;
  }
}

void copyString(char* dest, char* src, unsigned int start, unsigned int end) {
  unsigned int n = end - start + 1;
  realloc(dest, sizeof(char) * (n + 1));
  memcpy(dest, src + start, n);
  dest[n + 1] = '\0';
}

// translate accepting state into more uniform token type
// ie. ID_E, ID_S, etc. all get converted to IDENTIFIER
TokenType normalizeTokenType(TokenType type) {
  
}

// get the next token from input
Token maximalMunch(char* input, unsigned int start, DFA dfa) {
  TokenType state = START;
  TokenType acceptingState = BAD_STATE;
  unsigned int cur = start;
  unsigned int acceptingEnd = 0;

  // keep looping until we reach a bad state
  for (;(state = dfaStep(&(input + cur, state))) != BAD_STATE; cur++) {
    if (state > START) {
      acceptingState = state;
      acceptingEnd = cur + 1;
    }
  }

  // allocate token to return
  Token out = malloc(sizeof(Token));
  // copy the lexeme for our token from input
  unsigned int numChars = acceptingEnd - start;
  out->lexeme = malloc(numChars + 1);
  memcpy(out->lexeme, input + start, numChars);
  out->lexeme[numChars + 1] = '\0';
}
