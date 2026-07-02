#pragma once
#include "ACommand.hpp"

class Pass : public ACommand
{
public:
	Pass();
	~Pass();

	int execute(Server& server,
				Client& client,
				const std::vector<std::string>& args);
};


