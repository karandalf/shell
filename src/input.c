#include "input.h"
#include "command.h"
#include "file.h"

Command *createCommand (char *name, int type, int job){
	Command *command = (Command *)malloc(sizeof(Command));
	if (command != NULL){
		command->name = name;
		command->type = type;
		command->job = job;
	}
	return command;
};

void commands(Command **commandList){
	size_t p = 0;
	commandList[p++] = createCommand("exit", BUILTIN, EXIT);
	commandList[p++] = createCommand("echo", BUILTIN, ECHO);
	commandList[p++] = createCommand("type", BUILTIN, TYPE);
}

void getInput(struct shell *shell, Command **commandList){
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
	shell->job = job;
}

void eval(struct shell *shell, Command **commandList){
	if (shell->job == EXIT)
		shell->run = 0;
	else if (shell->job == ECHO)
		printf("%s\n", shell->token);
	else if (shell->job == TYPE){
		size_t i;
		for (i = 0; i < COMMANDS; i++){
			if (strcmp(shell->token,(*(commandList + i))->name) == 0)
				break;
		}
		//Checking for builtin command
		if (i < COMMANDS)
			if ((*(commandList + i))->type == BUILTIN)
				printf("%s is a shell builtin\n", shell->token);
		if (i == COMMANDS){
			if(!checkFile(shell))
				printf("%s: not found\n", shell->token);
		}
	}
	else
		printf("%s: command not found\n", shell->command);
}
