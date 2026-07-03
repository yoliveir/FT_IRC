#include "Quit.hpp"

Quit::Quit() {}

Quit::~Quit() {}

int Quit::execute(Server& server,
						 User& user,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)user;
	(void)args;

	return (0);
}