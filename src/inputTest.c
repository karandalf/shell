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
	shell->stream.fileOut = 0;
	shell->stream.fileErr = 0;
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
	shell->argNum = parseToken(shell);
}

void eval(struct shell *shell, Command **commandList){
	if (shell->job == EXIT){
		shell->run = 0;
	}
	else if (shell->job == ECHO){
		redirect(shell);
		for (size_t i = 0; i < (shell->argNum - 1); i++)
			printf("%s", *(shell->tokens + 1 + i));
		putchar('\n');
		closeRedirect(shell);	
		freeTokens(shell);
	}
	else if (shell->job == TYPE){
		size_t i;
		for (i = 0; i < COMMANDS; i++){
			if (strcmp(*(shell->tokens + 1),(*(commandList + i))->name) == 0)
				break;
		}
		//Checking for builtin command
		redirect(shell);
		if (i < COMMANDS)
			if ((*(commandList + i))->type == BUILTIN)
				printf("%s is a shell builtin\n", *(shell->tokens + 1));
		if (i == COMMANDS){
			if(!checkFile(shell)){
				printf("%s%s: not found\n", *(shell->tokens + 1), AC_RED);
				printf("%s", AC_NORMAL);
			}
		}
		closeRedirect(shell);
		memset(shell->path, '\0', strlen(shell->path));
		memset(shell->token, '\0',  strlen(shell->token));
		freeTokens(shell);
	}
	else if (shell->job == PWD){
		char cwd[BUFSIZE];
		redirect(shell);
		if (getcwd(cwd, sizeof cwd) != NULL)
			printf("%s\n", cwd);	
		else
			printf("Cannot print CWD\n");
		closeRedirect(shell);
		freeTokens(shell);
	}
	else if (shell->job == CD){
		if (!strcmp(*(shell->tokens + 1),"~"))
			chdir(getenv("HOME"));
		else if (chdir(*(shell->tokens + 1))){
			printf("cd: %s%s: No such file or directory\n", *(shell->tokens + 1), AC_RED);
			printf("%s", AC_NORMAL);
		}
	}
	else{
		//char *tokens[BUFSIZE];
		redirect(shell);
		//printf("shell arg: %d\n", shell->argNum);
		if(!checkFile(shell) || *(shell->command) == '\0'){
			printf("%s%s: command not found\n", shell->command, AC_RED);
			printf("%s", AC_NORMAL);
			return;
		}
		pid_t pid = fork();
		if (pid == 0){
		//	printf("shell->path: %s\n", shell->path);
			execv(shell->path, shell->tokens);	
		}
		else{
			wait(NULL);
		}
		closeRedirect(shell);
		freeTokens(shell);
	}
}
