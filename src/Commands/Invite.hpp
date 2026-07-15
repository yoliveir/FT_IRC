#pragma once

#include "ACommand.hpp"

class Invite : public ACommand
{
public:
	Invite();
	~Invite();

	int execute(Server& server,
				User& User,
				const string_vector& args);
};