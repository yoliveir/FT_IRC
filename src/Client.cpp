#include "Client.hpp"

Client::Client(const int fd_socket) : _fd_socket(fd_socket), _authenticated(false)
{
}

Client::~Client(void)
{}

int Client::get_fd_socket() const
{
	return (_fd_socket);
}