#ifndef TOKENISER
#define TOKENISER

#include "input.h"

struct quoting {
	int singleQ;
	int doubleQ;
	int backslash;
	int mode;
};
void parseInput(struct shell *shell);
int parseToken(struct shell *shell);

#endif
