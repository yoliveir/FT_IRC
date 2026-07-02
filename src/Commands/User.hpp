#pragma once

#include "ACommand.hpp"

class User : public ACommand
{
public:
	User();
	~User();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};