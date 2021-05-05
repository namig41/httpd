#include "message.h"

t_status*	status_init(char* method, char* path, char* protocol)
{
	t_status* status = (t_status *) calloc(1, sizeof(t_status));
	status->method = strdup(method);
	status->path = strdup(path);
	status->protocol = strdup(protocol);
	return status;
}

t_status*	status_parse(char* line)
{	
	char** s_line = strsplit(line, " ");
	t_status* status = status_init(s_line[0], s_line[1], s_line[2]);
	strsplit_free(s_line);
	return status;
}

void status_print(t_status* status)
{
	printf("%s %s %s\n", status->method,status->path, status->protocol);
}

void status_free(t_status* status)
{
	free(status->method);
	free(status->path);
	free(status->protocol);
	free(status);
}
