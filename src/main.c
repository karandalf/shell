#include <stdio.h>
#include <stdlib.h>
#include "input.h"

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	char command[BUFSIZE];

	while (true){
	printf("$ ");
	getInput(command);
	printf("%s: command not found\n", command);
	}

	return 0;
}
