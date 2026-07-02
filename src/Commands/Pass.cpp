#include "Pass.hpp"

Pass::Pass() {}

Pass::~Pass() {}

int Pass::execute(Server& server,
						 Client& client,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}