#include <stdio.h>
#include <stdlib.h>

#include "error.h"

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
