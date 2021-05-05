#include "utilities.h"

char** strsplit(char* str, const char* delim)
{
    char** res = NULL;
    char*  part = NULL;
    int i = 0;

    part = strtok(str, delim);
    while (part) {
	    if (i == 0) {
		    res = (char **)calloc(1, sizeof(char *));
	    } else {
		    res = (char **)realloc(res, (i + 1) * sizeof(char *));
	    }
	    *(res + i) = strdup(part);
        part = strtok(NULL, delim);
        i++;
    }
    res = (char **)realloc(res, (i + 1) * sizeof(char *));
    *(res + i) = NULL;
    return res;
}

void   strsplit_free(char** str)
{
	for (int i = 0; str[i]; i++) {
		free(str[i]);
	}
	free(str);
}
