#include "message.h"

void response_set_content(t_response* response, char* content)
{
	response->content = content;
	char num[16];
	sprintf(num, "%d", strlen(content));
	t_header* header = header_init("Content-Length", num);
	response_add_header(response, header);
}

void response_init_status(t_response* response)
{
	switch (response->code) {
		case OK:
			response->status = strdup("HTTP/1.1 200 OK\n\r");
			break;
		case FOUND:
			break;
		case NOT_FOUND:
			response->status = strdup("HTTP/1.1 404 Not Found\n\r");
			break;
	}
}

t_response* response_init(t_page* page)
{
	t_response* response = (t_response *)calloc(1, sizeof(t_response));
	if (page) {
		char* content = page_read(page);
		response->code = OK;
		response_set_content(response, content);
	} else {
		response->code = NOT_FOUND;
	}
	response_init_status(response);
	return response;
}

char* response_to_string(t_response* response)
{
	char* s_response = (char *)calloc(1, sizeof(char));
	char* s_status = response->status;
	s_response = (char *)realloc(s_response,
			(strlen(s_response) + strlen(s_status)) * sizeof(char));
	char* s_headers = header_to_string_all(response->headers, response->header_size);
	s_response = (char *)realloc(s_response,
			(strlen(s_response) + strlen(s_headers)) * sizeof(char));
	char* s_content = response->content;
	s_response = (char *)realloc(s_response,
			(strlen(s_response) + strlen(s_content)) * sizeof(char));
	return s_response;
}

void response_add_header(t_response* response, t_header* header)
{
	response->header_size += 1;
	if (response->header_size == 1) {
		response->headers = (t_header **)calloc(response->header_size, 
				sizeof(t_header *));
	} else {
		response->headers = (t_header **)realloc(response->headers,
				response->header_size * sizeof(t_header *));
	}
	response->headers[response->header_size - 1] = header;
}
