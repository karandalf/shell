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
	job = getInput(&shell, commandList);
	eval(job, &shell);
	}

	return 0;
}
