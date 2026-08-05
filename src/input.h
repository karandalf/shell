#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define COMMANDS 4


typedef struct{
	char *name;
	int type;
	int job;
} Command;

struct shell{
	int run;
	int job;
	char path[BUFSIZE];
	char command[BUFSIZE];
	char token[BUFSIZE];
};


void getInput(struct shell *shell, Command **commandList);
void commands(Command **commandList);
void eval(struct shell *shell, Command **commandList);

#endif
