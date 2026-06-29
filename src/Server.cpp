#include "Server.hpp"
#include "Client.hpp"

Server::Server(char *port, std::string password) :
													_password(password),
													_fd_socket(socket(AF_INET, SOCK_STREAM, 0)),
													_sockets_in_list(0)
{
	_address.sin_family = AF_INET; //familia de protocolo: ipv4 por ejemplo
	_address.sin_addr.s_addr = INADDR_ANY;  // por qué interfaz nos podemos conectar
	_address.sin_port = htons(std::atoi(port));

	if (bind(_fd_socket, (const struct sockaddr *)&_address, sizeof(sockaddr_in)) == -1)
	{
		std::cout << "COULD NOT BIND...\n";
		exit(-1);
	}

	//!fcntl USAR AQUI¡
	listen(_fd_socket, CLIENT_WAIT_LIST);
	std::memset(_msg_buffer, '\0', sizeof(_msg_buffer));

	insert_into_socket_list(_fd_socket);
}

Server::~Server()
{
}

void	Server::insert_into_socket_list(const int fd)
{
	_fd_list_sockets[_sockets_in_list].fd = fd;
	_fd_list_sockets[_sockets_in_list].events = POLLIN;
	++_sockets_in_list;
}

void	Server::swich_server_on(void)
{
	Client	client();
	socklen_t			client_address_sizeof  = (socklen_t)sizeof(sockaddr_in); //es una variable de 32bit! (tipo int)

	while (true)
	{
		int read_pending_count = poll(_fd_list_sockets, _sockets_in_list, POLL_TIMEOUT);

		if (_fd_list_sockets[FD_SOCKET_SERVER].revents == POLLIN)
		{
			Client	client(accept(_fd_socket, NULL, NULL));
		}

	}

}