#include "Nick.hpp"

Nick::Nick() {}

Nick::~Nick() {}

int Nick::execute(Server& server,
						 Client& client,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}