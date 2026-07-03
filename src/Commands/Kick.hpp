#pragma once

#include "ACommand.hpp"

class Kick : public ACommand
{
public:
	Kick();
	~Kick();

	int execute(Server& server,
				User& User,
				const std::vector<std::string>& args);
};