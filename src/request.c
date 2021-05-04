#include "message.h"

void request_print(t_request* request)
{
	status_print(request->status);
	header_print_all(request->headers, request->header_size);
}

t_request* request_parse(char* src)
{
	char** s_src = strsplit(src, "\n\r");
	
	t_request* request = (t_request *)calloc(1, sizeof(t_request));

	request->status = status_parse(s_src[0]);

	for (int i = 1; s_src[i]; i++)
	{
		t_header* header = header_parse(s_src[i]);
		request_add_header(request, header);
	}
	return request;
}

void request_free(t_request* request)
{
	header_free_all(request->headers, request->header_size);
	status_free(request->status);
	free(request);
}

void request_add_header(t_request* request, t_header* header)
{
	request->header_size += 1;
	if (request->header_size == 0) {
		request->headers = (t_header **)calloc(request->header_size, 
				sizeof(t_header *));
	} else {
		request->headers = (t_header **)realloc(request->headers,
				request->header_size * sizeof(t_header *));
	}
	request->headers[request->header_size - 1] = header;
}
