#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

typedef struct	s_token 
{
	enum {
		TOKEN_ID,
		TOKEN_INT,
		TOKEN_COLON,
		TOKEN_EOF	
	} type;
	
	char* value;
	
}		t_token;

t_token*	init_token(char* value, int type);

#endif
