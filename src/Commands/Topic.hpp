#pragma once

#include "ACommand.hpp"

class Topic : public ACommand
{
public:
	Topic();
	~Topic();

	int execute(Server& server,
				User& User,
				const string_vector& args);
};