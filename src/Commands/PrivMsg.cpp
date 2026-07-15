#include "PrivMsg.hpp"

PrivMsg::PrivMsg() {}

PrivMsg::~PrivMsg() {}

int PrivMsg::execute(Server& server,
							User& User,
							const string_vector& args)
{
	(void)server;
	(void)User;
	(void)args;

	return (0);
}