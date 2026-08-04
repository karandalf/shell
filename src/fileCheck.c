#include "input.h"
#include "file.h"


static int exists(char *currentPath, struct shell *shell){
	FILE *file;
	strcat(currentPath, shell->token);
	file = fopen(currentPath, "r");
	//printf("current path: %s\n", currentPath);
	if (file == NULL){
	//	printf("File does not exist\n");	
		return DNE;
	}
	struct stat sb;
	if (stat(currentPath, &sb) == 0 && sb.st_mode & S_IXUSR){
		printf("%s is %s\n", shell->token, currentPath);
		fclose(file);
		file = NULL;
		return EXIST;
	}
	fclose(file);
	file = NULL;
	return DNE;
}

static char *parse(char *path, char *currentPath){
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
		path = parse(path, currentPath);
		//printf("%s\n", currentPath);
		//printf("distance through: %ld\n", path - start);
		//printf("difference: %ld\n", strlen(start) - (path - start));
		if (exists(currentPath, shell) == EXIST)
			break;
		dif = strlen(start) - (path - start);
	}
	return (dif > 0) ? EXIST : DNE; 
}
