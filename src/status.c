#include "message.h"

t_status*	status_init(char* method, char* path, char* protocol)
{
	t_status* status = (t_status *) calloc(1, sizeof(t_status));
	status->method = method;
	status->path = path;
	status->protocol = protocol;
	return status;
}

t_status*	status_parse(char* line)
{	
	char** s_line = strsplit(line, " ");
	t_status* status = status_init(s_line[0], s_line[1], s_line[2]);
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
