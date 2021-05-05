#include "message.h"

t_header* header_init(char* key, char* value)
{
	t_header* header = (t_header *) calloc(1, sizeof(t_header));
	header->key = strdup(key);
	header->value = strdup(value);
	return header;
}

t_header* header_parse(char* line)
{
	char** s_line = strsplit(line, ":");
	t_header* header = header_init(s_line[0], s_line[1] + 1);
	strsplit_free(s_line);
	return header;
}

void header_free(t_header* header)
{
	free(header->key);
	free(header->value);
	free(header);
}

void header_print(t_header* header)
{
	printf("%s: %s\n", header->key, header->value);
}

char* header_to_string(t_header* header) {
	char s_header[126];
	sprintf(s_header, "%s: %s\n\r", header->key, header->value);
	return strdup(s_header);
}

char* header_to_string_all(t_header** headers, size_t header_size)
{
	char* s_headers = (char *)calloc(1, sizeof(char));
	for (size_t i = 0; i < header_size; i++) {
		char* s_header = header_to_string(headers[i]);
		s_headers = (char *)realloc(s_headers,
				(strlen(s_headers) + strlen(s_header) + 1) * sizeof(char));
		strcat(s_headers, s_header);
	}
	s_headers = (char *)realloc(s_headers,
			(strlen(s_headers) + 3) * sizeof(char));
	strcat(s_headers, "\n\r");
	return s_headers;
}

void header_print_all(t_header** headers, size_t header_size)
{
	for (size_t i = 0; i < header_size; i++) {
		header_print(headers[i]);
	}
}

void  header_free_all(t_header** headers, size_t header_size)
{
	for (size_t i = 0; i < header_size; i++) {
		header_free(headers[i]);
	}
	free(headers);
}
