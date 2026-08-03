#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define COMMANDS 2

#define BUILTIN 1
#define EXIT 1
#define ECHO 2

typedef struct{
	char *name;
	int type;
	int job;
} Command;

struct shell{
	int run;
	char command[BUFSIZE];
	char token[BUFSIZE];
};


int getInput(struct shell *shell, Command **commandList);
void commands(Command **commandList);
void eval(int job, struct shell *shell);
#endif
