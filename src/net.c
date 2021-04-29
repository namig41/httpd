#if defined(__linux__) || defined(__WIN32)

#include "net.h"

static int isdigit(char c)
{
	return '0' <= c && c <= '9';
}

static int8_t net_parse_address(char* address, char* ipv4, char* port) 
{
	size_t i = 0;

	while (address[i] != ':') {
		if (address[i] == '\0') {
			return 1;
		}
		if (i >= 15) {
			return 2;
		}
		if (isdigit(address[i]) || address[i] == '.') {
			ipv4[i] = address[i];
		} else {
			return 3;
		}
		i++;
	}
	ipv4[i++] = '\0';
	size_t j = 0;
	while (address[i]) {
		if (j >= 5) {
			return 4;
		}	
		if (isdigit(address[i])) {
			port[j] = address[i];
		} else {
			return 3;
		}
		i++, j++;
	}
	port[j] = '\0';
	return 0;
}

int net_listen(char* addr)
{
#ifdef __WIN32
	WSDATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return WINSOCK_ERR;
	}
#endif
	int listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0) {
		return SOCKET_ERR;
	}
	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
		return SETOPT_ERR;
	}
	char ipv4[16];
	char port[6];

	if (net_parse_address(addr, ipv4, port) != 0) {
		return PARSE_ERR;
	}
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(port));
	address.sin_addr.s_addr = inet_addr(ipv4);
	if (bind(listener, (struct sockaddr *)&address, sizeof(address)) != 0) {
		return BIND_ERR;
	}
	if (listen(listener, SOMAXCONN) != 0) {
		return LISTEN_ERR;
	}
	return listener;
}

int net_accept(int listener)
{
	return accept(listener, NULL, NULL);
}

int net_connect(char* addr)
{
#ifdef __WIN32
	WSDATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return WINSOCK_ERR;
	}
#endif
	char ipv4[16];
	char port[6];
	int conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn < 0) {
		return SOCKET_ERR;
	}
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(port));
	address.sin_addr.s_addr = inet_addr(ipv4);
	if (bind(conn, (struct sockaddr *)&address, sizeof(addr)) != 0) {
		return CONNECT_ERR;
	}
}

int net_close(int conn)
{
#ifdef __linux__ 
	return close(conn);
#elif __WIN32 
	return closesocket(conn);
#endif
}

int net_send(int conn, char* buff, size_t size)
{
	return send(conn, buff, (int)size, 0);
}

int net_recv(int conn, char* buff, size_t size)
{
	return recv(conn, buff, (int)size, 0);
}

#endif /* defined(__linux__) || defined(__WIN32) */

