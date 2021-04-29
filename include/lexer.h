#ifndef LEXER_H
#define LEXER_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

typedef struct s_lexer
{
	char c;
	size_t i;
	size_t src_size;
	char* src;
}				t_lexer;

t_lexer*		init_lexer(char *src);

void			lexer_advance(t_lexer* lexer);
void			lexer_skip_whitspace(t_lexer* lexer);

t_token*		lexer_next_token(t_lexer* lexer);
t_token*		lexer_advance_current(t_lexer* lexer, int type);

t_token*		lexer_parser_id(t_lexer* lexer);

#endif
