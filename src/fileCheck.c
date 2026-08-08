#include "input.h"
#include "command.h"
#include "file.h"


static int exists(char *currentPath, struct shell *shell){
	char *command;
	FILE *file;
	command = (shell->job == TYPE) ? shell->token : shell->command;
	strcat(currentPath, command);
	file = fopen(currentPath, "r");
	if (file == NULL){
		return DNE;
	}
	struct stat sb;
	if (stat(currentPath, &sb) == 0 && (sb.st_mode & S_IXUSR) && (strncmp(currentPath, "/mnt", 4) != 0)){
		if (shell->job == TYPE) printf("%s is %s\n", command, currentPath);
		strcpy(shell->path, currentPath);
		fclose(file);
		file = NULL;
		return EXIST;
	}
	fclose(file);
	file = NULL;
	return DNE;
}

static char *parsePath(char *path, char *currentPath){
	while(*currentPath++ = *path++){
		if (*path == ':' || *path == ';')
			break;
	}
	*currentPath++ = '/';
	*currentPath = '\0';
	return ++path;
}

int checkFile(struct shell *shell){
	//Gets the PATH directory into some pointer to char and evaluates that, checking for the given executable	
	int dif;
	char *start = getenv("PATH");
	char *path = start;
	char currentPath[BUFSIZE];
	dif = strlen(start) - (path - start);
	while(dif > 0){
		path = parsePath(path, currentPath);
		if (exists(currentPath, shell) == EXIST)
			break;
		dif = strlen(start) - (path - start);
	}
	return (dif > 0) ? EXIST : DNE; 
}

