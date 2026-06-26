// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <iostream>

// #include <unistd.h>
// #include <poll.h>
// #include <stdlib.h>

// int	create_socket(void)
// {
// 	int					fd_socket;
// 	struct sockaddr_in	address; // direcion socket INternet

// 	fd_socket = socket(AF_INET, SOCK_STREAM, 0);
// 	address.sin_family = AF_INET; //familia de protocolo: ipv4 por ejemplo
// 	address.sin_addr.s_addr = INADDR_ANY;  // por qué interfaz nos podemos conectar

// 	srand(time(NULL));
// 	int port = rand() % 100;
// 	address.sin_port = htons(8000 + port); //METER UN PUERTO RANDOM PARAA QUE FALLE MENOS AL CERRAR CON CTRL+C SIN LIMPIAR LOS PUERTOS!!! ESTO ES UN APAÑO CUTRE NO HACER ASI EN EL PROYECTOOOOOO
// 	std::cerr << "PORT:" << (port + 8000) << "\n";
// 	if (bind(fd_socket, (const struct sockaddr *)&address, sizeof(sockaddr_in)) == -1)
// 	{
// 		std::cout << "COULD NOT BIND...\n";
// 		exit(-1);
// 	}
// 	listen(fd_socket, 10);
// 	return (fd_socket);
// }










// #include <cstring>
// #include <stdio.h>
// #define FD_SOCKET_SERVER 0

// int	main()
// {
// 	int fd_socket = create_socket();

	// struct sockaddr_in	client_address;
	// memset(&client_address, '\0', sizeof(client_address));
	// socklen_t			client_address_sizeof  = (socklen_t)sizeof(sockaddr_in); //es una variable de 32bit! (tipo int)
	
	// int fd_client = 0;

	// int total_sockets_fd = 1;

	// unsigned char data[10000];
	// std::memset(data, '\0', sizeof(data));
	// struct pollfd poll_candidate[10]; // {"FD de donde eschucha", EVENT info binaria del qeu tipo quere leer, REVENTS es }

	while (1)
	{
		poll_candidate[FD_SOCKET_SERVER].fd = fd_socket;
		poll_candidate[FD_SOCKET_SERVER].events = POLLIN;
		int read_pending_count = poll(poll_candidate, total_sockets_fd, 10);

		if (poll_candidate[FD_SOCKET_SERVER].revents ==  POLLIN)
		{
			fd_client = accept(fd_socket, (struct sockaddr *)&client_address, &client_address_sizeof);
			//!fcntl USAR AQUIIO¡
			poll_candidate[total_sockets_fd].fd = fd_client;
			poll_candidate[total_sockets_fd].events = POLLIN;
			if (fd_client == -1)
			{
				perror("aaaaaaaaaaaah: "); 
				return (-1);
			}
			std::cout << "fd_client::::  " << fd_client << "\n";
			std::cout << inet_ntoa(client_address.sin_addr) << " conection accepted\n";
			send(fd_client, "BIENVENIDO AL SERVIDOR\n", 23, 0);
			++total_sockets_fd;
		}

		for (int i = 1; i < total_sockets_fd; i++)
		{
			if (poll_candidate[i].revents > 0)
			{
				recv(poll_candidate[i].fd, data, 1000, 0);
				std::cout <<  data << "\n";
				std::memset(data, '\0', sizeof(data));
			}
		}
		usleep(100000);
	}
}