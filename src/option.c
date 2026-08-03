#include "input.h"

void getInput(char *command){
	char c;
	size_t i;
	for (i = 0; (c = getchar()) != '\n'; i++){
		*(command + i) = c;
	}
	*(command + i) = '\0';
}

