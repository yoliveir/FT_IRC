 #pragma once

# include <poll.h>
# include <sys/socket.h>
# include <arpa/inet.h>


#define FD_SOCKET_SERVER 0
class User
{
private:
	const int	_fd_socket;
	bool		_authenticated;

public:
	User(const int fd_socket);
	~User(void);
	int get_fd_socket() const;
};