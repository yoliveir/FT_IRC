#pragma once

# include <poll.h>
# include <sys/socket.h>
# include <arpa/inet.h>


#define FD_SOCKET_SERVER 0
class Client
{
private:
	int					_fd_socket;
	bool				_authenticated;

public:
	Client(void);
};