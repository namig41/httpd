#include "utilities.h"

char** strsplit(char* str, const char* delim)
{
    char** res = NULL;
    char*  part = NULL;
    int i = 0;

    char* aux = strdup(str);

    part = strdup(strtok(aux, delim));

    while (part) {
        res = (char**)realloc(res, (i + 1) * sizeof(char*));
        *(res + i) = strdup(part);

        part = strtok(NULL, delim);
        i++;
    }

    res = (char **)realloc(res, i * sizeof(char *));
    *(res + i) = NULL;

    return res;
}
