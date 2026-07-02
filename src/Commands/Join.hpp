#pragma once

#include "ACommand.hpp"

class Join : public ACommand
{
public:
	Join();
	~Join();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};