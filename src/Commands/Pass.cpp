#include "Pass.hpp"
#include "User.hpp"      // <- añadir
#include "Server.hpp" 

Pass::Pass() {}

Pass::~Pass() {}

int Pass::execute(Server& server,
						 User& user,
						 const std::vector<std::string>& args)
{
if (args.size() < 2)
    {
        send(user.get_fd_socket(), "461 PASS :Not enough parameters\r\n", 36, 0);
        return (1);
    }

    // if (args[1] != server.getPassword())
    // {
    //     send(user.get_fd_socket(), "464 Password incorrect\r\n", 24, 0);
    //     return (1);
    // }

    // user.setAuthenticated(true);

    return (0);
}