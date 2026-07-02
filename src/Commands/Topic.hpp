#pragma once

#include "ACommand.hpp"

class Topic : public ACommand
{
public:
	Topic();
	~Topic();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};