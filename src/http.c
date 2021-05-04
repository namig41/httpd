#include "http.h"

t_http*	http_init(char* root_dir, char* address)
{
	t_http* http = (t_http *)calloc(1, sizeof(t_http));
	http->pages = 0;
	http->host = strdup(address);
	http->root_dir = strdup(root_dir);
	return http;
}

void http_server_run(t_http* http)
{
	printf("Server is listening\n");
	http_listen(http);
}

void http_free(t_http* http)
{
	free(http->host);
	free(http);
}

int8_t http_listen(t_http* http)
{
	int listener = net_listen(http->host);
	if (listener < 0) {
		return listener;
	}
	while (1) {
		int conn = net_accept(listener);
		if (conn < 0) {
			continue;
		}
		t_request* request = 0;
		while (1) {
			char buf[BUF_SIZE] = {};
			int n = net_recv(conn, buf, BUF_SIZE);
			request = request_parse(buf);
			if (n != BUF_SIZE) {
				break;
			}
		}
		/* request_print(request); */
		t_page* page = http_search_page(http, request->status->path);
		t_response* response = response_init(page);
		char* s_response = response_to_string(response);
		net_send(conn, s_response, strlen(s_response));
		/* free(response); */
		/* request_free(request); */
	}
	net_close(listener);
}

void http_add_page(t_http* http, t_page* page)
{
	http->page_size += 1;
	if (http->page_size == 1) {
		http->pages = (t_page **)calloc(http->page_size, sizeof(t_page *));
	} else {
		http->pages = (t_page **)realloc(http->pages,
				sizeof(t_page *) * http->page_size);
	}
	http->pages[http->page_size - 1] = page;
}

void  http_read_dir(t_http* http)
{
	http_read_dir_r(http, http->root_dir);
}

void  http_read_dir_r(t_http* http, char *path)
{
	DIR* dp = opendir(path);
    if(!dp) {
        perror(path);
        return;
    }
    struct dirent* ep;
    char newdir[MAX_PATH];
	char file_path[MAX_PATH];
    dp = opendir(path);
	while ((ep = readdir(dp))) {
		if (strncmp(ep->d_name, ".", 1) == 0) {
			continue;
		}
		else if (ep->d_type == DT_DIR) {
			sprintf(newdir, "%s/%s", path, ep->d_name);
			http_read_dir_r(http, newdir);
		} else {
			sprintf(file_path, "%s/%s", path, ep->d_name);
			t_page* page = page_init(file_path);
			http_add_page(http, page);
		}
    }
    closedir(dp);
}


void http_print_dir(t_http* http)
{
	for (size_t i = 0; i < http->page_size; i++) {
		page_path_print(http->pages[i]);
	}
}

t_page* http_search_page(t_http* http, char* path)
{
	char file_path[MAX_PATH];
	sprintf(file_path, "%s/%s", http->root_dir, path + 1);
	size_t len = strlen(file_path);
	for (size_t i = 0; i < http->page_size; i++) {
		/* printf("%s %s", http->pages[i]->path, file_path); */
		if (strncmp(http->pages[i]->path, file_path, len) == 0) {
			return http->pages[i];
		}
	}
	return NULL;
}
