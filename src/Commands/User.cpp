#include "User.hpp"

User::User() {}

User::~User() {}

int User::execute(Server& server,
						 Client& client,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}