#pragma once

#include "ACommand.hpp"

class UserCommand : public ACommand
{
public:
	UserCommand();
	~UserCommand();

	int execute(Server& server,
				User& User,
				const string_vector& args);
};