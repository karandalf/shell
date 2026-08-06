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

int parseToken(struct shell *shell){
	size_t i, j;
	size_t p = 0;
	char c;
	char arg[BUFSIZE];
	struct quoting quoting;
	i = 0;
	j = 0;
	quoting.mode = 0;
	shell->tokens[p++] = createArg(shell->command);
	switch(*(shell->token)){
		case '\'':
			quoting.singleQ = 1;
			quoting.mode = 1;
			i += 1;
	}
	while(*(arg + j++) = *(shell->token + i++)){
		switch(*(shell->token + i)){
			case '\'':
				quoting.singleQ = 0;
				quoting.mode = 0;
				i += 1;
		}
		/*if ((*(shell->token + i) == ' ' || *(shell->token + i) == '\0') && quoting.mode == 0){
			*(arg + j) = '\0';
			shell->tokens[p++] = createArg(arg);
			//p = (quoting.singleQ == 1) ? --p : p;
			j = 0;
		}*/
		if (quoting.mode == 0){
			while (*(shell->token + i) == ' ')
				i++;
			if (*(shell->token + i - 1) == ' ' || *(shell->token + i) == '\0'){
				*(arg + j) = '\0';
				shell->tokens[p++] = createArg(arg);
				j = 0;
			}
		}
	}
	memset(shell->token, '\0', sizeof shell->token);
	shell->tokens[p] == NULL;
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

