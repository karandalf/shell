#include "tokeniser.h"
#include "input.h"
#include "command.h"
#include "file.h"

void freeTokens(struct shell *shell){
	for(size_t i = 0; i < (shell->argNum); i++){
		free(*(shell->tokens + i));
		*(shell->tokens + i) = NULL;
	}
}
static char *createArg(char *arg){
	//Needs strlen(arg) + 1 for the NULL terminator
	char *token = (char *)malloc(strlen(arg) + 1);
	if (token != NULL){
		strcpy(token, arg);
	}
	return token;
};

int parseToken(struct shell *shell){
	size_t i, j;
	size_t p = 0;
	size_t fp = 0;
	char c;
	int end = SPACE;
	int commandTokens = 0;
	char arg[BUFSIZE];
	i = 0;
	j = 0;
	shell->tokens[p++] = createArg(shell->command);
	//printf("shell command: %s\n", shell->command);
	while(*(shell->token + i) == ' ')
		i++;
	while(*(shell->token + i) != '\0'){
		switch(*(shell->token + i)){
			case ' ':
				if (shell->job == ECHO || end == WORD){
					if (shell->job == ECHO){
						*(arg + j++) = ' ';
					}
					*(arg + j) = '\0';
					shell->tokens[p++] = createArg(arg);
				}
				while(*(shell->token + i) == ' ')
					i++;
				j = 0;
				end = SPACE;
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
				end = QUOTE;
				continue;
			case '\"':
				i++;
				while (*(shell->token + i) != '\"' && *(shell->token + i) != '\0'){
					if (*(shell->token + i) == '\\'){
						*(arg + j++) = *(shell->token + ++i);
						i++;
						continue;
					}
					*(arg + j++) = *(shell->token + i++);
				}
				*(arg + j) = '\0';
				shell->tokens[p++] = createArg(arg);
				i++;
				j = 0;
				end = QUOTE;
				continue;
			case '\\':
				i++;
				*(arg + j++) = *(shell->token + i++);
				continue;
		//TODO:Need to come up with redirection method.
			case '>':
				if (end == WORD){
					*(arg + j) = '\0';
					shell->tokens[p++] = createArg(arg);
					j = 0;
				}
				commandTokens = (commandTokens == 0) ? p : commandTokens;
				shell->stream.files[fp] = p;
				shell->stream.mode[fp] = (*(shell->token + i + 1) == '>') ? APPEND : WRITE;
				if (*(shell->token + i - 1) != '2') {
					shell->stream.fileOut = p;
					shell->stream.outIndex = fp++;
				}
				if (*(shell->token + i - 1) == '2'){
					shell->stream.fileErr = p;
					shell->stream.errIndex = fp++;
				}
				i = (*(shell->token + i) == '>' || *(shell->token + i) == ' ') ? (i + 1) : i;
				end = OTHER;
				continue;
			case '1':
			case '2':
				if (*(shell->token + i + 1) == '>'){
					i++;
					continue;
				}
			default:
				*(arg + j++) = *(shell->token + i++);
				end = WORD;
		}
	}
	if (!end){
		*(arg + j) = '\0';
		shell->tokens[p++] = createArg(arg);
	}
	memset(shell->token, '\0', sizeof shell->token);
	shell->tokens[p] = NULL;
	shell->stream.files[fp] = '\0';
	shell->stream.fileNum = fp;
//	printf("p: %ld\n", p);
	return (commandTokens == 0) ? p : commandTokens;
}

void parseInput(struct shell *shell){
	size_t i;
	char c, quote;
	if ((c = getchar()) == '\'' || c == '\"'){
		quote = c;	
		i = 0;
		while ((c = getchar()) != quote){
			c = (quote == '\"' && c == '\\') ? getchar() : c;
			*(shell->command + i++) = c;
		}	
		c = getchar();
	}
	else{
		for (i = 0; c != ' ' && (c != '\n'); i++){
			*(shell->command + i) = c;
			c = getchar();
		}
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
