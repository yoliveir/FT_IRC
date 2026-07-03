#pragma once

#include "ACommand.hpp"

class Nick : public ACommand
{
public:
	Nick();
	~Nick();

	int execute(Server &server, User &user, const std::vector<std::string> &args);
};