#include "User.hpp"
	

std::map<int, User *> User::_map_fd_user;

// static std::map<int, User &> _map_fd_user; //esto es nuevo
User::User(const int fd_socket) : _fd_socket(fd_socket), _authenticated(false)
{
	_map_fd_user[fd_socket] = this;
}

// User::~User(void)
// {}

int User::get_fd_socket() const
{
	return (_fd_socket);
}

User	&User::getUser(int fd)
{
	return (*_map_fd_user[fd]); //de essta manera devolvemos value del mapa en el corespondete fd
}

const	std::string& User::getUsername() const
{
	return (_nickname);
}
