#pragma once

#include "ACommand.hpp"

class UserCommand : public ACommand
{
public:
	UserCommand();
	~UserCommand();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};