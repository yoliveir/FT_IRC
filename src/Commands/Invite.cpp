#include "Invite.hpp"

Invite::Invite() {}

Invite::~Invite() {}

int Invite::execute(Server& server,
							User& User,
							const std::vector<std::string>& args)
{
	(void)server;
	(void)User;
	(void)args;

	return (0);
}