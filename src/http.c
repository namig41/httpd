#include "http.h"

t_http*	http_init(char* address)
{
	t_http* http = (t_http *)calloc(1, sizeof(t_http));
	http->len = 0;
	http->page = 0;
	http->host = strdup(address);
	return http;
}

void http_run(char *address)
{
	t_http* http = http_init(address);
	
	printf("Server is listening\n");
	http_listen(http);
}

void http_free(t_http* http)
{
	free(http->host);
	free(http);
}

/* void http_handle(t_http* http, char* path, void(*fun)(int, t_request*)) */
/* { */

/* } */

int8_t http_listen(t_http* http)
{
	int listener = net_listen(http->host);
	if (listener < 0) {
		return 1;
	}
	while (1) {
		int conn = net_accept(listener);
		if (conn < 0) {
			continue;
		}
		while (1) {
			char buf[BUF_SIZE] = {};
			int n = net_recv(conn, buf, BUF_SIZE);
			t_request* request = request_parse(buf);
			if (n != BUF_SIZE) {
				break;
			}
		}
	}
}

