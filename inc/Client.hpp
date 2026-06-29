 #pragma once

# include <poll.h>
# include <sys/socket.h>
# include <arpa/inet.h>


#define FD_SOCKET_SERVER 0
class Client
{
private:
	const int	_fd_socket;
	bool		_authenticated;

public:
	Client(const int fd_socket);
	~Client(void);
	int get_fd_socket() const;
};