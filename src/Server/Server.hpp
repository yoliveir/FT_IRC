#pragma once

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <unistd.h>
# include <poll.h>
# include <stdlib.h>
# include "../src/Commands/CommandManager.hpp"
# include <cstring>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include "Channel.hpp"

# define FD_SOCKET_SERVER 0
# define USER_WAIT_LIST 10
# define MSG_BUFFER 512
# define FD_LIST_NUMBER 10 //! Esto es una solución temporal creo
# define POLL_TIMEOUT 10
#define CR_LF "\r\n"
#define CR_LF_NOT_FOUND -1

class Server
{
private:
	std::map<std::string, Channel*> _channels;
	const std::string	_password;
	const int			_server_fd_socket;
	struct sockaddr_in	_address; // direcion socket INternet

	int					_n_socket_used;
	unsigned char		_msg_buffer[MSG_BUFFER];
	struct pollfd		_fd_list_sockets[FD_LIST_NUMBER];
	void				welcome(const int fd_user);
	void				check_if_user_ready();
	void				switchServerOff(void);
	static void			signalHandler(int signal);
	void				handleMessage(int socket_index, User &user);
	static bool			_server_on;

public:
	Server(char *port, std::string password);
	void	insert_into_socket_list(const int fd);

	void	switchServerOn(void);
	~Server();
	Channel*	getChannel(const std::string& name);
	Channel*	createChannel(const std::string& name);
	const 		std::string& getPassword() const;
	void		disconect_user(User &user, int index);
};

/*
SUPOSTORIOS DE FASES:

	fase 1: montar el servidor;
	fase 2: emezar a parsear los mensajes del usuario;
	fase 3: mplementar comaandos;
	
*/