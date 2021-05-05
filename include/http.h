#ifndef HTTP_H
#define HTTP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

#include "net.h"
#include "message.h"
#include "page.h"

#define BUF_SIZE 1028

typedef struct	s_http 
{
	char*		host;
	char*		root_dir;
	t_page**	pages;
	size_t		page_size;
}				t_http;

t_http*			http_init(char* root_dir, char* address);
void			http_free(t_http* http);
void			http_server_run(t_http* http);

_Noreturn void            http_listen(t_http* http);

t_page*			http_search_page(t_http* http, char* file_name);

char*			http_read_page(char* file_name);
void			http_add_page(t_http* http, t_page* page);
void			http_print_dir(t_http* http);
void   			http_read_dir(t_http* http);
void			http_read_dir_r(t_http* http, char *path);

#endif
