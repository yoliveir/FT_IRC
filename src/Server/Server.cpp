#include "Server.hpp"
#include "User.hpp"
#include "Parser.hpp"

Server::Server(char *port, std::string password) :	_password(password),
													_server_fd_socket(socket(AF_INET, SOCK_STREAM, 0)),
													_n_socket_used(0)
{
	int	reuseaddr_value = true;

	if (setsockopt(_server_fd_socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_value, sizeof(int)))
	{
		std::cout << "SETSOCKOPT FAILED...\n";
		exit(-1);
	}

	_address.sin_family = AF_INET; //familia de protocolo: ipv4 por ejemplo
	_address.sin_addr.s_addr = INADDR_ANY;  // por cual interfaz nos podemos conectar
	_address.sin_port = htons(std::atoi(port));

	// bind significa unir: el socket con adress ip
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

void	Server::disconect_user(User &user, int index)
{
	close(user.get_fd_socket());
	if (index != _n_socket_used - 1)
		_fd_list_sockets[index] = _fd_list_sockets[_n_socket_used - 1];
	--_n_socket_used;
	std::cout << "user " << user.getNickname() << "[" << user.get_fd_socket() << "] desconectado\n";
	delete (&user);
}

void	Server::handleMessage(int socket_index, User &user)
{
	int			recv_result;
	Parser		parser;

	recv_result = recv(_fd_list_sockets[socket_index].fd, _msg_buffer, MSG_BUFFER, 0);
	user.addToBuffer((char *)_msg_buffer);
	memset(_msg_buffer, '\0', MSG_BUFFER);

	if(recv_result == 0)
		disconect_user(user, socket_index);
	else if (user.getBuffer().find(CR_LF) == CR_LF_NOT_FOUND)
		return ;
	else
	{
		parser.parseMsg(user, *this);
		user.cleanBuffer();
	}
}

void	Server::check_if_user_ready()
{

	for (int i = 1; i < _n_socket_used; i++)
	{
		if (_fd_list_sockets[i].revents == POLLIN)
		{
			try
			{
				handleMessage(i, User::getUser(_fd_list_sockets[i].fd));
			}
			catch(const std::exception& e)
			{
				std::string msg = e.what();
				msg += "\n";
				std::cerr << msg;
				send(_fd_list_sockets[i].fd, msg.c_str(), msg.size(), 0);
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
		send(_fd_list_sockets[i].fd, "Server close connection.\n", 25, 0);
		User &user = User::getUser(_fd_list_sockets[i].fd);
		disconect_user(user, i);
	}
}

void	Server::switchServerOn(void)
{
	signal(SIGINT, signalHandler);

	while (true)
	{
		if (g_signal == SIGINT)
		{
			switchServerOff();
			return ;
		}
		poll(_fd_list_sockets, _n_socket_used, POLL_TIMEOUT);
		//int read_pending_count = poll(_fd_list_sockets, _n_socket_used, POLL_TIMEOUT); Es necesario ese read_pending_count???
		if (_fd_list_sockets[FD_SOCKET_SERVER].revents == POLLIN)
		{
			User	*user = new User(accept(_server_fd_socket, NULL, NULL));
			insert_into_socket_list(user->get_fd_socket());
			welcome(user->get_fd_socket());
		}
		check_if_user_ready(); //controla si el usario esta listo para escribir
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