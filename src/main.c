#include <stdio.h>
#include <stdlib.h>
#include "input.h"


int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	char command[BUFSIZE], input[BUFSIZE];
	struct shell shell;
	int job;

	Command *commandList[COMMANDS];
	commands(commandList);

	shell.run = 1;
	
	while (shell.run){
		printf("$ ");
		getInput(&shell, commandList);
		eval(&shell, commandList);
	}

	return 0;
}
