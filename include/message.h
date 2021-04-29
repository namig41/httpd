#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

typedef enum	e_http_code {
	OK		  = 200,
	FOUND	  = 303,
	NOT_FOUND = 404
}				t_http_code;

typedef struct s_header
{
	char*		key;
	char*		value;
}				t_header;

typedef struct s_request
{
	char*		method;
	char*		version;
	char*		path;
	t_header**	headers;
	size_t		size_header;
}				t_request;

typedef struct	s_response
{
	char*		method;
	char		path[2048];
	t_http_code code;
	t_header**	headers;
	size_t		size_header;
	char*		content;
}				t_response;

t_request*		request_parse(char* src);
t_header*		header_parse(t_parser* parser);


#endif

