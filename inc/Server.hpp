#pragma once

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <unistd.h>
# include <poll.h>
# include <stdlib.h>

# include <cstring>
# include <stdio.h>
# define FD_SOCKET_SERVER 0
# define CLIENT_WAIT_LIST 10

class Server
{
private:
	const std::string	_password;
	const int			_fd_socket;
	struct sockaddr_in	_address; // direcion socket INternet

	int					_fd_total_sockets;
	unsigned char		_msg_buffer[10000];
	struct pollfd		_fd_list_sockets[10]; //el 10 es temporal!
	
public:
	Server(char *port, std::string password);

	~Server();
};