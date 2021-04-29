#ifndef NET_H
#define NET_H

#ifdef __linux__
	#include <unistd.h>
	#include <arpa/inet.h>
#elif __WIN32
	 #include <winsock2.h>
#else
	#warning "net.h platform not supported"
#endif

#include <stdint.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h>

typedef enum	e_error
{
	WINSOCK_ERR = -1,
	SOCKET_ERR  = -2,
	SETOPT_ERR	= -3,
	PARSE_ERR	= -4,
	BIND_ERR    = -5,
	LISTEN_ERR  = -6,
	CONNECT_ERR = -7
}				t_error;

int net_listen(char* addr);
int net_accept(int listener);
int net_connect(char* addr);
int net_close(int conn);
int net_send(int conn, char* buff, size_t size);
int net_recv(int conn, char* buff, size_t size);

#endif
