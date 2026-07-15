#include "User.hpp"
#include <iostream>

std::map<int, User *> User::_map_fd_user;

User::User(const int fd_socket) : _fd_socket(fd_socket), _authenticated(false)
{
	_map_fd_user[fd_socket] = this;
}

User::User(User const &user): _fd_socket(user._fd_socket)
{
	*this = user;
}
User	&User::operator=(User const &user)
{
	_authenticated = user._authenticated;
	_registered = user._registered;
	_nickname = user._nickname;
	_username = user._username;
	_realname = user._realname;

	return (*this);
}

User::~User(void)
{
	_map_fd_user.erase(_map_fd_user.find(_fd_socket));
}

int User::get_fd_socket() const
{
	return (_fd_socket);
}

User	&User::getUser(int fd)
{
	std::map<int, User *>::iterator it = _map_fd_user.find(fd);
	if (it == _map_fd_user.end())
		throw std::exception();

	return (*it->second);
}

const std::string	&User::getNickname() const
{
	return (_nickname);
}

void	User::setNickname(const std::string &nickname)
{
	_nickname = nickname;
}

const std::string	&User::getUsername(void) const
{
	return (_username);
}

void	User::setUsername(const std::string &username)
{
	_username = username;
}

bool	User::isAuthenticated(void) const
{
	return (_authenticated);
}

void	User::setAuthenticated(bool authenticated)
{
	_authenticated = authenticated;
}

bool	User::isRegistered(void) const
{
	return (_registered);
}
void	User::setRegistered(bool registered)
{
	_registered = registered;
}