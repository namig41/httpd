#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <string.h>

char** strsplit(char* str, const char* delim);
void   strsplit_free(char** str);

#endif
