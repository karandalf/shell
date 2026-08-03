#include "input.h"

Command *createCommand (char *name, int type, int job){
	Command *command = (Command *)malloc(sizeof(Command));
	command->name = name;
	command->type = type;
	command->job = job;
	return command;
};

void commands(Command **commandList){
	size_t p = 0;
	commandList[p++] = createCommand("exit", BUILTIN, EXIT);
}

int getInput(char *input, Command **commandList){
	char c;
	size_t i;
	int job = 0;
	for (i = 0; (c = getchar()) != '\n'; i++){
		*(input + i) = c;
	}
	*(input + i) = '\0';
	for (i = 0; i < COMMANDS; i++){
		if (strcmp(input,(*commandList)->name) == 0){
			job = (*commandList)->job;
			break;
		}
	}
	return job;
}

void eval(int job, char *input, struct shell *shell){
	if (job == EXIT)
		shell->run = 0;
	else
		printf("%s: command not found\n", input);	
}


