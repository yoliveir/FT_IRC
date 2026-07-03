#pragma once

#include "ACommand.hpp"

class Mode : public ACommand
{
public:
	Mode();
	~Mode();

	int execute(Server& server,
				User& User,
				const std::vector<std::string>& args);
};