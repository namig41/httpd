#include "http.h"

t_http*	http_init(char* root_dir, char* address)
{
	t_http* http = (t_http *)calloc(1, sizeof(t_http));
	http->pages = 0;
	http->page_size = 0;
	http->host = strdup(address);
	http->root_dir = strdup(root_dir);
	return http;
}

void http_server_run(t_http* http)
{
	http_listen(http);
}

void http_free(t_http* http)
{
	free(http->host);
	free(http->root_dir);
	page_free_all(http->pages, http->page_size);
	free(http);
}

static void signal_child(int sig)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) ;
	return;
}

_Noreturn void http_listen(t_http* http)
{
	int listener = net_listen(http->host);
	if (listener < 0) {
		perror("Listener error");
		exit(1);
	}
	while (1) {
		signal(SIGCHLD, signal_child);
		int conn = net_accept(listener);
		if (conn > 0) {
			pid_t pid = fork();
			if (pid == 0) {
				t_request* request;
				while (1) {
					char buf[BUF_SIZE] = {0};
					int n = net_recv(conn, buf, BUF_SIZE);
					request = request_parse(buf);
					if (n != BUF_SIZE) {
						break;
					}
				}
				t_page* page = http_search_page(http, request->status->path);
				t_response* response = response_init(page);
				char* s_response = response_to_string(response);
				net_send(conn, s_response, strlen(s_response));
				response_free(response);
				request_free(request);
				free(s_response);
				net_close(conn);
				exit(0);
			} else if (pid > 0) {
				net_close(conn);
			}
		} 
	}
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
			sprintf(newdir, "%s%s/", path, ep->d_name);
			http_read_dir_r(http, newdir);
		} else {
			sprintf(file_path, "%s%s", path, ep->d_name);
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
	char file_path[MAX_PATH] = {0};
	if (strcmp(path, "/") == 0) {
		sprintf(file_path, "%sindex", http->root_dir);
	} else {
		sprintf(file_path, "%s%s", http->root_dir, path + 1);
	}
	size_t len = strlen(file_path);
	for (size_t i = 0; i < http->page_size; i++) {
		if (strncmp(http->pages[i]->path, file_path, len) == 0) {
			return http->pages[i];
		}
	}
	return NULL;
}
