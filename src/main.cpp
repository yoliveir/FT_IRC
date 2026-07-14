#include "Server.hpp"
#include "User.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Must be: " << argv[0] << " <port> <password>\n";
		return (1);
	}

	Server server(argv[1], argv[2]);

	server.switchServerOn();

	return (0);
}
