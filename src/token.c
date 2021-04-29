#include "token.h"

t_token*	init_token(char* value, int type)
{
	t_token* token = (t_token *)calloc(1, sizeof(t_token));
	token->type = type;
	token->value = strdup(value);
	return token;
}
