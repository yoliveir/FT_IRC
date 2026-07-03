#include "User.hpp"

UserCommand::UserCommand() {}

UserCommand::~UserCommand() {}

int UserCommand::execute(Server& server,
						 User& user,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)user;
	(void)args;

	return (0);
}