#include "http.h"

t_page* page_init(char* path)
{
	t_page* page = (t_page *) calloc(1, sizeof(t_page));
	page->path = strdup(path);
	return page;
}

void page_free(t_page* page)
{
	free(page->path);
	free(page);
}

void page_free_all(t_page** pages, size_t page_size)
{
	for (size_t i = 0; i < page_size; i++) {
		page_free(pages[i]);
	}
	free(pages);
}

void page_path_print(t_page* page)
{
	printf("%s\n", page->path);
}

void page_print(t_page* page)
{
	char* src = page_read(page);
	printf("%s", src);
}

char* page_read(t_page* page)
{
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	size_t read;

	fp = fopen(page->path, "r");
	if (fp == NULL) {
		printf("Could not read file %s\n", page->path);
		exit(1);
	}

	char* buffer = (char *)calloc(1, sizeof(char));
	buffer[0] = '\0';

	while ((read = getline(&line, &len, fp)) != -1) {
		buffer = (char *)realloc(buffer,
				(strlen(buffer) + strlen(line) + 1) * sizeof(char));
		strcat(buffer, line);
	}

	fclose(fp);
	if (line) {
		free(line);
	}
	return buffer;
}
