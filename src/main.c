#include <stdio.h>
#include <stdlib.h>
#include "input.h"


int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	char command[BUFSIZE], input[BUFSIZE];
	char cwd[BUFSIZE];
	struct shell shell;
	int job;

	Command *commandList[COMMANDS];
	commands(commandList);

	shell.run = 1;

	while (shell.run == 1){
		getcwd(cwd, sizeof cwd);
		printf("%s", AC_CYAN);
		printf("%s", cwd); 
		printf("%s$ ", AC_BLUE);
		printf("%s", AC_NORMAL);
		getInput(&shell, commandList);
		eval(&shell, commandList);
	}

	return 0;
}
