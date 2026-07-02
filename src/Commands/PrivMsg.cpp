#include "PrivMsg.hpp"

PrivMsg::PrivMsg() {}

PrivMsg::~PrivMsg() {}

int PrivMsg::execute(Server& server,
							Client& client,
							const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}