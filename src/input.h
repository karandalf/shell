#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define COMMANDS 1

#define BUILTIN 1
#define EXIT 1

typedef struct{
	char *name;
	int type;
	int job;
} Command;

struct shell{
	int run;
};


int getInput(char *input, Command **commandList);
void commands(Command **commandList);
void eval(int job, char *input, struct shell *shell);
#endif
