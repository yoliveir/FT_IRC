#include "Server.hpp"
#include "User.hpp"

Server::Server(char *port, std::string password) :
													_password(password),
													_server_fd_socket(socket(AF_INET, SOCK_STREAM, 0)),
													_n_socket_used(0)
{
	_address.sin_family = AF_INET; //familia de protocolo: ipv4 por ejemplo
	_address.sin_addr.s_addr = INADDR_ANY;  // por cual interfaz nos podemos conectar
	_address.sin_port = htons(std::atoi(port));

	//bind es unir: el socket con adress ip
	if (bind(_server_fd_socket, (const struct sockaddr *)&_address, sizeof(sockaddr_in)) == -1)
	{
		std::cout << "COULD NOT BIND...\n";
		exit(-1);
	}

	//!fcntl USAR AQUI¡
	listen(_server_fd_socket, CLIENT_WAIT_LIST); //listen sirve a poner e fd en eeschucha
	std::memset(_msg_buffer, '\0', sizeof(_msg_buffer));
	
	setPassword(password);
	insert_into_socket_list(_server_fd_socket);
}

Server::~Server()
{
}

void	Server::insert_into_socket_list(const int fd_socket)
{
	if (fd_socket == -1)
	{
		perror("aaaaaaaaaaaah: "); 
		exit(1);
	}
	_fd_list_sockets[_n_socket_used].fd = fd_socket;
	_fd_list_sockets[_n_socket_used].events = POLLIN;
	++_n_socket_used;

}


#include <sys/time.h>
// extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
void Server::welcome(int fd_user)
{
	send(fd_user, "BiEnVeNiD@\n", 11, 0);

}
// esto es de  comunicador
const std::string Server::extract_cmd() const
{
	std::string msg_buffer((char *)_msg_buffer);
	std::string command;
	int len_command = msg_buffer.find(" ", 0);
	command = msg_buffer.substr(0, len_command);
	return (command);
 }

#define CMDS_QUANTITY 9

void	Server::parser_msg()
{
	std::string command = extract_cmd();
	const std::string string_array[CMDS_QUANTITY] = 
	{
		"PASS",
		"NICK",
		"USER",
		"JOIN",
		"PRIVMSG",
		"KICK",
		"INVITE",
		"TOPIC",
		"MODE"
	};

	int cases = 0;
	while (cases < CMDS_QUANTITY)
	{
		if (string_array[cases] == command)
		{
			break ;
		}
		cases++;
	}
	std::string command = extract_cmd();
	// Necesito el FD de cliente
	_commandManager.execute(*this, _fd_list_sockets[i].fd, command);

}


/* void	Server::disconect_user(int fd, int index)
{
	close(fd);
	this->_n_socket_used;
	_fd_list_sockets;
}
 */
void	Server::check_if_user_ready()
{
	int			error_code;
	socklen_t	error_code_size = sizeof(int);

	for (int i = 1; i < _n_socket_used; i++)
	{
		if (_fd_list_sockets[i].revents == POLLIN)
		{
			if(recv(_fd_list_sockets[i].fd, _msg_buffer, MSG_BUFFER, 0) == 0)
				// disconect_user(_fd_list_sockets[i].fd, i);
				std::cout << "user desconectado\n";
			else
			{
				std::cout << "User (fd: " << _fd_list_sockets[i].fd << ") sent: " << _msg_buffer << "\n";
				parser_msg();
				memset(_msg_buffer, '\0', MSG_BUFFER);
			}
		}
	}
}

void	Server::swich_server_on(void)
{
	while (true)
	{
		int read_pending_count = poll(_fd_list_sockets, _n_socket_used, POLL_TIMEOUT);
		
		if (_fd_list_sockets[FD_SOCKET_SERVER].revents == POLLIN)
		{
			User	user(accept(_server_fd_socket, NULL, NULL));
			//!fcntl USAR AQUIIO¡

			insert_into_socket_list(user.get_fd_socket());
			welcome(user.get_fd_socket());
		}
		check_if_user_ready();
	}
}