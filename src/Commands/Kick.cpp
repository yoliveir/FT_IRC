#include "Kick.hpp"

Kick::Kick() {}

Kick::~Kick() {}

int Kick::execute(Server& server,
						 User& User,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)User;
	(void)args;

	return (0);
}