#ifndef HTTP_H
#define HTTP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "net.h"
#include "message.h"
#include "parser.h"

#define BUF_SIZE 1080

typedef struct s_page
{
	void		(*func)(int, t_request*);
	char*		filename;
}				t_page;

typedef struct	s_http 
{
	char*		host;
	int32_t		len;
	t_request	request;
	t_page**	page;
}				t_http;

t_http*			http_init(char* address);
void			http_free(t_http* http);
void			http_handle(t_http* http, char* path);
int8_t			http_listen(t_http* http);

#endif
