#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

int	main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
//	struct sockaddr addr;
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	std::cout << inet_ntoa(address.sin_addr) << "\n";
	
}
