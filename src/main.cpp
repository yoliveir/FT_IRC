#include "Server.hpp"


void	swich_server_on()
{
	struct sockaddr_in	client_address;
socklen_t			client_address_sizeof  = (socklen_t)sizeof(sockaddr_in); //es una variable de 32bit! (tipo int)
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "must be: " << argv[0] << " <port> <password>\n";
		return (1);
	}

	Server server(argv[1], argv[2]);

	swich_server_on();
	struct sockaddr_in	client_address;
	
	return (0);
}