#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "lex.h"
#include "error.h"

// given the current char and state, takes on step forward in the DFA
TokenType dfaStep(char ch, TokenType state) {
  switch (state) {
    case T_START:
      switch (ch) {
        case '\\': return T_BACKSLASH;
        case '!': return T_BANG;
        case '=': return T_EQUAL;
        case '-': return T_MINUS;
        case '+': return T_PLUS;
        case '/': return T_SLASH;
        case '<': return T_LTHAN;
        case '>': return T_GTHAN;
        case '.': return T_DOT;
        case '*': return T_STAR;
        case '%': return T_MOD;
        case '&': return T_AND;
        case '|': return T_OR;
        case '~': return T_NOT;
        case '^': return T_XOR;
        case '(': return T_LPAREN;
        case ')': return T_RPAREN;
        case '[': return T_LBRACK;
        case ']': return T_RBRACK;
        case '{': return T_LBRACE;
        case '}': return T_RBRACE;
        case ',': return T_COMMA;
        case ':': return T_COLON;
        case 'b': return T_ID_B;
        case 'd': return T_ID_D;
        case 'e': return T_ID_E;
        case 'f': return T_ID_F;
        case 'i': return T_ID_I;
        case 's': return T_ID_S;
        case 't': return T_ID_T;
        case 'u': return T_ID_U;
        case '0': return T_INTEGER;
        case '#': return T_COMMENT;
        case '\'': return T_STRING_UNCLOSED;
        case '\n': return T_NEWLINE;
        default:
          if (isspace(ch)) return T_WHITESPACE;
          if (isalpha(ch)) return T_IDENTIFIER;
          if (isdigit(ch)) return T_INTEGER;
          return T_BAD_STATE;
      }

    case T_BANG:
      switch (ch) {
        case '=': return T_BANG_EQUAL;
        default: return T_BAD_STATE;
      }

    case T_EQUAL:
      switch (ch) {
        case '>': return T_FAT_ARROW;
        default: return T_BAD_STATE;
      }

    case T_MINUS:
      switch (ch) {
        case '>': return T_ARROW;
        default:
          if (isdigit(ch)) return T_INTEGER;
          return T_BAD_STATE;
      }

    case T_PLUS:
      if (isdigit(ch)) return T_INTEGER;
      return T_BAD_STATE;

    case T_SLASH:
      switch (ch) {
        case '/': return T_SLASH_SLASH;
        default: return T_BAD_STATE;
      }

    case T_LTHAN:
      switch (ch) {
        case '=': return T_LTHAN_EQUAL;
        default: return T_BAD_STATE;
      }

    case T_GTHAN:
      switch (ch) {
        case '=': return T_GTHAN_EQUAL;
        default: return T_BAD_STATE;
      }

    case T_STAR:
      switch (ch) {
        case '*': return T_STAR_STAR;
        default: return T_BAD_STATE;
      }

    case T_AND:
      switch (ch) {
        case '&': return T_AND_AND;
        default: return T_BAD_STATE;
      }

    case T_OR:
      switch (ch) {
        case '|': return T_OR_OR;
        default: return T_BAD_STATE;
      }

    case T_ID_B:
      switch (ch) {
        case 'o': return T_ID_BO;
        default: return T_IDENTIFIER;
      }

    case T_ID_D:
      switch (ch) {
        case 'b': return T_ID_DB;
        default: return T_IDENTIFIER;
      }

    case T_ID_E:
      switch (ch) {
        case 'l': return T_ID_EL;
        default: return T_IDENTIFIER;
      }

    case T_ID_F:
      switch (ch) {
        case 'a': return T_ID_FA;
        default: return T_IDENTIFIER;
      }

    case T_ID_I:
      switch (ch) {
        case 'n': return T_ID_IN;
        default: return T_IDENTIFIER;
      }

    case T_ID_S:
      switch (ch) {
        case 't': return T_ID_ST;
        default: return T_IDENTIFIER;
      }

    case T_ID_U:
      switch (ch) {
        case 'i': return T_ID_UI;
        default: return T_IDENTIFIER;
      }

    case T_ID_BO:
      switch (ch) {
        case 'o': return T_ID_BOO;
        default: return T_IDENTIFIER;
      }

    case T_ID_DB:
      switch (ch) {
        case 'l': return T_TYPE_DBL;
        default: return T_IDENTIFIER;
      }

    case T_ID_EL:
      switch (ch) {
        case 's': return T_ID_ELS;
        default: return T_IDENTIFIER;
      }

    case T_ID_FA:
      switch (ch) {
        case 'l': return T_ID_FAL;
        default: return T_IDENTIFIER;
      }

    case T_ID_IN:
      switch (ch) {
        case 't': return T_TYPE_INT;
        default: return T_IDENTIFIER;
      }

    case T_ID_ST:
      switch (ch) {
        case 'r': return T_TYPE_STR;
        default: return T_IDENTIFIER;
      }

    case T_ID_UI:
      switch (ch) {
        case 'n': return T_ID_UIN;
        default: return T_IDENTIFIER;
      }

    case T_ID_BOO:
      switch (ch) {
        case 'l': return T_TYPE_BOOL;
        default: return T_IDENTIFIER;
      }

    case T_ID_ELS:
      switch (ch) {
        case 'e': return T_ELSE;
        default: return T_IDENTIFIER;
      }

    case T_ID_UIN:
      switch (ch) {
        case 't': return T_TYPE_UINT;
        default: return T_IDENTIFIER;
      }

    case T_COMMENT:
      switch (ch) {
        case '\n':
        case '\r':
        case '\f':
        case '#': return T_COMMENT_END;
        default: return T_COMMENT;
      }

    case T_STRING_UNCLOSED:
      switch (ch) {
        case '\\': return T_CANCEL_QUOTE;
        case '\'': return T_STRING;
        case '\n': return T_BAD_STATE;
        default: return T_STRING_UNCLOSED;
      }

    case T_CANCEL_QUOTE:
      switch (ch) {
        case '\n': return T_BAD_STATE;
        default: return T_STRING_UNCLOSED;
      }

    case T_INTEGER:
      if (isdigit(ch)) return T_INTEGER;
      if (isalpha(ch)) return T_INTALPHA;
      return T_BAD_STATE;

    case T_INTALPHA:
      if (isalpha(ch) || isdigit(ch) || ch == '_') return T_INTALPHA;
      return T_BAD_STATE;

    case T_IDENTIFIER:
      if (isalpha(ch) || isdigit(ch) || ch == '_') return T_IDENTIFIER;
      return T_BAD_STATE;

    default:
      return T_BAD_STATE;
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
    case T_BOOLEAN:
      boolOut = malloc(sizeof(bool));
      *boolOut = (str[start] == 't' ? true : false);
      return boolOut;

    case T_INTEGER:
      intOut = malloc(sizeof(int));
      copyString(&intStr, str, start, end);
      *intOut = strtoimax(intStr, &endPtr, 10);
      free (intStr);
      return intOut;

    case T_STRING:
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
  if (type >= T_ID_S) {
    return T_IDENTIFIER;
  }

  switch (type) {
    case T_COMMENT_END: return T_COMMENT;
    case T_NEWLINE: return T_WHITESPACE;
    default: return type;
  }
}

// some nice global variables for our lexing
int lineNum = 1;
int lineStart = 0;
bool hasLexError = false;

// get the next token from input; returns length of lexeme
int maximalMunch(Token* dest, const char* input, int start) {
  TokenType state = T_START;
  TokenType acceptingState = T_BAD_STATE;
  int cur = start;
  int acceptingEnd = cur;

  // keep looping until we reach a bad state
  while (input[cur] != '\0' && (state = dfaStep(input[cur], state)) != T_BAD_STATE) {
    if (state > T_START) {
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
      case T_BAD_STATE:
        acceptingEnd++;
        // intentional fall through

      case T_INTALPHA:
        error = ERR_BAD_TOKEN;
        break;

      case T_STRING_UNCLOSED:
        error = ERR_BAD_STRING;
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
      case T_BOOLEAN:
        printf("`%s`\n", *(bool*)cur->value ? "true" : "false");
        break;
      case T_INTEGER:
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
