#include "Server.hpp"
#include "User.hpp"
#include "./Parser/Parser.hpp"

bool	Server::_server_on = true;

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

	fcntl(_server_fd_socket, F_SETFL, O_NONBLOCK);
	listen(_server_fd_socket, USER_WAIT_LIST); //listen sirve a poner e fd en eeschucha
	std::memset(_msg_buffer, '\0', sizeof(_msg_buffer));
	
	//setPassword(password);
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
	fcntl(fd_socket, F_SETFL, O_NONBLOCK);
	++_n_socket_used;

}


#include <sys/time.h>
// extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
void Server::welcome(int fd_user)
{
	send(fd_user, "BiEnVeNiD@\n", 11, 0);

}

void	Server::disconect_user(int fd, int index)
{
	close(fd);
	if (index != _n_socket_used - 1)
		_fd_list_sockets[index] = _fd_list_sockets[_n_socket_used - 1];
	--_n_socket_used;
	std::cout << "user " << User::getUser(fd).getNickname() << "(" << fd<< ") desconectado\n";
	delete (&User::getUser(fd));
}

void	Server::check_if_user_ready()
{
	int			error_code;
	int			recv_result;
	socklen_t	error_code_size = sizeof(int);
	Parser		parser;

	for (int i = 1; i < _n_socket_used; i++)
	{
		if (_fd_list_sockets[i].revents == POLLIN)
		{
			recv_result = recv(_fd_list_sockets[i].fd, _msg_buffer, MSG_BUFFER, 0);
			if(recv_result == 0)
			{
				disconect_user(_fd_list_sockets[i].fd, i);
			}
			else if (recv_result > 0)
			{
				std::cout << "User (fd: " << _fd_list_sockets[i].fd << ") sent [" << _msg_buffer << "]\n";
				parser.parseMsg(std::string((char *)_msg_buffer), _fd_list_sockets[i].fd, *this);
				memset(_msg_buffer, '\0', MSG_BUFFER);
			}
		}
	}
}

void	Server::switchServerOff(void)
{
	std::cout << "Hasta luego maricarmen\n";
	const int	clients_connected = _n_socket_used;

	close(_server_fd_socket);
	for (int i = 1; i < clients_connected; ++i)
	{
		disconect_user(_fd_list_sockets[i].fd, i);
		send(_fd_list_sockets[i].fd, "Server close conection.\n", 24, 0);
	}
}

void	Server::signalHandler(int signal)
{
	(void) signal;
	_server_on = false;
}

void	Server::switchServerOn(void)
{
	signal(SIGINT, signalHandler);
	while (true)
	{
		if (_server_on == false)
		{
			switchServerOff();
			return ;
		}
		int read_pending_count = poll(_fd_list_sockets, _n_socket_used, POLL_TIMEOUT);
		
		if (_fd_list_sockets[FD_SOCKET_SERVER].revents == POLLIN)
		{
			User	*user = new User(accept(_server_fd_socket, NULL, NULL));
			insert_into_socket_list(user->get_fd_socket());
			welcome(user->get_fd_socket());
		}
		check_if_user_ready();
	}
}

Channel* Server::getChannel(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);
	if (it == _channels.end())
		return NULL;
	return it->second;
}

Channel* Server::createChannel(const std::string& name)
{
	Channel* channel = new Channel(name);
	_channels.insert(std::make_pair(name, channel));
	return channel;
}

const std::string	&Server::getPassword() const
{
	return (_password);
}
