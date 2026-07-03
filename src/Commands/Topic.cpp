#include "Topic.hpp"

Topic::Topic() {}

Topic::~Topic() {}

int Topic::execute(Server& server,
						  User& User,
						  const std::vector<std::string>& args)
{
	(void)server;
	(void)User;
	(void)args;

	return (0);
}