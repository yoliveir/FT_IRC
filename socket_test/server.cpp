#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include <unistd.h>
#include <poll.h>
#include <stdlib.h>

int	create_socket(void)
{
	int					fd_socket;
	struct sockaddr_in	address; // direcion socket INternet

	fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET; //familia de protocolo: ipv4 por ejemplo
	address.sin_addr.s_addr = INADDR_ANY;  // por qué interfaz nos podemos conectar

	srand(time(NULL));
	int port = rand() % 100;
	address.sin_port = htons(8000 + port); //METER UN PUERTO RANDOM PARAA QUE FALLE MENOS AL CERRAR CON CTRL+C SIN LIMPIAR LOS PUERTOS!!! ESTO ES UN APAÑO CUTRE NO HACER ASI EN EL PROYECTOOOOOO
	std::cout << "PORT:" << (port + 8000) << "\n";
	if (bind(fd_socket, (const struct sockaddr *)&address, sizeof(sockaddr_in)) == -1)
	{
		std::cout << "COULD NOT BIND...\n";
		exit(-1);
	}
	listen(fd_socket, 10);
	return (fd_socket);
}
#include <cstring>
#include <stdio.h>
int	main()
{
	int fd_socket = create_socket();

	struct sockaddr_in	peer_address;
	socklen_t			peer_address_sizeof;
	int fd_client = 0;

	while (1)
	{
		unsigned char data[1000];
		std::memset(data, '\0', sizeof(data));
		struct pollfd poll_candidate; // {"FD de donde eschucha", EVENT info binaria del qeu tipo quere leer, REVENTS es }

		poll_candidate.fd = fd_socket;
		poll_candidate.events = POLLIN;
		int read_pending_count = poll(&poll_candidate, 1, 10);
		//std::cout << poll_candidate.revents << "\n";
		if (poll_candidate.revents ==  POLLIN)
		{
			fd_client = accept(fd_socket, NULL, &peer_address_sizeof);
			if (fd_client == -1)
			{
				perror("aaaaaaaaaaaah: "); 
				return (-1);
			}
			std::cout << "fd_client::::  " << fd_client << "\n";
			std::cout << inet_ntoa(peer_address.sin_addr) << " conection accepted\n";
			send(fd_client, "BIENVENIDO AL SERVIDOR\n", 23, 0);
		}
		if (fd_client == -1)
		{
			std::cerr << "EL CLIENTE NO SE HA PODIDO CONECTAAAAR\n";
			fd_client = 0;
		}
		if (fd_client > 0) {
			send(fd_client, "ESTAS EN EL SERVIDOR\n", 22, 0);
			recv(fd_client, data, 1000, 0);
			std::cout <<  data << "\n";
			//read(0, data, 1000);
		}
		usleep(100000);
	}
}