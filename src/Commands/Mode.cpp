#include "Mode.hpp"

Mode::Mode() {}

Mode::~Mode() {}

int Mode::execute(Server& server,
						 Client& client,
						 const std::vector<std::string>& args)
{
	(void)server;
	(void)client;
	(void)args;

	return (0);
}