#include "Quit.hpp"

Quit::Quit() {}

Quit::~Quit() {}

int Quit::execute(Server& server,
						 User& user,
						 const string_vector& args)
{
	(void)server;
	(void)user;
	(void)args;

	return (0);
}