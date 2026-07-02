#pragma once

#include "ACommand.hpp"

class PrivMsg : public ACommand
{
public:
	PrivMsg();
	~PrivMsg();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};