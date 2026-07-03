#include "User.hpp"

User::User(const int fd_socket) : _fd_socket(fd_socket), _authenticated(false)
{
}

// User::~User(void)
// {}

int User::get_fd_socket() const
{
	return (_fd_socket);
}