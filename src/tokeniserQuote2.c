#include "tokeniser.h"
#include "input.h"
#include "command.h"
#include "file.h"

char *createArg(char *arg){
	char *token = (char *)malloc(sizeof arg);
	if (token != NULL){
		while(*arg == ' ')
			arg++;
		strcpy(token, arg);
	}
	return token;
};

int quoteSingle(struct shell *shell, size_t start, char *arg){
	size_t i = start;
	int j;
	printf("hi.\n");
	for(j = 0; j < strlen(shell->token); j++)
		printf("%c\n", *(shell->token + j));
	printf("shell->token: %s\n", shell->token);
	while (1){
		printf("val: %c\n", *(shell->token + i));
		*arg++ = *(shell->token + i++);	
		if (*(shell->token + i) == '\''){
			printf("hello\n");
			break;
		}
	}
	*arg = '\0';
	return i;
}
int parseToken(struct shell *shell){
	size_t i, j;
	size_t p = 0;
	char c;
	char arg[BUFSIZE];
	struct quoting quoting;
	i = 0;
	j = 0;
	quoting.mode = 0;
	memset(shell->tokens, '\0', sizeof shell->tokens);
	shell->tokens[p++] = createArg(shell->command);
	printf("shell->token: %s\n", shell->token);
	while(*(shell->token + i)){
		switch(*(shell->token + i)){
			case '\'':
				//*(arg + j) = '\0';
				//shell->tokens[p++] = createArg(arg);
				//j = 0;
				i = quoteSingle(shell, ++i, arg);		
				printf("arg: %s\n", arg);
				shell->tokens[p++] = createArg(arg);
			case ' ':
				*(arg + j) = '\0';
				shell->tokens[p++] = createArg(arg);
				j = 0;
			case '\0':
				*(arg + j) = '\0';
				shell->tokens[p++] = createArg(arg);
				j = 0;
		}
		/*if ((*(shell->token + i) == ' ' || *(shell->token + i) == '\0')){
			*(arg + j) = '\0';
			shell->tokens[p++] = createArg(arg);
			//p = (quoting.singleQ == 1) ? --p : p;
			j = 0;
		}*/
	}
	memset(shell->token, '\0', strlen(shell->token));
	shell->tokens[p] = NULL;
	return p;
}

void parseInput(struct shell *shell){
	size_t i;
	char c;
	for (i = 0; (c = getchar()) != ' ' && (c != '\n'); i++){
		*(shell->command + i) = c;
	}
	*(shell->command + i) = '\0';
	memset(shell->token, '\0',  strlen(shell->token));
	if (c == ' '){
		for (i = 0; (c = getchar()) != '\n' && (c != EOF); i++){
			*(shell->token + i) = c;
		}
		*(shell->token + i) = '\0';
	}
}

