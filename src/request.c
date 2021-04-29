#include "message.h"

t_header* header_parse(t_parser* parser)
{
	t_header* header = (t_header *)calloc(1, sizeof(t_header));
	header->key = parser->cur_token->value;
	parser_advance(parser, TOKEN_COLON);
	parser_advance(parser, TOKEN_ID);
	header->value = parser->cur_token->value;
	return header;
}

t_request* request_parse(char* src)
{
	printf("%s\n", src);

	t_request* request = (t_request *)calloc(1, sizeof(t_request));

	t_lexer* lexer = init_lexer(src);
	t_parser* parser = init_parser(lexer);

	request->method = parser->cur_token->value;
	parser_advance(parser, TOKEN_ID);
	request->path = parser->cur_token->value;
	parser_advance(parser, TOKEN_ID);
	request->version = parser->cur_token->value;
	parser_advance(parser, TOKEN_ID);

	while (parser->cur_token->type != TOKEN_EOF) 
	{
		t_header* header = header_parse(parser);
		if (request->size_header == 0) {
			request->size_header += 1;
			request->headers = (t_header **)calloc(request->size_header, 
					sizeof(t_header *));
			request->headers[request->size_header - 1] = header;
		} else {
			request->size_header += 1;
			request->headers = (t_header **)realloc(request->headers,
					request->size_header * sizeof(t_header *));
			request->headers[request->size_header - 1] = header;
		}
		parser_advance(parser, TOKEN_ID);
	}

	return request;
}

