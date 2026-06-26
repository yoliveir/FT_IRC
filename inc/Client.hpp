#pragma once

# include <sys/socket.h>
# include <arpa/inet.h>

class Client
{
private:
	int					_fd_socket;
	bool				_authenticated;

public:
	Client(void);
};