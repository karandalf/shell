#include "tokeniser.h"
#include "input.h"
#include "command.h"
#include "file.h"

char *createArg(char *arg){
	char *token = (char *)malloc(strlen(arg));
	if (token != NULL){
		strcpy(token, arg);
	}
	return token;
};

int parseToken(struct shell *shell){
	size_t i, j;
	size_t p = 0;
	char c;
	int end = 1;
	char arg[BUFSIZE];
	i = 0;
	j = 0;
	shell->tokens[p++] = createArg(shell->command);
	while(*(shell->token + i) == ' ')
		i++;
	while(*(shell->token + i) != '\0'){
		switch(*(shell->token + i)){
			case ' ':
				if (shell->job == ECHO || end == 0){
					if (shell->job == ECHO){
						*(arg+j++) = ' ';
					}
					*(arg + j) = '\0';
					shell->tokens[p++] = createArg(arg);
				}
				while(*(shell->token + i) == ' ')
					i++;
				j = 0;
				end = 1;
				continue;
			case '\'':
				i++;
				while (*(shell->token + i) != '\'' && *(shell->token + i) != '\0'){
					*(arg + j++) = *(shell->token + i++);
				}
				*(arg + j) = '\0';
				shell->tokens[p++] = createArg(arg);
				i++;
				j = 0;
				end = 1;
				continue;
			case '\"':
				i++;
				while (*(shell->token + i) != '\"' && *(shell->token + i) != '\0'){
					if (*(shell->token + i) == '\\'){
						*(arg + j++) = *(shell->token + ++i);
						continue;
					}
					*(arg + j++) = *(shell->token + i++);
				}
				*(arg + j) = '\0';
				shell->tokens[p++] = createArg(arg);
				i++;
				j = 0;
				end = 1;
				continue;
			case '\\':
				i++;
				*(arg + j++) = *(shell-> token + i++);
				continue;
			default:
				*(arg + j++) = *(shell->token + i++);
				end = 0;
		}
	}
	if (!end){
		*(arg + j) = '\0';
		shell->tokens[p++] = createArg(arg);
	}
	memset(shell->token, '\0', sizeof shell->token);
	shell->tokens[p] = NULL;
//	printf("p: %ld\n", p);
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
