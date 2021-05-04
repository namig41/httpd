#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <dirent.h>
#include <errno.h>

typedef struct s_page
{
	char*		path;
}				t_page;

t_page*			page_init(char* path);
void			page_free(t_page* page);
void			page_free_all(t_page** pages, size_t page_size);
void			page_path_print(t_page* page);
void			page_print(t_page* page);
char*			page_read(t_page* page);


#endif
