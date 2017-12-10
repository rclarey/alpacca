#pragma once

// colours for pretty printing
#define NRM "\x1B[0m"
#define RED "\x1B[31m"
#define YEL "\x1B[33m"

// error strings
#define ERR_BAD_TOKEN "Invalid or unexpected token"
#define ERR_BAD_STRING  "Unclosed string"

void lexError(const char* input, char* error, int lineStart, int line, int col, int end);


