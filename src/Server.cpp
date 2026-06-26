#include "Server.hpp"

Server::Server(char *port, std::string password) :
													_password(password),
													_fd_socket(socket(AF_INET, SOCK_STREAM, 0)),
													_total_sockets_fd(1)
{
	_address.sin_family = AF_INET; //familia de protocolo: ipv4 por ejemplo
	_address.sin_addr.s_addr = INADDR_ANY;  // por qué interfaz nos podemos conectar
	_address.sin_port = htons(std::atoi(port));
	if (bind(_fd_socket, (const struct sockaddr *)&_address, sizeof(sockaddr_in)) == -1)
	{
		std::cout << "COULD NOT BIND...\n";
		exit(-1);
	}
	//!fcntl USAR AQUIIO¡
	listen(_fd_socket, CLIENT_WAIT_LIST);
	std::memset(_data, '\0', sizeof(_data));
}

Server::~Server()
{
}
