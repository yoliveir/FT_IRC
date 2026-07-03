 #pragma once

# include <poll.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string>


#define FD_SOCKET_SERVER 0
class User
{
private:
    const int   _fd_socket;

    bool        _authenticated;
    bool        _registered;

    std::string _nickname;
    std::string _username;
    std::string _realname;

public:

    User(int fd);

    int get_fd_socket() const;

    bool isAuthenticated() const;
    void setAuthenticated(bool);

    bool isRegistered() const;
    void setRegistered(bool);

    const std::string& getNickname() const;
    void setNickname(const std::string&);

    const std::string& getUsername() const;
    void setUsername(const std::string&);

    void sendMessage(const std::string&);
};