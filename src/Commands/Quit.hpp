#pragma once
#include "ACommand.hpp"

class Quit : public ACommand
{
public:
	Quit();
	~Quit();

	int execute(Server& server,
				User& user,
				const string_vector& args);
};