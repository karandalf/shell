#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define COMMANDS 5

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

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
	char *tokens[BUFSIZE];
};


void getInput(struct shell *shell, Command **commandList);
void commands(Command **commandList);
void eval(struct shell *shell, Command **commandList);

#endif
