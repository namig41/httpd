#include "http.h"

int main(int argc, char** argv) 
{
	t_http* http = http_init(argv[1], "127.0.0.1:8800");
	http_read_dir(http);
	/* http_print_dir(http); */	
	/* page_print(http->pages[0]); */
	http_server_run(http);
	http_free(http);
	return 0;
}
