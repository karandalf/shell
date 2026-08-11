#include "input.h"
#include "command.h"
#include "file.h"
#include "tokeniser.h"

static void openFiles(struct shell *shell){
	int tokenNum;
	for (size_t i = 0; i < (shell->stream.fileNum); i++){
		FILE *file;
		tokenNum = shell->stream.files[i];
		file = fopen((shell->tokens[tokenNum]), (shell->stream.mode[i] == WRITE) ? "w" : "a");
		fclose(file);
	}
}

void redirect(struct shell *shell){
	if (!(shell->stream.fileOut) && !(shell->stream.fileErr)) return;
	openFiles(shell);
	shell->stream.og_stdout = dup(STDOUT_FILENO);
	shell->stream.og_stderr = dup(STDERR_FILENO);
	FILE *fileOut, *fileErr;
	if (shell->stream.fileOut){
		fflush(stdout);
		fileOut = fopen((shell->tokens[shell->stream.fileOut]), (shell->stream.mode[shell->stream.outIndex] == WRITE) ? "w" : "a");
		int fileOut_fd = fileno(fileOut);
		dup2(fileOut_fd, STDOUT_FILENO);
		close(fileOut_fd);
		fclose(fileOut);
	}
	//TODO: Needs to include error redirects and error handling
	if (shell->stream.fileErr){
		fflush(stderr);
		fileErr = fopen((shell->tokens[shell->stream.fileErr]), (shell->stream.mode[shell->stream.errIndex] == WRITE) ? "w" : "a");
		int fileErr_fd = fileno(fileErr);
		dup2(fileErr_fd, STDERR_FILENO);
		close(fileErr_fd);
		fclose(fileErr);
	}
}

void closeRedirect(struct shell *shell){
	if (!(shell->stream.fileOut) && !(shell->stream.fileErr)) return;
	if (shell->stream.fileOut){
		fflush(stdout);
		dup2(shell->stream.og_stdout, STDOUT_FILENO);
		close(shell->stream.og_stdout);
	}
	if (shell->stream.fileErr){
		fflush(stderr);
		dup2(shell->stream.og_stderr, STDERR_FILENO);
		close(shell->stream.og_stderr);
	}
}

static int exists(char *currentPath, struct shell *shell){
	char *command;
	FILE *file;
	command = (shell->job == TYPE) ? *(shell->tokens + 1) : shell->command;
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

