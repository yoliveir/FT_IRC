#include "Client.hpp"

Client::Client(void) : _authenticated(false)
{
	struct pollfd poll_candidate[10];	// 
										// {"FD de donde eschucha",
										// EVENT info binaria del qeu tipo quere leer,
										// REVENTS es }

	int total_sockets_fd = 1;
	int fd_client = 0;

}