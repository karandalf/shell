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

int parseToken(struct shell *shell, char **tokens){
	size_t i, j;
	size_t p = 0;
	char c;
	char arg[BUFSIZE];
	i = 0;
	j = 0;
	tokens[p++] = createArg(shell->command);
	printf("shell token: %s\n", shell->token);
	while(*(arg + j++) = *(shell->token + i++)){
		if (*(shell->token + i) == ' ' || *(shell->token + i) == '\0'){
			*(arg + j) = '\0';
			tokens[p++] = createArg(arg);
			j = 0;
		}
	}
	memset(shell->token, '\0', sizeof shell->token);
	tokens[p] == NULL;
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
	printf("parsed shell token: %s\n", shell->token);
}

