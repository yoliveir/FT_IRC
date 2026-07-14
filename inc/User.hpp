 #pragma once

# include <poll.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string>
# include <map>

#define FD_SOCKET_SERVER 0
class User
{
private:
	const int						_fd_socket;
	static std::map<int, User *>	_map_fd_user; //esto es nuevo
	bool							_authenticated;
	bool							_registered;

	std::string						_nickname;
	std::string						_username;
	std::string						_realname;

public:

	User(int fd);
	User(User const &user);
	User	&operator=(User const &user);
	~User(void);

	int		get_fd_socket() const;
	static User	&getUser(int fd);

	bool isAuthenticated() const;
	void setAuthenticated(bool);

	bool isRegistered() const;
	void setRegistered(bool);

	const std::string& getNickname() const;
	void setNickname(const std::string&);

	const std::string& getUsername() const;
	void setUsername(const std::string&);

	// void sendMessage(const std::string&);
};