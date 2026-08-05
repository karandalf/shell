#ifndef CHECKFILE
#define CHECKFILE

#include <sys/stat.h>
#define DNE 0
#define EXIST 1

int checkFile(struct shell *shell);
int checkDir(struct shell *shell);

#endif
