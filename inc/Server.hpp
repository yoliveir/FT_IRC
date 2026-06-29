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
# define MSG_BUFFER 1000
# define FD_LIST_NUMBER 10 //! Esto es una solución temporal creo
# define POLL_TIMEOUT 10

class Server
{
private:
	const std::string	_password;
	const int			_server_fd_socket;
	struct sockaddr_in	_address; // direcion socket INternet

	int					_sockets_in_list;
	unsigned char		_msg_buffer[MSG_BUFFER];
	struct pollfd		_fd_list_sockets[FD_LIST_NUMBER];

public:
	Server(char *port, std::string password);
	void	insert_into_socket_list(const int fd);
	void	swich_server_on(void);
	~Server();
};