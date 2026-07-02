#pragma once

#include "ACommand.hpp"

class Invite : public ACommand
{
public:
	Invite();
	~Invite();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};