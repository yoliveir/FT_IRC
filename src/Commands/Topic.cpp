#include "Topic.hpp"

Topic::Topic() {}

Topic::~Topic() {}

int Topic::execute(Server& server,
						  Client& client,
						  const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}