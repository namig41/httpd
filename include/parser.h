#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"

typedef struct	s_parser 
{
	t_lexer*	lexer;
	t_token*	cur_token;
}				t_parser;

t_parser*		init_parser(t_lexer* lexer);
t_token*		parser_advance(t_parser* parser, int type);
#endif
