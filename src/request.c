#include "message.h"

char** str_split(char* a_str, const char a_delim)
{
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}
	count += last_comma < (a_str + strlen(a_str) - 1);
	count++;
	result = malloc(sizeof(char*) * count);
	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		*(result + idx) = 0;
	}

	return result;
}

t_header* header_parse(char* line)
{
	t_header* header = (t_header *) calloc(1, sizeof(t_header));
	char** spl = str_split(line, ':');
	header->key = spl[0];
	header->value = spl[1];
	return header;
}

t_info* info_parse(char* line)
{
	t_info* header = (t_info *) calloc(1, sizeof(t_info));
	char** spl = str_split(line, ':');
	header->key = spl[0];
	header->value = spl[1];
	return header;
}

t_request* request_parse(char* src)
{
	char** spl = str_split(src, '\n');
	int i = 0;

	t_request* request = (t_request *)calloc(1, sizeof(t_request));

	request->method =
	request->path =
	request->version =

	return request;
}

