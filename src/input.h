#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define COMMANDS 3


typedef struct{
	char *name;
	int type;
	int job;
} Command;

struct shell{
	int run;
	int job;
	char command[BUFSIZE];
	char token[BUFSIZE];
};


void getInput(struct shell *shell, Command **commandList);
void commands(Command **commandList);
void eval(struct shell *shell, Command **commandList);
#endif
