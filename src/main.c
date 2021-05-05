#include "http.h"

int main(int argc, char** argv) 
{
	if (argc < 3) {
		printf("Usage: ./httpd  [resource path] [address:port]");
		return 1;
	}
	pid_t parpid;

	parpid = fork();
	if (parpid < 0) {
		printf("\ncan't fork");
		exit(1);
	}
	else if (parpid != 0) {
		exit(0);
	} else {
		setsid();
		t_http* http = http_init(argv[1], argv[2]);
		http_read_dir(http);
		http_server_run(http);
		http_free(http);
	}
//	t_http* http = http_init(argv[1], argv[2]);
//	http_read_dir(http);
//	http_server_run(http);
//	http_free(http);
	return 0;
}
