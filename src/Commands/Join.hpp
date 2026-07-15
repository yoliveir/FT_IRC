#pragma once

#include "ACommand.hpp"

class Join : public ACommand
{
public:
	Join();
	~Join();

	int execute(Server& server,
				User& user,
				const string_vector& args);
};