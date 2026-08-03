#include <stdio.h>
#include <stdlib.h>
#include "input.h"


int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	char input[BUFSIZE];
	struct shell shell;
	int job;

	Command *commandList[COMMANDS];
	commands(commandList);

	shell.run = 1;
	
	while (shell.run){
	printf("$ ");
	job = getInput(input, commandList);
	eval(job, input, &shell);
	}

	return 0;
}
