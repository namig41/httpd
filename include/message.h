#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

#include "utilities.h"
#include "page.h"

#define MAX_PATH 518

typedef enum	e_http_code {
	OK		  = 200,
	FOUND	  = 302,
	NOT_FOUND = 404
}				t_http_code;

typedef struct s_header
{
	char*		key;
	char*		value;
}				t_header;

typedef struct  s_status
{
	char*		method;
	char*		path;
	char*		protocol;
}               t_status;

typedef struct s_request
{
	t_status*   status;
	t_header**	headers;
	size_t		header_size;
}				t_request;

typedef struct	s_response
{
	char*		status;
	t_http_code code;
	t_header**	headers;
	size_t		header_size;
	char*		content;
}				t_response;


t_request*		request_parse(char* src);
void			request_print(t_request* request);
void			request_free(t_request* request);
void			request_add_header(t_request* request, t_header* header);

t_header*		header_init(char* key, char* value);
t_header*		header_parse(char* line);
void			header_free(t_header* header);
void			header_free_all(t_header** headers, size_t header_size);
void			header_print(t_header* header);
void			header_print_all(t_header** headers, size_t header_size);
char*			header_to_string(t_header* header);
char*			header_to_string_all(t_header** headers, size_t header_size);

t_status*		status_init(char* method, char* protocol, char* path);
t_status*		status_parse(char* line);
void			status_free(t_status* status);
void			status_print(t_status* status);

t_response*		response_init(t_page* page);
void			response_add_header(t_response* response, t_header* header);
void			response_set_content(t_response* response, char* src);
void			response_init_status(t_response* response);
char*			response_to_string(t_response* response);
void            response_free(t_response* response);

#endif

