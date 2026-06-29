#include "Server.hpp"
#include "Client.hpp"

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

	insert_into_socket_list(_server_fd_socket);
}

Server::~Server()
{
}

void	Server::insert_into_socket_list(const int fd_socket)
{
	_fd_list_sockets[_n_socket_used].fd = fd_socket;
	_fd_list_sockets[_n_socket_used].events = POLLIN;
	++_n_socket_used;
}


#include <sys/time.h>
// extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
void Server::welcome(int fd_client)
{
	send(fd_client, "BiEnVeNiD@", 10, 0);

}

void	Server::swich_server_on(void)
{
	while (true)
	{
		int read_pending_count = poll(_fd_list_sockets, _n_socket_used, POLL_TIMEOUT);
		
		if (_fd_list_sockets[FD_SOCKET_SERVER].revents == POLLIN)
		{
			Client	client(accept(_server_fd_socket, NULL, NULL));
			insert_into_socket_list(client.get_fd_socket());
			welcome(client.get_fd_socket());
		}
	}
}