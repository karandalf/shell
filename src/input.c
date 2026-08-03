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
	commandList[p++] = createCommand("echo", BUILTIN, ECHO);
}

int getInput(struct shell *shell, Command **commandList){
	char c;
	size_t i;
	int job = 0;
	for (i = 0; (c = getchar()) != ' ' && (c != '\n'); i++){
		*(shell->command + i) = c;
	}
	*(shell->command + i) = '\0';
	if (c == ' '){
		for (i = 0; (c = getchar()) != '\n' && (c != EOF); i++){
			*(shell->token + i) = c;
		}
	}
	*(shell->token + i) = '\0';
	for (i = 0; i < COMMANDS; i++){
		if (strcmp(shell->command,(*(commandList + i))->name) == 0){
			job = (*(commandList + i))->job;
			break;
		}
	}
	return job;
}

void eval(int job, struct shell *shell){
	if (job == EXIT)
		shell->run = 0;
	else if (job == ECHO)
		printf("%s\n", shell->token);
	else
		printf("%s: command not found\n", shell->command);
}


