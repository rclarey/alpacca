#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

// we purposefully put non-accepting states first so we can do
// `state > START` to check if `state` is accepting
typedef enum TokenType {
  // non-accepting states
  BAD_STATE = 0,
  EQUAL,
  BACKSLASH,
  START,

  // "accepting" states for the purpose of nice errors
  INTALPHA,
  STRING_UNCLOSED,
  CANCEL_QUOTE,

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
  NEWLINE,

  BANG_EQUAL,
  EQUAL_EQUAL,
  FAT_ARROW,
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
  BOOLEAN,
  INTEGER,
  COMMENT,
  COMMENT_END,
  STRING,
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
  ID_T,
  ID_TR,
  ID_TRU,
  ID_F,
  ID_FA,
  ID_FAL,
  ID_FALS,
} TokenType;

typedef struct Token {
  TokenType type;
  void* value;
  struct Token* next;
  int line;
  int col;
} Token;

// given the current char and state, takes on step forward in the DFA
TokenType dfaStep(char ch, TokenType state) {
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
        case 'f': return ID_F;
        case 'i': return ID_I;
        case 's': return ID_S;
        case 't': return ID_T;
        case 'u': return ID_U;
        case '0': return INTEGER;
        case '#': return COMMENT;
        case '\'': return STRING_UNCLOSED;
        case '\n': return NEWLINE;
        default:
          if (isspace(ch)) return WHITESPACE;
          if (isalpha(ch)) return IDENTIFIER;
          if (isdigit(ch)) return INTEGER;
          return BAD_STATE;
      }

    case BANG:
      switch (ch) {
        case '=': return BANG_EQUAL;
        default: return BAD_STATE;
      }

    case EQUAL:
      switch (ch) {
        case '>': return FAT_ARROW;
        default: return BAD_STATE;
      }

    case MINUS:
      switch (ch) {
        case '>': return ARROW;
        default:
          if (isdigit(ch)) return INTEGER;
          return BAD_STATE;
      }

    case PLUS:
      if (isdigit(ch)) return INTEGER;
      return BAD_STATE;

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
        default: return BAD_STATE;
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

    case ID_F:
      switch (ch) {
        case 'a': return ID_FA;
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

    case ID_FA:
      switch (ch) {
        case 'l': return ID_FAL;
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

    case STRING_UNCLOSED:
      switch (ch) {
        case '\\': return CANCEL_QUOTE;
        case '\'': return STRING;
        case '\n': return BAD_STATE;
        default: return STRING_UNCLOSED;
      }

    case CANCEL_QUOTE:
      switch (ch) {
        case '\n': return BAD_STATE;
        default: return STRING_UNCLOSED;
      }

    case INTEGER:
      if (isdigit(ch)) return INTEGER;
      if (isalpha(ch)) return INTALPHA;
      return BAD_STATE;

    case INTALPHA:
      if (isalpha(ch) || isdigit(ch) || ch == '_') return INTALPHA;
      return BAD_STATE;

    case IDENTIFIER:
      if (isalpha(ch) || isdigit(ch) || ch == '_') return IDENTIFIER;
      return BAD_STATE;

    default:
      return BAD_STATE;
  }
}

void copyString(char** dest, const char* src, int start, int end) {
  int n = end - start + 1;
  *dest = realloc(*dest, sizeof(char) * (n + 1));
  memcpy(*dest, src + start, n);
  (*dest)[n + 1] = '\0';
}

void* strToValue(TokenType type, const char* str, int start, int end) {
  bool* boolOut;
  int* intOut;
  char* strOut;

  char* intStr = NULL;
  char* endPtr;
  int n;

  switch (type) {
    case BOOLEAN:
      boolOut = malloc(sizeof(bool));
      *boolOut = (str[start] == 't' ? true : false);
      return boolOut;

    case INTEGER:
      intOut = malloc(sizeof(int));
      copyString(&intStr, str, start, end);
      *intOut = strtoimax(intStr, &endPtr, 10);
      free (intStr);
      return intOut;

    case STRING:
      // -2 b/c we don't care about quotes
      n = end - start - 2;
      strOut = malloc(sizeof(char) * (n + 1));
      memcpy(strOut, str + 1, n);
      strOut[n] = '\0';
      return strOut;

    // capture the lexeme as a string for anything else
    default:
      n = end - start;
      strOut = malloc(sizeof(char) * (n + 1));
      memcpy(strOut, str + start, n);
      strOut[n] = '\0';
      return strOut;
  }
}

// translate accepting state into more uniform token type
// ie. ID_E, ID_S, etc. all get converted to IDENTIFIER
TokenType normalizeTokenType(TokenType type) {
  if (type >= ID_S) {
    return IDENTIFIER;
  }

  switch (type) {
    case COMMENT_END: return COMMENT;
    case NEWLINE: return WHITESPACE;
    default: return type;
  }
}

#define NRM "\x1B[0m"
#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define ERR_INVALID "Invalid or unexpected token"
#define ERR_STRING  "Unclosed string"

void lexError(const char* input, char* error, int lineStart, int line, int col, int end) {
  char* lineStr = NULL;
  int lineLength = strcspn(input + lineStart, "\n\0") - 1;
  copyString(&lineStr, input, lineStart, lineStart + lineLength);

  int lineNumLength = 1;
  int n = line;
  while ((n = n / 10)) lineNumLength++;

  printf(RED "Syntax Error: %s on line %d\n" NRM, error, line);
  printf("%d: %s\n", line, lineStr);
  for (int i = -(lineNumLength + 2); i < col; i++) {
    printf(" ");
  }
  for (int i = 0; i < end; i++) {
    printf("^");
  }
  printf("\n\n");

  free (lineStr);
}

// some nice global variables for our lexing
int lineNum = 1;
int lineStart = 0;
bool hasLexError = false;

// get the next token from input; returns length of lexeme
int maximalMunch(Token* dest, const char* input, int start) {
  TokenType state = START;
  TokenType acceptingState = BAD_STATE;
  int cur = start;
  int acceptingEnd = cur;

  // keep looping until we reach a bad state
  while (input[cur] != '\0' && (state = dfaStep(input[cur], state)) != BAD_STATE) {
    if (state > START) {
      acceptingState = state;
      acceptingEnd = cur + 1;
    }

    if (input[cur] == '\n') {
      lineNum++;
      lineStart = cur + 1;
    }
    cur++;
  }

  // handle lexing errors
  if (acceptingState < BANG) {
    char* error;
    hasLexError = true;

    switch (acceptingState) {
      case BAD_STATE:
        acceptingEnd++;
        // intentional fall through

      case INTALPHA:
        error = ERR_INVALID;
        break;

      case STRING_UNCLOSED:
        error = ERR_STRING;
        break;

      default:
        break;
    }

    lexError(input, error, lineStart, lineNum, start - lineStart, acceptingEnd - start);
  }

  // create token to return
  dest->type = normalizeTokenType(acceptingState);
  dest->value = strToValue(dest->type, input, start, acceptingEnd);
  dest->next = malloc(sizeof(Token));
  dest->line = lineNum;
  dest->col = start - lineStart;

  return acceptingEnd - start;
}

// produce a linked list of Tokens from the given string
Token* lex(const char* input) {
  Token* out = malloc(sizeof(Token));
  Token* nextToken = out;
  Token* curToken;
  int pos = 0;
  int length = 0;
  const int end = strlen(input);

  while (pos < end) {
    length = maximalMunch(nextToken, input, pos);
    // TODO: handle fail to get token
    curToken = nextToken;
    nextToken = nextToken->next;
    pos += length;
  }

  // make sure LL ends in NULL
  curToken->next = NULL;

  return out;
}

void printTokens(Token* head) {
  Token* cur = head;

  printf("~~~~~~~\nTOKENS:\n~~~~~~~\n");
  while (cur != NULL) {
    switch (cur->type) {
      case BOOLEAN:
        printf("`%s`\n", *(bool*)cur->value ? "true" : "false");
        break;
      case INTEGER:
        printf("`%d`\n", *(int*)cur->value);
        break;
      default:
        if (((char*)cur->value)[0] == '\n') {
          printf("`\\n`\n");
        } else {
          printf("`%s`\n", (char*)cur->value);
        }
        break;
    }
    cur = cur->next;
  }
}

int main(int argc, const char* argv[]) {
  Token* toks = lex(argv[1]);
  printTokens(toks);
}
