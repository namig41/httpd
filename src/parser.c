#include "parser.h"

t_parser*	init_parser(t_lexer* lexer)
{
	t_parser* parser = (t_parser *)calloc(1, sizeof(t_parser));
	parser->lexer = lexer;
	parser->cur_token = lexer_next_token(lexer);
	return parser;
}


t_token* parser_advance(t_parser* parser, int type)
{
	parser->cur_token = lexer_next_token(parser->lexer);
	if (parser->cur_token->type != type) {
		printf("Unexpect token");
		exit(1);
	}
	return parser->cur_token;
}
