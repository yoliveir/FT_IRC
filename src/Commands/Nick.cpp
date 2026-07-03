#include "Nick.hpp"

Nick::Nick() {}

Nick::~Nick() {}

int Nick::execute(Server& server,
						 User& User,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)User;
	(void)args;

	return (0);
}