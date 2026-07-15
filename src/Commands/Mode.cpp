#include "Mode.hpp"

typedef std::vector<std::string> string_vector;

Mode::Mode() {}

Mode::~Mode() {}

int Mode::execute(Server& server,
						 User& user,
						 const string_vector &args)
{
	(void)server;
	(void)user;
	(void)args;

	return (0);
}