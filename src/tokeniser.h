#ifndef TOKENISER
#define TOKENISER

#include "input.h"

#define WORD 0
#define QUOTE 1
#define SPACE 2
#define OTHER 3

#define WRITE 1
#define APPEND 2

void parseInput(struct shell *shell);
int parseToken(struct shell *shell);
void freeTokens(struct shell *shell);

#endif
