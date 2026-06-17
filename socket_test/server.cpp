#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include <unistd.h>
#include <poll.h>
//la funcion socket: 
int	main()
{
	int fd_socket = socket(AF_INET, SOCK_STREAM, 0);
//	struct sockaddr addr;
	struct sockaddr_in	address;
	address.sin_family = AF_INET;
//	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_addr.s_addr = INADDR_ANY;
//	std::cout << inet_ntoa(address.sin_addr) << "\n";
	address.sin_port = htons(8080);
	int r = bind(fd_socket, (const struct sockaddr *)&address, sizeof(sockaddr_in));
	if (r == -1)
		std::cout << "COULD NOT BIND\n";
	listen(fd_socket, 1);

	struct sockaddr_in	peer_address;
	socklen_t			peer_address_sizeof;
	int fd_client = 0;
	while (1)
	{
		unsigned char data[1000];
		struct pollfd poll_candidate;


		poll_candidate.fd = fd_socket;
		poll_candidate.events = POLLIN;
		int read_pending_count = poll(&poll_candidate, 1, 10);
		//std::cout << poll_candidate.revents << "\n";
		if (poll_candidate.revents ==  POLLIN) {
			fd_client = accept(fd_socket, (struct sockaddr *)&peer_address, &peer_address_sizeof);
			send(fd_client, "BIENVENIDO AL SERVIDOR\n", 23, 0);
		}
		
		if (fd_client != 0) {
			send(fd_client, "ESTAS EN EL SERVIDOR\n", 22, 0);
		}
		usleep(100000);
		//		std::cout << inet_ntoa(peer_address.sin_addr) << " conection accepted\n";
//		recv(fd_client, data, 1000, 0);
//		std::cout << data << "\n";
//		read(0, data, 1000);
//		send(fd_client, data, 22, 0);
	}
}