#include "UserCommand.hpp"

UserCommand::UserCommand() {}

UserCommand::~UserCommand() {}

int UserCommand::execute(Server& server,
						 User& user,
						 const string_vector& args)
{
	(void)server;
	(void)user;
	(void)args;

	return (0);
}