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
# include "../src/Channel.hpp"
# include <map>
# define FD_SOCKET_SERVER 0
# define User_WAIT_LIST 10
# define MSG_BUFFER 512
# define FD_LIST_NUMBER 10 //! Esto es una solución temporal creo
# define POLL_TIMEOUT 10

class Server
{
private:
//	CommandManager 		_commandManager; Lo he quitado de aquí y está dentro de Parser::parseMsg();
	std::map<std::string, Channel*> _channels;
	const std::string	_password;
	const int			_server_fd_socket;
	struct sockaddr_in	_address; // direcion socket INternet

	int					_n_socket_used;
	unsigned char		_msg_buffer[MSG_BUFFER];
	struct pollfd		_fd_list_sockets[FD_LIST_NUMBER];
	void				welcome(const int fd_user);
	void				check_if_user_ready();
	void				parser_msg();

public:
	Server(char *port, std::string password);
	void		insert_into_socket_list(const int fd);
	void		swich_server_on(void);
	~Server();
	Channel*	getChannel(const std::string& name);
	Channel*	createChannel(const std::string& name);
	const 		std::string& getPassword() const;
    void 		setPassword(const std::string&);
	const 		std::string extract_cmd() const; //el buffer puede que es algo del usere!
	void		disconect_user(int fd, int index);
};

/*
SUPOSTORIOS DE FASES:

	fase 1: montar el servidor;
	fase 2: emezar a parsear los mensajes del usuario;
	fase 3: mplementar comaandos;
	
*/