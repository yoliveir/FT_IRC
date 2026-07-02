#include "Invite.hpp"

Invite::Invite() {}

Invite::~Invite() {}

int Invite::execute(Server& server,
						   Client& client,
						   const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}