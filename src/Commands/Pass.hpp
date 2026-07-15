#pragma once
#include "ACommand.hpp"

class Pass : public ACommand
{
public:
	Pass();
	~Pass();

	int execute(Server& server,
				User& user,
				const string_vector& args);
};


