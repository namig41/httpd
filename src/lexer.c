#include "lexer.h"

t_lexer* init_lexer(char* src)
{
	t_lexer* lexer = (t_lexer *)calloc(1, sizeof(t_lexer));
	lexer->i = 0;
	lexer->src = src;
	lexer->src_size = strlen(src);
	return lexer;
}

void lexer_advance(t_lexer* lexer)
{
	lexer->i += 1;
	lexer->c = lexer->src[lexer->i];
}

void lexer_skip_whitspace(t_lexer* lexer)
{
	while (isspace(lexer->c)) {
		lexer_advance(lexer);
	}
}

t_token* lexer_parser_id(t_lexer* lexer)
{
	char* value = (char *)calloc(1, sizeof(char));

	while (isalpha(lexer->c)) {
		value = (char *)realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char []){lexer->c, '\0'});
		lexer_advance(lexer);
	}
	return init_token(value, TOKEN_ID);
}

t_token* lexer_advance_current(t_lexer* lexer, int type)
{
	char* value = (char *)calloc(2, sizeof(char));
	value[0] = lexer->c;
	value[1] = '\0';

	t_token* token = init_token(value, type);
	lexer_advance(lexer);
	return token;
}

t_token* lexer_next_token(t_lexer* lexer)
{
	while (lexer->c) {
		lexer_skip_whitspace(lexer);

		if (isalpha(lexer->c)) {
			return lexer_parser_id(lexer);
		}

		switch (lexer->c) {
			case ':': return lexer_advance_current(lexer, TOKEN_COLON);
			case '\0': break;
		}
	}
	return init_token(0, TOKEN_EOF);
}
