#include "input.h"
#include "command.h"
#include "file.h"
#include "tokeniser.h"

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
	commandList[p++] = createCommand("pwd", BUILTIN, PWD);
	commandList[p++] = createCommand("cd", BUILTIN, CD);
}

void getInput(struct shell *shell, Command **commandList){
	size_t i;
	int job = 0;
	parseInput(shell);
	for (i = 0; i < COMMANDS; i++){
		if (strcmp(shell->command,(*(commandList + i))->name) == 0){
			job = (*(commandList + i))->job; 
			break;
		}
	}
	shell->job = job;
}

void eval(struct shell *shell, Command **commandList){
	if (shell->job == EXIT){
		shell->run = 0;
	}
	else if (shell->job == ECHO){
		int argNum = parseToken(shell);
		for (size_t i = 0; i < argNum - 1; i++)
			printf("%s", *(shell->tokens + 1 + i));
		putchar('\n');
		memset(shell->token, '\0', sizeof shell->token);
		for(size_t i = 0; i < argNum; i++){
			free(*(shell->tokens+i));
			*(shell->tokens + i) = NULL;
		}
	}
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
		memset(shell->token, '\0',  strlen(shell->token));
	}
	else if (shell->job == PWD){
		char cwd[BUFSIZE];
		if (getcwd(cwd, sizeof cwd) != NULL)
			printf("%s\n", cwd);	
		else
			printf("Cannot print CWD\n");
	}
	else if (shell->job == CD){
		if (!strcmp(shell->token,"~"))
			chdir(getenv("HOME"));
		else if (chdir(shell->token)){
			printf("cd: %s: No such file or directory\n", shell->token);
		}
		memset(shell->token, '\0',  strlen(shell->token));
	}
	else{
		size_t i;
		int argNums;
		//char *tokens[BUFSIZE];
		if(!checkFile(shell) || *(shell->command) == '\0'){
			printf("%s: command not found\n", shell->command);
			return;
		}
		argNums = parseToken(shell);			
		pid_t pid = fork();
		if (pid == 0){
			//printf("path: %s\n", shell->path);
			execv(shell->path, shell->tokens);	
		}
		else{
			wait(NULL);
		}
		for(i = 0; i < argNums; i++){
			free(*(shell->tokens+i));
			*(shell->tokens + i) = NULL;
		}
	}
}
