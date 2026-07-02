#include "Kick.hpp"

Kick::Kick() {}

Kick::~Kick() {}

int Kick::execute(Server& server,
						 Client& client,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}