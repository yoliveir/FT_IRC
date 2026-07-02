#pragma once

#include "ACommand.hpp"

class Kick : public ACommand
{
public:
	Kick();
	~Kick();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};