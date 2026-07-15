#include "Kick.hpp"

Kick::Kick() {}

Kick::~Kick() {}

int Kick::execute(Server& server,
						 User& User,
						 const string_vector& args)
{
	(void)server;
	(void)User;
	(void)args;

	return (0);
}